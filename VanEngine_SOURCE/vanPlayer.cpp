#include "vanPlayer.h"

van::Player::Player()
{
}

van::Player::~Player()
{
}

void van::Player::Initialize()
{
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
