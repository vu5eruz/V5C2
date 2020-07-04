//==========================================================
//
//  V5C2  --  src/client/main.cpp
//
//==========================================================


#include "client/main.h"
#include "client/platform.h"
#include "client/texture.h"

#include <iostream>
#include <memory>
#include <stdexcept>


namespace v5c2::client
{
    namespace
    {
        GLFWwindow* g_MainWindow{};
        TexturePtr g_LogoTxt{};


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

        ::glEnable(GL_BLEND);
        ::glEnable(GL_TEXTURE_2D);

        ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        ::glMatrixMode(GL_PROJECTION);
        ::glLoadIdentity();
        ::glOrtho(0, 800, 600, 0, -1.0, 1.0);

        ::glMatrixMode(GL_MODELVIEW);
        ::glLoadIdentity();

        g_LogoTxt = std::make_shared<Texture>();
        
        Texture::Bind(g_LogoTxt.get());
        g_LogoTxt->Image("images/V5c2Logo.png");
        g_LogoTxt->Parameter(Texture::MinFilter, Texture::Linear);
        g_LogoTxt->Parameter(Texture::MagFilter, Texture::Linear);
        Texture::Bind(nullptr);
    }


    void UninitializeClient()
    {
        g_LogoTxt.reset();
        ::glfwTerminate();
    }


    bool IsRunning()
    {
        return !::glfwWindowShouldClose(g_MainWindow);
    }
    
    
    void DoCycle()
    {
        ::glfwPollEvents();

        ::glClearColor(0.06125f, 0.06125f, 0.06125f, 1.0f);
        ::glClear(GL_COLOR_BUFFER_BIT);

        Texture::Bind(g_LogoTxt.get());

        ::glBegin(GL_QUADS);
        ::glTexCoord2f(0.0f, 0.0f); ::glVertex2f(32, 32);
        ::glTexCoord2f(1.0f, 0.0f); ::glVertex2f(32 + 128, 32);
        ::glTexCoord2f(1.0f, 1.0f); ::glVertex2f(32 + 128, 32 + 128);
        ::glTexCoord2f(0.0f, 1.0f); ::glVertex2f(32, 32 + 128);
        ::glEnd();

        Texture::Bind(nullptr);

        ::glfwSwapBuffers(g_MainWindow);
    }
}
