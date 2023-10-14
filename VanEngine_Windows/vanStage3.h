#pragma once
#include "vanScene.h"

namespace van
{
	class Stage3 : public Scene
	{
	public:
		Stage3();
		virtual ~Stage3();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:

	};
}