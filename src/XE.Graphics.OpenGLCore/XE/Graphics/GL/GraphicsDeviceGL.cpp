
#include "GraphicsDeviceGL.hpp"

#include "Conversion.hpp"
#include "BufferGL.hpp"
#include "SubsetGL.hpp"
#include "Texture2DGL.hpp"
#include "Texture2DArrayGL.hpp"
#include "Texture3DGL.hpp"
#include "ProgramGL.hpp"
#include "InputManagerGLFW.hpp"
#include "WindowGLFW.hpp"
#include "Util.hpp"

#include <XE/Graphics/Material.hpp>
#include <XE/Graphics/Uniform.hpp>
#include <XE/Graphics/Subset.hpp>
#include <XE/Graphics/Texture3D.hpp>
#include <XE/Graphics/Texture2DArray.hpp>
#include <XE/Graphics/TextureCubeMap.hpp>
#include <iostream>

namespace XE::Graphics::GL {
/*#if defined(GLAD_DEBUG)
    void gladPostCallback(const char *name, void *funcptr, int len_args, ...) {
        if (std::string(name) != "glGetError") {
            GLenum error = glGetError();
            assert(error == GL_NO_ERROR);
        }
    }
#endif
*/

    void errorCallback(int error, const char *description) {
        std::cout << error << ":" << description << std::endl;
    }

    GraphicsDeviceGL::GraphicsDeviceGL() {
        std::cout << "[GL] Initializing GLFW ..." << std::endl;
        ::glfwInit();

        ::glfwSetErrorCallback(errorCallback);

#if defined(__APPLE__)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        ::glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, 1);
#endif
        // ::glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
        ::glfwWindowHint(GLFW_DEPTH_BITS, 24);
        ::glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
        ::glfwWindowHint(GLFW_RED_BITS, 8);
        ::glfwWindowHint(GLFW_GREEN_BITS, 8);
        ::glfwWindowHint(GLFW_BLUE_BITS, 8);
        ::glfwWindowHint(GLFW_ALPHA_BITS, 0);

        std::cout << "[GL] Creating Window/Context ..." << std::endl;
        m_windowGLFW = ::glfwCreateWindow(1200, 800, "Test", nullptr, nullptr);

        if (!m_windowGLFW) {
            const char description[256] = {};
            int error = ::glfwGetError((const char **)&description);
            throw std::runtime_error(description);
        }

        std::cout << "[GL] Making Context current ..." << std::endl;
        ::glfwMakeContextCurrent(m_windowGLFW);

        std::cout << "[GL] Loading OpenGL Extensions ..." << std::endl;
        if (!gladLoadGL()) {
            throw std::runtime_error("Failed to load OpenGL extensions");
        }

/*
#if defined(GLAD_DEBUG)
    // glad_set_pre_callback(gladPreCallback);
    // glad_set_post_callback(gladPostCallback);
#endif
*/
        std::cout << "[GL] Creating the GLFW-based input manager ..." << std::endl;

        m_window.reset(new WindowGLFW(m_windowGLFW));
        m_inputManager.reset(new InputManagerGLFW(m_windowGLFW));

        XE_GRAPHICS_GL_CHECK_ERROR();
    }

    GraphicsDeviceGL::~GraphicsDeviceGL() {
        if (m_windowGLFW) {
            ::glfwMakeContextCurrent(nullptr);
            ::glfwDestroyWindow(m_windowGLFW);
            ::glfwTerminate();

            m_windowGLFW = nullptr;
        }
    }
    
    Window* GraphicsDeviceGL::GetWindow() const {
        return m_window.get();
    }

    XE::Input::InputManager* GraphicsDeviceGL::GetInputManager() {
        return m_inputManager.get();
    }

    std::unique_ptr<Subset> GraphicsDeviceGL::CreateSubset(
            SubsetDescriptor& desc, 
            std::vector<std::unique_ptr<Buffer>> buffers, 
            const std::map<std::string, int> &bufferMapping, 
            std::unique_ptr<Buffer> indexBuffer) {
        return std::make_unique<SubsetGL>(desc, std::move(buffers), bufferMapping, std::move(indexBuffer));
    }
        
