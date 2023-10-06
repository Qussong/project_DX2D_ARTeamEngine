#include "vanPlayScene.h"
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

#define GAP 0.142f

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
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.6f, 0.0f));
		player->AddComponent<PlayerScript>();
		AddGameObject(player, LAYER::PLAYER);

		// Floor1
		for (size_t i = 0; i < 5; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP - 0.4f, -0.8f, 0.0f));
			AddGameObject(floor, LAYER::FLOOR);
		}

		// Floor2L
		for (size_t i = 0; i < 3; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP - 0.8f, -0.3f, 0.0f));
			AddGameObject(floor, LAYER::FLOOR);
		}

		// Floor2R
		for (size_t i = 0; i < 3; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP + 0.4f, -0.3f, 0.0f));
			AddGameObject(floor, LAYER::FLOOR);
		}

		// Floor3
		for (size_t i = 0; i < 3; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP - 0.2f, 0.2f, 0.0f));
			AddGameObject(floor, LAYER::FLOOR);
		}


		// Collision Setting
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, true);
	}

	void PlayScene::Update()
	{
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
