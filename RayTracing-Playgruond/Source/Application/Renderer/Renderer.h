#pragma once

#include "Framework/Image.h"
#include <glm/glm.hpp>
#include <memory>

#include "Camera.h"
#include "Scene.h"

namespace Ry_App
{
	struct Ray
	{
		glm::vec3 Origin;
		glm::vec3 Direction;
	};

	struct HitPayload
	{
		float HitDistance;
		glm::vec3 WorldPosition;
		glm::vec3 WorldNormal;
		int ObjectIndex;
	};

	class Renderer
	{
	public:
		Renderer() = default;

		// Primary functions
		void OnResize(uint32_t width, uint32_t height);
		void Render(const Scene& scene, const Camera& camera);

		std::shared_ptr<Image> GetFinalImage() const { return m_FinalImage; }

		// Renderer states
		void ResetFrameIndex() { m_FrameIndex = 1; }
		int& GetRayBounces() { return m_RayBounces; }
		bool& GetReflectionState() { return m_Reflections; }
		bool& GetAccumulationState() { return m_Accumulate; }
	private:
		// "Shader" functions
		glm::vec4 RayGeneration(uint32_t x, uint32_t y);

		HitPayload TraceRay(const Ray& ray);
		HitPayload ClosestHit(const Ray& ray, float hitDistance, int objectIndex);
		HitPayload Miss(const Ray& ray);
	private:
		std::shared_ptr<Image> m_FinalImage;
		
		const Scene* m_ActiveScene = nullptr;
		const Camera* m_ActiveCamera = nullptr;
		uint32_t* m_ImageData = nullptr;
		glm::vec4* m_AccumulationData = nullptr;
		uint32_t m_FrameIndex = 1;

		int m_RayBounces = 5;
		bool m_Reflections = true;
		bool m_Accumulate = true;
	};
}