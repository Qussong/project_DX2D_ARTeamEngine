#pragma once
#include "vanGameObject.h"



namespace van
{
	class Floor : public GameObject
	{
	public:
		Floor();
		virtual ~Floor();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class  Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		bool GetCollisionEnter() { return mbCollisionEnterFlag; }
		void SetCollisionEnter(bool flag) { mbCollisionEnterFlag = flag; }

		bool GetDoubleJumpFlag() { return mbDoubleJumpFlag; }
		void SetDoubleJumpFlag(bool flag) { mbDoubleJumpFlag = flag; }

	private:
		bool mbCollisionEnterFlag;
		bool mbDoubleJumpFlag;
	};
}

