#include "vanStage4.h"
#include "vanPlayer.h"
#include "vanSceneManager.h"
#include "vanTransform.h"
#include "vanPlayerScript.h"
#include "vanCollisionManager.h"

#include "vanFloor.h"
#include "vanFloorScript.h"
#include "vanPortalInScript.h"
#include "vanPortalOutScript.h"
#include "vanDisappearScript.h"
#include "vanJumpScript.h"
#include "vanSpikeScript.h"
#include "vanStraightScript.h"

#include "vanItem.h"
#include "vanStarScript.h"
#include "vanDoubleJumpScript.h"


#define GAP_X 0.0715f
#define GAP_Y 0.125f

namespace van
{
	Stage4::Stage4()
	{
	}

	Stage4::~Stage4()
	{
	}

	void Stage4::Initialize()
	{
		// Player
		Player* player = SceneManager::GetPlayer();
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f + GAP_X * 0, 0.0f + GAP_Y * 1, 0.0f));
		player->GetComponent<PlayerScript>();

		// Basic Floor
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			floor->AddComponent<FloorScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}

		// Spike
		{
			Floor* floor1 = new Floor();
			floor1->GetComponent<Transform>()->SetPosition(Vector3(GAP_X * 1, GAP_Y * 0, 0.0f));
			floor1->AddComponent<SpikeScript>();
			AddGameObject(floor1, LAYER::FLOOR);

			Floor* floor2 = new Floor();
			floor2->GetComponent<Transform>()->SetPosition(Vector3(GAP_X * -1, GAP_Y * 0, 0.0f));
			floor2->AddComponent<SpikeScript>();
			AddGameObject(floor2, LAYER::FLOOR);

			for (size_t i = 4; i < 14; i++)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(GAP_X * -1 * i, GAP_Y * -6, 0.0f));
				floor->AddComponent<SpikeScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}
		}

		// Portal
		{
			Floor* portal1 = new Floor();
			portal1->GetComponent<Transform>()->SetPosition(Vector3(GAP_X * 5, GAP_Y * -7, 0.0f));
			PortalInScript* portalScript1 = portal1->AddComponent<PortalInScript>();
			portalScript1->SetOutPortalPos(Vector3(GAP_X * 6, GAP_Y * 7, 0.0f));
			AddGameObject(portal1, LAYER::FLOOR);

			Floor* portal2 = new Floor();
			portal2->GetComponent<Transform>()->SetPosition(Vector3(GAP_X * 6, GAP_Y * -7, 0.0f));
			PortalInScript* portalScript2 = portal2->AddComponent<PortalInScript>();
			portalScript2->SetOutPortalPos(Vector3(GAP_X * 0, GAP_Y * 7, 0.0f));
			AddGameObject(portal2, LAYER::FLOOR);
		}

		// PowerJump
		{
			Floor* floor1 = new Floor();
			floor1->GetComponent<Transform>()->SetPosition(Vector3(GAP_X * 10, GAP_Y * -7, 0.0f));
			floor1->AddComponent<JumpScript>();
			AddGameObject(floor1, LAYER::FLOOR);

			Floor* floor2 = new Floor();
			floor2->GetComponent<Transform>()->SetPosition(Vector3(GAP_X * 13, GAP_Y * -3, 0.0f));
			floor2->AddComponent<JumpScript>();
			AddGameObject(floor2, LAYER::FLOOR);
		}

		// Disappear
		{
			for (size_t i = 6; i < 8; i++)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(GAP_X * i, GAP_Y * 0, 0.0f));
				floor->AddComponent<DisappearScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			for (size_t i = 1; i < 8; i++)
			{
				Floor* floor = new Floor();
				floor->GetComponent<Transform>()->SetPosition(Vector3(0.0f - GAP_X * i * 2, GAP_Y * 2, 0.0f));
				floor->AddComponent<DisappearScript>();
				AddGameObject(floor, LAYER::FLOOR);
			}

			Floor* floor1 = new Floor();
			floor1->GetComponent<Transform>()->SetPosition(Vector3(GAP_X * -8, GAP_Y * 4, 0.0f));
			floor1->AddComponent<DisappearScript>();
			AddGameObject(floor1, LAYER::FLOOR);

			Floor* floor2 = new Floor();
			floor2->GetComponent<Transform>()->SetPosition(Vector3(GAP_X * -10, GAP_Y * 6, 0.0f));
			floor2->AddComponent<DisappearScript>();
			AddGameObject(floor2, LAYER::FLOOR);
		}

		// Straight
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(GAP_X,GAP_Y * -7, 0.0f));
			StraightScript* floorScript = floor->AddComponent<StraightScript>();
			floorScript->SetDirection(StraightDir::Left);
			AddGameObject(floor, LAYER::FLOOR);
		}

		// DoubleJump
		{
			Item* item1 = new Item();
			item1->GetComponent<Transform>()->SetPosition(Vector3(GAP_X * 6, GAP_Y * 1, 0.0f));
			item1->AddComponent<DoubleJumpScript>();
			AddGameObject(item1, LAYER::ITEM);

			Item* item2 = new Item();
			item2->GetComponent<Transform>()->SetPosition(Vector3(0.0f - GAP_X * 8, GAP_Y * 3, 0.0f));
			item2->AddComponent<DoubleJumpScript>();
			AddGameObject(item2, LAYER::ITEM);
		}

		// Star
		{
			Item* star1 = new Item();
			star1->GetComponent<Transform>()->SetPosition(Vector3(0.0f + GAP_X * -13, 0.0f + GAP_Y * 7, 0.0f));
			star1->AddComponent<StarScript>();
			AddGameObject(star1, LAYER::FLOOR);

			Item* star2 = new Item();
			star2->GetComponent<Transform>()->SetPosition(Vector3(0.0f + GAP_X * 13, 0.0f + GAP_Y * 3, 0.0f));
			star2->AddComponent<StarScript>();
			AddGameObject(star2, LAYER::FLOOR);

			Item* star3 = new Item();
			star3->GetComponent<Transform>()->SetPosition(Vector3(0.0f + GAP_X * -13, 0.0f + GAP_Y * -7, 0.0f));
			star3->AddComponent<StarScript>();
			AddGameObject(star3, LAYER::FLOOR);

			Item* star4 = new Item();
			star4->GetComponent<Transform>()->SetPosition(Vector3(0.0f + GAP_X * 10, 0.0f + GAP_Y * -6, 0.0f));
			star4->AddComponent<StarScript>();
			AddGameObject(star4, LAYER::FLOOR);
		}
		 
		// Collision Setting
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, true);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::ITEM, true);
	}

	void Stage4::Update()
	{
		int test = SceneManager::GetActiveScene()->GetStarCount();
		Scene::Update();
	}

	void Stage4::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Stage4::Render()
	{
		Scene::Render();
	}
}