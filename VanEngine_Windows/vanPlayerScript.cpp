#include "vanPlayerScript.h"
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

#include "vanStraightScript.h"

#define VELOCITY_X	3.f

namespace van
{
	PlayerScript::PlayerScript()
	{
		mTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
		mCollider = SceneManager::GetPlayer()->GetComponent<Collider>();;
		mRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();;

		mSize = mTransform->GetScale();
		mPosition = mTransform->GetPosition();
		mColor = Vector4::Zero;
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
	}

	void PlayerScript::Update()
	{
		Player* player = SceneManager::GetPlayer();

		Vector3 pos = mTransform->GetPosition();
		Vector3 playerVelocty = player->GetComponent<Rigidbody>()->GetVelocity();

		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED
			|| Input::GetKeyState(KEY_CODE::LEFT) == KEY_STATE::PRESSED)
		{
			player->SetPlayerDir(PlayerDir::Left);
			mRigidbody->SetFriction(1.0f);
			mRigidbody->AddVelocity(Vector3(-VELOCITY_X, 0.0f, 0.0f) * Time::DeltaTime());
		}

		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED
			|| Input::GetKeyState(KEY_CODE::RIGHT) == KEY_STATE::PRESSED)
		{
			player->SetPlayerDir(PlayerDir::Right);
			mRigidbody->SetFriction(1.0f);
			mRigidbody->AddVelocity(Vector3(VELOCITY_X, 0.0f, 0.0f) * Time::DeltaTime());
		}

		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::UP
			|| Input::GetKeyState(KEY_CODE::D) == KEY_STATE::UP)
			mRigidbody->SetFriction(10.0f);

		bool bCheck = player->GetDoubleJumpCheck();
		if (Input::GetKeyState(KEY_CODE::SPACE) == KEY_STATE::DOWN && bCheck)
		{
			mRigidbody->SetLimitedVeloctyX(0.85f);

			if (player->GetPlayerDir() == PlayerDir::Left)
				mRigidbody->SetVelocity(Vector3(-0.85f, 1.1f, 0.0f));
			else
				mRigidbody->SetVelocity(Vector3(0.85f, 1.1f, 0.0f));

			player->SetDoubleJumpCheck(false);
		}

		
		mCollider->SetPosition(pos);
	}

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render()
	{
		//Player* owner = dynamic_cast<Player*>(GetOwner());

		//mColor += Vector4(0.0f, 1.0f, 0.0f, 0.0f);

		//// 상수버퍼설정
		//ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];
		//renderer::TransformCB data = {};
		//data.pos = mPosition;
		//data.color = mColor;
		//data.scale = mSize;

		//cb->SetData(&data);
		//cb->Bind(graphics::eShaderStage::VS);

		////owner->GetComponent<Shader>()->Update();
		//owner->GetComponent<Mesh>()->Render();
	}
}