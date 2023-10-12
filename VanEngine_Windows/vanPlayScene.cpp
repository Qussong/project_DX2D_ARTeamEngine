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
#include "vanDoubleJumpScript.h"
#include "vanPortalOutScript.h"
#include "vanPortalInScript.h"
#include "vanStraightScript.h"
#include "vanSpikeScript.h"


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
			floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.4f, -0.8f, 0.0f));
			FloorScript* straightScript = floor->AddComponent<FloorScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}

		// FloorV
		for (size_t i = 0; i < 4; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(0.35f, i * GAP_Y - 0.8f, 0.0f));
			StraightScript* straightScript = floor->AddComponent<StraightScript>();
			straightScript->SetDirection(StraightDir::Right);
			AddGameObject(floor, LAYER::FLOOR);
		}

		//// FloorH2
		///*for (size_t i = 0; i < 1; ++i)
		//{*/
		//	Floor* floor = new Floor();
		//	floor->GetComponent<Transform>()->SetPosition(Vector3(0.f, -0.3f, 0.0f));
		//	StraightScript* straightScript = floor->AddComponent<StraightScript>();
		//	straightScript->SetDirection(StraightDir::Left);
		//	AddGameObject(floor, LAYER::FLOOR);
		////}

		// FloorH3
		//for (size_t i = 0; i < 3; ++i)
		//{
		//	Floor* floor = new Floor();
		//	floor->GetComponent<Transform>()->SetPosition(Vector3(i * GAP_X - 0.5f, -0.5f, 0.0f));
		//	SpikeScript* straightScript = floor->AddComponent<SpikeScript>();
		//	AddGameObject(floor, LAYER::FLOOR);
		//}

		for (size_t i = 1; i < 3; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(0.15f, i * GAP_Y - 0.8f, 0.0f));
			PortalInScript* portalinScript = floor->AddComponent<PortalInScript>();
			portalinScript->SetOutPortalPos(Vector3(-0.5f, i * GAP_Y - 0.8f, 0.f));
			AddGameObject(floor, LAYER::FLOOR);
		}

		for (size_t i = 0; i < 4; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(0.0f, i * GAP_Y, 0.0f));
			JumpScript* jumpScript = floor->AddComponent<JumpScript>();
			AddGameObject(floor, LAYER::FLOOR);
		}

		//for (size_t i = 0; i < 4; ++i)
		//{
		//	Floor* floor = new Floor();
		//	floor->GetComponent<Transform>()->SetPosition(Vector3(0.55f, i * GAP_Y - 0.8f, 0.0f));
		//	PortalOutScript* straightScript = floor->AddComponent<PortalOutScript>();
		//	AddGameObject(floor, LAYER::FLOOR);
		//}


		for (size_t i = 0; i < 4; ++i)
		{
			Floor* floor = new Floor();
			floor->GetComponent<Transform>()->SetPosition(Vector3(0.75f, i * GAP_Y - 0.8f, 0.0f));
			DoubleJumpScript* straightScript = floor->AddComponent<DoubleJumpScript>();
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
