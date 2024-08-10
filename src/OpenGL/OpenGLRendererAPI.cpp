#include "pch.h"
#include "OpenGLRendererAPI.h"
#include <glad/gl.h>

void OpenGLMessageCallback(
  GLenum source,
  GLenum type,
  GLuint id,
  GLenum severity,
  GLsizei length,
  const GLchar* message,
  const void* userParam)
{
  switch (severity)
  {
    // case GL_DEBUG_SEVERITY_HIGH:         CORE_CRITICAL(message); return;
    // case GL_DEBUG_SEVERITY_MEDIUM:       CORE_ERROR(message); return;
    // case GL_DEBUG_SEVERITY_LOW:          CORE_WARN(message); return;
    // case GL_DEBUG_SEVERITY_NOTIFICATION: CORE_TRACE(message); return;
    default:
    return;
  }
}

void OpenGLRendererAPI::Init()
{
#ifdef HZ_DEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(OpenGLMessageCallback, nullptr);
  
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
}

void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
  glViewport(x, y, width, height);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
  glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
// {
//   vertexArray->Bind();
//   uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
//   glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
// }

// void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
// {
//   vertexArray->Bind();
//   glDrawArrays(GL_LINES, 0, vertexCount);
// }

void OpenGLRendererAPI::SetLineWidth(float width)
{
  glLineWidth(width);
}
