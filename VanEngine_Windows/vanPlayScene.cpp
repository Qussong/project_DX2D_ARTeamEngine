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
		player->AddComponent<PlayerScript>();
		AddGameObject(player, LAYER::PLAYER);

		// Floor1
		Floor* floor1 = new Floor();
		floor1->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.8f, 0.0f));
		AddGameObject(floor1, LAYER::FLOOR);

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
