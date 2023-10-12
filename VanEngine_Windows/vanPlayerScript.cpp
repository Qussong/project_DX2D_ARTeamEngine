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
		Transform* tr = player->GetComponent<Transform>();
		Rigidbody* rb = player->GetComponent<Rigidbody>();
		Vector3 pos = tr->GetPosition();
		Collider* col = player->GetComponent<Collider>();

		
		//Player* playercast = dynamic_cast<Player*>(GetOwner());

		
		
		


		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED
			|| Input::GetKeyState(KEY_CODE::LEFT) == KEY_STATE::PRESSED)
		{
			rb->SetFriction(1.0f);
			rb->AddVelocity(Vector3(-VELOCITY_X, 0.0f, 0.0f) * Time::DeltaTime());
		}

		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED
			|| Input::GetKeyState(KEY_CODE::RIGHT) == KEY_STATE::PRESSED)
		{
			rb->SetFriction(1.0f);
			rb->AddVelocity(Vector3(VELOCITY_X, 0.0f, 0.0f) * Time::DeltaTime());
		}

		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::UP
			|| Input::GetKeyState(KEY_CODE::D) == KEY_STATE::UP)
		{
			rb->SetFriction(10.0f);
		}

		

		

		//tr->SetPosition(pos);
		col->SetPosition(pos);
	}

	void PlayerScript::LateUpdate()
	{
		
	}

	void PlayerScript::Render()
	{
	}
}