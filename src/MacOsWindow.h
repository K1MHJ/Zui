#pragma once

#include "Window.h"
#include "GraphicsContext.h"
#include <GLFW/glfw3.h>

class MacOsWindow : public Window
{
public:
  MacOsWindow(const WindowProps& props);
  virtual ~MacOsWindow();

  void OnUpdate() override;

  unsigned int GetWidth() const override {return m_Data.Width;}
  unsigned int GetHeight() const override {return m_Data.Height;}
  
  // attributes 
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

  void* GetNativeWindow() const override{ return m_Window;}
private:
  virtual void Init(const WindowProps& props);
  virtual void Shutdown();
private:
  GLFWwindow* m_Window;
  Scope<GraphicsContext> m_Context;

  struct WindowData
  {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;
  };
  WindowData m_Data;
};
