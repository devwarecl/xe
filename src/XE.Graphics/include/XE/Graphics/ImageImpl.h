
#ifndef __XE_GRAPHICS_IMAGEIMPL_HPP__
#define __XE_GRAPHICS_IMAGEIMPL_HPP__

#include "Image.h"

namespace XE {
    /**
     * @brief Image implementation class.
     */
    class ImageImpl : public Image {
    public:
        ImageImpl();

        virtual ~ImageImpl();

        virtual const std::byte* getPointer() const override;
        
        virtual PixelFormat getFormat() const override;

        virtual Vector2i getSize() const override;

        void allocate(const PixelFormat format, const Vector2i &size);

        void free();

    private:
        std::byte *pixels = nullptr;
        PixelFormat format = PixelFormat::Unknown;
        Vector2i size = {0, 0};
    };
}

#endif
