
#ifndef __XE_GRAPHICS_GRAPHICSDEVICE_HPP__
#define __XE_GRAPHICS_GRAPHICSDEVICE_HPP__

#include <vector>
#include <XE/DataType.hpp>
#include <XE/Math/Vector.hpp>

namespace XE::Graphics {
    /**
     * @brief Specify wich buffer will be used to clear
     */
    enum class ClearFlags {
        Color = 0x01,
        Depth = 0x02,
        Stencil = 0x04,
        ColorDepth = Color | Depth,
        All = Color | Depth | Stencil
    };
    
    inline bool operator&(const ClearFlags flags, const ClearFlags value) {
        int nflags = static_cast<int>(flags);
        int nvalue = static_cast<int>(value);
        
        if (nflags & nvalue) {
            return true;
        } else {
            return false;
        }
    }
    
    enum class PrimitiveType {
        Unknown,
        PointList,
        LineList,
        LineStrip,
        TriangleStrip,
        TriangleList,
        TriangleFan
    };
    
    /**
     * @brief Interpretation information for geometry buffers
     */
    struct DrawEnvelope {
        //! The primitive used for render
        PrimitiveType Primitive;
        
        //! The count of vertices
        int VertexCount;
        
        //! The start offset used for vertex counting
        int VertexStart = 0;
    };
    
    enum class BufferType {
        VertexBuffer,
        IndexBuffer
    };
    
    class InputManager;
    class Buffer;
    class Subset;
    
    struct SubsetFormat;
    
    class Texture2D;
    class Texture3D;
    class Texture2DArray;
    class TextureCubeMap;
    
    enum class PixelFormat;
    
    struct Structure;

    class Program;
    
    enum class ShaderType;
    
    class GraphicsDevice {
    public:
        virtual ~GraphicsDevice() {}
        
        virtual InputManager* GetInputManager() = 0;
        
        virtual Subset* CreateSubset(const SubsetFormat *format, std::vector<Buffer*> buffers, const DataType indexType=DataType::Unknown, Buffer *indexBuffer=nullptr) = 0;
        
        virtual Buffer* CreateBuffer(const BufferType bufferType, const int size, const void *data=nullptr) = 0;
        
        virtual Texture2D* CreateTexture2D(const PixelFormat format, const XE::Math::Vector2i &size, const PixelFormat sourceFormat, const DataType sourceDataType, const void *sourceData) = 0;
        
        virtual Texture3D* CreateTexture3D(const PixelFormat format, const XE::Math::Vector3i &size, const PixelFormat sourceFormat, const DataType sourceDataType, const void *sourceData) = 0;
        
        virtual Texture2DArray* CreateTexture2DArray(const PixelFormat format, const XE::Math::Vector2i &size, const int count, const PixelFormat sourceFormat, const DataType sourceDataType, const void **sourceData) = 0;
        
        virtual TextureCubeMap* CreateTextureCubeMap(const PixelFormat format, const XE::Math::Vector2i &size, const PixelFormat sourceFormat, const DataType sourceDataType, const void **sourceData) = 0;
        
        virtual Program* CreateProgram(const std::vector<std::tuple<ShaderType, std::string>> &shaderSources) = 0;
        
        virtual void SetProgram(const Program *program) = 0;
        
        virtual const Program* GetProgram() const = 0;
        
        virtual void SetSubset(const Subset *subset) = 0;
        
        virtual const Subset* GetSubset() const = 0;
        
        virtual void Draw(const std::vector<DrawEnvelope> &envelopes) = 0;
        
        virtual void BeginFrame(const ClearFlags flags) = 0;
        
        virtual void EndFrame() = 0;
        
        virtual void ApplyUniform(const Structure* structure, const void *uniform) = 0;
    };
}

#endif