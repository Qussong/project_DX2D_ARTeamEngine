#include "vanItem.h"
#include "vanCollider.h"
#include "vanPlayer.h"
#include "vanRigidBody.h"
#include "vanTransform.h"
#include "vanResourceManager.h"

namespace van
{
	Item::Item()
	{
		Transform* tr = AddComponent<Transform>();
		tr->SetPosition(Vector3(0.0f, -.5f, 0.0f));
		tr->SetScale(Vector3(0.125f, 0.125f, 1.f));

		Collider* col1 = AddComponent<Collider>();
		col1->SetScale(tr->GetScale());
		col1->SetPosition(tr->GetPosition());
		col1->SetMesh(ResourceManager::Find<Mesh>(L"RectangleColliderMesh"));
	}
	Item::~Item()
	{
	}
	void Item::Initialize()
	{
		GameObject::Initialize();

	}
	void Item::Update()
	{
		GameObject::Update();

		{
			Vector3 trPos = GetComponent<Transform>()->GetPosition();
			Vector3 colPos = GetComponent<Collider>()->GetPosition();
			if (trPos != colPos)
				GetComponent<Collider>()->SetPosition(trPos);
		}
	}
	void Item::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Item::Render()
	{
		GameObject::Render();
	}
	void Item::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		// Floor 객체와 충돌한 객체가 Playe 인 경우
		if (player != nullptr)
		{
			mbCollisionEnterFlag = true;
		}
	}
	void Item::OnCollisionStay(Collider* other)
	{
	}
	void Item::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			mbCollisionEnterFlag = false;
			player->SetCollisionCheck(false);
		}
	}
}