#include "vanCollider.h"
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanConstantBuffer.h"
#include "vanRenderer.h"
#include "vanMeshRenderer.h"
#include "vanResources.h"


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

		mMesh = Resources::Find<Mesh>(L"CircleColliderMesh");
		mShader = Resources::Find<Shader>(L"TriangleShader2");

		//MeshRenderer* meshRenderer = new MeshRenderer;
		//meshRenderer->SetMesh(mMesh);
		//meshRenderer->SetShader(mShader);
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{

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
		//data.scale = mScale;
		data.scale = mSize;
		cb->SetData(&data);

		cb->Bind(graphics::eShaderStage::VS);

		mShader->SetToplogy(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		mShader->Update();
		mMesh->Render();

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
