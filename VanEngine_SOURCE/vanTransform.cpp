#include "vanTransform.h"
#include "vanGraphicsDevice_DX11.h"
#include "vanRenderer.h"

namespace van
{
	Transform::Transform()
		: Component(COMPONENTTYPE::TRANSFORM)
		, mColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f))
	{

	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::LateUpdate()
	{
	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];
		renderer::TransformCB data = {};
		data.pos = mPosition;
		data.scale = mScale;
		data.color = mColor;
		cb->SetData(&data);

		cb->Bind(graphics::eShaderStage::VS);
	}

}