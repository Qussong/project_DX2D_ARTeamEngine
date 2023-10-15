#include "vanStage1.h"
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
	Stage1::Stage1()
	{
		// nothing
	}

	Stage1::~Stage1()
	{
		// nothing
	}

	void Stage1::Initialize()
	{
		// Player
		Player* player = SceneManager::GetPlayer();
		player->GetComponent<Transform>()->SetPosition(Vector3(0.95f, 0.8f, 0.0f));
		player->GetComponent<PlayerScript>();

		// Floor1
		for (size_t i = 0; i < 5; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X + 0.68f, 0.5f, 0.0f));
			FloorScript* floorScript = floor->AddComponent<FloorScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}

		for (size_t i = 0; i < 2; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X + 0.54f, 0.5f, 0.0f));
			DisappearScript* disappearScript = floor->AddComponent<DisappearScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}

		for (size_t i = 0; i < 4; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(0.467f, i * GAP_Y + 0.5f, 0.0f));
			FloorScript* floorScript = floor->AddComponent<FloorScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}

		for (size_t i = 0; i < 9; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X, 0.0f, 0.0f));
			if (i % 2 == 0)
			{
				SpikeScript* spikeScript = floor->AddComponent<SpikeScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
			else
			{
				DisappearScript* disappearScript = floor->AddComponent<DisappearScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		for (size_t i = 0; i < 4; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(0.68f, i * GAP_Y + 0.0f, 0.0f));
			FloorScript* floorScript = floor->AddComponent<FloorScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}

		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(-GAP_X, 0.0f, 0.0f));
			JumpScript* jumpScript = floor->AddComponent<JumpScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}

		for (int i = 0; i < 3; i++)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(-GAP_X * 2, i * GAP_Y + 0.0f, 0.0f));
			FloorScript* jumpScript = floor->AddComponent<FloorScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}

		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(0.2f, 0.5f, 0.0f));
			StraightScript* straightScript = floor->AddComponent<StraightScript>();
			straightScript->SetDirection(StraightDir::Left);
			AddGameObject(floor, LAYER::FLOOR);
		}

		for (size_t i = 0; i < 5; ++i)
		{
			if (i == 4)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * -GAP_X - 0.2f, 0.4f, 0.0f));
				JumpScript* spikeScript = floor->AddComponent<JumpScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
			else
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * -GAP_X - 0.2f, 0.4f, 0.0f));
				SpikeScript* spikeScript = floor->AddComponent<SpikeScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(-0.486f, 0.9f, 0.0f));
			PortalInScript* portalInScript = floor->AddComponent<PortalInScript>();
			AddGameObject(floor, LAYER::FLOOR);

			portalInScript->SetOutPortalPos(Vector3(-0.886f, 0.7f, 0.0f));
		}

		for (size_t i = 0; i < 4; i++)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(-0.57f, i * GAP_Y + 0.5f, 0.0f));
			SpikeScript* spikeScript = floor->AddComponent<SpikeScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}

		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(-0.9f, 0.3f, 0.0f));
			StraightScript* straightScript = floor->AddComponent<StraightScript>();
			straightScript->SetDirection(StraightDir::Right);
			AddGameObject(floor, LAYER::FLOOR);
		}

		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(-0.35f, 0.125f, 0.0f));
			StraightScript* straightScript = floor->AddComponent<StraightScript>();
			straightScript->SetDirection(StraightDir::Left);
			AddGameObject(floor, LAYER::FLOOR);
		}

		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(-0.9f, 0.0f, 0.0f));
			StraightScript* straightScript = floor->AddComponent<StraightScript>();
			straightScript->SetDirection(StraightDir::Right);
			AddGameObject(floor, LAYER::FLOOR);
		}

		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(-0.23f, 0.0f, 0.0f));
			PortalInScript* portalInScript = floor->AddComponent<PortalInScript>();
			portalInScript->SetOutPortalPos(Vector3(-0.9f, -0.13f, 0.0f));
			AddGameObject(floor, LAYER::FLOOR);
		}

		for (size_t i = 0; i < 5; i++)
		{
			Item* item = new Item();
			item->GetComponent<Transform>()->SetPosition(Vector3(i * 0.3f - 0.53f, -0.13f, 0.0f));
			StarScript* starScript = item->AddComponent<StarScript>();
			AddGameObject(item, LAYER::ITEM);
		}

		for (size_t i = 0; i < 25; i++)
		{
			if (i == 24)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.95f, -0.3f, 0.0f));
				JumpScript* jumpScript = floor->AddComponent<JumpScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
			else
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.95f, -0.3f, 0.0f));
				SpikeScript* spikeScript = floor->AddComponent<SpikeScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		for (size_t i = 0; i < 6; i++)
		{
			if (i == 5)
			{
				Item* item = new Item();
				item->GetComponent<Transform>()->SetPosition(Vector3(0.8375f, i * GAP_Y - 0.3f, 0.0f));
				DoubleJumpScript* doubleJumpScript = item->AddComponent<DoubleJumpScript>();
				AddGameObject(item, LAYER::ITEM);
			}
			else
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(0.8475f, i * GAP_Y - 0.3f, 0.0f));
				SpikeScript* spikeScript = floor->AddComponent<SpikeScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		for (size_t i = 0; i < 9; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X + 0.2f, -0.8f, 0.0f));

			DisappearScript* disappearScript = floor->AddComponent<DisappearScript>();
			AddGameObject(floor, LAYER::FLOOR);

			if (i == 2)
			{
				Item* item = new Item;
				item->GetComponent<Transform>()->SetPosition(i* GAP_X + 0.15f, -0.7f, 0.0f);
				DoubleJumpScript* doubleJumpScript = item->AddComponent<DoubleJumpScript>();
				AddGameObject(item, LAYER::ITEM);
			}
		}

		for (size_t i = 0; i < 9; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.9f, -0.8f, 0.0f));

			DisappearScript* disappearScript = floor->AddComponent<DisappearScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}

		for (size_t i = 0; i < 4; ++i)
		{
			Item* item = new Item();
			item->GetComponent<Transform>()->SetPosition(i* 0.15f - 0.87f, -0.7f, 0.0f);
			StarScript* starScript = item->AddComponent<StarScript>();
			AddGameObject(item, LAYER::ITEM);
		}

		for (size_t i = 0; i < 4; ++i)
		{
			Item* item = new Item();
			item->GetComponent<Transform>()->SetPosition(i* 0.17f + 0.2f, -0.7f, 0.0f);
			StarScript* starScript = item->AddComponent<StarScript>();
			AddGameObject(item, LAYER::ITEM);
		}

		// Collision Setting
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, true);
	}

	void Stage1::Update()
	{
		int test = SceneManager::GetActiveScene()->GetStarCount();
		Scene::Update();
	}

	void Stage1::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Stage1::Render()
	{
		Scene::Render();
	}
}
