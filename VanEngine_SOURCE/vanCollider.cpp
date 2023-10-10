#include "vanCollider.h"
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanConstantBuffer.h"
#include "vanRenderer.h"
#include "vanMeshRenderer.h"
#include "vanResourceManager.h"

#include "vanTime.h"

namespace van
{
	UINT Collider::mCollisionCount = 0;

	Collider::Collider()
		:Component(COMPONENTTYPE::COLLIDER)
		, mSize(Vector3::Zero)
		, mOffset(Vector3::Zero)
		, mCollisionNumber(-1)
		, mbIsCollision(false)
		, mColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f))
		, mbColorFlag(false)
		, mbVisible(true)
	{
		mCollisionNumber = mCollisionCount;
		mCollisionCount++;

		mMesh = ResourceManager::Find<Mesh>(L"RectangleColliderMesh");
		mShader = ResourceManager::Find<Shader>(L"TriangleColShader");
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
		// Collider Color Change
		if (mbColorFlag)
			SmoothDecreaseColor();
	}

	void Collider::LateUpdate()
	{
	}

	void Collider::Render()
	{
		// 상수버퍼설정
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];

		renderer::TransformCB data = {};
		data.pos = mPosition;
		data.color = mColor;
		data.scale = mSize;
		cb->SetData(&data);

		cb->Bind(graphics::eShaderStage::VS);

		if (mbVisible)
		{
			mShader->SetToplogy(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

			mShader->Update();
			mMesh->Render();
		}

	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		mbIsCollision = true;
		GetOwner()->OnCollisionEnter(other);

		mColor = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		mbIsCollision = false;
		GetOwner()->OnCollisionExit(other);

		mbColorFlag = true;
	}

	void Collider::SmoothDecreaseColor()
	{
		mColor -= (Vector4(0.0f, 0.9f, 0.0f, 0.0f) * Time::DeltaTime());
		if (mColor == Vector4::Zero)
			mbColorFlag = false;
	}
}
