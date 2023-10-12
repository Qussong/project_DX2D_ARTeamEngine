#pragma once
#include "..\\VanEngine_SOURCE\\vanScript.h"
#include "..\\VanEngine_SOURCE\\vanShader.h"
#include "..\\VanEngine_SOURCE\\vanMesh.h"
#include "..\\VanEngine_SOURCE\\vanMeshRenderer.h"



namespace van
{
	class Transform;
	class Collider;
	class Floor;

	using namespace math;
	using namespace graphics;

	class StraightScript : public Script
	{
	public:
		StraightScript();
		virtual ~StraightScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void Straight();

		void SetDirection(StraightDir _dir) { mDir = _dir; }

	private:

		Mesh* mMesh;
		Shader* mShader;
		MeshRenderer* mMeshRenderer;

		Vector3 mSize;
		Vector3 mPosition;
		Vector4 mColor;


		Transform* mTransform;
		Collider* mCollider;

		StraightDir mDir;
		bool isSetDir;

		bool mbStraight;
	};
}