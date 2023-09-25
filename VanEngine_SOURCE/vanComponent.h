#pragma once
#include "vanEnums.h"
#include "vanEntity.h"
#include "vanMath.h"
#include "vanGameObject.h"

namespace van
{
	using namespace enums;
	using namespace math;

	class GameObject;
	class Component : public Entity
	{
	public:
		friend GameObject;
		Component(COMPONENTTYPE type);
		virtual ~Component();

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void Render() = 0;

		GameObject* GetOwner() { return mOwner; }
		UINT GetUpdateOrder() { return (UINT)mType; }

	private:
		const COMPONENTTYPE mType;
		GameObject* mOwner;
	};
}
