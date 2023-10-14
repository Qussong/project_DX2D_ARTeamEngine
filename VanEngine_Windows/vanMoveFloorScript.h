#pragma once
#include "vanScript.h"

namespace van
{
	class Transform;
	class Collider;
	class Rigidbody;
	class Floor;

	using namespace math;

	class MoveFloorScript : public Script
	{
	public:
		MoveFloorScript();
		virtual ~MoveFloorScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void SetmMovingTime(float time) { mMovingTime = time; }		// 최대 이동 시간
		void SetDir(bool value) { mbGoLeft = value; }				// 진행 방향세팅 (기본 오른쪽)

	private:
		Transform* mFloorTransform;
		Collider* mFloorCollider;
		Rigidbody* mFloorRigidbody;

		Transform* mPlayerTransform;
		Collider* mPlayerCollider;
		Rigidbody* mPlayerRigidbody;

		Floor* mLeftfloor;
		Floor* mRightfloor;

		Vector3 mOwnerPos;
		Vector3 mLeftFloorPos;
		Vector3 mRightFloorPos;
		
		float mTime;
		float mMovingTime;
		bool mbGoLeft;
		
	};
}