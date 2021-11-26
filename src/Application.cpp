#include <pch.h>

#include "Core/Display.h"

#include "Render/Shader.h"

using namespace ForestHunt;

static const GLfloat vertexData[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};

static Shader s_Shader{"DefaultShader"};

static GLuint s_VaoID;
static GLuint s_VboID;

static void Init() {

    s_Shader.Create();

    glGenVertexArrays(1, &s_VaoID);
    glBindVertexArray(s_VaoID);

    glGenBuffers(1, &s_VboID);
    glBindBuffer(GL_ARRAY_BUFFER, s_VboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
}

static void Update(float deltaTime) {

    s_Shader.Bind();

    glBindVertexArray(s_VaoID);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, s_VboID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    // std::cout << glGetError() << std::endl; 

    // std::cout << deltaTime << std::endl;

}

int main() {

    Display::CreateDisplay(Init, Update);    

}