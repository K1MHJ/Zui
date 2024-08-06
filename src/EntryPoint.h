#pragma once
#include <iostream>
#include "Base.h"
#include "Application.h"

extern Application* CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
  std::cout << "Start" << std::endl;

  auto app = CreateApplication({argc, argv});

  app->Run();

  delete app;


  std::cout << "End" << std::endl;
  return 0;
}
