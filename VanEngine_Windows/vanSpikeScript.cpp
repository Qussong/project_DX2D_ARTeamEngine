#include "vanSpikeScript.h"
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
#include "vanFloor.h"

#define VELOCITY_X	3.f

namespace van
{
	SpikeScript::SpikeScript()
		: mSize(0.1f * 0.5625f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mColor(Vector4(1.0f, 0.0f, 0.0f, 0.0f))
	{
	}

	SpikeScript::~SpikeScript()
	{
	}

	void SpikeScript::Initialize()
	{
		mFloorTransform = GetOwner()->GetComponent<Transform>();
		mFloorCollider = GetOwner()->GetComponent<Collider>();
		mFloorRigidbody = GetOwner()->GetComponent<Rigidbody>();

		mPlayerTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
		mPlayerCollider = SceneManager::GetPlayer()->GetComponent<Collider>();
		mPlayerRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();

		mFloorCollider->SetScale(Vector3(0.125f * 0.5625, 0.05f, 1.f));

		mMesh = ResourceManager::Find<Mesh>(L"DeathBlockMesh");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");
	}

	void SpikeScript::Update()
	{
		Player* player = SceneManager::GetPlayer();
		Floor* owner = dynamic_cast<Floor*>(GetOwner());

		// 플레이어 외에 다른 충돌가능한 객체 존재시 조건문 변경 필요
		// 조건문 변경하지 않으면 플레이어가 충돌하지 않아도 플레이어가 사망판정된다.
		if (owner->GetCollisionEnter())
		{
			player->SetPlayerDeadCheck(true);
		}
	}

	void SpikeScript::LateUpdate()
	{
		
	}

	void SpikeScript::Render()
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