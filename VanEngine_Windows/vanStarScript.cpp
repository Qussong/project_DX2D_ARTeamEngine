#include "vanTransform.h"
#include "vanGameObject.h"
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
#include "vanStarScript.h"
#include "vanItem.h"


namespace van
{
	StarScript::StarScript()
		: mSize(0.1f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mColor(Vector4(1.0f, 1.0f, 0.0f, 0.0f)),
		mStarCount(NULL)
	{
	}
	StarScript::~StarScript()
	{
	}
	void StarScript::Initialize()
	{
		mItemTransform = GetOwner()->GetComponent<Transform>();
		mItemCollider = GetOwner()->GetComponent<Collider>();
		mItemRigidbody = GetOwner()->GetComponent<Rigidbody>();

		mItemCollider->SetVisible(true);

		mPlayerTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
		mPlayerCollider = SceneManager::GetPlayer()->GetComponent<Collider>();
		mPlayerRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();

		mItemCollider->SetScale(Vector3(0.07f, 0.07f, 0.07f));

		mSize = mItemTransform->GetScale();
		mSize *= 0.3f;
		mMesh = ResourceManager::Find<Mesh>(L"StarMesh");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");

		mStarCount = SceneManager::GetActiveScene()->GetStarCount();
		SceneManager::GetActiveScene()->SetStarCount(++mStarCount);
	}
	void StarScript::Update()
	{
		Player* player = SceneManager::GetPlayer(); 
		Item* owner = dynamic_cast<Item*>(GetOwner());
		int StarCount = SceneManager::GetActiveScene()->GetStarCount();
		
		if (owner->GetCollisionEnter())
		{
			mStarCount = SceneManager::GetActiveScene()->GetStarCount();
			SceneManager::GetActiveScene()->SetStarCount(--mStarCount);

			// »èÁ¦
			Destroy(owner);
		}
	}
	void StarScript::LateUpdate()
	{
	}
	void StarScript::Render()
	{
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];

		renderer::TransformCB data = {};
		data.pos = mItemTransform->GetPosition();
		data.color = mColor;
		data.scale = mSize;
		cb->SetData(&data);

		cb->Bind(graphics::eShaderStage::VS);

		mShader->SetToplogy(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mShader->Update();
		mMesh->Render();
	}
}