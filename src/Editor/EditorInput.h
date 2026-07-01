#ifndef LOGEN_EDITORCAMERA_H
#define LOGEN_EDITORCAMERA_H
#include <memory>


class EditorInput {
public:
    EditorInput()= default;
    ~EditorInput() = default;
    void ProcessInput(float deltaTime);

private:
    bool isFirstMouseMovement = true;
    bool bWasSprintKeyPressedLastFrame = false;
    float movementSpeed = 2.5f;
    float sprintSpeedMultiplier = 5.0f;
};


#endif //LOGEN_EDITORCAMERA_H
