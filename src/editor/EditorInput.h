#ifndef LOGEN_EDITORCAMERA_H
#define LOGEN_EDITORCAMERA_H
#include <memory>


class EditorInput {
public:
    EditorInput();
    ~EditorInput() = default;
    void ProcessInput(float deltaTime);

private:
    bool isFirstMouseMovement = true;
    float movementSpeed = 2.5f;
};


#endif //LOGEN_EDITORCAMERA_H
