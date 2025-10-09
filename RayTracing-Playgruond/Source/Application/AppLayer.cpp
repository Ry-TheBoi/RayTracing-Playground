#include "AppLayer.h"
#include "Utils/Timer.h"
#include "Utils/Random.h"
#include <iostream>

namespace Ry_App
{
	void AppLayer::OnAttach()
	{
	}

	void AppLayer::OnDetach()
	{
	}

	void AppLayer::OnUIRender()
	{
		// Debug Window
		{
			ImGui::Begin("Debug");
			ImGui::Text("Frame Time: %.3f ms", m_FrameTime);
			ImGui::Text("FPS: %.3f FPS", m_FPS);
			ImGui::End();
		}

		// Viewport
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("Viewport");
			m_ViewportWidth = ImGui::GetContentRegionAvail().x;
			m_ViewportHeight = ImGui::GetContentRegionAvail().y;


			if (m_Image)
				ImGui::Image(m_Image->GetDescriptorSet(), { (float)m_Image->GetWidth(), (float)m_Image->GetHeight() });

			ImGui::End();
			ImGui::PopStyleVar();

			Render();
		}
	}

	void AppLayer::Render()
	{
		Timer timer;

		// Recreate the image if image doesn't exist or width & height don't match current one due to resize
		if (!m_Image || m_ViewportWidth != m_Image->GetWidth() || m_ViewportHeight != m_Image->GetHeight())
		{
			m_Image = std::make_shared<Image>(m_ViewportWidth, m_ViewportHeight, ImageFormat::RGBA);
			delete[] m_ImageData;
			m_ImageData = new uint32_t[m_ViewportWidth * m_ViewportHeight];
		}

		// Make every pixel a random color
		for (uint32_t i = 0; i < m_ViewportWidth * m_ViewportHeight; i++)
		{
			m_ImageData[i] = Random::UInt();
			m_ImageData[i] |= 0xff000000;
		}


		m_Image->SetData(m_ImageData);
		m_FrameTime = timer.ElapsedMillis();
		m_FPS = 1000.0f / m_FrameTime;
	}
}