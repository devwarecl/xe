
#ifndef __XE_GRAPHICS_TEXTURE2D_HPP__
#define __XE_GRAPHICS_TEXTURE2D_HPP__

#include <cstdint>
#include <cstddef>
#include <XE/Predef.h>
#include <XE/Graphics/Texture.h>

namespace XE {
    enum class DataType : std::int16_t;

    class Texture2D : public Texture {
    public:
        virtual TextureType getType() const override;

    public:
        virtual ~Texture2D();
        
        virtual Vector2i getSize() const = 0;
        
        virtual void setData(const std::byte *surfaceData, const int mipLevel, const PixelFormat surfaceFormat, const DataType surfaceDataType, const Recti &area) = 0;

        virtual void getData(std::byte *surfaceData, const int mipLevel, const PixelFormat surfaceFormat, const DataType surfaceDataType) const = 0;
    };
}

#endif
