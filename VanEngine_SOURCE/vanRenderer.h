#pragma once
#include "vanEnums.h"
#include "CommonInclude.h"
#include "vanEngine.h"
#include "vanMath.h"
#include "vanGraphicsDevice_DX11.h"

#include "vanMesh.h"
#include "vanShader.h"
#include "vanConstantBuffer.h"

using namespace van::graphics;
using namespace van::enums;
using namespace van::math;

namespace van::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Vector3 pos;
		int padd1;

		Vector3 scale;
		int padd2;
	};

	extern Mesh* mesh;	// Circle
	extern Mesh* mesh2;	// Rectangle
	extern Shader* shader;
	extern ConstantBuffer* constantBuffers[];

	// Initialize the renderer
	void Initialize();
	void Release();
}
