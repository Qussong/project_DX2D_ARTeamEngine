#include "vanStraightScript.h"
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
	StraightScript::StraightScript()
		: mSize(0.1f * 0.5625f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mColor(Vector4(0.5f, 0.5f, 0.5f, 0.5f)),
		mDir(StraightDir::None),
		isSetDir(false),
		mbStraight(false)
	{
	}

	StraightScript::~StraightScript()
	{
	}

	void StraightScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mCollider = GetOwner()->GetComponent<Collider>();

		mSize = mTransform->GetScale();
		mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
		mColor = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
		mMesh = ResourceManager::Find<Mesh>(L"TriangleMeshL");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");

		
	}

	void StraightScript::Update()
	{
		Player* player = SceneManager::GetPlayer();
		Floor* owner = dynamic_cast<Floor*>(GetOwner());
	
		if (player->IsCollisionCheck() && mbStraight)
		{
			Rigidbody* rb = player->GetComponent<Rigidbody>();
			mbStraight = false;
			rb->SetStraight(false);
		}


		if (owner->GetCollisionEnter())
		{
			Transform* tr = player->GetComponent<Transform>();
			Rigidbody* rb = player->GetComponent<Rigidbody>();

			switch (mDir)
			{
			case van::enums::StraightDir::Left:
				tr->SetPosition(Vector3(mTransform->GetPosition().x - 0.07f, mTransform->GetPosition().y, 0.0f));
				rb->SetVelocity(Vector3(0.f));
				rb->SetStraight(true);
				mbStraight = true;
				break;
			case van::enums::StraightDir::Right:
				tr->SetPosition(Vector3(mTransform->GetPosition().x + 0.07f, mTransform->GetPosition().y, 0.0f));
				rb->SetVelocity(Vector3(0.f));
				rb->SetStraight(true);
				mbStraight = true;
				break;
			case van::enums::StraightDir::None:
				break;
			default:
				break;
			}
		}
	

		if (mbStraight)
		{
			Rigidbody* rb = player->GetComponent<Rigidbody>();

			switch (mDir)
			{
			case van::enums::StraightDir::Left:
				rb->AddVelocity(Vector3(-3.0f, 0.f, 0.f));
				break;
			case van::enums::StraightDir::Right:
				rb->AddVelocity(Vector3(3.0f, 0.f, 0.f));
				break;
			case van::enums::StraightDir::None:
				break;
			default:
				break;
			}
		}


		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::DOWN
			|| Input::GetKeyState(KEY_CODE::LEFT) == KEY_STATE::DOWN)
		{
			Rigidbody* rb = player->GetComponent<Rigidbody>();
			rb->SetStraight(false); 
			mbStraight = false;
		}

		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::DOWN
			|| Input::GetKeyState(KEY_CODE::RIGHT) == KEY_STATE::DOWN)
		{
			Rigidbody* rb = player->GetComponent<Rigidbody>();
			rb->SetStraight(false);
			mbStraight = false;
		}

		// 231010 
		// straight 스크립트 
		// 구조가 너무마음에 안든다.
		// 
		// 지금 짜인 구조는 조건문 마다 RigidBody를 새로 만들어서 값을 수정해주는것인데
		// 이렇게 짜여있는 이유는 straight스크립트가 여러개라고 가정했을때 update에서 RigidBody를 만들어주면
		// 충돌하지않은 straight floor도 rigid body값을 수정하여 이상하게 이동시키기때문이다.
		// 
		// 이런 기이한 구조가 나온이유는 
		// 1. 클래스의 경우 충돌이벤트와 동시에 충돌이벤트를 하며 받아온 충돌체만 영향을 주었지만 
		// 스크립트는 충돌이벤트가 아닌 update에서 할 수 밖에 없으니 이런것
		// 
		// 2. Movement와 control가 분리되지않음 -> 이동과 입력이 합쳐져있어 이동& 입력 관련 작업을 할때 난감하다.
		// 
		// 
		// 
			

		if (isSetDir == false)
		{
			if (mDir == StraightDir::Left)
			{
				mMesh = ResourceManager::Find<Mesh>(L"TriangleMeshL");
			}
			else if (mDir == StraightDir::Right)
			{
				mMesh = ResourceManager::Find<Mesh>(L"TriangleMeshR");
			}

			isSetDir = true;
		}

	}

	void StraightScript::LateUpdate()
	{
	}

	void StraightScript::Render()
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
	void StraightScript::Straight()
	{
		
	}
}