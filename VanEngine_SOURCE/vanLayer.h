#pragma once
#include "vanEntity.h"
#include "vanGameObject.h"

namespace van
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObject);
		void RemoveGameObjects();

		std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }

	private:
		std::vector<GameObject*> mGameObjects;
	};
}
