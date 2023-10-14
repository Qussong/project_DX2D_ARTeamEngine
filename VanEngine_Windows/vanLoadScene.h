#pragma once
#include "vanSceneManager.h"
#include "vanPlayScene.h"
#include "vanStage1.h"
#include "vanStage2.h"


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
		SceneManager::CreateScene<Stage1>(L"Stage1");
		SceneManager::CreateScene<Stage2>(L"Stage2");

		SceneManager::LoadScene(L"Stage1");
	}
}