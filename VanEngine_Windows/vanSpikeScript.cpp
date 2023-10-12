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

#include "..\\VanEngine_SOURCE\\vanPlayer.h"
#include "..\\VanEngine_SOURCE\\vanFloor.h"

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
		mTransform = GetOwner()->GetComponent<Transform>();
		mCollider = GetOwner()->GetComponent<Collider>();

		mCollider->SetScale(Vector3(0.125f * 0.5625, 0.05f, 1.f));

		mMesh = ResourceManager::Find<Mesh>(L"DeathBlockMesh");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");
	}

	void SpikeScript::Update()
	{
		Player* player = SceneManager::GetPlayer();
		Floor* owner = dynamic_cast<Floor*>(GetOwner());

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