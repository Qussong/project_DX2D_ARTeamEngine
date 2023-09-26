#include "vanCollider.h"

namespace van
{
	Collider::Collider()
		: Component(COMPONENTTYPE::COLLIDER)
		, mSize(math::Vector2::Zero)			// 충돌체 기본크기 0
		, mOffset(math::Vector2::Zero)			// 객체의 중점으로부터 충돌체의 위치수정값
		, mPos(math::Vector2::Zero)				// 충돌체의 중심좌표 : (0,0)
		, mCollisionNum(-1)						// 이름 기본값 : -1
		, mbIsCollision(false)					// 충돌여부 기본값 : 비충돌상태
		, lineColor(RGB(50, 255, 50))			// 형광 초록색
		, collisionLineColor(RGB(255, 50, 50))	// 붉은색
		, inActiveLineColor(RGB(128, 128, 128))	// 회색
		, mbActive(true)
		, mbAffectedCamera(true)
	{
		SetName(L"Collider class");
		// 충돌체 Numbering : 0 ~ ...
		mCollisionNum = mCollisionCount;	// 충돌체가 생성되면 몇번째 충돌체인지 이름을 받고
		++mCollisionCount;					// 전체 충돌체의 개수를 하나 올려준다.
	}

	Collider::~Collider()
	{
		// nothing
	}

	void Collider::Initialize()
	{
		// nothing
	}

	void Collider::Update()
	{
	}

	void Collider::Render()
	{
	}

	void Collider::OnCollisionEnter(Collider* _other)
	{
	}

	void Collider::OnCollisionStay(Collider* _other)
	{
	}

	void Collider::OnCollisionExit(Collider* _other)
	{
	}
}