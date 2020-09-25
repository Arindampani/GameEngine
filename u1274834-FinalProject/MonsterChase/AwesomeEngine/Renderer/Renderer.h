#pragma once
#include "../GameObject/GameObject.h"
#include "GLib.h"
#include <string>
namespace Engine {
	namespace Renderer
	{
		void Init();
		void Draw();
		void ShutDown();
		void AddRenderable(const SmartPointer<GameObject>& i_GameObject, const std::string& i_pFilename);
		void RemoveRenderable(WeakPointer<GameObject>& i_NewGameObject);

	};
}

