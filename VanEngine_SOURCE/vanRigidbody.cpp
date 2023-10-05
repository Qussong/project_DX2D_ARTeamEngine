#include "vanRigidbody.h"
#include "vanTime.h"
#include "vanGameObject.h"
#include "vanTransform.h"

namespace van
{
	Rigidbody::Rigidbody()
		: Component(COMPONENTTYPE::RIGIDBODY)
		, mMass(1.0f)
		, mFriction(1.0f)
		, mbGround(false)
	{
		mLimitedVelocty.x = 2.0f;
		mLimitedVelocty.y = 100.0f;
		mGravity = Vector3(0.0f, 20.0f, 0.0f);
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::Update()
	{
		//이동
		// F = M x A
		// A = F / M
		mAccelation = mForce / mMass;

		// 속도에 가속도를 더한다
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// 땅위에 있을때
			Vector3 gravity = mGravity;
			gravity.Normalize();
			float dot = mVelocity.Dot(gravity);
			mVelocity += gravity * dot;
		}
		else
		{
			// 공중에 있을 때
			mVelocity -= mGravity * Time::DeltaTime();
		}


		// 최대 속도 제한
		Vector3 gravity = mGravity;
		gravity.Normalize();
		float dot = mVelocity.Dot(gravity);
		gravity = gravity * dot;

		Vector3 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocty.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitedVelocty.y;
		}

		if (mLimitedVelocty.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocty.x;
		}
		mVelocity = gravity + sideVelocity;

		//마찰력 조건 ( 적용된 힘이 없고, 속도가 0 이 아닐 )
		if (!(mVelocity == Vector3::Zero))
		{
			// 속도에 반대 방향으로 마찰력을 적용
			Vector3 friction = -mVelocity;
			friction.Normalize();
			friction = friction * mFriction * mMass * Time::DeltaTime();

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
			if (mVelocity.Length() < friction.Length())
			{
				// 속도를 0 로 만든다.
				mVelocity = Vector3(0.f, 0.f , 0.0f);
			}
			else
			{
				// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
				mVelocity += friction;
			}
		}


		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();	// ??
		tr->SetPosition(pos);
		//mForce.Clear();
		mForce = Vector3::Zero; // .clear
	}

	void Rigidbody::LateUpdate()
	{
	}

	void Rigidbody::Render()
	{

	}

}
