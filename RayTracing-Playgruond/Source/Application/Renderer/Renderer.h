#pragma once

#include "Framework/Image.h"
#include <glm/glm.hpp>
#include <memory>

#include "Camera.h"
#include "Scene.h"

namespace Ry_App
{
	struct RayPayload
	{
		glm::vec3 Origin;
		glm::vec3 Direction;
	};

	class Renderer
	{
	public:
		Renderer() = default;

		// Primary functions
		void OnResize(uint32_t width, uint32_t height);
		void Render(const Scene& scene, const Camera& camera);

		std::shared_ptr<Image> GetFinalImage() const { return m_FinalImage; }
	private:
		// "Shader" functions
		glm::vec4 RayGeneration(const Scene& scene, const RayPayload& rayPayload);
	private:
		std::shared_ptr<Image> m_FinalImage;
		uint32_t* m_ImageData = nullptr;
		RayPayload m_RayPayload;
	};
}