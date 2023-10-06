#pragma once
#include "..\\VanEngine_SOURCE\\vanScene.h"

namespace van
{
	class Stage1 : public Scene
	{
	public:
		Stage1();
		virtual ~Stage1();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:

	};
}