    std::unique_ptr<Buffer> GraphicsDeviceGL::CreateBuffer(const BufferDescriptor &desc) {
        return std::make_unique<BufferGL>(desc);
    }
        
    std::unique_ptr<Texture2D> GraphicsDeviceGL::CreateTexture2D(const PixelFormat format, const XE::Math::Vector2i &size, const PixelFormat sourceFormat, const DataType sourceDataType, const void *sourceData) {
        return std::make_unique<Texture2DGL>(format, size, sourceFormat, sourceDataType, sourceData);
    }
        
    std::unique_ptr<Texture3D> GraphicsDeviceGL::CreateTexture3D(const PixelFormat format, const XE::Math::Vector3i &size, const PixelFormat sourceFormat, const DataType sourceDataType, const void *sourceData) {
        return std::make_unique<Texture3DGL>(format, size, sourceFormat, sourceDataType, sourceData);
    }

    std::unique_ptr<Texture2DArray> GraphicsDeviceGL::CreateTexture2DArray(const PixelFormat format, const XE::Math::Vector2i &size, const int count) {
        return std::make_unique<Texture2DArrayGL>(format, size, count);
    }
        
    std::unique_ptr<TextureCubeMap> GraphicsDeviceGL::CreateTextureCubeMap(const PixelFormat format, const XE::Math::Vector2i &size, const PixelFormat sourceFormat, const DataType sourceDataType, const void **sourceData) {
        return std::unique_ptr<TextureCubeMap>();
    }
        
    std::unique_ptr<Program> GraphicsDeviceGL::CreateProgram(const ProgramDescriptor &desc) {
        return std::make_unique<ProgramGL>(desc);
    }
    
    void GraphicsDeviceGL::Draw(const Subset *subset, const SubsetEnvelope *envelopes, const int envelopeCount) {
        auto subsetGL = static_cast<const SubsetGL *>(subset);
        auto descriptor = subsetGL->GetDescriptor();
        ::glBindVertexArray(subsetGL->GetID());

        auto indexBuffer = subsetGL->GetIndexBuffer();

        if (!indexBuffer) {
            for (int i=0; i<envelopeCount; i++) {
                const SubsetEnvelope &env = envelopes[i];
                const GLenum primitiveGL = ConvertToGL(env.Primitive);

                ::glDrawArrays(primitiveGL, env.VertexStart, env.VertexCount);
            }
        } else {
            const GLenum indexTypeGL = ConvertToGL(descriptor.indexType);

            for (int i=0; i<envelopeCount; i++) {
                const SubsetEnvelope &env = envelopes[i];
                const GLenum primitiveGL = ConvertToGL(env.Primitive);
                
                if (env.VertexStart == 0) {
                    ::glDrawElements(primitiveGL, env.VertexCount, indexTypeGL, nullptr);
                } else {
                    ::glDrawElementsBaseVertex(primitiveGL, env.VertexCount, indexTypeGL, nullptr, env.VertexStart);
                }
            }
        }

        ::glBindVertexArray(0);
        XE_GRAPHICS_GL_CHECK_ERROR();
    }
        
    void GraphicsDeviceGL::BeginFrame(const ClearFlags flags, const XE::Math::Vector4f &color, const float depth, const int stencil) {
        const GLenum clearFlagsGL =
            (flags & ClearFlags::Color   ? GL_COLOR_BUFFER_BIT   : 0) | 
            (flags & ClearFlags::Depth   ? GL_DEPTH_BUFFER_BIT   : 0) | 
            (flags & ClearFlags::Stencil ? GL_STENCIL_BUFFER_BIT : 0) ;

        ::glClearColor(color.X, color.Y, color.Z, color.W);
        ::glClearDepth(static_cast<GLdouble>(depth));
        ::glClearStencil(stencil);
        ::glClear(clearFlagsGL);

        XE_GRAPHICS_GL_CHECK_ERROR();
    }
        
