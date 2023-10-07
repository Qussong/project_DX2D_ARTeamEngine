#include "vanPlayer.h"
#include "vanTransform.h"

#include "vanMeshRenderer.h"
#include "vanRigidbody.h"
#include "vanResourceManager.h"
#include "vanCollider.h"
#include "vanSceneManager.h"
#include "..//VanEngine_Windows//vanPlayerScript.h"



van::Player::Player()
{
}

van::Player::~Player()
{
}

void van::Player::Initialize()
{
	Transform* tr = AddComponent<Transform>();
	tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	tr->SetScale(Vector3(0.1f, 0.1f, 0.0f));

	MeshRenderer* meshRenderer = AddComponent<MeshRenderer>();
	meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"CircleMesh"));
	meshRenderer->SetShader(ResourceManager::Find<Shader>(L"PlayerShader"));
	Rigidbody* rb = AddComponent<Rigidbody>();

	Collider* col = AddComponent<Collider>();
	col->SetScale(Vector3(0.056f, 0.1f, 0.0f));
	col->SetPosition(tr->GetPosition());
	col->SetMesh(ResourceManager::Find<Mesh>(L"RectangleColliderMeesh"));
	col->SetVisible(false);

	PlayerScript* playerScript = AddComponent<PlayerScript>();
	GameObject::Initialize();
}

void van::Player::Update()
{
	GameObject::Update();
}

void van::Player::LateUpdate()
{
	GameObject::LateUpdate();
}

void van::Player::Render()
{
	GameObject::Render();
}

void van::Player::OnCollisionEnter(Collider* other)
{
	int a = 0;
}

void van::Player::OnCollisionStay(Collider* other)
{
}

void van::Player::OnCollisionExit(Collider* other)
{
}
