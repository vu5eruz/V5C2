//==========================================================
//
//  V5C2  --  src/client/main.cpp
//
//==========================================================


#include "client/main.h"
#include "client/platform.h"

#include <iostream>
#include <stdexcept>


namespace v5c2::client
{
    namespace
    {
        void ErrorCallback(int code, const char* description)
        {
            std::cerr << "GLFW error (" << code <<  "): " << description << std::endl;
        }
    }


    void InitializeClient()
    {
        std::cout << "GLFW version: " << ::glfwGetVersionString() << std::endl;

        ::glfwSetErrorCallback(ErrorCallback);

        // TODO(vu5eruz): Development in Mac OS
        ::glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
        ::glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_FALSE);

        if (!::glfwInit())
        {
            throw std::runtime_error("glfwInit failed");
        }
    }


    void UninitializeClient()
    {
        ::glfwTerminate();
    }
}
