#pragma once
#include "Framework/Layer.h"
#include "Framework/Application.h"
#include "Framework/Image.h"

namespace Ry_App
{
	class AppLayer : public Layer
	{
	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnUIRender() override;

		void Render();
	private:
		std::shared_ptr<Image> m_Image;
		uint32_t* m_ImageData = nullptr;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		float m_FrameTime = 0.0f;
		float m_FPS = 0.0f;
	};
}