#include "vanPortalInScript.h"
#include "vanTransform.h"
#include "vanGameObject.h"
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
	PortalInScript::PortalInScript()
		: mSize(0.1f * 0.5625f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mColor(Vector4(0.5f, 0.5f, 0.5f, 0.5f))
	{
	}

	PortalInScript::~PortalInScript()
	{
	}

	void PortalInScript::Initialize()
	{
		mFloorTransform = GetOwner()->GetComponent<Transform>();
		mFloorCollider = GetOwner()->GetComponent<Collider>();
		mFloorRigidbody = GetOwner()->GetComponent<Rigidbody>();

		mPlayerTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
		mPlayerCollider = SceneManager::GetPlayer()->GetComponent<Collider>();
		mPlayerRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();

		mSize = mFloorTransform->GetScale();
		mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
		mMesh = ResourceManager::Find<Mesh>(L"CircleMesh");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");

	}

	void PortalInScript::Update()
	{
	}

	void PortalInScript::LateUpdate()
	{
	}

	void PortalInScript::Render()
	{

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];

		renderer::TransformCB data = {};
		data.pos = mFloorTransform->GetPosition();
		data.color = mColor;
		data.scale = mSize;
		cb->SetData(&data);



		cb->Bind(graphics::eShaderStage::VS);

		mShader->SetToplogy(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mShader->Update();
		mMesh->Render();
	}
}