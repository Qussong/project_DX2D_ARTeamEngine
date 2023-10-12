#pragma once
#include "vanComponent.h"


namespace van
{
	using namespace math;
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate()override;
		virtual void Render() override;

		void AddForce(Vector3 force) { mForce += force; }
		void AddVelocity(Vector3 velocity) { mVelocity += velocity; }
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool ground) { mbGround = ground; }
		Vector3 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector3 velocity) { mVelocity = velocity; }
		void SetFriction(float friction) { mFriction = friction; }

		void SetStraight(bool straight) { mbStraight = straight; }
		bool IsStraight() { return mbStraight; }

	private:
		float mMass;

		float mFriction;
		float mStaticFriction;
		float mKineticFrction;
		float mCoefficentFrction;

		Vector3 mForce;
		Vector3 mAccelation;
		Vector3 mVelocity;
		Vector3 mGravity;
		Vector3 mLimitedVelocty;

		bool mbGround;
		bool mbStraight;
	};
}
