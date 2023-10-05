#include "vanPlayerScript.h"
#include "vanTransform.h"
#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanTime.h"
#include "vanInput.h"

#include "vanCollider.h"

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
		Vector3 pos = tr->GetPosition();

		Collider* col = player->GetComponent<Collider>();

		if (Input::GetKeyState(KEY_CODE::W) == KEY_STATE::PRESSED)
		{
			pos.y += 2.5f * Time::DeltaTime();
		}
		if (Input::GetKeyState(KEY_CODE::S) == KEY_STATE::PRESSED)
		{
			pos.y -= 2.5f * Time::DeltaTime();
		}
		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED)
		{
			pos.x -= 2.5f * Time::DeltaTime();
		}
		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED)
		{
			pos.x += 2.5f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
		col->SetPosition(pos);
	}

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render()
	{
	}
}