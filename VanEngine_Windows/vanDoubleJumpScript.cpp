#include "vanDoubleJumpScript.h"
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanTime.h"
#include "vanInput.h"

#include "vanCollider.h"
#include "vanRigidbody.h"
#include "vanMeshRenderer.h"
#include "vanResourceManager.h"
#include "vanConstantBuffer.h"
#include "vanRenderer.h"
#include "vanSceneManager.h"
#include "vanPlayer.h"

#define VELOCITY_X	3.f

namespace van
{
	DoubleJumpScript::DoubleJumpScript()
		: mSize(0.05f, 0.05f, 0.0f),
		mPosition(Vector3::Zero),
		mColor(Vector4(1.0f, 0.5f, 0.2f, 0.0f))
	{
	}

	DoubleJumpScript::~DoubleJumpScript()
	{
	}

	void DoubleJumpScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mCollider = GetOwner()->GetComponent<Collider>();
		mCollider->SetVisible(true);

		mSize = mTransform->GetScale();
		mSize += Vector3(0.02f, -0.05f, 0.0f); // GetOwner()의 사이즈 수정

		mMesh = ResourceManager::Find<Mesh>(L"CircleMesh");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");
	}

	void DoubleJumpScript::Update()
	{
	}

	void DoubleJumpScript::LateUpdate()
	{
	}

	void DoubleJumpScript::Render()
	{

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];

		renderer::TransformCB data = {};
		data.pos = mTransform->GetPosition();
		data.color = mColor;
		data.scale = mSize;
		cb->SetData(&data);



		cb->Bind(graphics::eShaderStage::VS);

		mShader->SetToplogy(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mShader->Update();
		mMesh->Render();
	}
}