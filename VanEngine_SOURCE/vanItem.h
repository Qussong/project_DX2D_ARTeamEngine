#pragma once
#include "vanGameObject.h"

namespace van
{
	class Item : public GameObject
	{
	public:
		Item();
		virtual ~Item();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class  Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		bool GetCollisionEnter() { return mbCollisionEnterFlag; }
		void SetCollisionEnter(bool flag) { mbCollisionEnterFlag = flag; }

	private:
		bool mbCollisionEnterFlag;
	};
}

