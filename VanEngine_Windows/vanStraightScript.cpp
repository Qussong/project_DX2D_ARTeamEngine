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

#include "vanPlayer.h"
#include "vanFloor.h"

#define VELOCITY_X	3.f

namespace van
{
	StraightScript::StraightScript()
		: mSize(0.1f * 0.5625f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mColor(Vector4(0.5f, 0.5f, 0.5f, 0.5f)),
		mDir(StraightDir::None),
		mbIsSetDir(false),
		mbStraight(false)
	{
	}

	StraightScript::~StraightScript()
	{
	}

	void StraightScript::Initialize()
	{
		mFloorTransform = GetOwner()->GetComponent<Transform>();
		mFloorCollider = GetOwner()->GetComponent<Collider>();
		mFloorRigidbody = GetOwner()->GetComponent<Rigidbody>();

		mPlayerTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
		mPlayerCollider = SceneManager::GetPlayer()->GetComponent<Collider>();
		mPlayerRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();

		mSize = mFloorTransform->GetScale();
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
			mbStraight = false;
			mPlayerRigidbody->SetStraight(false);
		}


		if (owner->GetCollisionEnter())
		{

			switch (mDir)
			{
			case van::enums::StraightDir::Left:
				mPlayerTransform->SetPosition(Vector3(mFloorTransform->GetPosition().x - 0.07f, mFloorTransform->GetPosition().y, 0.0f));
				mPlayerRigidbody->SetVelocity(Vector3(0.f));
				mPlayerRigidbody->SetStraight(true);
				mbStraight = true;
				break;
			case van::enums::StraightDir::Right:
				mPlayerTransform->SetPosition(Vector3(mFloorTransform->GetPosition().x + 0.07f, mFloorTransform->GetPosition().y, 0.0f));
				mPlayerRigidbody->SetVelocity(Vector3(0.f));
				mPlayerRigidbody->SetStraight(true);
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
			switch (mDir)
			{
			case van::enums::StraightDir::Left:
				mPlayerRigidbody->SetVelocity(Vector3(-3.0f, 0.f, 0.f));
				break;
			case van::enums::StraightDir::Right:
				mPlayerRigidbody->SetVelocity(Vector3(3.0f, 0.f, 0.f));
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

	


		if (mbIsSetDir == false)
		{
			if (mDir == StraightDir::Left)
			{
				mMesh = ResourceManager::Find<Mesh>(L"TriangleMeshL");
			}
			else if (mDir == StraightDir::Right)
			{
				mMesh = ResourceManager::Find<Mesh>(L"TriangleMeshR");
			}

			mbIsSetDir = true;
		}

	}

	void StraightScript::LateUpdate()
	{
	}

	void StraightScript::Render()
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