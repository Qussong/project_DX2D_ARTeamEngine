#pragma once
#include "..\\VanEngine_SOURCE\\vanScript.h"
#include "..\\VanEngine_SOURCE\\vanShader.h"
#include "..\\VanEngine_SOURCE\\vanMeSh.h"



namespace van
{
	class Transform;
	class Rigidbody;
	class Collider;

	using namespace math;
	using namespace graphics;

	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		virtual ~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:

		Mesh* mMesh;
		Shader* mShader;
		
		Vector3 mSize;
		Vector3 mPosition;
		Vector4 mColor;

		Transform* mTransform;
		Collider* mCollider;
		Rigidbody* mRigidbody;
	

	};
}