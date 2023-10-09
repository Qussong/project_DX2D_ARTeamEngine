#include "vanFloor.h"
#include "vanCollider.h"
#include "vanPlayer.h"
#include "vanRigidBody.h"
#include "vanTransform.h"
#include "vanMeshRenderer.h"
#include "vanResourceManager.h"

#define RATIO       0.5625f
#define ERRPRVALUE  0.05f
#define FORCE_X     1.5f
#define FORCE_Y     2.5f

namespace van
{
    Floor::Floor()
    {
        Transform* tr = AddComponent<Transform>();
        tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
        tr->SetScale(Vector3(0.125f * RATIO, 0.125f, 1.f));

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
            Rigidbody* rb = player->GetComponent<Rigidbody>();

            Collider* colPlayer = player->GetComponent<Collider>(); // Player의 콜라이더
            Vector3 playerSize = colPlayer->GetSize();              // Player의 콜라이더의 사이즈
            Vector3 playerPos = colPlayer->GetPosition();           // Player의 콜라이더의 위치

            Collider* colFloor = GetComponent<Collider>();          // Floor 의 콜라이더
            Vector3 floorSize = colFloor->GetSize();                // Floor 의 콜라이더의 사이즈
            Vector3 floorPos = colFloor->GetPosition();             // Floor 의 콜라이더의 위치

            // Player와 Floor 의 위치값 비교 - 윗면 충돌
            bool collisionFlagX = (playerPos.y - playerSize.y / 2) >= (floorPos.y + floorSize.y / 2) - ERRPRVALUE;
            // Player와 Floor 의 위치값 비교 - 옆면 충돌
            bool collisionFlagY = false;

            // Y축 충돌(오차값 = 0.05)
            if (collisionFlagX)
            {
                Vector3 temp = Vector3(rb->GetVelocity().x, 0.0f, rb->GetVelocity().z);
                rb->SetVelocity(temp + Vector3(0.0f, FORCE_Y, 0.0f));
            }
            // X축 충돌
            else
            {
                // Player 가 Floor 보다 오른쪽에 있을 때 (Right)
                if (playerPos.x > floorPos.x)
                {
                    collisionFlagY = (floorPos.x + floorSize.x / 2) > (playerPos.x - playerSize.x / 2);
                    if (collisionFlagY)
                    {
                        Vector3 temp = Vector3(0.0f, rb->GetVelocity().y, rb->GetVelocity().z);
                        rb->SetVelocity(temp + Vector3(FORCE_X, 0.0f, 0.0f));
                    }
                }
                // Player 가 Floor 보다 왼쪽에 있을 때 (Left)
                else
                {
                    collisionFlagY = (floorPos.x - floorSize.x / 2) < (playerPos.x + playerSize.x / 2);
                    if (collisionFlagY)
                    {
                        Vector3 temp = Vector3(0.0f, rb->GetVelocity().y, rb->GetVelocity().z);
                        rb->SetVelocity(temp + Vector3(-FORCE_X, 0.0f, 0.0f));
                    }
                }
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