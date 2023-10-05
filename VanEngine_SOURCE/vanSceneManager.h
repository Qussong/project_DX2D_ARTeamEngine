#pragma once
#include "vanScene.h"

namespace van
{
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
			mScenes.insert(std::make_pair(name, scene));
			scene->Initialize();

			return true;
		}
		static Scene* LoadScene(const std::wstring name);
		static Scene* GetActiveScene() { return mActiveScene; }

	private:
		//static Scene* mPlayScene;
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;
	};
}
