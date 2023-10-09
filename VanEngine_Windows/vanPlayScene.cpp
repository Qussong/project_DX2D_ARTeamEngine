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
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.6f, 0.0f));



		// FloorH1
		for (size_t i = 0; i < 5; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.4f, -0.8f, 0.0f));
			AddGameObject(floor, LAYER::FLOOR);
		}

		// FloorV
		for (size_t i = 0; i < 4; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(0.35f, i * GAP_Y - 0.8f, 0.0f));
			AddGameObject(floor, LAYER::FLOOR);
		}

		// FloorH2
		for (size_t i = 0; i < 3; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.8f, -0.3f, 0.0f));
			AddGameObject(floor, LAYER::FLOOR);
		}

		// FloorH3
		for (size_t i = 0; i < 3; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.3f, 0.2f, 0.0f));
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