    void GraphicsDeviceGL::EndFrame() {
        ::glFlush();
        ::glfwSwapBuffers(m_windowGLFW);

        XE_GRAPHICS_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::PreRenderMaterial(const Material *material) {
        const auto &rs = material->renderState;

        // clip distances
        for (int i=0; i<rs.clipDistanceCount; i++) {
            const GLenum clipDistanceGL = GL_CLIP_DISTANCE0 + i;

            if (rs.clipDistances[i]) {
                ::glEnable(clipDistanceGL);
            } else {
                ::glDisable(clipDistanceGL);
            }
        }

        // depth buffer configuration
        if (rs.depthTest) {
            ::glEnable(GL_DEPTH_TEST);
        } else {
            ::glDisable(GL_DEPTH_TEST);
        }

        const GLenum depthFuncGL = ConvertToGL(rs.depthFunc);
        ::glDepthFunc(depthFuncGL);

        // polygon mode
        const GLenum fillModeGL = ConvertToGL(rs.polygonMode);
        ::glPolygonMode(GL_FRONT_AND_BACK, fillModeGL);

        // front face definition
        const GLenum faceGL = ConvertToGL(rs.frontFace);
        ::glFrontFace(faceGL);

        // back face culling
        if (rs.cullBackFace) {
            ::glEnable(GL_CULL_FACE);
        } else {
            ::glDisable(GL_CULL_FACE);
        }

        // point and line sizing
        ::glPointSize(rs.pointSize);
        ::glLineWidth(rs.lineWidth);

        // blending
        if (rs.blendEnable) {
            ::glEnable(GL_BLEND);

            const GLenum sfactorGL = ConvertToGL(rs.blendSource);
            const GLenum dfactorGL = ConvertToGL(rs.blendDestination);
            ::glBlendFunc(sfactorGL, sfactorGL);
        } else {
            ::glDisable(GL_BLEND);
        }

        // texture layers
        for (int i=0; i<material->layerCount; i++) {
            const auto &layer = material->layers[i];

            if (!layer.texture) {
                continue;
            }

            // FIXME: This will cause segfaults if the real implementation isn't derived from the Texture/TextureBaseGL family
            auto textureBaseGL = dynamic_cast<const TextureBaseGL*>(layer.texture);
            auto target = textureBaseGL->GetTarget();
            
            std::cout << target << ", " << textureBaseGL->GetID() << std::endl;

            ::glActiveTexture(GL_TEXTURE0 + i);
            ::glBindTexture(target, textureBaseGL->GetID());
            ::glTexParameteri(target, GL_TEXTURE_MAG_FILTER, ConvertToGL(layer.minFilter));
            ::glTexParameteri(target, GL_TEXTURE_MIN_FILTER, ConvertToGL(layer.magFilter));
            ::glTexParameteri(target, GL_TEXTURE_WRAP_S, ConvertToGL(layer.wrapS));
            ::glTexParameteri(target, GL_TEXTURE_WRAP_T, ConvertToGL(layer.wrapT));
            ::glTexParameteri(target, GL_TEXTURE_WRAP_R, ConvertToGL(layer.wrapR));
        }

        XE_GRAPHICS_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::PostRenderMaterial(const Material *material) {
        const auto &rs = material->renderState;

        // clip distances
        for (int i=0; i<rs.clipDistanceCount; i++) {
            const GLenum clipDistanceGL = GL_CLIP_DISTANCE0 + i;

            if (rs.clipDistances[i]) {
                ::glDisable(clipDistanceGL);
            }
        }

        // depth buffer configuration
        if (rs.depthTest) {
            ::glDisable(GL_DEPTH_TEST);
        }

        // back face culling
        if (rs.cullBackFace) {
            ::glDisable(GL_CULL_FACE);
        }

        // blending
        if (rs.blendEnable) {
            ::glDisable(GL_BLEND);
        }

        // texture layers
        for (int i=0; i<material->layerCount; i++) {
            const auto &layer = material->layers[i];

            if (!layer.texture) {
                continue;
            }

            // FIXME: This will cause segfaults if the real implementation isn't derived from Texture/TextureBaseGL family
            auto textureBaseGL = reinterpret_cast<const TextureBaseGL*>(layer.texture);

            ::glActiveTexture(GL_TEXTURE0 + i);
            ::glBindTexture(textureBaseGL->GetTarget(), 0);
        }

        ::glActiveTexture(GL_TEXTURE0);

        XE_GRAPHICS_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::SetMaterial(const Material *material) {
        if (m_material == material) {
            return;
        }

        if (m_material) {
            this->PostRenderMaterial(m_material);
        }

        this->PreRenderMaterial(material);

        m_material = material;

        XE_GRAPHICS_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::SetProgram(const Program *program) {
        m_program = static_cast<const ProgramGL*>(program);

        if (m_program) {
            ::glUseProgram(m_program->GetID());
        } else {
            ::glUseProgram(0);
        }

        XE_GRAPHICS_GL_CHECK_ERROR();
    }
    
    const Program* GraphicsDeviceGL::GetProgram() const {
        return m_program;
    }

    void GraphicsDeviceGL::ApplyUniform(const UniformMatrix *uniformMatrix, const int count, const std::byte *data) {
        // TODO: Add support for matrix transposition

        assert(m_program);
        assert(uniformMatrix);
        assert(count > 0);
        assert(data);

        int offset = 0;

        for (int i=0; i<count; i++) {
            const UniformMatrix *current = &uniformMatrix[i];
            const GLint location = m_program->GetUniformLoction(current->Name);

            switch (current->Type) {
            case DataType::Float32: 
                switch (current->Rows) {
                case 2:
                    switch (current->Columns) {
                    case 2: ::glUniformMatrix2fv(location, current->Count, GL_FALSE, (const GLfloat*)&data[offset]); break;
                    case 3: ::glUniformMatrix2x3fv(location, current->Count, GL_FALSE, (const GLfloat*)&data[offset]); break;
                    case 4: ::glUniformMatrix2x4fv(location, current->Count, GL_FALSE, (const GLfloat*)&data[offset]); break;
                    }
                    break;

                case 3:
                    switch (current->Columns) {
                    case 2: ::glUniformMatrix3x2fv(location, current->Count, GL_FALSE, (const GLfloat*)&data[offset]); break;
                    case 3: ::glUniformMatrix3fv(location, current->Count, GL_FALSE, (const GLfloat*)&data[offset]); break;
                    case 4: ::glUniformMatrix3x4fv(location, current->Count, GL_FALSE, (const GLfloat*)&data[offset]); break;
                    }
                    break;

                case 4:
                    switch (current->Columns) {
                    case 2: ::glUniformMatrix4x2fv(location, current->Count, GL_FALSE, (const GLfloat*)&data[offset]); break;
                    case 3: ::glUniformMatrix4x3fv(location, current->Count, GL_FALSE, (const GLfloat*)&data[offset]); break;
                    case 4: ::glUniformMatrix4fv(location, current->Count, GL_FALSE, (const GLfloat*)&data[offset]); break;
                    }
                    break;
                }
                break;

            case DataType::Float64: 
                switch (current->Rows) {
                case 2:
                    switch (current->Columns) {
                    case 2: ::glUniformMatrix2dv(location, current->Count, GL_FALSE, (const GLdouble*)&data[offset]); break;
                    case 3: ::glUniformMatrix2x3dv(location, current->Count, GL_FALSE, (const GLdouble*)&data[offset]); break;
                    case 4: ::glUniformMatrix2x4dv(location, current->Count, GL_FALSE, (const GLdouble*)&data[offset]); break;
                    }
                    break;

                case 3:
                    switch (current->Columns) {
                    case 2: ::glUniformMatrix3x2dv(location, current->Count, GL_FALSE, (const GLdouble*)&data[offset]); break;
                    case 3: ::glUniformMatrix3dv(location, current->Count, GL_FALSE, (const GLdouble*)&data[offset]); break;
                    case 4: ::glUniformMatrix3x4dv(location, current->Count, GL_FALSE, (const GLdouble*)&data[offset]); break;
                    }
                    break;

                case 4:
                    switch (current->Columns) {
                    case 2: ::glUniformMatrix4x2dv(location, current->Count, GL_FALSE, (const GLdouble*)&data[offset]); break;
                    case 3: ::glUniformMatrix4x3dv(location, current->Count, GL_FALSE, (const GLdouble*)&data[offset]); break;
                    case 4: ::glUniformMatrix4dv(location, current->Count, GL_FALSE, (const GLdouble*)&data[offset]); break;
                    }
                    break;
                }
                break;
            }

            offset += XE::ComputeByteSize(current->Type) * current->Rows * current->Columns * current->Count;
        }

        XE_GRAPHICS_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::ApplyUniform(const Uniform *uniform, const int count, const std::byte *data) {
        assert(m_program);
        assert(uniform);
        assert(count > 0);
        assert(data);

        int offset = 0;

        for (int i=0; i<count; i++) {
            const Uniform *current = &uniform[i];
            const GLint location = m_program->GetUniformLoction(current->Name);

            assert(location >= 0);

            switch (current->Type) {
            case DataType::Int32:
                // std::cout << current->Name << ": " << location << ", " << *((const GLint*)&data[offset]) << std::endl;
                switch (current->Size) {
                    case 1: ::glUniform1iv(location, current->Count, (const GLint*)&data[offset]); break;
                    case 2: ::glUniform2iv(location, current->Count, (const GLint*)&data[offset]); break;
                    case 3: ::glUniform3iv(location, current->Count, (const GLint*)&data[offset]); break;
                    case 4: ::glUniform4iv(location, current->Count, (const GLint*)&data[offset]); break;
                    default: assert(false);
                }
                break;
            
            case DataType::Float32:
                switch (current->Size) {
                    case 1: ::glUniform1fv(location, current->Count, (const GLfloat*)&data[offset]); break;
                    case 2: ::glUniform2fv(location, current->Count, (const GLfloat*)&data[offset]); break;
                    case 3: ::glUniform3fv(location, current->Count, (const GLfloat*)&data[offset]); break;
                    case 4: ::glUniform4fv(location, current->Count, (const GLfloat*)&data[offset]); break;
                    default: assert(false);
                }
                break;

            case DataType::UInt32:
                switch (current->Size) {
                    case 1: ::glUniform1uiv(location, current->Count, (const GLuint*)&data[offset]); break;
                    case 2: ::glUniform2uiv(location, current->Count, (const GLuint*)&data[offset]); break;
                    case 3: ::glUniform3uiv(location, current->Count, (const GLuint*)&data[offset]); break;
                    case 4: ::glUniform4uiv(location, current->Count, (const GLuint*)&data[offset]); break;
                    default: assert(false);
                }
                break;

            default:
                assert(false);
            }

            offset += XE::ComputeByteSize(current->Type) * current->Size * current->Count;
        }

        XE_GRAPHICS_GL_CHECK_ERROR();
    }

    void GraphicsDeviceGL::SetViewport(const Viewport &viewport) {
        GLint x = static_cast<GLint>(viewport.position.X);
        GLint y = static_cast<GLint>(viewport.position.Y);

        GLint w = static_cast<GLint>(viewport.size.X);
        GLint h = static_cast<GLint>(viewport.size.Y);

        ::glViewport(x, y, w, h);

        m_viewport = viewport;

        XE_GRAPHICS_GL_CHECK_ERROR();
    }

    Viewport GraphicsDeviceGL::GetViewport() const {
        return m_viewport;
    }

    const Material* GraphicsDeviceGL::GetMaterial() const {
        return m_material;
    }
}
