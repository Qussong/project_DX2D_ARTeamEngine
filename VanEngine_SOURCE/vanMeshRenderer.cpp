#include "vanMeshRenderer.h"
#include "vanGameObject.h"
#include "vanTransform.h"

namespace van
{
	MeshRenderer::MeshRenderer()
		: Component(COMPONENTTYPE::MESH)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initialize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::LateUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();
		
		mShader->Update();
		mMesh->Render();
	}
}

