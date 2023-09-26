#include "vanRigidBody.h"
#include "vanTransform.h"
#include "vanTime.h"

namespace van
{
	RigidBody::RigidBody()
		: Component(COMPONENTTYPE::RIGIDBODY)
		, mMass(1.0f)
		, mFriction(15.0f)
		, mForce(math::Vector2::Zero)
		, mAccelation(math::Vector2::Zero)
		, mVelocity(math::Vector2::Zero)
		, mGravity(math::Vector2(0.0f, 0.0f))	// 값 설정해줘야 한다.
		, mLimitedVelocity(math::Vector2(0.0f, 0.0f))	// 값 설정 해줘야 한다.
		, mbGround(false)
	{
		SetName(L"RigidBody class");
	}

	RigidBody::~RigidBody()
	{
		// nothing
	}

	void RigidBody::Initialize()
	{
		// nothing
	}

	void RigidBody::Update()
	{
		mAccelation = mForce / mMass;	// F = m * a -> a = F / m
		mVelocity += mAccelation * Time::DeltaTime();	// v1 = v0 + at

		if (mbGround)					// y축 값 작용 x
		{
			math::Vector2 gravity = mGravity;			// 중력 초기값 -> x = 0, y = 980
			gravity.Normalize();						// 중력 -> x = 0, y = 1
			float dot = mVelocity.Dot(gravity);			
			math::Vector2 vel = gravity * dot;
			mVelocity -= vel;							
		}
		else
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		// 최대 속도 제한
		math::Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = mVelocity.Dot(gravity);
		gravity = gravity * dot;
		math::Vector2 sideVelocity = mVelocity - gravity;

		if (mLimitedVelocity.y < gravity.Length())			// y방향 속도가 y방향 제한속도보다 클때
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.Length())		// x방향 속도가 x방향 제한속도보다 클때
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		// 마찰력
		bool noSpeed = (mVelocity == math::Vector2::Zero);
		if (!noSpeed)	// 속도 0이 아닐 경우
		{
			math::Vector2 friction = -mVelocity;	// 속도의 반대 방향으로 마찰력 작용
			friction.Normalize();
			friction = friction * mFriction * mMass * Time::DeltaTime();	// 마찰력 = 마찰력 계수 * 무게

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
			if (mVelocity.Length() < friction.Length())
			{
				// 속도를 0 로 만든다.
				mVelocity = math::Vector2(0.0f, 0.0f);
			}
			else
			{
				// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
				// 마찰력은 속도의 반대방향이기에 '+' 한다.
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();	// 해당 부분 때문에 GameObject 의 생성자에서 Transform 추가해줌
		math::Vector3 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();	// Vector3 + Vector2 * float 인데 정상적인 값이 반환될지 모르겠다.
		tr->SetPosition(pos);
		//mForce.Clear();	// 이거 왜 해주는거지? 마지막에 힘을 왜 없애?
	}

	void RigidBody::Render()
	{
		// nothing
	}
}