#include "Zui.h"
#include <Core/EntryPoint.h>
#include "MyLayer.h"

class MyApp : public Application
{
public:
  MyApp(const ApplicationSpecification& specification)
  : Application(specification)
  {
    PushLayer(new MyLayer);
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

