#include "QuadRenderer.h"

#include "Shader.h"

#include "Scene/Scene.h"

using namespace ForestHunt;

static constexpr uint32_t QUAD_VERTEX_COUNT = 4;

static constexpr glm::vec3 QUAD_VERTEX_POSITIONS[QUAD_VERTEX_COUNT] = {
    { -0.5f, -0.5f, 0.0f },
    {  0.5f, -0.5f, 0.0f },
    {  0.5f,  0.5f, 0.0f },
    { -0.5f,  0.5f, 0.0f }
};

static constexpr size_t MAX_QUAD_COUNT = 20000;
static constexpr size_t MAX_VERTEX_COUNT = MAX_QUAD_COUNT * QUAD_VERTEX_COUNT;
static constexpr size_t MAX_INDEX_COUNT = MAX_QUAD_COUNT * 6;

static Shader s_Shader{"DefaultShader"};

static RenderBatch s_Batch;

QuadRenderer::~QuadRenderer() {
    if(m_IsCreated) {
        Dispose();
    }
}

void QuadRenderer::Initialize() {

    // Create the shader
    if(!s_Shader.IsCreated()) {
        s_Shader.Create();
    }

    // Create the vertices
    s_Batch.Vertices  = new Vertex[MAX_VERTEX_COUNT];
    s_Batch.VertexPtr = s_Batch.Vertices;

    // Create the VAO
    glGenVertexArrays(1, &s_Batch.VaoID);
    glBindVertexArray(s_Batch.VaoID);

    // Create the VBO
    glGenBuffers(1, &s_Batch.VboID);
    glBindBuffer(GL_ARRAY_BUFFER, s_Batch.VboID);

    // Allocate Space In GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_VERTEX_COUNT, nullptr, GL_DYNAMIC_DRAW);

    // Define the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, Position));
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, Tint));

    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Create the Indices Data
    uint32_t indices[MAX_INDEX_COUNT];
    uint32_t offset = 0;

    // Indice Order: 0, 1, 2, 2, 3, 0
    for(size_t i = 0; i < MAX_INDEX_COUNT; i += 6) {
        // First Triangle
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        // Second Triangle
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;

        offset += 4; // Four Vertices Per Quad
    }

    // Create the Indices Buffer
    glGenBuffers(1, &s_Batch.IboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Batch.IboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    // Unbind Indices Buffer and VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind indicies buffer
    glBindVertexArray(0); // Unbind VAO

    m_IsCreated = true;
}

void QuadRenderer::StartBatch() {
    s_Batch.IndexCount = 0; // Reset Indices

    s_Batch.VertexPtr = s_Batch.Vertices; // Reset VertexPtr
}

void QuadRenderer::UpdateBatchVertexData() {
    // Calculate how many vertices are needed
    GLsizeiptr size = (uint8_t*) s_Batch.VertexPtr - (uint8_t*) s_Batch.Vertices;

    glBindBuffer(GL_ARRAY_BUFFER, s_Batch.VaoID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Batch.Vertices);
}

void QuadRenderer::Render() {
    // Bind the Shader
    s_Shader.Bind();

    // Get Uniform Locations
    static const GLint projectionViewMatrixLocation = s_Shader.GetUniformLocation("uProjectionViewMatrix");

    // Add Uniforms To Shader
    s_Shader.AddUniformMat4(projectionViewMatrixLocation, SceneManager::GetActiveSceneCamera()->GetViewProjectionMatrix());

    // Bind the VAO
    glBindVertexArray(s_Batch.VaoID);

    // Bind the Vertex Attrib Arrays That Are Needed
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Bind the Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Batch.IboID);

    // Draw the Data
    glDrawElements(GL_TRIANGLES, s_Batch.IndexCount, GL_UNSIGNED_INT, 0);

    // TODO: Only do in Debug Mode
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the IBO

    // Disable all Vertex Attrib Pointers
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Unbind the VAO
    glBindVertexArray(0);

    // Unbind the Shader
    glUseProgram(0);
}

void QuadRenderer::EndBatch() {
    QuadRenderer::UpdateBatchVertexData();
    QuadRenderer::Render();
}

void QuadRenderer::Dispose() {
    // Delete the vertices array
    delete[] s_Batch.Vertices;
    s_Batch.Vertices  = nullptr;
    s_Batch.VertexPtr = nullptr;

    // Delete the OpenGL buffers
    glDeleteBuffers(1, &s_Batch.IboID);
    glDeleteBuffers(1, &s_Batch.VboID);
    glDeleteVertexArrays(1, &s_Batch.VaoID);
}

void QuadRenderer::AllocateVertices(uint32_t amount) {
    uint32_t vertexCount = s_Batch.VertexPtr - s_Batch.Vertices;

    if(vertexCount + amount >= MAX_VERTEX_COUNT) {
        QuadRenderer::EndBatch();
        QuadRenderer::StartBatch();
    }
}

void QuadRenderer::DrawQuad(const glm::vec3& position) {
    AllocateVertices(QUAD_VERTEX_COUNT);

    for(uint32_t i = 0; i < QUAD_VERTEX_COUNT; i++) {
        s_Batch.VertexPtr->Position = position + QUAD_VERTEX_POSITIONS[i];
        s_Batch.VertexPtr->Tint = { 1.0f, 1.0f, 1.0f, 1.0f };
        s_Batch.VertexPtr++;
    }

    s_Batch.IndexCount += 6; // 6 indices per quad
}