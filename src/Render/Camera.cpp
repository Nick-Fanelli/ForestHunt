#include "Camera.h"

using namespace ForestHunt;

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
    UpdateProjection();
}

void Camera::CalculateProjectionViewMatrix() {
    m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::UpdateProjection() {
    m_ProjectionMatrix = glm::ortho(-m_AspectRatio + m_Zoom, m_AspectRatio - m_Zoom, -1.0f + m_Zoom, 1.0f - m_Zoom, m_NearClip, m_FarClip);
    UpdateView();
}

void Camera::UpdateView() {
    m_ViewMatrix = glm::lookAt(m_Position, m_Position + glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
    CalculateProjectionViewMatrix();
}