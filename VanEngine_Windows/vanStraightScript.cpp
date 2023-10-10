#include "vanStraightScript.h"
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

#define VELOCITY_X	3.f

namespace van
{
	StraightScript::StraightScript()
		: mSize(0.1f * 0.5625f, 0.1f, 1.f),
		mPosition(Vector3::Zero),
		mColor(Vector4(0.5f, 0.5f, 0.5f, 0.5f)),
		mDir(StraightDir::None),
		isSetDir(false)
	{
	}

	StraightScript::~StraightScript()
	{
	}

	void StraightScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mCollider = GetOwner()->GetComponent<Collider>();


		//if (mDir == StraightDir::Left)
		//{
		//	mSize = mTransform->GetScale();
		//	mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
		//	mMesh = ResourceManager::Find<Mesh>(L"TriangleMeshL");
		//	mShader = ResourceManager::Find<Shader>(L"FloorShader");
		//}
		//else if (mDir == StraightDir::Right)
		//{
		//	mSize = mTransform->GetScale();
		//	mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
		//	mMesh = ResourceManager::Find<Mesh>(L"TriangleMeshR");
		//	mShader = ResourceManager::Find<Shader>(L"FloorShader");
		//}
	}

	void StraightScript::Update()
	{

		if (isSetDir == false)
		{
			if (mDir == StraightDir::Left)
			{
				mSize = mTransform->GetScale();
				mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
				mColor = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
				mMesh = ResourceManager::Find<Mesh>(L"TriangleMeshL");
				mShader = ResourceManager::Find<Shader>(L"FloorShader");
			}
			else if (mDir == StraightDir::Right)
			{
				mSize = mTransform->GetScale();
				mSize = Vector3(mSize.x - 0.001f, mSize.y - 0.005f, 0.0f);
				mColor = Vector4(0.0f, 1.0f, 1.0f, 0.0f);
				mMesh = ResourceManager::Find<Mesh>(L"TriangleMeshR");
				mShader = ResourceManager::Find<Shader>(L"FloorShader");
			}

			isSetDir = true;
		}

	}

	void StraightScript::LateUpdate()
	{
	}

	void StraightScript::Render()
	{

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];

		renderer::TransformCB data = {};
		data.pos = mTransform->GetPosition();
		data.color = mColor;
		data.scale = mSize;
		cb->SetData(&data);



		cb->Bind(graphics::eShaderStage::VS);

		mShader->SetToplogy(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mShader->Update();
		mMesh->Render();
	}
}