#include "vanScene.h"

namespace van
{

	Scene::Scene()
		: mStarCount(NULL)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
		//mLayers.resize((UINT)LAYER::MAX);
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.LateUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}

	void Scene::AddGameObject(GameObject* gameObject, UINT layerIndex)
	{
		mLayers[layerIndex].AddGameObject(gameObject);
	}

	void  Scene::RemoveLayer(enums::LAYER type)
	{
		// 해당 레이어 안의 오브젝트를 삭제
		mLayers[(int)type].RemoveGameObjects();
	}
}