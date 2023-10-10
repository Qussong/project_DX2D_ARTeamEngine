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

		Vector4 color;
	};

	extern Mesh* meshDeathBlock;
	extern Mesh* meshCircle;		// Circle
	extern Mesh* meshRectangle;		// Rectangle
	extern Mesh* meshTriangle;
	extern Mesh* meshTriangleR;
	extern Mesh* meshTriangleL;
	extern Mesh* meshColRectangle;	// collider
	extern Mesh* meshColCircle;		// collider


	extern Shader* shaderPlayer;	// player
	extern Shader* shaderCollider;	// collider
	extern Shader* shaderFloor;		// floor
	extern ConstantBuffer* constantBuffers[];

	// Initialize the renderer
	void Initialize();
	void Release();
}
