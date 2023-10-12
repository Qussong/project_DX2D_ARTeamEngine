#include "vanDisappearScript.h"
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
#include "vanFloor.h"

van::DisappearScript::DisappearScript()
{

}

van::DisappearScript::~DisappearScript()
{

}

void van::DisappearScript::Initialize()
{
	mFloorTransform = GetOwner()->GetComponent<Transform>();
	mFloorCollider = GetOwner()->GetComponent<Collider>();
	mFloorRigidbody = GetOwner()->GetComponent<Rigidbody>();

	mPlayerTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
	mPlayerCollider = SceneManager::GetPlayer()->GetComponent<Collider>();
	mPlayerRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();

	//mSize = mFloorTransform->GetScale();
	//mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
	//mMesh = ResourceManager::Find<Mesh>(L"RectangleMesh");
	//mShader = ResourceManager::Find<Shader>(L"FloorShader");
}

void van::DisappearScript::Update()
{
	Floor* owner = dynamic_cast<Floor*>(GetOwner());

	if(owner->GetCollisionEnter())
		mFloorTransform->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
}

void van::DisappearScript::LateUpdate()
{

}

void van::DisappearScript::Render()
{

}
