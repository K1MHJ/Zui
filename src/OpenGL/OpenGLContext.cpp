#include "pch.h"
#include "OpenGLContext.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
    : m_WindowHandle(windowHandle) {
  CORE_ASSERT(windowHandle, "Window handle is null");
}

void OpenGLContext::Init() {
  PROFILE_FUNCTION();

  glfwMakeContextCurrent(m_WindowHandle);
  gladLoadGL(glfwGetProcAddress);
  CORE_INFO("OpenGL Info:");
  CORE_INFO("Vendor: {0}", (char*)glGetString(GL_VENDOR));
  CORE_INFO("Renderer: {0}",(char*)glGetString(GL_RENDERER));
  CORE_INFO("Version: {0}", (char*)glGetString(GL_VERSION));

  CORE_ASSERT(GLVersion.major > 4 ||
                  (GLVersion.major == 4 && GLVersion.minor >= 5),
              "Hazel requires at least OpenGL version 4.5!");
}

void OpenGLContext::SwapBuffers() {
  PROFILE_FUNCTION();
  glfwSwapBuffers(m_WindowHandle);
}
