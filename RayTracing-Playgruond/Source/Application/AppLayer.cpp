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
		Material& redSphere = m_Scene.Materials.emplace_back();
		redSphere.Albedo = { 1.0f, 0.0f, 0.0f };
		redSphere.Roughness = 0.0f;

		Material& blueSphere = m_Scene.Materials.emplace_back();
		blueSphere.Albedo = { 0.2f, 0.3f, 1.0f };
		blueSphere.Roughness = 0.1f;

		{
			Sphere sphere;
			sphere.Position = { 0.0f, 0.0f, 0.0f };
			sphere.Radius = 1.0f;
			sphere.MaterialIndex = 0;
			m_Scene.Spheres.push_back(sphere);
		}

		{
			Sphere sphere;
			sphere.Position = { 0.0f, -101.0f, 0.0f };
			sphere.Radius = 100.0f;
			sphere.MaterialIndex = 1;
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
			ImGui::Separator();

			ImGui::DragInt("Ray Bounces", &m_Renderer.GetRayBounces(), 1.0f, 2, 16);
			ImGui::Checkbox("Reflections", &m_Renderer.GetReflectionState());
			ImGui::Checkbox("Accumulate", &m_Renderer.GetAccumulationState());

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
				ImGui::DragInt("Material", &sphere.MaterialIndex, 1.0f, 0, (int)m_Scene.Materials.size() - 1);
				ImGui::Separator();
				ImGui::PopID();
			}

			for (size_t i = 0; i < m_Scene.Materials.size(); i++)
			{
				ImGui::PushID(i);
				Material& material = m_Scene.Materials[i];
				ImGui::ColorEdit3("Albedo", glm::value_ptr(material.Albedo));
				ImGui::DragFloat("Roughness", &material.Roughness, 0.05f, 0.0f, 1.0f);
				ImGui::DragFloat("Metallic", &material.Metallic, 0.05f, 0.0f, 1.0f);
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
		if (m_Camera.OnUpdate(ts))
			m_Renderer.ResetFrameIndex();
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