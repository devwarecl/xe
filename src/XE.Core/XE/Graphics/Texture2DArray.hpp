
#ifndef __XE_GRAPHICS_TEXTURE2DARRAY_HPP__
#define __XE_GRAPHICS_TEXTURE2DARRAY_HPP__

#include <XE/Predef.hpp>
#include <XE/Graphics/Texture.hpp>

namespace XE {
    enum class DataType : std::int16_t;
}

namespace XE::Graphics {
    class Texture2DArray : public Texture {

    public:
        virtual TextureType Texture2DArray::GetType() const override;

    public:
        virtual ~Texture2DArray();
        
        virtual XE:: Math::Vector2i GetSize() const = 0;
        
        virtual int GetCount() const = 0;
        
        virtual void SetData(const void *surfaceData, const int mipLevel, const int arrayIndex, const PixelFormat surfaceFormat, const DataType surfaceDataType, const XE::Math::Recti &area, int count) = 0;
        
        virtual void GetData(void *surfaceData, const int mipLevel, const int arrayIndex, const PixelFormat surfaceFormat, const DataType surfaceDataType, const XE::Math::Recti &area) const = 0;
    };
}

#endif
