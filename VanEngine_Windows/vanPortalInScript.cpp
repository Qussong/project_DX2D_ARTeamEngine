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
		mTime(0.f),
		mbCreateOutPortal(true),
		mbReCreateOutPortal(false)
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

		mFloorCollider->SetVisible(false);
	}

	void PortalInScript::Update()
	{
		Player* player = SceneManager::GetPlayer();
		Floor* owner = dynamic_cast<Floor*>(GetOwner());

		// Out포탈 기본 생성
		if (mbCreateOutPortal)
		{
			mbCreateOutPortal = false;
			Floor* Outfloor = new Floor();										// 아웃포탈 스크립트 사용에 필요한 기본바닥생성
			mPotalOutTransform = Outfloor->GetComponent<Transform>();
			Outfloor->GetComponent<Collider>()->SetVisible(false);
			mPotalOutTransform->SetPosition(owner->GetComponent<Transform>()->GetPosition());	// Out/In floor 위치일치

			if (mOutPortalPos == Vector3::Zero)					// OutPortal 위치 미지정
			{
				mOutPortalPos = mPotalOutTransform->GetPosition();
				mOutPortalPos += Vector3(-0.25f, 0.f, 0.0f);	// OutPortal 기본위치
				mPotalOutTransform->SetPosition(mOutPortalPos);					// 새로운 out위치에 floor/script 위치 조정
			}
			else // OutPortal 위치 지정
			{
				mPotalOutTransform->SetPosition(mOutPortalPos);
			}
			PortalOutScript* outPortalScript = Outfloor->AddComponent<PortalOutScript>();
			SceneManager::GetActiveScene()->AddGameObject(Outfloor, LAYER::NONECOLLISION);
		}

		// Out포탈 재생성
		if (mbCreateOutPortal == false && mbReCreateOutPortal == true)
		{
			mbReCreateOutPortal = false;
			Floor* Outfloor = new Floor();										// 아웃포탈 스크립트 사용에 필요한 기본바닥생성
			mPotalOutTransform = Outfloor->GetComponent<Transform>();
			Outfloor->GetComponent<Collider>()->SetVisible(false);
			mPotalOutTransform->SetPosition(owner->GetComponent<Transform>()->GetPosition());	// Out/In floor 위치일치

			if (mOutPortalPos == Vector3::Zero)					// OutPortal 위치 미지정
			{
				mOutPortalPos = mPotalOutTransform->GetPosition();
				mOutPortalPos += Vector3(-0.25f, 0.f, 0.0f);	// OutPortal 기본위치
				mPotalOutTransform->SetPosition(mOutPortalPos);					// 새로운 out위치에 floor/script 위치 조정
			}
			else // OutPortal 위치 지정
			{
				mPotalOutTransform->SetPosition(mOutPortalPos);
			}
			PortalOutScript* outPortalScript = Outfloor->AddComponent<PortalOutScript>();
			SceneManager::GetActiveScene()->AddGameObject(Outfloor, LAYER::NONECOLLISION);
			outPortalScript->SetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));	// 없어졌을때 색상값(재생성시 시작컬러)
			outPortalScript->SetReCreate(true);							//Out스크립트에서 IncreaseColor()를 위한 조건
		}

		if (mTime != 0.0f)
		{
			mTime -= Time::DeltaTime();
			if (mTime <= 0.0f)
			{
				mTime = 0.0f;
				mbReCreateOutPortal = true;
			}
		}

		if (owner->GetCollisionEnter() && mTime == 0.0f)	// OutPortal이 없으면 InPortal 무시조건 mTime == 0.0f
		{
			owner->SetCollisionEnter(false);
			mPlayerTransform->SetPosition(mOutPortalPos);
			player->SetCollisionCheck(false);
			mTime = 2.0f;
		}
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