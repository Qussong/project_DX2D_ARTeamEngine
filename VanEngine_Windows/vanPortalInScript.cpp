#include "vanPortalInScript.h"
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
#include "vanPortalOutScript.h"

#define VELOCITY_X	3.f

namespace van
{
	PortalInScript::PortalInScript()
		: mSize(0.1f * 0.5625f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mOutPortalPos(Vector3::Zero),
		mColor(Vector4(0.5f, 0.5f, 0.5f, 0.5f)),
		mbCreateOutPortal(true)
	{
	}

	PortalInScript::~PortalInScript()
	{
	}

	void PortalInScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mCollider = GetOwner()->GetComponent<Collider>();

		mSize = mTransform->GetScale();
		mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
		mMesh = ResourceManager::Find<Mesh>(L"CircleMesh");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");

	}

	void PortalInScript::Update()
	{
		Player* player = SceneManager::GetPlayer();
		Floor* owner = dynamic_cast<Floor*>(GetOwner());

		if (mbCreateOutPortal)
		{
			mbCreateOutPortal = false;
			Floor* Outfloor = new Floor();										// 아웃포탈 스크립트 사용에 필요한 기본바닥생성
			Transform* tr = Outfloor->GetComponent<Transform>();
			tr->SetPosition(owner->GetComponent<Transform>()->GetPosition());	// Out/In floor 위치일치

			if (mOutPortalPos == Vector3::Zero)					// OutPortal 위치 미지정
			{
				mOutPortalPos = tr->GetPosition();
				mOutPortalPos += Vector3(-0.25f, 0.f, 0.0f);	// OutPortal 기본위치
				tr->SetPosition(mOutPortalPos);					// 새로운 out위치에 floor/script 위치 조정
			}
			else // OutPortal 위치 지정
			{
				tr->SetPosition(mOutPortalPos);
			}
			PortalOutScript* outPortalScript = Outfloor->AddComponent<PortalOutScript>();
			SceneManager::GetActiveScene()->AddGameObject(Outfloor, LAYER::FLOOR);
		}

		if (owner->GetCollisionEnter())
		{
			owner->SetCollisionEnter(false);
			player->GetComponent<Transform>()->SetPosition(mOutPortalPos);
			player->SetCollisionCheck(false);
		}
	}

	void PortalInScript::LateUpdate()
	{
	}

	void PortalInScript::Render()
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