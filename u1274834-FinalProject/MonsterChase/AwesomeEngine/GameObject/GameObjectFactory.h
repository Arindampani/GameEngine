#pragma once
#include "../Containers/Pointers.h"
#include "GameObject.h"
#include "nlohmann/json.hpp"
#include "World.h"
#include "../Renderer/Renderer.h"
#include "../Physics/Physics.h"
#include "../File/LoadFileToBuffer.h"
#include <assert.h>
#include "..//AwesomeEngine/JobSystem/JobSystem.h"
#include "../AwesomeEngine/Syncronization/ScopeLock.h"
#include "../Collision/Collision.h"

#include <future>


static std::mutex s_JsonMutex;
std::vector<std::future<void>> m_futures;

namespace Engine {

	std::vector<GameObject*> NewGameObjects;
	Engine::Mutex NewGameObjectMutex;
	void CreateActor(const char* i_pScriptFilename);

	void operator<<(Vector3& vec, nlohmann::json& json_obj) {

		assert(json_obj.is_array() && json_obj.size() == 3);

		vec.x(json_obj[0]);
		vec.y(json_obj[1]);
		vec.z(json_obj[2]);
	}


	void CreateActorJobs()
	{


		m_futures.push_back(std::async(std::launch::async, CreateActor, "data\\player.json"));
		m_futures.push_back(std::async(std::launch::async, CreateActor, "data\\Enemy.json"));
		m_futures.push_back(std::async(std::launch::async, CreateActor, "data\\Enemy1.json"));
		m_futures.push_back(std::async(std::launch::async, CreateActor, "data\\Enemy2.json"));
		m_futures.push_back(std::async(std::launch::async, CreateActor, "data\\Enemy3.json"));
		m_futures.push_back(std::async(std::launch::async, CreateActor, "data\\Enemy4.json"));
		m_futures.push_back(std::async(std::launch::async, CreateActor, "data\\Enemy5.json"));
		//m_futures.push_back(std::async(std::launch::async, CreateActor, "data\\background.json"));
		m_futures.push_back(std::async(std::launch::async, CreateActor, "data\\OOB-Bottom.json"));

	}

	void CreateStartUpJobs() {
		m_futures.push_back(std::async(std::launch::async, CreateActor, "data\\background.json"));
		m_futures.push_back(std::async(std::launch::async, CreateActor, "data\\startMenu.json"));

	}
	void CreateActor(const char* i_pScriptFilename) {

		using json = nlohmann::json;

		std::lock_guard<std::mutex> lock(s_JsonMutex);

		std::vector<uint8_t> PlayerData = LoadFileToBuffer(i_pScriptFilename);
		if (!PlayerData.empty())
		{
			json PlayerJSON = json::parse(PlayerData);

			std::string Name = PlayerJSON["name"];

			Vector3 InitialPosition(0.0f, 0.0f, 0.0f);
			Vector3 InitialVelocity(0.0f, 0.0f, 0.0f);
			Vector3 InitialRotation(0.0f, 0.0f, 0.0f);
			float mass = 0.0f;



			if (PlayerJSON.contains("initial_position"))
			InitialPosition << PlayerJSON["initial_position"];

			if (PlayerJSON.contains("initial_velocity"))
			InitialVelocity << PlayerJSON["initial_velocity"];

			if (PlayerJSON.contains("initial_rotation"))
			InitialRotation << PlayerJSON["initial_rotation"];
			if (PlayerJSON.contains("mass")) {
				assert(PlayerJSON["mass"].is_number_float());
				mass =  PlayerJSON["mass"];
			}







			SmartPointer<GameObject> newGameObject = SmartPointer<GameObject>(new GameObject(InitialPosition, InitialVelocity, InitialRotation, mass,Name));

			AddGameObjectToWorld(newGameObject);

			if (PlayerJSON.contains("physics_data")) {

				float mass =  0.0f;
				float kd = 0.0f;
				bool hasGravity = false;
				bool isControllable = false;
				if (PlayerJSON.contains("physics_data")) {

					assert(PlayerJSON["physics_data"]["mass"].is_number_float());
					assert(PlayerJSON["physics_data"]["kd"].is_number_float());
					assert(PlayerJSON["physics_data"]["hasGravity"].is_boolean());
					assert(PlayerJSON["physics_data"]["isControllable"].is_boolean());

					mass = PlayerJSON["physics_data"]["mass"];
					kd = PlayerJSON["physics_data"]["kd"];
					hasGravity = PlayerJSON["physics_data"]["hasGravity"];
					isControllable = PlayerJSON["physics_data"]["isControllable"];

				}

				Physics::AddMovable(newGameObject, mass, kd, hasGravity, isControllable);
			}

			if (PlayerJSON.contains("collision_data")) {

				Vector3 offset(0.0f,0.0f,0.0f);
				Vector3 extents(0.0f, 0.0f, 0.0f);
				if (PlayerJSON.contains("collision_data")) {
					
					offset << PlayerJSON["collision_data"]["offset"];
					extents << PlayerJSON["collision_data"]["extents"];
				}
				Collision::AddCollidable(newGameObject,offset,extents);
			}

			if (PlayerJSON.contains("components"))
			{
				assert(PlayerJSON["components"].is_object());

				for (json::iterator it = PlayerJSON["components"].begin(); it != PlayerJSON["components"].end(); ++it)
				{
					const std::string& ComponentName = it.key();

					//auto ComponentCreator = ComponentCreators.find(ComponentName);
					//if (ComponentCreator != ComponentCreators.end())
					//{
					//	ComponentCreator->second(Dummy, it.value());
					//}
				}

			}
			if (PlayerJSON.contains("render_data")) {

				assert(PlayerJSON["render_data"]["sprite"].is_string());

				std::string Sprite = PlayerJSON["render_data"]["sprite"];

				Renderer::AddRenderable(newGameObject, Sprite);

			}

		}
	}


	
}

