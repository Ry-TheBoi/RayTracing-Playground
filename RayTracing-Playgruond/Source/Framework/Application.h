#pragma once

#include "Layer.h"

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "imgui.h"
#include "vulkan/vulkan.h"

void check_vk_result(VkResult err);

struct GLFWwindow;

namespace Ry_App {

	struct ApplicationSpecification
	{
		std::string Name = "Ry Tools App";
		uint32_t Width = 1280;
		uint32_t Height = 720;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& applicationSpecification = ApplicationSpecification());
		~Application();

		void Run();
		void ToggleMenuBarState(bool value) { m_MenuBar = value; }

		template<typename T>
		void PushLayer()
		{
			static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer!");
			m_LayerStack.emplace_back(std::make_shared<T>())->OnAttach();
		}

		void PushLayer(const std::shared_ptr<Layer>& layer) { m_LayerStack.emplace_back(layer); layer->OnAttach(); }

		void Close();

		static VkInstance GetInstance();
		static VkPhysicalDevice GetPhysicalDevice();
		static VkDevice GetDevice();

		static VkCommandBuffer GetCommandBuffer(bool begin);
		static void FlushCommandBuffer(VkCommandBuffer commandBuffer);

		static void SubmitResourceFree(std::function<void()>&& func);

		static Application& Get() { return *s_Instance; }
	private:
		void Init();
		void Shutdown();
	private:
		ApplicationSpecification m_Specification;
		GLFWwindow* m_WindowHandle = nullptr;
		bool m_Running = false;

		std::vector<std::shared_ptr<Layer>> m_LayerStack;
		bool m_MenuBar = false;
	private:
		static Application* s_Instance;
	};

	// Implemented by CLIENT
	Application* CreateApplication(int argc, char** argv);
}