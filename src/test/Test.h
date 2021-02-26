#pragma once
#include <vector>
#include <functional>
#include <iostream>
namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
		virtual void OnUpdate(float deltaTime) {}
	private:

	};


	class TestMenu :public Test {
	private:
		Test*& m_CurrentTest;
		std::vector <std::pair<std::string, std::function<Test* ()>>> m_Tests;
	public:
		TestMenu(Test*& currentTest);
		void OnImGuiRender() override;
		template<typename T>
		void RegisterTest(const std::string& name) {
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}
	};

}
