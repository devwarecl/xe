
#include <array>
#include <string>
#include <iostream>
#include <map>
#include <XE/Util/Timer.hpp>

#include "SandboxApp.hpp"

std::vector<std::string> ConvertArgs(int argc, char **argv) {
    std::vector<std::string> args;

    for (int i=1; i<argc; i++) {
        args.push_back(argv[i]);
    }

    return args;
}

int main(int argc, char **argv) {
    try {
        std::vector<std::string> args = ConvertArgs(argc, argv);
        auto app = XE::Application::create(args);

        app->initialize();

        int lastTime = XE::Timer::getTick();

        while (!app->shouldClose()) {
            int current = XE::Timer::getTick() - lastTime;
            float seconds = static_cast<float>(current) / 1000.0f;

            lastTime = XE::Timer::getTick();

            app->update(seconds);
            app->render();
        }
    } catch (const std::exception &exp) {
        std::cout << exp.what() << std::endl;
    }

    return 0;
}
