#include "vanLayer.h"

namespace van
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			delete gameObject;
			gameObject = nullptr;
		}
	}

	void Layer::Initialize()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			gameObject->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			gameObject->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			gameObject->LateUpdate();
		}
	}

	void Layer::Render()
	{
		//for (GameObject* gameObject : mGameObjects)
		//{
		//	gameObject->Render();
		//}

		for (GameObject* obj : mGameObjects)
		{
			if (obj->GetGameObjState() == GameObject::eState::Paused)
				continue;

			obj->Render();
		}

		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			if ((*iter)->GetGameObjState() == GameObject::eState::Dead)
			{
				GameObject* deadObj = *iter;
				delete deadObj;
				deadObj = nullptr;

				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		mGameObjects.push_back(gameObject);
	}

	void Layer::RemoveGameObjects()
	{
		mGameObjects.clear();
	}
}