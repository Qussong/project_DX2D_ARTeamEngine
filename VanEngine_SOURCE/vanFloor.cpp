#include "vanFloor.h"
#include "vanCollider.h"
#include "vanPlayer.h"
#include "vanRigidBody.h"
#include "vanTransform.h"

namespace van
{
	Floor::Floor()
	{
	}

	Floor::~Floor()
	{
	}

	void Floor::Initialize()
	{
		GameObject::Initialize();
	}

	void Floor::Update()
	{
		GameObject::Update();
	}

	void Floor::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Floor::Render()
	{
		GameObject::Render();
	}

	void Floor::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Rigidbody* rb = player->GetComponent<Rigidbody>();
			Vector3 temp = Vector3(rb->GetVelocity().x, 0.0f, rb->GetVelocity().z);
			rb->SetVelocity(temp + Vector3(0.0f, 10.0f, 0.0f));
		}
	}

	void Floor::OnCollisionStay(Collider* other)
	{
	}

	void Floor::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Rigidbody* rb = player->GetComponent<Rigidbody>();
			//rb->SetGround(false);
		}
	}
}