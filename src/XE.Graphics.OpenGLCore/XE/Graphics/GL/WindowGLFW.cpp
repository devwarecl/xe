
#include "WindowGLFW.hpp"

#include <GLFW/glfw3.h>
#include <XE/Graphics/GraphicsDevice.hpp>

namespace XE::Graphics::GL {
    WindowGLFW::WindowGLFW(GLFWwindow *window) {
        assert(window);
        m_windowGLFW = window;
    }

    XE::Math::Vector2i WindowGLFW::GetSize() const {
        int width, height;

        ::glfwGetWindowSize(m_windowGLFW, &width, &height);

        return {width, height};
    }
}