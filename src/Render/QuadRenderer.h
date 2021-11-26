#pragma once

#include "pch.h"

#include "Vertex.h"

namespace ForestHunt {

    struct RenderBatch {

        GLuint VaoID = 0;
        GLuint VboID = 0;
        GLuint IboID = 0;

        size_t IndexCount = 0;

        Vertex* Vertices = nullptr;
        Vertex* VertexPtr = nullptr;

    };

    class QuadRenderer {

    public:
        QuadRenderer() = default;
        ~QuadRenderer();
        
        void Initialize();

        void StartBatch();
        void EndBatch();

        void DrawQuad(const glm::vec3& position);

    private:
        void UpdateBatchVertexData();
        void Render();

        void AllocateVertices(uint32_t amount);

        void Dispose();

    private:
        bool m_IsCreated = false;
        
    };

}