#include "vanMoveFloorScript.h"
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanTime.h"
#include "vanInput.h"

#include "vanCollider.h"
#include "vanRigidbody.h"
#include "vanResourceManager.h"
#include "vanConstantBuffer.h"
#include "vanRenderer.h"
#include "vanSceneManager.h"
#include "vanPlayer.h"
#include "vanFloor.h"
#include "vanTime.h"
#include "vanFloorScript.h"

#define GAP_X 0.0715f
#define DelayTime 2.5f	// 타일 시작/최대지점 대기시간

namespace van
{
	MoveFloorScript::MoveFloorScript()
		: mTime(0.0f)
		, mMovingTime(5.0f)
		, mLeftfloor(nullptr)
		, mRightfloor(nullptr)
		, mOwnerPos(Vector3::Zero)
		, mLeftFloorPos(Vector3::Zero)
		, mRightFloorPos(Vector3::Zero)
		, mbGoLeft(false)
	{
	}

	MoveFloorScript::~MoveFloorScript()
	{
	}

	void MoveFloorScript::Initialize()	// 초기화때 다른 타일과 겹쳐질시 그려지지 않음 
	{
		mFloorTransform = GetOwner()->GetComponent<Transform>();
		mFloorCollider = GetOwner()->GetComponent<Collider>();
		mFloorRigidbody = GetOwner()->GetComponent<Rigidbody>();

		mPlayerTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
		mPlayerCollider = SceneManager::GetPlayer()->GetComponent<Collider>();
		mPlayerRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();

		// 중심 바닥
		FloorScript* floorScript = GetOwner()->AddComponent<FloorScript>();
		SceneManager::GetActiveScene()->AddGameObject(GetOwner(), LAYER::FLOOR);

		// 왼쪽 바닥
		mLeftfloor = new Floor();
		FloorScript* LeftfloorScript = mLeftfloor->AddComponent<FloorScript>();
		SceneManager::GetActiveScene()->AddGameObject(mLeftfloor, LAYER::FLOOR);
		mLeftFloorPos = mFloorTransform->GetPosition() - Vector3(GAP_X, 0.0f, 0.0f);
		mLeftfloor->GetComponent<Transform>()->SetPosition(mLeftFloorPos);

		// 오른쪽 바닥
		mRightfloor = new Floor();
		FloorScript* RightfloorScript = mRightfloor->AddComponent<FloorScript>();
		SceneManager::GetActiveScene()->AddGameObject(mRightfloor, LAYER::FLOOR);
		mRightFloorPos = mFloorTransform->GetPosition() + Vector3(GAP_X, 0.0f, 0.0f);
		mRightfloor->GetComponent<Transform>()->SetPosition(mRightFloorPos);
	}

	void MoveFloorScript::Update()
	{
		Floor* owner = dynamic_cast<Floor*>(GetOwner());
		mFloorTransform = owner->GetComponent<Transform>();
		Vector3 pos = mFloorTransform->GetPosition();

		mTime += Time::DeltaTime();
		if (mTime > DelayTime)
		{
			if (mTime < mMovingTime)	// 셋팅한 MovingTime 시간까지 이동(=최대이동시간)
			{
				if (mbGoLeft)
				{
					pos.x -= 0.08f * Time::DeltaTime();
					mFloorTransform->SetPosition(pos);

					mRightFloorPos = mFloorTransform->GetPosition() + Vector3(GAP_X, 0.0f, 0.0f);	// owner의 포지션 동기화
					mRightfloor->GetComponent<Transform>()->SetPosition(mRightFloorPos);

					mLeftFloorPos = mFloorTransform->GetPosition() - Vector3(GAP_X, 0.0f, 0.0f);
					mLeftfloor->GetComponent<Transform>()->SetPosition(mLeftFloorPos);
					pos.x += 0.08f * Time::DeltaTime();
				}
				else
				{
					pos.x += 0.08f * Time::DeltaTime();
					mFloorTransform->SetPosition(pos);

					mRightFloorPos = mFloorTransform->GetPosition() + Vector3(GAP_X, 0.0f, 0.0f);
					mRightfloor->GetComponent<Transform>()->SetPosition(mRightFloorPos);

					mLeftFloorPos = mFloorTransform->GetPosition() - Vector3(GAP_X, 0.0f, 0.0f);
					mLeftfloor->GetComponent<Transform>()->SetPosition(mLeftFloorPos);
				}
			}
			else // 최대 지점 도달시 방향 전환
			{
				mTime = 0.0f;
				if (mbGoLeft)
					mbGoLeft = false;
				else
					mbGoLeft = true;
			}
		}

	}

	void MoveFloorScript::LateUpdate()
	{
	}

	void MoveFloorScript::Render()
	{
	}

}