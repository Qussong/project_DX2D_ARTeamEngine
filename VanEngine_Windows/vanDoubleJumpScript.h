#pragma once
#include "vanScript.h"
#include "vanShader.h"
#include "vanMesh.h"
#include "vanMeshRenderer.h"



namespace van
{
	class Transform;
	class Collider;
	class Rigidbody;

	using namespace math;
	using namespace graphics;

	class DoubleJumpScript : public Script
	{
	public:
		DoubleJumpScript();
		virtual ~DoubleJumpScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:

		Mesh* mMesh;
		Shader* mShader;
		MeshRenderer* mMeshRenderer;

		Vector3 mSize;
		Vector3 mPosition;
		Vector4 mColor;

		Transform* mFloorTransform;
		Collider* mFloorCollider;
		Rigidbody* mFloorRigidbody;

		Transform* mPlayerTransform;
		Collider* mPlayerCollider;
		Rigidbody* mPlayerRigidbody;

	};
}