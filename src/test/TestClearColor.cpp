#include "Renderer.h"
#include "Glad/glad.h"
#include "imgui/imgui.h"
#include "TestClearColor.h"


test::TestClearColor::TestClearColor() :m_ClearColor{ 0.19f,0.31f,0.82f,1.0f }
{

}

test::TestClearColor::~TestClearColor()
{

}

void test::TestClearColor::OnRender()
{
	GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void test::TestClearColor::OnImGuiRender()
{
	ImGui::ColorEdit4("Test Color", m_ClearColor);
}

void test::TestClearColor::OnUpdate(float deltaTime)
{
}
