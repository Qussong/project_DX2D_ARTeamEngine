#pragma once
#include "..\\VanEngine_SOURCE\\vanScript.h"
#include "..\\VanEngine_SOURCE\\vanShader.h"
#include "..\\VanEngine_SOURCE\\vanMesh.h"
#include "..\\VanEngine_SOURCE\\vanMeshRenderer.h"



namespace van
{
	class Transform;
	class Collider;
	class Rigidbody;

	using namespace math;
	using namespace graphics;

	class PortalOutScript : public Script
	{
	public:
		PortalOutScript();
		virtual ~PortalOutScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		
		void DecreaseColor();
		void IncreaseColor();
		
		void SetColor(Vector4 color) { mColor = color; }
		void SetReCreate(bool can) { mbReCreate = can; }

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

		float mTime;
		bool mbReCreate;
		bool mbDead;

	};
}