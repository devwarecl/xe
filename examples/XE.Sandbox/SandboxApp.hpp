
#ifndef __XE_SANDBOX_SANDBOXAPP_HPP__
#define __XE_SANDBOX_SANDBOXAPP_HPP__

#include <memory>
#include <string>
#include <vector>

namespace XE {
    class Application {
    public:
        virtual ~Application() {}

        virtual void initialize() = 0;
        virtual void update(const float seconds) = 0;
        virtual void render() = 0;

        virtual bool shouldClose() const = 0;

    public:
        static std::unique_ptr<Application> create(const std::vector<std::string> &args);
    };
}

#endif
