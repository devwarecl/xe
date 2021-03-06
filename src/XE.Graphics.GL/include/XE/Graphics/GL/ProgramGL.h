
#ifndef __XE_GRAPHICS_GL_PROGRAMGL_HPP__
#define __XE_GRAPHICS_GL_PROGRAMGL_HPP__

#include <XE/Graphics/Program.h>
#include <vector>
#include <string>
#include <memory>
#include <tuple>
#include <glad/glad.h>

namespace XE {
    enum class ShaderType;
    struct ProgramDescriptor;
}

namespace XE {
    class ShaderGL;
    class ProgramGL : public Program {
    public:
        ProgramGL(const ProgramDescriptor &desc);

        virtual ~ProgramGL();

        virtual int getShaderCount() const override;

        virtual Shader* getShader(const int index) override;

        GLuint GetID() const {
            return m_id;
        }

    public:
        int getUniformLoction(const std::string &name) const;

        int getAttributeLocation(const std::string &name) const;

    private:
        GLuint m_id;
        std::vector<std::unique_ptr<ShaderGL>> m_shaders;
    };
}

#endif
