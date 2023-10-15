#pragma once
#include "vanScene.h"

namespace van
{
	class Stage4 : public Scene
	{
	public:
		Stage4();
		virtual ~Stage4();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
	};
}