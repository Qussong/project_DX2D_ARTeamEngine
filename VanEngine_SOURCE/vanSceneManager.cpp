#include "vanSceneManager.h"
#include "vanResourceManager.h"
#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanMeshRenderer.h"
#include "vanPlayer.h"
#include "vanInput.h"
#include "..//VanEngine_Windows//vanStage1.h"
#include "..//VanEngine_Windows//vanStage2.h"
#include "..//VanEngine_Windows//vanStage3.h"
#include "..//VanEngine_Windows//vanStage4.h"


#include "vanRigidbody.h"
#include "vanCollider.h"
#include "..//VanEngine_Windows//vanPlayScene.h"
namespace van
{
	Scene* SceneManager::mActiveScene = nullptr;
	Player* SceneManager::mPlayer = new Player;

	std::map<std::wstring, Scene*> SceneManager::mScenes = {};

	void SceneManager::Initialize()
	{
		mPlayer->Initialize();
	}

	void SceneManager::Update()
	{
		//Player가 Dead면 레이어에서 제거후 다시 씬을만들어줌
		if (mPlayer->GetPlayerDeadCheck())				
		{
			mPlayer->GetComponent<Rigidbody>()->SetVelocity(Vector3::Zero);
			mPlayer->GetComponent<Rigidbody>()->SetGround(false);
			mPlayer->SetDoubleJumpCheck(false);

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
			else if (mActiveScene->GetName() == L"Stage3")
			{
				mActiveScene->RemoveLayer(enums::LAYER::PLAYER);
				mActiveScene->RemoveLayer(enums::LAYER::FLOOR);
				SceneManager::DeleteScene<Stage3>(L"Stage3");

				SceneManager::CreateScene<Stage3>(L"Stage3");

				LoadScene(L"Stage3");
				mPlayer->SetPlayerDeadCheck(false);
			}
			else if (mActiveScene->GetName() == L"Stage4")
			{
				mActiveScene->RemoveLayer(enums::LAYER::PLAYER);
				mActiveScene->RemoveLayer(enums::LAYER::FLOOR);
				SceneManager::DeleteScene<Stage4>(L"Stage4");
				SceneManager::CreateScene<Stage4>(L"Stage4");

				LoadScene(L"Stage4");
				mPlayer->SetPlayerDeadCheck(false);
			}
		}

		// 다음 스테이지 로드(Q버튼)
		if (mActiveScene->GetStarCount() <= 0 
			|| Input::GetKeyState(KEY_CODE::Q) == KEY_STATE::DOWN) 
		{
			// 플레이어 상태 초기화
			mPlayer->GetComponent<Rigidbody>()->SetVelocity(Vector3::Zero);
			mPlayer->GetComponent<Rigidbody>()->SetGround(false);
			mPlayer->SetDoubleJumpCheck(false);

			// 스테이지 클리어시 다음 스테이지 로드
			if (mActiveScene->GetName() == L"Stage1")				
			{
				mActiveScene->RemoveLayer(enums::LAYER::PLAYER);
				mActiveScene->RemoveLayer(enums::LAYER::FLOOR);

				LoadScene(L"Stage2");
			}
			else if (mActiveScene->GetName() == L"Stage2")
			{
				mActiveScene->RemoveLayer(enums::LAYER::PLAYER);
				mActiveScene->RemoveLayer(enums::LAYER::FLOOR);

				LoadScene(L"Stage3");
			}
			else if (mActiveScene->GetName() == L"Stage3")
			{
				mActiveScene->RemoveLayer(enums::LAYER::PLAYER);
				mActiveScene->RemoveLayer(enums::LAYER::FLOOR);
				LoadScene(L"Stage4");
			}
			else if (mActiveScene->GetName() == L"Stage4")
			{
				mActiveScene->RemoveLayer(enums::LAYER::PLAYER);
				mActiveScene->RemoveLayer(enums::LAYER::FLOOR);
				LoadScene(L"PlayScene");
			}
		}

		//  이전 스테이지 로드(W버튼)
		if (Input::GetKeyState(KEY_CODE::W) == KEY_STATE::DOWN)
		{
			// 플레이어 상태 초기화
			mPlayer->GetComponent<Rigidbody>()->SetVelocity(Vector3::Zero);
			mPlayer->GetComponent<Rigidbody>()->SetGround(false);
			mPlayer->SetDoubleJumpCheck(false);

			// 스테이지 클리어시 다음 스테이지 로드
			if (mActiveScene->GetName() == L"Stage2")
			{
				mActiveScene->RemoveLayer(enums::LAYER::PLAYER);
				mActiveScene->RemoveLayer(enums::LAYER::FLOOR);
				LoadScene(L"Stage1");
			}
			else if (mActiveScene->GetName() == L"Stage3")
			{
				mActiveScene->RemoveLayer(enums::LAYER::PLAYER);
				mActiveScene->RemoveLayer(enums::LAYER::FLOOR);
				LoadScene(L"Stage2");
			}
			else if (mActiveScene->GetName() == L"Stage4")
			{
				mActiveScene->RemoveLayer(enums::LAYER::PLAYER);
				mActiveScene->RemoveLayer(enums::LAYER::FLOOR);
				LoadScene(L"Stage3");
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
			mActiveScene->Initialize();
		}
		return iter->second;
	}
}
