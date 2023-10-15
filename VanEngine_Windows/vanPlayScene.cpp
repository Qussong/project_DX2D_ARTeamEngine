#include "vanPlayScene.h"
#include "vanResourceManager.h"
#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanMeshRenderer.h"
#include "vanPlayerScript.h"
#include "vanRigidbody.h"
#include "vanCollisionManager.h"
#include "vanSceneManager.h"
#include "vanScript.h"

#include "vanPlayer.h"
#include "vanFloor.h"
#include "vanFloorScript.h"
#include "vanJumpScript.h"
#include "vanDisappearScript.h"
#include "vanDoubleJumpScript.h"
#include "vanPortalOutScript.h"
#include "vanPortalInScript.h"
#include "vanStraightScript.h"
#include "vanSpikeScript.h"
#include "vanStarScript.h"
#include "vanItem.h"
#include "vanDisappearScript.h"

#define GAP_X 0.0715f
#define GAP_Y 0.125f

namespace van
{
	PlayScene::PlayScene()
	{

		// nothing
	}

	PlayScene::~PlayScene()
	{
		// nothing
	}

	void PlayScene::Initialize()
	{
		// Player
		Player* player = SceneManager::GetPlayer();
		player->GetComponent<Transform>()->SetPosition(Vector3(-0.3f, 0.6f, 0.0f));



		// FloorH1
		for (size_t i = 0; i < 10; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.35f, -0.8f, 0.0f));
			FloorScript* floorScript = floor->AddComponent<FloorScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}


		// E
		{
			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.7f, 6 * GAP_Y + 0.f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.7f, 3 * GAP_Y + 0.f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.7f, 0.f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 7; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(-0.7f, i* GAP_Y - 0.f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}
		
		// n
		{
			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(-0.2f, i * GAP_Y - 0.f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 5; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.2f, 3* GAP_Y+ 0.f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(4 * GAP_X - 0.2f, i * GAP_Y - 0.f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}


		// d
		{
			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(0.4f, i * GAP_Y - 0.f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X + 0.4f, 3 * GAP_Y + 0.f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X + 0.4f, 0.f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 7; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(3 * GAP_X + 0.4f, i * GAP_Y - 0.f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		

		// Star
		{
			Item* item = new Item();
			item->GetComponent<Transform>()->SetPosition(Vector3(0.5f, 0.2f, 0.0f));
			StarScript* Script = item->AddComponent<StarScript>();
			AddGameObject(item, LAYER::ITEM);
		}
	
	

	

		// Collision Setting
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, true);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::ITEM, true);
	}

	void PlayScene::Update()
	{
		int test = SceneManager::GetActiveScene()->GetStarCount();
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}
