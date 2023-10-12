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
		: mSize(Vector3::Zero),
		mPosition(Vector3::Zero),
		mColor(Vector4::Zero)
	{
		mTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
		mCollider = SceneManager::GetPlayer()->GetComponent<Collider>();;
		mRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();;
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{

	}

	void PlayerScript::Update()
	{
		GameObject* player = GetOwner();

		Vector3 pos = mTransform->GetPosition();



		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED
			|| Input::GetKeyState(KEY_CODE::LEFT) == KEY_STATE::PRESSED)
		{
			mRigidbody->SetFriction(1.0f);
			mRigidbody->AddVelocity(Vector3(-VELOCITY_X, 0.0f, 0.0f) * Time::DeltaTime());
		}

		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED
			|| Input::GetKeyState(KEY_CODE::RIGHT) == KEY_STATE::PRESSED)
		{
			mRigidbody->SetFriction(1.0f);
			mRigidbody->AddVelocity(Vector3(VELOCITY_X, 0.0f, 0.0f) * Time::DeltaTime());
		}

		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::UP
			|| Input::GetKeyState(KEY_CODE::D) == KEY_STATE::UP)
		{
			mRigidbody->SetFriction(10.0f);
		}

		mCollider->SetPosition(pos);
	}

	void PlayerScript::LateUpdate()
	{
		
	}

	void PlayerScript::Render()
	{
	}
}