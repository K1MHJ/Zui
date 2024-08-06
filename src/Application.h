#pragma once

#include "Base.h"
#include "Window.h"


int main(int argc, char** argv);

struct ApplicationCommandLineArgs
{
  int Count = 0;
  char** Args = nullptr;

  const char* operator[](int index) const
  {
    return Args[index];
  }
};

struct ApplicationSpecification
{
  std::string Name = "Application";
  std::string WorkingDirectory;
  ApplicationCommandLineArgs CommandLineArgs;
};

class Application
{
public:
  Application(const ApplicationSpecification& specification);
  virtual ~Application();
 
  Window& GetWindow() {return *m_Window;}
  void Close();

  static Application& Get() { return *s_Instance; }
  const ApplicationSpecification& GetSpecification() const{return m_Specification;}
  
  void SubmitToMainThread(const std::function<void()>& function);
private:
  void Run();
  bool OnWindowClose();
  bool OnWindowResize();

  void ExecuteMainThreadQueue();

private:
  ApplicationSpecification m_Specification;
  Scope<Window> m_Window;

  bool m_Running = true;
  bool m_Minimized = false;

  std::vector<std::function<void()>> m_MainThreadQueue;
  std::mutex m_MainThreadQueueMutex;
private:
  static Application* s_Instance;
  friend int ::main(int argc, char** argv);
};

Application* CreateApplication(ApplicationCommandLineArgs args);
