#pragma once
#include "vanScene.h"
#include "..\\VanEngine_SOURCE\\vanScene.h"

namespace van
{

	class Player;

	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();

		template <typename T>
		static bool CreateScene(const std::wstring name)
		{
			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);



			if (iter != mScenes.end())
				return false;


			T* scene = new T();
			scene->SetName(name);
			mScenes.insert(std::make_pair(name, scene));
			mActiveScene = scene;
			scene->Initialize();

			int tmep = mActiveScene->GetStarCount();
			return true;
		}

		template <typename T>
		static bool DeleteScene(const std::wstring name)
		{
			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);

			if (iter == mScenes.end())
				return false;


			delete iter->second;
			iter->second = nullptr;

			mScenes.erase(iter);

			


			return true;
		}
		static Scene* LoadScene(const std::wstring name);
		static Scene* GetActiveScene() { return mActiveScene; }

		static Player* GetPlayer() { return mPlayer; }

	private:
		//static Scene* mPlayScene;
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;
		static Player* mPlayer;
	};
}
