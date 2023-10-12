#include "vanFloor.h"
#include "vanCollider.h"
#include "vanPlayer.h"
#include "vanRigidBody.h"
#include "vanTransform.h"
#include "vanMeshRenderer.h"
#include "vanResourceManager.h"
#include "..//VanEngine_Windows//vanFloorScript.h"
#include "..//VanEngine_Windows\\vanSpikeScript.h"
#include "..//VanEngine_Windows\\vanPortalOutScript.h"

#define RATIO       0.5625f

namespace van
{
	Floor::Floor()
		: mbCollisionEnterFlag(false)
	{
		Transform* tr = AddComponent<Transform>();
		tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		tr->SetScale(Vector3(0.125f * RATIO, 0.125f, 1.f));

		/* MeshRenderer* meshRenderer1 = AddComponent<MeshRenderer>();
		 meshRenderer1->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		 meshRenderer1->SetShader(ResourceManager::Find<Shader>(L"FloorShader"));*/

		Collider* col1 = AddComponent<Collider>();
		col1->SetScale(tr->GetScale());
		col1->SetPosition(tr->GetPosition());
		col1->SetMesh(ResourceManager::Find<Mesh>(L"RectangleColliderMesh"));
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

		// Collider 위치 수정
		{
			Vector3 trPos = GetComponent<Transform>()->GetPosition();
			Vector3 colPos = GetComponent<Collider>()->GetPosition();
			if (trPos != colPos)
				GetComponent<Collider>()->SetPosition(trPos);
		}
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

		// Floor 객체와 충돌한 객체가 Playe 인 경우
		if (player != nullptr)
		{
			mbCollisionEnterFlag = true;
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
			mbCollisionEnterFlag = false;
			player->SetCollisionCheck(false);
		}

	}
}