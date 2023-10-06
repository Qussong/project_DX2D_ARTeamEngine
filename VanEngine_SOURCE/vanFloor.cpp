#include "vanFloor.h"
#include "vanCollider.h"
#include "vanPlayer.h"
#include "vanRigidBody.h"
#include "vanTransform.h"
#include "vanMeshRenderer.h"
#include "vanResourceManager.h"

#define RATIO       0.5625f
#define ERRORVALUE  0.05f
namespace van
{
    Floor::Floor()
    {
        Transform* tr = AddComponent<Transform>();
        tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
        tr->SetScale(Vector3(0.25f * RATIO, 0.25f, 1.f));

        MeshRenderer* meshRenderer1 = AddComponent<MeshRenderer>();
        meshRenderer1->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
        meshRenderer1->SetShader(ResourceManager::Find<Shader>(L"FloorShader"));

        Collider* col1 = AddComponent<Collider>();
        col1->SetScale(tr->GetScale());
        col1->SetPosition(tr->GetPosition());
        col1->SetMesh(ResourceManager::Find<Mesh>(L"RectangleColliderMeesh"));
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
            Collider* colPlayer = player->GetComponent<Collider>();
            Vector3 playerSize = colPlayer->GetSize();
            Vector3 playerPos = colPlayer->GetPosition();

            Collider* colFloor = GetComponent<Collider>();
            Vector3 floorSize = colFloor->GetSize();
            Vector3 floorPos = colFloor->GetPosition();

            // Player와 Floor 의 위치값 비교
            bool collisionFlag = (playerPos.y - playerSize.y / 2) >= (floorPos.y + floorSize.y / 2) - ERRORVALUE;

            // Player의 아랫면이 Floor 의 윗면보다 위에 있을경우(오차값 = 0.05)
            if (collisionFlag)
            {
                Rigidbody* rb = player->GetComponent<Rigidbody>();
                Vector3 temp = Vector3(rb->GetVelocity().x, 0.0f, rb->GetVelocity().z);
                rb->SetVelocity(temp + Vector3(0.0f, 3.5f, 0.0f));
            }

        }
    }

    void Floor::OnCollisionStay(Collider* other)
    {
    }

    void Floor::OnCollisionExit(Collider* other)
    {

    }
}