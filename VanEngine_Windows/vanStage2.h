#pragma once
#include "vanScene.h"

namespace van
{
	class Stage2 : public Scene
	{
	public:
		Stage2();
		virtual ~Stage2();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:

	};
}