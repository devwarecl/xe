
#ifndef __XE_UI_FRAME_HPP__
#define __XE_UI_FRAME_HPP__

#include <cstddef>
#include <string>
#include <functional>
#include <XE/Predef.hpp>
#include <XE/Math/Vector.hpp>

namespace XE {
    class XE_API InputManager;
    /**
     * @brief 
     */
    typedef void* FrameHandle;

    struct FrameProperties {
        std::string Caption;
        XE::Vector2i Size;
        XE::Vector2i Position;
    };

    /**
     * @brief Abstract a (possible) native OS window frame, for presenting rendering content to the user.
     */
    class Frame {
    public:
        virtual ~Frame();

        virtual bool GetCloseRequested() const = 0;

        virtual FrameHandle GetHandle() const = 0;

        virtual FrameProperties GetProperties() const = 0;

        virtual void SetProperties(const FrameProperties &properties) = 0;
    };
}

#endif
