#pragma once
#include "Framework/Layer.h"
#include "Framework/Application.h"
#include "Framework/Image.h"

#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"
#include "Renderer/Scene.h"

namespace Ry_App
{
	class AppLayer : public Layer
	{
	public:
		AppLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnUIRender() override;

		void OnUpdate(float ts) override;

		void Render();
	private:
		Camera m_Camera;
		Renderer m_Renderer;
		Scene m_Scene;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		float m_FrameTime = 0.0f;
		float m_FPS = 0.0f;
	};
}