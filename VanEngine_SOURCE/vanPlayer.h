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

		PlayerDir GetPlayerDir() { return mPlayerDir; }
		void SetPlayerDir(PlayerDir dir) { mPlayerDir = dir; }

		bool GetDoubleJumpCheck() { return mbDoubleJumpCheck; }
		void SetDoubleJumpCheck(bool value) { mbDoubleJumpCheck = value; }

	private:

		Player* mPlayer;
		bool mbDead;
		bool mbCollisionCheck;
		bool mbDoubleJumpCheck;
		PlayerDir mPlayerDir;
		Collider* mCollisionOther;
	};
}

