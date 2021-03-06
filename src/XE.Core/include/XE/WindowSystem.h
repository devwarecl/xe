
#ifndef __XE_UI_WINDOWSYSTEM_HPP__
#define __XE_UI_WINDOWSYSTEM_HPP__

#include <memory>
#include <XE/Predef.h>

namespace XE {
    class XE_API [[deprecated]] Frame;

    class XE_API [[deprecated]] WindowSystem {
    public:
        virtual ~WindowSystem();

        virtual std::unique_ptr<Frame> CreateFrame() = 0;
    };
}

#endif
