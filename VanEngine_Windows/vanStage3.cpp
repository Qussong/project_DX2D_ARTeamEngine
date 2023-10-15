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
#include "vanMoveFloorScript.h"
#include "vanStage3.h"


#define GAP_X 0.0715f
#define GAP_Y 0.125f

namespace van
{
	van::Stage3::Stage3()
	{
	}

	Stage3::~Stage3()
	{
	}

	void Stage3::Initialize()
	{
		Player* player = SceneManager::GetPlayer();
		player->GetComponent<Transform>()->SetPosition(Vector3(-0.8877f, 0.8f, 0.0f));
		player->GetComponent<PlayerScript>();

		//Floor 1F
		{
			for (size_t i = 0; i < 5; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(-0.9592f, i * GAP_Y + 0.5f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.8877f, 0.5f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 4; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(0.9592f, i * GAP_Y + 0.6f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 2; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X + 0.8162f, 0.6f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
			
			{
				Item* item = new Item();
				item->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.7f, 0.0f));
				StarScript* itemScript = item->AddComponent<StarScript>();
				AddGameObject(item, LAYER::FLOOR);
			}

			{
				Item* item = new Item();
				item->GetComponent<Transform>()->SetPosition(Vector3(1 * GAP_X + 0.8f, 0.6f + GAP_Y, 0.0f));
				StarScript* itemScript = item->AddComponent<StarScript>();
				AddGameObject(item, LAYER::FLOOR);
			}

			// Move floor
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(-0.45f, 0.5f, 0.0f));
				MoveFloorScript* MoveScript = floor->AddComponent<MoveFloorScript>();
				MoveScript->SetmMovingTime(13.0f);
				AddGameObject(floor, LAYER::FLOOR);
			}

			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(0.65f, 0.5f, 0.0f));
				DisappearScript* disappearScript = floor->AddComponent<DisappearScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		//Floor 2F
		{
			for (size_t i = 0; i < 17; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.9595f, 0.05f, 0.0f));
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 0; i < 17; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.9595f, 0.05f + GAP_Y, 0.0f));
				if (i == 16)
				{
					FloorScript* floorScript = floor->AddComponent<FloorScript>();
					Floor* floor2 = new Floor();
					floor2->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.9595f, 0.05f + GAP_Y * 2, 0.0f));
					SpikeScript* spikeScript = floor2->AddComponent<SpikeScript>();
					AddGameObject(floor2, LAYER::FLOOR);
				}
				else
					SpikeScript* floorScript = floor->AddComponent<SpikeScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(GAP_X + 0.8162f, 0.05f + GAP_Y , 0.0f));
				StraightScript* floorScript = floor->AddComponent<StraightScript>();
				floorScript->SetDirection(StraightDir::Left);
				AddGameObject(floor, LAYER::FLOOR);
			}

			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(17 * GAP_X - 0.9595f, 0.05f, 0.0f));
				PortalInScript* floorScript = floor->AddComponent<PortalInScript>();
				floorScript->SetOutPortalPos(Vector3(-0.9595f, 0.048f - GAP_Y, 0.0f));
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		//stair
		{
			for (size_t i = 0; i < 5; ++i)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.9595f, -0.95f + GAP_Y * i, 0.0f));
				if (i % 2 != 0)
				{
					SpikeScript* floorScript = floor->AddComponent<SpikeScript>();
				}
				else
				FloorScript* floorScript = floor->AddComponent<FloorScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(20 * GAP_X - 0.9595f, -1.0f + GAP_Y, 0.0f));
				StraightScript* floorScript = floor->AddComponent<StraightScript>();
				floorScript->SetDirection(StraightDir::Right);
				AddGameObject(floor, LAYER::FLOOR);
			}

			{
				Item* item = new Item();
				item->GetComponent<Transform>()->SetPosition(Vector3(4* GAP_X - 0.9595f, -0.95f + GAP_Y * 3, 0.0f));
				StarScript* itemScript = item->AddComponent<StarScript>();
				AddGameObject(item, LAYER::FLOOR);
			}

			{
				Item* item = new Item();
				item->GetComponent<Transform>()->SetPosition(Vector3(10 * GAP_X - 0.9595f, -0.95f + GAP_Y * 3, 0.0f));
				DoubleJumpScript* itemScript = item->AddComponent<DoubleJumpScript>();
				AddGameObject(item, LAYER::ITEM);
			}

			// Move floor
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(4 * GAP_X - 0.9595f, -1.0f + GAP_Y * 0.5 , 0.0f));
				MoveFloorScript* MoveScript = floor->AddComponent<MoveFloorScript>();
				MoveScript->SetmMovingTime(10.0f);
				AddGameObject(floor, LAYER::FLOOR);
			}
		}
		// Jump Floor
		{
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(0.65f, -0.7f, 0.0f));
				JumpScript* floorScript = floor->AddComponent<JumpScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(0.65f, 1 * GAP_Y - 0.7f, 0.0f));
				DisappearScript* disappearScript = floor->AddComponent<DisappearScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(0.65f, 2 * GAP_Y - 0.7f, 0.0f));
				DisappearScript* disappearScript = floor->AddComponent<DisappearScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(GAP_X + 0.8162f, -0.3, 0.0f));
				JumpScript* floorScript = floor->AddComponent<JumpScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			{
				Item* item = new Item();
				item->GetComponent<Transform>()->SetPosition(Vector3(GAP_X + 0.8162f, -1.0f + GAP_Y, 0.0f));
				StarScript* itemScript = item->AddComponent<StarScript>();
				AddGameObject(item, LAYER::FLOOR);
			}
		}


		// Collision Setting
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, true);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::ITEM, true);
	}

	void Stage3::Update()
	{
		int test = SceneManager::GetActiveScene()->GetStarCount();
		Scene::Update();
	}

	void Stage3::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Stage3::Render()
	{
		Scene::Render();
	}
}