#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include "include/Utils.hpp"

const int DEBUG = 1;

CheckPoint appLog;
const int WIDTH = 2560;
const int HEIGHT = 1440;

void log(Logger* logger, std::string s) {
    if (DEBUG) {
        appLog.note(s);
        logger->print(s);
    }
}

class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;
    VkInstance instance;
    Logger* initLogger = new Logger("INIT", DEBUG, GREEN);
    Logger* mainLoopLogger = new Logger("MAIN_LOOP", DEBUG, BLUE);
    Logger* cleanUpLogger = new Logger("CLEANUP", DEBUG, YELLOW);

    void initWindow() {
        log(initLogger, "Beginning initialization of GLFW");
        glfwInit();
        log(initLogger, "initialized GLFW successfully");
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
        log(initLogger, "created GLFW window successfully");
    }
    
    void initVulkan() {
        log(initLogger, "Beginning initialization of Vulkan");
        createInstance();
    }

    void createInstance() {
        log(initLogger, "Creating instance");
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
        log(initLogger, "Successfully Created instance");
    }

    void mainLoop() {
        log(mainLoopLogger, "Entering main loop");
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
        log(mainLoopLogger, "Safe exit from main loop");
    }

    void cleanup() {
        log(cleanUpLogger, "Cleaning up program");
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    Logger* mainLogger = new Logger("MAIN", 1, MAGENTA);
    log(mainLogger, "Main Entry Point into Application");
    HelloTriangleApplication app;

    try {
        app.run();
    }
    catch (const std::exception & e) {
        Logger* errorLogger = new Logger("ERROR", 1, RED);
        std::string log = "Last known location was position " + appLog.getLastCheckPoint();
        appLog.note("CRASH");
        errorLogger->print(log);
        errorLogger->print(e.what());
        std::cerr << e.what() << std::endl;
        appLog.dumpLog(DEBUG);
        return EXIT_FAILURE;
    }
    if (DEBUG) {
        log(mainLogger, "Safely Shut Down");
        appLog.dumpLog(DEBUG);
    }
    
    return EXIT_SUCCESS;
}