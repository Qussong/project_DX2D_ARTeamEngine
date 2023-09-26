#include "vanGameObject.h"
//#include "vanTransform.h"

namespace van
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		SetName(L"GameObject class");
		mComponents.resize(COMPONENTTYPE::END);
		//AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{

	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Initialize();
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;
			
			script->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->LateUpdate();
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->LateUpdate();
		}

	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render();
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Render();
		}
	}
}
