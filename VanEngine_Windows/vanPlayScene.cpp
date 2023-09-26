#include "vanPlayScene.h"
#include "vanResources.h"
#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanMeshRenderer.h"
#include "vanPlayerScript.h"


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
			GameObject* object = new GameObject();
			Transform* tr = object->AddComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, -0.5f, 0.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 0.5f));

			MeshRenderer* meshRenderer = object->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(Resources::Find<Mesh>(L"RectangleMesh"));
			meshRenderer->SetShader(Resources::Find<Shader>(L"TriangleShader"));

			AddGameObject(object, LAYER::NONE);
			object->AddComponent<PlayerScript>();
			//object->AddComponent<PlayerScript2>();
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
