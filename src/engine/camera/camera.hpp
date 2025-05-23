#pragma once

#include "core/gl_includes.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };
enum class Projection { Perspective, Orthographic };

class Camera {
public:
    static constexpr float defaultYaw = -90.0f;
    static constexpr float defaultPitch = 0.0f;
    static constexpr float defaultSpeed = 2.5f;
    static constexpr float defaultSensitivity = 0.1f;
    static constexpr float defaultFov = 45.0f;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = defaultYaw, float pitch = defaultPitch)
        : position_(position),
        front_(glm::vec3(0.0f, 0.0f, -1.0f)),
        worldUp_(up),
        yaw_(yaw),
        pitch_(pitch),
        movementSpeed_(defaultSpeed),
        mouseSensitivity_(defaultSensitivity),
        fov_(defaultFov) {
        updateCameraVectors();
    }

    ~Camera() = default;

    // No copying or moving
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
    Camera(Camera&&) = delete;
    Camera& operator=(Camera&&) = delete;

    // Camera matrices
    [[nodiscard]] glm::mat4 getViewMatrix() const {
        return glm::lookAt(position_, position_ + front_, up_);
    }

    [[nodiscard]] glm::mat4 getProjectionMatrix(float aspectRatio) const {
        if (projectionMode_ == Projection::Perspective) {
            return glm::perspective(glm::radians(fov_), aspectRatio, 0.1f, 100.0f);
        }
        else {
            float orthoSize = 3.0f;
            return glm::ortho(-orthoSize * aspectRatio, orthoSize * aspectRatio,
                -orthoSize, orthoSize, 0.1f, 100.f);
        }
    }

    [[nodiscard]] glm::mat4 getViewProjectionMatrix(float aspectRatio) const {
        return getProjectionMatrix(aspectRatio) * getViewMatrix();
    }

        // Camera movement and input handling
        void processKeyboard(CameraMovement direction, float deltaTime) {
            const float velocity = movementSpeed_ * deltaTime;
            if (direction == CameraMovement::FORWARD)
                position_ += front_ * velocity;
            if (direction == CameraMovement::BACKWARD)
                position_ -= front_ * velocity;
            if (direction == CameraMovement::LEFT)
                position_ -= right_ * velocity;
            if (direction == CameraMovement::RIGHT)
                position_ += right_ * velocity;
        }

        void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
            xoffset *= mouseSensitivity_;
            yoffset *= mouseSensitivity_;

            yaw_ += xoffset;
            pitch_ += yoffset;

            if (constrainPitch)
                pitch_ = glm::clamp(pitch_, -89.0f, 89.0f);

            updateCameraVectors();
        }

        void processMouseScroll(float yoffset) {
            fov_ = glm::clamp(fov_ - yoffset, 1.0f, 45.0f);
        }

        // Read-only accessors
        [[nodiscard]] glm::vec3  getPosition()       const { return position_; }
        [[nodiscard]] glm::vec3  getFront()          const { return front_; }
        [[nodiscard]] glm::vec3  getUp()             const { return up_; }
        [[nodiscard]] glm::vec3  getRight()          const { return right_; }
        [[nodiscard]] float      getYaw()            const { return yaw_; }
        [[nodiscard]] float      getPitch()          const { return pitch_; }
        [[nodiscard]] float      getFov()            const { return fov_; }
        [[nodiscard]] Projection getProjectionMode() const { return projectionMode_; }


        void setPosition(const glm::vec3 & position) {
            position_ = position;
        }


        void toggleProjectionMode() {
            projectionMode_ = (projectionMode_ == Projection::Perspective)
                ? Projection::Orthographic
                : Projection::Perspective;
        }

        void setProjectionMode(Projection mode) {
            projectionMode_ = mode;
        }


        void reset() {
            position_ = glm::vec3(0.0f, 0.0f, 3.0f);
            yaw_ = defaultYaw;
            pitch_ = defaultPitch;
            fov_ = defaultFov;
            updateCameraVectors();
        }

private:
    void updateCameraVectors() {
        glm::vec3 front{};
        front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
        front.y = sin(glm::radians(pitch_));
        front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
        front_ = glm::normalize(front);

        right_ = glm::normalize(glm::cross(front_, worldUp_));
        up_    = glm::normalize(glm::cross(right_, front_));
    }

    // Camera attributes
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 worldUp_;

    // Euler angles
    float yaw_;
    float pitch_;

    // Camera options
    float movementSpeed_;
    float mouseSensitivity_;
    float fov_;

    Projection projectionMode_ = Projection::Perspective;
};