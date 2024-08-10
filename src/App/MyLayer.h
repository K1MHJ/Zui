#pragma once

#include "Zui.h"

class MyLayer : public Layer {
public:
  MyLayer();
  virtual ~MyLayer() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;

  void OnUpdate(Timestep ts) override;
  virtual void OnImGuiRender() override;
  void OnEvent(Event &e) override;

private:
  // OrthographicCameraController m_CameraController;

  // // Temp
  // Ref<VertexArray> m_SquareVA;
  // Ref<Shader> m_FlatColorShader;

  // Ref<Texture2D> m_CheckerboardTexture;

  glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};
