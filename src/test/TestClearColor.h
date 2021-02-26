#pragma once
#include "Test.h"

namespace test {
	class TestClearColor :public Test {

	public:
		TestClearColor();
		~TestClearColor();
		virtual void OnRender() override;


		virtual void OnImGuiRender() override;


		virtual void OnUpdate(float deltaTime) override;
	private:
		float m_ClearColor[4];
	};
}