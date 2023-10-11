#pragma once
#include "vanScript.h"
#include "vanShader.h"
#include "vanMesh.h"
#include "vanMeshRenderer.h"



namespace van
{
	class Transform;
	class Collider;
	class Floor;

	using namespace math;
	using namespace graphics;

	class SpikeScript : public Script
	{
	public:
		SpikeScript();
		virtual ~SpikeScript();

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

		// ¤¾¤¾
		Transform* mTransform;
		Collider* mCollider;

		//Floor* mOwner;
	};
}