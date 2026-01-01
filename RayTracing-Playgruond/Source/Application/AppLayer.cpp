#include "AppLayer.h"
#include "Utils/Timer.h"
#include "Utils/Random.h"
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

namespace Ry_App
{
	AppLayer::AppLayer()
		: m_Camera(45.0f, 0.1f, 100.0f)
	{
		{
			Sphere sphere;
			sphere.Position = { 0.0f, 0.0f, 0.0f };
			sphere.Radius = 0.5f;
			sphere.Albedo = { 1.0f, 0.0f, 0.0f };
			m_Scene.Spheres.push_back(sphere);
		}

		{
			Sphere sphere;
			sphere.Position = { 1.0f, 0.0f, -5.0f };
			sphere.Radius = 1.5f;
			sphere.Albedo = { 0.2f, 0.3f, 1.0f };
			m_Scene.Spheres.push_back(sphere);
		}
	}

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

		// Scene Window
		{
			ImGui::Begin("Scene");
			
			for (size_t i = 0; i < m_Scene.Spheres.size(); i++)
			{
				ImGui::PushID(i);
				Sphere& sphere = m_Scene.Spheres[i];
				ImGui::DragFloat3("Position", glm::value_ptr(sphere.Position), 0.1f);
				ImGui::DragFloat("Radius", &sphere.Radius, 0.1f);
				ImGui::ColorEdit3("Albedo", glm::value_ptr(sphere.Albedo));
				ImGui::Separator();
				ImGui::PopID();
			}

			ImGui::End();
		}

		// Viewport
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("Viewport");
			m_ViewportWidth = ImGui::GetContentRegionAvail().x;
			m_ViewportHeight = ImGui::GetContentRegionAvail().y;

			auto image = m_Renderer.GetFinalImage();
			if (image)
			{
				ImGui::Image(image->GetDescriptorSet(), { (float)image->GetWidth(), (float)image->GetHeight() },
					ImVec2(0, 1), ImVec2(1, 0));
			}

			ImGui::End();
			ImGui::PopStyleVar();

			Render();
		}
	}

	void AppLayer::OnUpdate(float ts)
	{
		m_Camera.OnUpdate(ts);
	}

	void AppLayer::Render()
	{
		Timer timer;

		m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Camera.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Renderer.Render(m_Scene, m_Camera);

		m_FrameTime = timer.ElapsedMillis();
		m_FPS = 1000.0f / m_FrameTime;
	}
}