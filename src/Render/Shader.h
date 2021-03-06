#pragma once

#include "pch.h"

namespace ForestHunt {

    class Shader {

    public:
        Shader() = default;
        Shader(const Shader&) = default;

        Shader(const std::string& shaderName);
        ~Shader();

        void Create();

        void Bind() const;

        bool IsCreated() const { return m_ProgramID != -1; }

        GLint GetUniformLocation(const char* varName) const;

        void AddUniformMat4(GLint location, const glm::mat4& mat4) const;

    private:
        void AttachVertexShader(const std::string& source);
        void AttachFragmentShader(const std::string& source);

        void Link();

    private:
        const std::string m_ShaderName;

        GLuint m_ProgramID = -1, m_VertexID, m_FragmentID;

    };

}