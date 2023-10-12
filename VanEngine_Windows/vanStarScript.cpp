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
		: mSize(0.1f * 0.5625f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mColor(Vector4(0.0f, 0.0f, 1.0f, 0.0f))
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

		mPlayerTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
		mPlayerCollider = SceneManager::GetPlayer()->GetComponent<Collider>();
		mPlayerRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();

		mSize = mItemTransform->GetScale();
		mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
		mMesh = ResourceManager::Find<Mesh>(L"TriangleMesh");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");

		int StarCount = SceneManager::GetActiveScene()->GetStarCount();
		SceneManager::GetActiveScene()->SetStarCount(StarCount++);
	}
	void StarScript::Update()
	{
		Player* player = SceneManager::GetPlayer();
		Item* owner = dynamic_cast<Item*>(GetOwner());

		
		if (owner->GetCollisionEnter())
		{
			int StarCount = SceneManager::GetActiveScene()->GetStarCount();
			SceneManager::GetActiveScene()->SetStarCount(StarCount--);

			// »èÁ¦
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