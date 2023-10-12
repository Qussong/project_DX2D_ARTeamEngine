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

	class PortalInScript : public Script
	{
	public:
		PortalInScript();
		virtual ~PortalInScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void SetOutPortalPos(Vector3 pos) { mOutPortalPos = pos; }

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

		Vector3 mOutPortalPos;
		bool mbCreateOutPortal;

	};
}