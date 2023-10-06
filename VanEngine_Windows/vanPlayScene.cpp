#include "vanPlayScene.h"
#include "vanResources.h"
#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanMeshRenderer.h"
#include "vanPlayerScript.h"
#include "vanRigidbody.h"
#include "vanCollisionManager.h"

#include "vanPlayer.h"
#include "vanFloor.h"

namespace van
{
	PlayScene::PlayScene()
	{

	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{
		{
			Player* player = new Player();
			Transform* tr = player->AddComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.5f, 0.0f));
			tr->SetScale(Vector3(0.1f, 0.1f, 0.0f));

			MeshRenderer* meshRenderer = player->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(Resources::Find<Mesh>(L"CircleMesh"));
			meshRenderer->SetShader(Resources::Find<Shader>(L"TriangleShader"));

			Rigidbody* rb = player->AddComponent<Rigidbody>();
			Collider* col = player->AddComponent<Collider>();
			col->SetSize(Vector3(0.1f, 0.1f, 0.0f));
			col->SetPosition(tr->GetPosition());
			col->SetMesh(Resources::Find<Mesh>(L"CircleColliderMesh"));
			

			AddGameObject(player, LAYER::PLAYER);
			player->AddComponent<PlayerScript>();
			
		

			//
			Floor* floor = new Floor();
			Transform* tr1 = floor->AddComponent<Transform>();
			tr1->SetPosition(Vector3(0.0f, -1.0f, 0.0f));
			tr1->SetScale(Vector3(1.05f, 0.25f, 1.f));

			MeshRenderer* meshRenderer1 = floor->AddComponent<MeshRenderer>();
			meshRenderer1->SetMesh(Resources::Find<Mesh>(L"RectangleMesh"));
			meshRenderer1->SetShader(Resources::Find<Shader>(L"TriangleShader"));

			Collider* col1 = floor->AddComponent<Collider>();
			col1->SetSize(Vector3(1.f, 0.25f, 0.0f));
			col1->SetPosition(tr1->GetPosition());
			col1->SetMesh(Resources::Find<Mesh>(L"ColliderMesh"));

			AddGameObject(floor, LAYER::FLOOR);

		

			CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, true);
		}
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
