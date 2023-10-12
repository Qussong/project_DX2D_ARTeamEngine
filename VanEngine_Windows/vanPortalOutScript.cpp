#include "vanPortalOutScript.h"
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
#include "vanFloor.h"
#include "vanTime.h"

#define VELOCITY_X	3.f

namespace van
{
	PortalOutScript::PortalOutScript()
		: mSize(0.1f * 0.5625f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mColor(Vector4(1.0f, 1.0f, 0.0f, 0.0f)),
		mTime(0.0f),
		mbDead(false)
	{
	}

	PortalOutScript::~PortalOutScript()
	{
	}

	void PortalOutScript::Initialize()
	{
		mFloorTransform = GetOwner()->GetComponent<Transform>();
		mFloorCollider = GetOwner()->GetComponent<Collider>();
		mFloorRigidbody = GetOwner()->GetComponent<Rigidbody>();

		mPlayerTransform = SceneManager::GetPlayer()->GetComponent<Transform>();
		mPlayerCollider = SceneManager::GetPlayer()->GetComponent<Collider>();
		mPlayerRigidbody = SceneManager::GetPlayer()->GetComponent<Rigidbody>();

		mSize = mFloorTransform->GetScale();
		mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
		mMesh = ResourceManager::Find<Mesh>(L"CircleMesh");
		mShader = ResourceManager::Find<Shader>(L"FloorShader");

	}

	void PortalOutScript::Update()
	{
		Floor* owner = dynamic_cast<Floor*>(GetOwner());

		if (mFloorTransform->GetPosition() == mPlayerTransform->GetPosition())
		{
			mbDead = true;
		}

		if (mbDead)
		{
			DecreaseColor();

			if (mColor.x <= 0.0f && mColor.y <= 0.0f)
			{
				Destroy(owner);
			}
		}

	}

	void PortalOutScript::LateUpdate()
	{
	}

	void PortalOutScript::Render()
	{
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];

		renderer::TransformCB data = {};
		data.pos = mFloorTransform->GetPosition();
		data.color = mColor;
		data.scale = mSize;
		cb->SetData(&data);

		cb->Bind(graphics::eShaderStage::VS);

		mShader->SetToplogy(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mShader->Update();
		mMesh->Render();
	}

	void PortalOutScript::DecreaseColor()
	{
		mColor -= (Vector4(3.0f, 3.0f, 0.0f, 0.0f) * Time::DeltaTime());
		if (mColor.x <=  0.0f)
		{
			mColor.x = 0.0f;
			mColor.z = 0.0f;
		}

		if (mColor.y <= 0.0f)
		{
			mColor.y = 0.0f;
			mColor.z = 0.0f;
		}
	}
}