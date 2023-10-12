#pragma once
#include "..\\VanEngine_SOURCE\\vanSceneManager.h"
#include "vanPlayScene.h"
#include "vanStage1.h"


//#ifdef  _DEBUG
//#pragma comment(lib, "..\\x64\\Debug\\YamYamEngine_Windows.lib")
//#else
//#pragma comment(lib, "..\\x64\\Release\\YamYamEngine_Windows.lib")
//#endif //  _DEBUG

namespace van
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<Stage1>(L"stage1");

		SceneManager::LoadScene(L"PlayScene");
	}
}