#include "pch.h"
#include "MacOsWindow.h"
#include "Renderer.h"
#include "OpenGLContext.h"

static uint8_t s_GLFWWindowCount = 0;
static void GLFWErrorCallback(int error, const char* description)
{
}

MacOsWindow::MacOsWindow(const WindowProps& props)
{
  Init(props);
}

MacOsWindow::~MacOsWindow()
{
  Shutdown();
}

void MacOsWindow::Init(const WindowProps& props)
{
  m_Data.Title = props.Title;
  m_Data.Width = props.Width;
  m_Data.Height = props.Height;

  if (s_GLFWWindowCount == 0)
  {
    int success = glfwInit();
    glfwSetErrorCallback(GLFWErrorCallback);
  }

  {
  #if defined(DEBUG)
    if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
      glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  #endif
    m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
    ++s_GLFWWindowCount;
  }

  m_Context = GraphicsContext::Create(m_Window);
  m_Context->Init();

  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(true);

  // Set GLFW callbacks
  glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
    data.Width = width;
    data.Height = height;

    // WindowResizeEvent event(width, height);
    // data.EventCallback(event);
  });

  glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
    // WindowCloseEvent event;
    // data.EventCallback(event);
  });

  glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    switch (action)
    {
      case GLFW_PRESS:
      {
        // KeyPressedEvent event(key, 0);
        // data.EventCallback(event);
        break;
      }
      case GLFW_RELEASE:
      {
        // KeyReleasedEvent event(key);
        // data.EventCallback(event);
        break;
      }
      case GLFW_REPEAT:
      {
        // KeyPressedEvent event(key, true);
        // data.EventCallback(event);
        break;
      }
    }
  });

  glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    // KeyTypedEvent event(keycode);
    // data.EventCallback(event);
  });

  glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    switch (action)
    {
      case GLFW_PRESS:
      {
        break;
      }
      case GLFW_RELEASE:
      {
        break;
      }
    }
  });

  glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

  });

  glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

  });
}

void MacOsWindow::Shutdown()
{
  glfwDestroyWindow(m_Window);
  --s_GLFWWindowCount;

  if (s_GLFWWindowCount == 0)
  {
    glfwTerminate();
  }
}

void MacOsWindow::OnUpdate()
{
  glfwPollEvents();
  m_Context->SwapBuffers();
}

void MacOsWindow::SetVSync(bool enabled)
{
  if (enabled)
    glfwSwapInterval(1);
  else
    glfwSwapInterval(0);

  m_Data.VSync = enabled;
}

bool MacOsWindow::IsVSync() const
{
  return m_Data.VSync;
}

