#pragma once
#include "Engine.h"
#include <iostream>
#include "../Physics/Physics.h"
#include "../Renderer/Renderer.h"
#include "../Input/Input.h"
#include <assert.h>
#include "../Timing/TimingSystem.h"
#include "../GameObject/World.h"
#include "../GameObject/GameObjectFactory.h"
#include "../Math/Matrix4.h"


namespace Engine
{
	void UnitTest();
	
	bool Init(const HINSTANCE& i_hInstance, const int& i_nCmdShow) {

		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Dodge The Ball", -1, 800, 600);
		assert(bSuccess);
		CreateActorJobs();
		return bSuccess;
	}

	void Run() {
		
		Collision::Init();
		Renderer::Init();
		do {

			GLib::Service(ToQuit);

				int dir = Input::Read();
				float dt = TimingSystem::CalcTimeSinceLastCall();

				Physics::Run(dir, dt);
				Collision::Run(dt);
				Renderer::Draw();
				if (Engine::QuitRequested())
					break;
		} while (!ToQuit);
		
		//	GLib::Sprites::Release(pGoodGuy);
	}

	bool QuitRequested() {
		return ToQuit;
	}
	void Shutdown() {

		Physics::ShutDown();
		Renderer::ShutDown();
		Collision::ShutDown();
		World::Shutdown();
		GLib::Shutdown();
		
	}

	void RequestShutdown() {
		ToQuit = true;
	}
}

	