#pragma once
#include "vanScript.h"
#include "vanShader.h"
#include "vanMesh.h"
#include "vanMeshRenderer.h"



namespace van
{
	class Transform;
	class Collider;

	using namespace math;
	using namespace graphics;

	class JumpScript : public Script
	{
	public:
		JumpScript();
		virtual ~JumpScript();

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


		Transform* mTransform;
		Collider* mCollider;

	};
}