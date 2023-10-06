#include "vanSceneManager.h"
#include "vanResourceManager.h"
#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanMeshRenderer.h"
#include "vanPlayer.h"

#include "vanRigidbody.h"
#include "vanCollider.h"

namespace van
{
	//Scene* SceneManager::mPlayScene = nullptr;
	Scene* SceneManager::mActiveScene = nullptr;
	Player* SceneManager::mPlayer = new Player;

	std::map<std::wstring, Scene*> SceneManager::mScenes = {};

	void SceneManager::Initialize()
	{
		Transform* tr = mPlayer->AddComponent<Transform>();
		tr->SetPosition(Vector3(0.0f, 0.5f, 0.0f));
		tr->SetScale(Vector3(0.1f, 0.1f, 0.0f));

		MeshRenderer* meshRenderer = mPlayer->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"CircleMesh"));
		meshRenderer->SetShader(ResourceManager::Find<Shader>(L"PlayerShader"));
		Rigidbody* rb = mPlayer->AddComponent<Rigidbody>();

		Collider* col = mPlayer->AddComponent<Collider>();
		col->SetScale(Vector3(0.056f, 0.1f, 0.0f));
		col->SetPosition(tr->GetPosition());
		col->SetMesh(ResourceManager::Find<Mesh>(L"RectangleColliderMeesh"));
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}

	Scene* SceneManager::LoadScene(const std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene = iter->second;
		return iter->second;
	}
}
