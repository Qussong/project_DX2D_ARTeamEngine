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
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.5f, 0.0f));
		player->GetComponent<PlayerScript>();
		//AddGameObject(player, LAYER::PLAYER);

		// Floor1
		for (size_t i = 0; i < 5; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP - 0.4f, -0.8f, 0.0f));
			AddGameObject(floor, LAYER::FLOOR);
		}

		

		// Collision Setting
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, true);
	}

	void Stage1::Update()
	{
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
