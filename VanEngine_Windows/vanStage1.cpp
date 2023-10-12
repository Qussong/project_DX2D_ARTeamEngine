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

#define GAP 0.0715f

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
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.6f, 0.0f));
		player->GetComponent<PlayerScript>();
		//AddGameObject(player, LAYER::PLAYER);

		// Floor1
		for (size_t i = 0; i < 10; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP - 0.4f, -0.8f, 0.0f));
			FloorScript* floorScript = floor->AddComponent<FloorScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}

		{
			Item* item = new Item();
			item->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.3f, 0.0f));
			StarScript* Script = item->AddComponent<StarScript>();
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
