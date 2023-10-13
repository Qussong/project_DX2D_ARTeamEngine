#include "vanStage2.h"
#include "vanResourceManager.h"
#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanMeshRenderer.h"
#include "vanPlayerScript.h"
#include "vanRigidbody.h"
#include "vanCollisionManager.h"
#include "vanSceneManager.h"

#include "vanPlayer.h"
#include "vanFloor.h"
#include "vanItem.h"
#include "vanStarScript.h"
#include "vanFloorScript.h"
#include "vanSpikeScript.h"
#include "vanStraightScript.h"
#include "vanPortalInScript.h"
#include "vanJumpScript.h"
#include "vanDoubleJumpScript.h"
#include "vanDisappearScript.h"


#define GAP_X 0.0715f
#define GAP_Y 0.125f

namespace van
{
	Stage2::Stage2()
	{
		// nothing
	}

	Stage2::~Stage2()
	{
		// nothing
	}

	void Stage2::Initialize()
	{
		// Player
		Player* player = SceneManager::GetPlayer();
		player->GetComponent<Transform>()->SetPosition(Vector3(-0.95f, 0.8f, 0.0f));
		player->GetComponent<PlayerScript>();

		// Basic Floor 1F
		{
			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(-1.015f, i * GAP_Y + 0.65f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}


			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.95f, 0.65f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 5; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(.24f, i * GAP_Y + 0.5f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		// Straight
		{
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(-0.65f, 0.65f, 0.0f));
				StraightScript* straightScript = floor->AddComponent<StraightScript>();
				straightScript->SetDirection(StraightDir::Right);
				AddGameObject(floor, LAYER::FLOOR);
			}


			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(0.95f, 0.45f, 0.f));
				StraightScript* straightScript = floor->AddComponent<StraightScript>();
				straightScript->SetDirection(StraightDir::Left);
				AddGameObject(floor, LAYER::FLOOR);
			}
		}


		// Basic Floor 2F
		{
			for (size_t i = 0; i < 2; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.3f, -0.8f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}
		


		

		// Spike
		{
			for (size_t i = 0; i < 7; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.65f, 0.5f, 0.0f));
				SpikeScript* spikeScript = floor->AddComponent<SpikeScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 3; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X + 0.02f, 0.5f, 0.0f));
				SpikeScript* spikeScript = floor->AddComponent<SpikeScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.6f, i * GAP_Y - 0.8f, 0.0f));
				SpikeScript* spikeScript = floor->AddComponent<SpikeScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X + 0.4f, 0.35f, 0.0f));
				SpikeScript* spikeScript = floor->AddComponent<SpikeScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		// Portal
		{
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(-0.1f, 0.35f, 0.0f));
				PortalInScript* portalinScript = floor->AddComponent<PortalInScript>();
				portalinScript->SetOutPortalPos(Vector3(-0.95f, 0.3f, 0.f));
				AddGameObject(floor, LAYER::FLOOR);
			}

			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(0.9f, -0.8f, 0.0f));
				PortalInScript* portalinScript = floor->AddComponent<PortalInScript>();
				portalinScript->SetOutPortalPos(Vector3(0.95f, 0.8f, 0.f));
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		// Star
		{
			Item* item = new Item();
			item->GetComponent<Transform>()->SetPosition(Vector3(0.3f, 0.2f, 0.0f));
			StarScript* Script = item->AddComponent<StarScript>();
			AddGameObject(item, LAYER::ITEM);
		}


		// Jump 
		{
			for (size_t i = 0; i < 2; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X -0.95f, -0.8f, 0.0f));
				JumpScript* jumpScript = floor->AddComponent<JumpScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(-0.7f, -0.4f, 0.0f));
				JumpScript* jumpScript = floor->AddComponent<JumpScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(0.2f, -0.7f, 0.0f));
				JumpScript* jumpScript = floor->AddComponent<JumpScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		// Disappear
		{
			for (int i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X + 0.45f, i* GAP_Y -0.5f, 0.0f));
				DisappearScript* disappear = floor->AddComponent<DisappearScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		// Double Jump Item
		{
			Item* item = new Item();
			item->GetComponent<Transform>()->SetPosition(Vector3(-0.2f, -0.65f, 0.0f));
			DoubleJumpScript* Script = item->AddComponent<DoubleJumpScript>();
			AddGameObject(item, LAYER::ITEM);
		}

		// Collision Setting
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, true);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::ITEM, true);
	}

	void Stage2::Update()
	{
		int test = SceneManager::GetActiveScene()->GetStarCount();
		Scene::Update();
	}

	void Stage2::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Stage2::Render()
	{
		Scene::Render();
	}
}
