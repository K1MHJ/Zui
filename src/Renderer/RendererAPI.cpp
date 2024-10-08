#include "pch.h"
#include "RendererAPI.h"
#include "OpenGLRendererAPI.h"

RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

Scope<RendererAPI> RendererAPI::Create()
{
  switch(s_API)
  {
    case RendererAPI::API::None: return nullptr;
    case RendererAPI::API::OpenGL: return CreateScope<OpenGLRendererAPI>();
  }
}
