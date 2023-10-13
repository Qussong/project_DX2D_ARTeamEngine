#include "vanDoubleJumpScript.h"
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
#include "vanFloor.h"

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
		mFloorTransform = GetOwner()->GetComponent<Transform>();
		mFloorCollider = GetOwner()->GetComponent<Collider>();
		mFloorRigidbody = GetOwner()->GetComponent<Rigidbody>();
		mFloorCollider->SetVisible(false);

		mPlayerTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
		mPlayerCollider = SceneManager::GetPlayer()->GetComponent<Collider>();
		mPlayerRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();

		mSize = mFloorTransform->GetScale();
		mSize += Vector3(0.02f, -0.05f, 0.0f); // GetOwner()의 사이즈 수정

		mMesh = ResourceManager::Find<Mesh>(L"CircleMesh");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");
	}

	void DoubleJumpScript::Update()
	{
		Player* player = SceneManager::GetPlayer();
		Floor* owner = dynamic_cast<Floor*>(GetOwner());

		if (owner->GetCollisionEnter())
		{
			player->SetDoubleJumpCheck(true);
			mFloorTransform->SetPosition(Vector3(10.0f, 10.0f, 0.0f));
		}
	}

	void DoubleJumpScript::LateUpdate()
	{
	}

	void DoubleJumpScript::Render()
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