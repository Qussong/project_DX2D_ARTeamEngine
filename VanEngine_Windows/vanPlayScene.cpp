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
			tr->SetPosition(Vector3(0.5f, 1.0f, 0.0f));
			//tr->SetScale(Vector3(0.1f, 0.1f, 0.1f));
			tr->SetScale(Vector3(0.15f, 0.15f, 0.f));

			MeshRenderer* meshRenderer = player->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(Resources::Find<Mesh>(L"CircleMesh"));
			meshRenderer->SetShader(Resources::Find<Shader>(L"TriangleShader"));

			Rigidbody* rb = player->AddComponent<Rigidbody>();
			Collider* col = player->AddComponent<Collider>();
			col->SetSize(Vector3(0.15f, 0.15f, 0.f));
			col->SetPosition(tr->GetPosition());

			AddGameObject(player, LAYER::PLAYER);
			player->AddComponent<PlayerScript>();
			
			// Player
			//GameObject* object = new GameObject();
			//Transform* tr = object->AddComponent<Transform>();
			//tr->SetPosition(Vector3(0.5f, 1.0f, 0.0f));
			//tr->SetScale(Vector3(0.1f, 0.1f, 0.1f));

			//MeshRenderer* meshRenderer = object->AddComponent<MeshRenderer>();
			//meshRenderer->SetMesh(Resources::Find<Mesh>(L"CircleMesh"));
			//meshRenderer->SetShader(Resources::Find<Shader>(L"TriangleShader"));

			//Rigidbody* rb = object->AddComponent<Rigidbody>();
			//Collider* col = object->AddComponent<Collider>();
			//col->SetSize(Vector3(0.05f, 0.05f, 0.0f));
			//col->SetPosition(tr->GetPosition());

			//AddGameObject(object, LAYER::PLAYER);
			//object->AddComponent<PlayerScript>();

			//
			Floor* floor = new Floor();
			Transform* tr1 = floor->AddComponent<Transform>();
			tr1->SetPosition(Vector3(0.3f, -1.5f, 0.0f));
			tr1->SetScale(Vector3(0.5f, 0.25f, 0.5f));

			MeshRenderer* meshRenderer1 = floor->AddComponent<MeshRenderer>();
			meshRenderer1->SetMesh(Resources::Find<Mesh>(L"RectangleMesh"));
			meshRenderer1->SetShader(Resources::Find<Shader>(L"TriangleShader"));

			Collider* col1 = floor->AddComponent<Collider>();
			col1->SetSize(Vector3(50.0f, 0.25f, 0.0f));
			col1->SetPosition(tr1->GetPosition());

			AddGameObject(floor, LAYER::FLOOR);

			// Floor
			//GameObject* object1 = new GameObject();
			//Transform* tr1 = object1->AddComponent<Transform>();
			//tr1->SetPosition(Vector3(0.3f, -1.5f, 0.0f));
			//tr1->SetScale(Vector3(0.5f, 0.25f, 0.5f));

			//MeshRenderer* meshRenderer1 = object1->AddComponent<MeshRenderer>();
			//meshRenderer1->SetMesh(Resources::Find<Mesh>(L"RectangleMesh"));
			//meshRenderer1->SetShader(Resources::Find<Shader>(L"TriangleShader"));

			//Collider* col1 = object1->AddComponent<Collider>();
			//col1->SetSize(Vector3(0.5f, 0.25f, 0.0f));
			//col1->SetPosition(tr1->GetPosition());

			//AddGameObject(object1, LAYER::FLOOR);
			////object->AddComponent<PlayerScript2>();

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
