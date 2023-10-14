#include "vanSceneManager.h"
#include "vanResourceManager.h"
#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanMeshRenderer.h"
#include "vanPlayer.h"
#include "vanInput.h"
#include "..//VanEngine_Windows//vanStage1.h"
#include "..//VanEngine_Windows//vanStage2.h"


#include "vanRigidbody.h"
#include "vanCollider.h"
#include "..//VanEngine_Windows//vanPlayScene.h"
namespace van
{
	//Scene* SceneManager::mPlayScene = nullptr;
	Scene* SceneManager::mActiveScene = nullptr;
	Player* SceneManager::mPlayer = new Player;

	std::map<std::wstring, Scene*> SceneManager::mScenes = {};

	void SceneManager::Initialize()
	{
		mPlayer->Initialize();
	}

	void SceneManager::Update()
	{
		if (mPlayer->GetPlayerDeadCheck())
		{
			if (mPlayer->GetDoubleJumpCheck())
			{
				mPlayer->GetComponent<Transform>()->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
				mPlayer->SetDoubleJumpCheck(false);
			}

			if (mActiveScene->GetName() == L"PlayScene")
			{
				mActiveScene->RemoveLayer(enums::LAYER::PLAYER);
				mActiveScene->RemoveLayer(enums::LAYER::FLOOR);
				SceneManager::DeleteScene<PlayScene>(L"PlayScene");

				SceneManager::CreateScene<PlayScene>(L"PlayScene");

				LoadScene(L"PlayScene");
				mPlayer->SetPlayerDeadCheck(false);
			}
			else if (mActiveScene->GetName() == L"Stage1")
			{
				mActiveScene->RemoveLayer(enums::LAYER::PLAYER);
				mActiveScene->RemoveLayer(enums::LAYER::FLOOR);
				SceneManager::DeleteScene<Stage1>(L"Stage1");

				SceneManager::CreateScene<Stage1>(L"Stage1");

				LoadScene(L"Stage1");
				mPlayer->SetPlayerDeadCheck(false);
			}
			else if (mActiveScene->GetName() == L"Stage2")
			{
				mActiveScene->RemoveLayer(enums::LAYER::PLAYER);
				mActiveScene->RemoveLayer(enums::LAYER::FLOOR);
				SceneManager::DeleteScene<Stage2>(L"Stage2");

				SceneManager::CreateScene<Stage2>(L"Stage2");

				LoadScene(L"Stage2");
				mPlayer->SetPlayerDeadCheck(false);
			}
			
		}

		if (mActiveScene->GetStarCount() <= 0)
		{

			if (mActiveScene->GetName() == L"PlayScene")
			{
				LoadScene(L"Stage1");
			}
			if (mActiveScene->GetName() == L"Stage1")
			{
				LoadScene(L"Stage2");
			}
			if (mActiveScene->GetName() == L"Stage2")
			{
				LoadScene(L"PlayScene");
			}
		}

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

		if (mActiveScene != nullptr)
		{
			mActiveScene->AddGameObject(mPlayer, LAYER::PLAYER);
		}
		return iter->second;
	}


}
