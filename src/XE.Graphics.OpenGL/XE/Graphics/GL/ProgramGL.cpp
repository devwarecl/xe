
#include "ProgramGL.hpp"
#include "ShaderGL.hpp"

namespace XE {
    ProgramGL::ProgramGL(const ProgramDescriptor &desc) {
        for (const auto &source: desc.sources) {
            m_shaders.emplace_back(new ShaderGL(source.type, source.text));
        }

        m_id = ::glCreateProgram();

        for (auto &shader : m_shaders) {
            ::glAttachShader(m_id, shader->GetID());
        }

        ::glLinkProgram(m_id);

        GLint status;
        ::glGetProgramiv(m_id, GL_LINK_STATUS, &status);

        if (status == GL_FALSE) {
            const GLint logsize = 4096;
            char buffer[logsize] = {};
                
            ::glGetProgramInfoLog(m_id, logsize, nullptr, buffer);

            throw std::runtime_error(buffer);
        }
    }

    ProgramGL::~ProgramGL() {
        m_shaders.clear();

        if (m_id) {
            ::glDeleteProgram(m_id);
        }
    }

    int ProgramGL::GetShaderCount() const {
        return int(m_shaders.size());
    }

    Shader* ProgramGL::GetShader(const int index) {
        return m_shaders[index].get();
    }

    int ProgramGL::GetUniformLoction(const std::string &name) const {
        return ::glGetUniformLocation(m_id, name.c_str());
    }

    int ProgramGL::GetAttributeLocation(const std::string &name) const {
        return ::glGetAttribLocation(m_id, name.c_str());
    }
}
