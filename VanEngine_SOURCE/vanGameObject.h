#pragma once
#include "vanEntity.h"
#include "vanComponent.h"
#include "vanScript.h"


namespace van
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
			End,
		};

		friend static __forceinline void Destroy(GameObject* gameObject);

		GameObject();
		virtual ~GameObject();

		template <typename T>
		T* AddComponent()
		{
			T* component = new T();

			Component* comp = dynamic_cast<Component*>(component);
			if(comp != nullptr)
			{
				int myOrder = comp->GetUpdateOrder();
				mComponents[myOrder] = comp;
				mComponents[myOrder]->mOwner = this;

			}

			Script* script = dynamic_cast<Script*>(component);
			if(script != nullptr)
			{
				mScripts.push_back(script);
				script->SetOwner(this);
				script->Initialize();

			}
		
			return component;
		}



		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (auto c : mComponents)
			{
				component = dynamic_cast<T*>(c);

				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class  Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		eState GetGameObjState() { return mState; }
		//void Pause() { mState = eState::Paused; }
		//void Active() { mState = eState::Active; }

	private:
		void death() { mState = eState::Dead; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;
	};

	static __forceinline void Destroy(GameObject* gameObject)
	{
		gameObject->death();
	}
}
