#include "vanCollider.h"
#include "vanTransform.h"
#include "vanGameObject.h"


namespace van
{
	UINT Collider::mCollisionCount = 0;

	Collider::Collider()
		:Component(COMPONENTTYPE::COLLIDER)
		, mSize(Vector3::Zero)
		, mOffset(Vector3::Zero)
		, mCollisionNumber(-1)
		, mbIsCollision(false)
	{
		mCollisionNumber = mCollisionCount;
		mCollisionCount++;
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
		// 나중에 initial로
		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 pos = tr->GetPosition();

		//pos.x -= mSize.x / 2.0f;
		//pos.y -= mSize.y / 2.0f;

		//mPosition = pos;
	}

	void Collider::LateUpdate()
	{
	}

	void Collider::Render()
	{
		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 pos = tr->GetPosition();
		//mPosition = pos + mOffset;

		//pos.x -= mSize.x / 2.0f;
		//pos.y -= mSize.y / 2.0f;
		//pos.x += mOffset.x;
		//pos.y += mOffset.y;

		////pos = Camera::CalculatePosition(pos);

		//HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		//HPEN pen = NULL;
		//if (mbIsCollision)
		//{
		//	pen = CreatePen(PS_SOLID, 2, RGB(255, 50, 50));
		//}
		//else
		//{
		//	pen = CreatePen(PS_SOLID, 2, RGB(50, 255, 50));
		//}

		//HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		//Rectangle(hdc
		//	, pos.x, pos.y
		//	, pos.x + mSize.x, pos.y + mSize.y);

		//SelectObject(hdc, oldBrush);
		//DeleteObject(transparentBrush);

		//SelectObject(hdc, oldPen);
		//DeleteObject(pen);
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		mbIsCollision = true;
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		mbIsCollision = false;
		GetOwner()->OnCollisionExit(other);
	}
}
