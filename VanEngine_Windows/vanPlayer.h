#pragma once
#include "vanGameObject.h"

namespace van
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class  Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:

	};
}

