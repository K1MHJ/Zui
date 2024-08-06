#include "pch.h"
#include "OpenGLContext.h"

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
  : m_WindowHandle(windowHandle)
{
}

void OpenGLContext::Init()
{
  glfwMakeContextCurrent(m_WindowHandle);
  gladLoadGL(glfwGetProcAddress);

  //CORE_INFO("Vendor:{0}",glGetString(GL_VENDOR));
  //CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
  //CORE_INFO("Version: {0}", glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers()
{
  glfwSwapBuffers(m_WindowHandle);
}

