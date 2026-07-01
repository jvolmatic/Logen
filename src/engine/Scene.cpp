#include "Scene.h"

#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <cctype>
#include <unordered_set>

#include "Light.h"
#include "MeshResource.h"

namespace {
    std::string StripUtf8Bom(const std::string &value) {
        if (value.size() >= 3 &&
            static_cast<unsigned char>(value[0]) == 0xEF &&
            static_cast<unsigned char>(value[1]) == 0xBB &&
            static_cast<unsigned char>(value[2]) == 0xBF) {
            return value.substr(3);
        }
        return value;
    }

    std::string LTrim(const std::string &value) {
        std::size_t index = 0;
        while (index < value.size() && std::isspace(static_cast<unsigned char>(value[index])) != 0) {
            ++index;
        }
        return value.substr(index);
    }

    std::string RTrim(const std::string &value) {
        if (value.empty()) {
            return value;
        }

        std::size_t end = value.size();
        while (end > 0 && std::isspace(static_cast<unsigned char>(value[end - 1])) != 0) {
            --end;
        }
        return value.substr(0, end);
    }

    std::filesystem::path ResolveResourcePath(const std::string &path) {
        namespace fs = std::filesystem;

        const fs::path directPath(path);
        if (fs::exists(directPath)) {
            return directPath;
        }

        const fs::path resourcePath = fs::path("resources") / directPath;
        if (fs::exists(resourcePath)) {
            return resourcePath;
        }

        return {};
    }

    bool ParseTransform(std::istringstream &stream, LogenCore::Vector3 &position, LogenCore::Vector3 &rotation) {
        return static_cast<bool>(
            stream >> position.x >> position.y >> position.z >> rotation.x >> rotation.y >> rotation.z
        );
    }

}

bool LogenCore::Scene::Instantiate() {
    objects.clear();
    shaders.clear();

    const std::filesystem::path resolvedScenePath = ResolveResourcePath(fsPath);
    if (resolvedScenePath.empty()) {
        return false;
    }

    std::ifstream sceneFile(resolvedScenePath);

    if (!sceneFile.is_open()) {
        return false;
    }

    std::string line;
    std::unordered_set<std::string> requiredShaderPaths;
    while (std::getline(sceneFile, line)) {
        std::string normalizedLine = LTrim(StripUtf8Bom(line));

        const std::size_t commentStart = normalizedLine.find("//");
        if (commentStart == 0) {
            continue;
        }
        if (commentStart != std::string::npos) {
            normalizedLine = RTrim(normalizedLine.substr(0, commentStart));
        }

        // Ignore comments
        if (normalizedLine.empty())
            continue;

        // Ignore lines that don't start with '#'
        if (normalizedLine[0] != '#')
            continue;

        // Handle each case
        std::istringstream lineStream(normalizedLine);
        std::string directiveToken;
        lineStream >> directiveToken;

        if (directiveToken.empty())
            continue;

        const std::string directive = directiveToken.substr(1);

        if (directive == "SCENE") {
            std::string parsedSceneName;
            if (lineStream >> parsedSceneName) {
                name = parsedSceneName;
            }
            continue;
        }

        if (directive == "CAMERA") {
            Vector3 position;
            Vector3 rotation;
            if (!ParseTransform(lineStream, position, rotation))
                return false;

            objects.push_back(std::make_unique<SceneObject>(position, rotation, SceneObjectType::Camera));
            continue;
        }

        if (const auto lightType = Light::FromSceneDirective(directive); lightType.has_value()) {
            Vector3 position;
            Vector3 rotation;
            if (!ParseTransform(lineStream, position, rotation))
                return false;

            // Optional direction for directional/spot lights; point lights can omit it.
            Vector3 direction;
            lineStream >> direction.x >> direction.y >> direction.z;

            objects.push_back(std::make_unique<Light>(position, rotation, *lightType, direction));
            continue;
        }

        if (directive == "RESOURCE_MESH") {
            std::string modelPath;
            std::string shaderPath;
            if (!(lineStream >> modelPath))
                return false;
            if (!(lineStream >> shaderPath))
                return false;

            Vector3 position;
            Vector3 rotation;
            if (!ParseTransform(lineStream, position, rotation))
                return false;

            objects.push_back(
                std::make_unique<MeshResource>(position, rotation, modelPath, shaderPath)
            );

            // if requiredShaders doesn't already contain shaderPath, add it
            const std::filesystem::path resolvedShaderPath = ResolveResourcePath(shaderPath);
            const std::string shaderLoadPath = resolvedShaderPath.empty()
                                                   ? shaderPath
                                                   : resolvedShaderPath.generic_string();
            if (requiredShaderPaths.insert(shaderLoadPath).second) {
                shaders.push_back(std::make_unique<Graphics::Shader>(shaderLoadPath.c_str()));
            }
            continue;
        }
    }

    // Compile required shaders for this scene
    if (!this->shaders.empty()) {
        for (const std::unique_ptr<Graphics::Shader> &shader: shaders) {
            shader->Compile();
        }
    }

    return true;
}
