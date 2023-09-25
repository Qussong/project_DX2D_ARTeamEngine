#pragma once
#include "..\\VanEngine_SOURCE\\vanScript.h"

namespace van
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		virtual ~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};
}