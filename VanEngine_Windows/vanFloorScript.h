#pragma once
#include "..\\VanEngine_SOURCE\\vanScript.h"
#include "..\\VanEngine_SOURCE\\vanShader.h"
#include "..\\VanEngine_SOURCE\\vanMesh.h"
#include "..\\VanEngine_SOURCE\\vanMeshRenderer.h"



namespace van
{
	class Transform;
	class Collider;

	using namespace math;
	using namespace graphics;

	class FloorScript : public Script
	{
	public:
		FloorScript();
		virtual ~FloorScript();

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