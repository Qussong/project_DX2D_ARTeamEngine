#pragma once
#include "vanComponent.h"
#include "vanShader.h"
#include "vanMesh.h"

namespace van
{
	using namespace math;
	using namespace graphics;

	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate()override;
		virtual void Render() override;

		void OnCollisionEnter(Collider* other);
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);

		Vector3 GetSize() { return mSize; }
		void SetScale(Vector3 size) { mSize = size; }
		Vector3 GetOffset() { return mOffset; }
		void SetOffset(Vector3 offset) { mOffset = offset; }
		Vector3 GetPosition() { return mPosition; }

		void SetPosition(Vector3 pos) { mPosition = pos; }

		UINT GetCollisionNumber() { return mCollisionNumber; }

		void SetMesh(Mesh* mesh) { mMesh = mesh; }

		void SmoothDecreaseColor();

		void SetVisible(bool _flag) { mbVisible = _flag; }
		bool GetVisible() { return mbVisible; }

	private:
		static UINT mCollisionCount;

		Vector3 mSize;
		Vector3 mOffset;
		Vector3 mPosition;

		Vector4 mColor;
		bool mbColorFlag;

		Mesh* mMesh;
		Shader* mShader;

		UINT mCollisionNumber;
		bool mbIsCollision;

		bool mbVisible;	// 화면상 콜라이더 출력여부
	};
}