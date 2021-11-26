#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

using namespace ForestHunt;

Shader::Shader(const std::string& shaderName) : m_ShaderName(shaderName) {

}

Shader::~Shader() {
    if(m_ProgramID == -1)
        return;

    glUseProgram(0);

    glDeleteProgram(m_ProgramID);
}

void Shader::Bind() const {
    glUseProgram(m_ProgramID);
}

static void ReadFile(const std::filesystem::path& filepath, std::string* result) {
    std::ifstream fileStream(filepath);
    std::string line;

    while(std::getline(fileStream, line)) {
        result->append(line).append("\n");
    }
}

void Shader::Create() {
    m_ProgramID = glCreateProgram();

    std::string vertexSource, fragmentSource;

    std::stringstream vertexFilepath;
    vertexFilepath << "res/shaders/" << m_ProgramID << ".vert.glsl";

    std::stringstream fragmentFilepath;
    vertexFilepath << "res/shaders/" << m_ProgramID << ".frag.glsl";

    ReadFile(std::filesystem::path(vertexFilepath.str()), &vertexSource);
    ReadFile(std::filesystem::path(fragmentFilepath.str()), &fragmentSource);

    AttachVertexShader(vertexSource);
    AttachVertexShader(fragmentSource);
    
    Link();
}

void Shader::AttachVertexShader(const std::string& source) {
    GLint result = GL_FALSE;
    int infoLogLength;

    m_VertexID = glCreateShader(GL_VERTEX_SHADER);
    const char* sourcePtr = source.c_str();

    glShaderSource(m_VertexID, 1, &sourcePtr, NULL);
    glCompileShader(m_VertexID);

    glGetShaderiv(m_VertexID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(m_VertexID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if(infoLogLength > 0) {
        std::vector<char> errorMessage(infoLogLength + 1);
        glGetShaderInfoLog(m_VertexID, infoLogLength, NULL, &errorMessage[0]);
        std::cout << "ERROR: " << &errorMessage[0] << std::endl;
        return;
    }

    glAttachShader(m_ProgramID, m_VertexID);
}

void Shader::AttachFragmentShader(const std::string& source) {
    GLint result = GL_FALSE;
    int infoLogLength;

    m_FragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* sourcePtr = source.c_str();

    glShaderSource(m_FragmentID, 1, &sourcePtr, NULL);
    glCompileShader(m_FragmentID);

    glGetShaderiv(m_FragmentID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(m_FragmentID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if(infoLogLength > 0) {
        std::vector<char> errorMessage(infoLogLength + 1);
        glGetShaderInfoLog(m_FragmentID, infoLogLength, NULL, &errorMessage[0]);
        std::cout << "ERROR: " << &errorMessage[0] << std::endl;
        return;
    }

    glAttachShader(m_ProgramID, m_FragmentID);
}

void Shader::Link() {
    glLinkProgram(m_ProgramID);

    GLint result = GL_FALSE;
    int infoLogLength;
    
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &result);
    glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if(infoLogLength > 0) {
        std::vector<char> errorMessage(infoLogLength + 1);
        glGetProgramInfoLog(m_ProgramID, infoLogLength, NULL, &errorMessage[0]);
        std::cout << "ERROR LINKING: " << &errorMessage[0] << std::endl;
    }

    glDetachShader(m_ProgramID, m_VertexID);
    glDetachShader(m_ProgramID, m_FragmentID);

    glDeleteShader(m_VertexID);
    glDeleteShader(m_FragmentID);
}