#include "EntryPoint.h"

class MyApp : public Application
{
public:
  MyApp(const ApplicationSpecification& specification)
  : Application(specification)
  {
  }

  ~MyApp()
  {
  }
};
Application* CreateApplication(ApplicationCommandLineArgs args)
{
  ApplicationSpecification spec;
  spec.Name = "ZuiApp";
  spec.WorkingDirectory = "./bin";
  spec.CommandLineArgs = args;

  return new MyApp(spec);
}

