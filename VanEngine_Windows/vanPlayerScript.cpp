#include "vanPlayerScript.h"
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanTime.h"
#include "vanInput.h"

#include "vanCollider.h"
#include "vanRigidbody.h"

namespace van
{
	PlayerScript::PlayerScript()
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

		if (Input::GetKeyState(KEY_CODE::W) == KEY_STATE::PRESSED)
		{
			//pos.y += 2.5f * Time::DeltaTime();
			rb->AddForce(Vector3(0.0f, 0.0f, 0.0f));
		}
		if (Input::GetKeyState(KEY_CODE::S) == KEY_STATE::PRESSED)
		{
			//pos.y -= 2.5f * Time::DeltaTime();
			rb->AddForce(Vector3(0.0f, 0.0f, 0.0f));
		}
		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED)
		{
			//pos.x -= 2.5f * Time::DeltaTime();
			rb->AddForce(Vector3(-15.0f, 0.0f, 0.0f));
		}
		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED)
		{
			//pos.x += 2.5f * Time::DeltaTime();
			rb->AddForce(Vector3(15.0f, 0.0f, 0.0f));
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