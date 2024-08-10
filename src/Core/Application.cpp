#include "pch.h"
#include "Core/Application.h"
#include "Core/Log.h"
#include "Renderer/Renderer.h"
#include "Utils/PlatformUtils.h"

Application* Application::s_Instance = nullptr;

Application::Application(const ApplicationSpecification& specification)
: m_Specification(specification)
{
  PROFILE_FUNCTION();
  CORE_ASSERT(!s_Instance, "Application already exists!"); 

  s_Instance = this;

  if(!m_Specification.WorkingDirectory.empty())
    std::filesystem::current_path(m_Specification.WorkingDirectory);
  
  m_Window = Window::Create(WindowProps(m_Specification.Name));
  //Renderer::Init();
}

Application::~Application()
{
  //Renderer::Shutdown();
}

void Application::Close()
{
  m_Running = false;
}
void Application::SubmitToMainThread(const std::function<void()>& function)
{
  std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);
  m_MainThreadQueue.emplace_back(function);
}
void Application::Run()
{
  while(m_Running)
  {
    ExecuteMainThreadQueue();

    if(!m_Minimized)
    {

    }
    m_Window->OnUpdate();
  }
}

bool Application::OnWindowClose()
{
  m_Running = false;
  return true;
}

bool Application::OnWindowResize()
{
  m_Minimized = true;
  return false;

  m_Minimized = false;
  return false;
}

void Application::ExecuteMainThreadQueue()
{
  std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);
  for(auto& func : m_MainThreadQueue)
  {
    func();
  }
  m_MainThreadQueue.clear();
}
