#include "pch.h"
#include "GraphicsContext.h"
#include "Renderer.h"
#include "OpenGLContext.h"

Scope<GraphicsContext> GraphicsContext::Create(void* window)
{
  switch(Renderer::GetAPI())
  {
    case RendererAPI::API::None: return nullptr;
    case RendererAPI::API::OpenGL: return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
  }
}



