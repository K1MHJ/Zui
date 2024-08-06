#pragma once

#include "Base.h"
#include <sstream>

struct WindowProps
{
  std::string Title;
  uint32_t Width;
  uint32_t Height;

  WindowProps(const std::string& title = "Main Window",
              uint32_t width = 400,
              uint32_t height = 400)
  :Title(title), Width(width), Height(height)
  {

  }
};

class Window
{
public:
  virtual ~Window() = default;
  virtual void OnUpdate() = 0;

  virtual uint32_t GetWidth() const = 0;
  virtual uint32_t GetHeight() const = 0;
   
  virtual void SetVSync(bool enalbed) = 0;
  virtual bool IsVSync() const = 0;
  virtual void* GetNativeWindow() const = 0;

  static Scope<Window> Create(const WindowProps& props = WindowProps());
};
