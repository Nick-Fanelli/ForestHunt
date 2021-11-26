#pragma once

#include "pch.h"

namespace ForestHunt {

    class Camera {
        
    public:
        Camera();

        void UpdateProjection();
        void UpdateView();

        void SetAspectRatio(float width, float height) {
            m_AspectRatio = width / height;
            UpdateProjection();
        }

        void SetZoom(float zoom) { m_Zoom = zoom; }
        inline float GetZoom() const { return m_Zoom; }

        inline const glm::mat4& GetViewProjectionMatrix() const { return m_ProjectionViewMatrix; }

    private:
        void CalculateProjectionViewMatrix();

    private:
        glm::mat4 m_ProjectionViewMatrix;
        glm::mat4 m_ProjectionMatrix, m_ViewMatrix;
        glm::vec3 m_Position = { 0.0f, 0.0f, 1.0f };

        float m_Zoom = 0.0f;

        float m_AspectRatio = 1600.0f / 900.0f;
        float m_NearClip = 0.01f, m_FarClip = 100.0f;

    };

}