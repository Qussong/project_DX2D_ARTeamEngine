#pragma once
#include "vanGameObject.h"
#include "..//VanEngine_SOURCE//vanScene.h"

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

		bool GetPlayerDeadCheck() { return mbDead; }
		void SetPlayerDeadCheck(bool set) { mbDead = set; }

		bool IsCollisionCheck() { return mbCollisionCheck; }
		void SetCollisionCheck(bool value) { mbCollisionCheck = value; }

	private:

		Player* mPlayer;
		bool mbDead;
		bool mbCollisionCheck;
	};
}

