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
        GLFWwindow* g_MainWindow{};


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

        ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

        g_MainWindow = ::glfwCreateWindow(800, 600, "V5C2", nullptr, nullptr);
        if (!g_MainWindow)
        {
            throw std::runtime_error("glfwCreateWindow failed");
        }

        ::glfwMakeContextCurrent(g_MainWindow);
        ::glfwSwapInterval(1);

        if (!::gladLoadGLLoader(reinterpret_cast<GLADloadproc>(::glfwGetProcAddress)))
        {
            throw std::runtime_error("OpenGL context loading failed");
        }
    }


    void UninitializeClient()
    {
        ::glfwTerminate();
    }


    bool IsRunning()
    {
        return !::glfwWindowShouldClose(g_MainWindow);
    }
    
    
    void DoCycle()
    {
        ::glfwPollEvents();

        ::glClear(GL_COLOR_BUFFER_BIT);

        ::glBegin(GL_TRIANGLES);
        ::glVertex2f(0.0f, 1.0f);
        ::glVertex2f(1.0f, -1.0f);
        ::glVertex2f(-1.0f, -1.0f);
        ::glEnd();

        ::glfwSwapBuffers(g_MainWindow);
    }
}
