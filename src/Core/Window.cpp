#include "pch.h"
#include "Window.h"

#ifdef PLATFORM_MACOS
  #include "MacOsWindow.h"
#endif

Scope<Window> Window::Create(const WindowProps& props)
{
  return CreateScope<MacOsWindow>(props);
}
