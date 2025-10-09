#pragma once

namespace Ry_App {

	class Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUIRender() {}
	};

}