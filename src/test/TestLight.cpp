#include "TestLight.h"
#include "imgui.h"
#include <cmath>
#include "GLFW/glfw3.h"
namespace test {

	TestLight::TestLight() :m_TranslationA(-1.0, -1.0, -0.30),
		m_TranslationB(100.f, 100.f, 0.f),
		m_lightColor(1.f, 1.f, 1.f),
		m_lightPos(0.f, 0.f, 2.f),
		m_Rotation(-1.f, -1.f, -1.f),
		m_Proj(glm::perspective(glm::radians(45.0f), 1.f, 0.1f, 100.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)))
	{
		m_Shader = std::make_unique<Shader>("res/shader/Light.shader");
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		unsigned int indices[] = {
			0,1,2,3,4,5,6,7,8,9,10,
			11,12,13,14,15,16,17,18,19,20,
			21,22,23,24,25,26,27,28,29,30,
			31,32,33,34,35
			
		};
		
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices));
		m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		m_VAO = std::make_unique<VertexArray>();
		m_VAO->AddBuffer(*m_VBO, layout);
		m_Shader->Bind();
	}

	TestLight::~TestLight()
	{
	}

	void TestLight::OnRender()
	{
		glEnable(GL_DEPTH_TEST);
		GLCall(glClearColor(0.f, 0.f, 0.f, 1.f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Renderer renderer;
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(0.f, 0.0f, 0.f));
		model = glm::rotate(model, 11 * glm::radians(60.0f), m_Rotation);
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("projection", m_Proj);
		m_Shader->SetUniformMat4f("view", m_View);
		m_Shader->SetUniformMat4f("model", model);
		m_Shader->SetUniform3f("lightPos",m_lightPos[0], m_lightPos[1], m_lightPos[2]);
		m_Shader->SetUniform3f("lightColor", m_lightColor[0], m_lightColor[1], m_lightColor[2]);

		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestLight::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, -1.f, 1.f);
		ImGui::SliderFloat3("Light Color", &m_lightColor.x, -1.f, 1.f);
		ImGui::SliderFloat3("Light Position", &m_lightPos.x, -2.f, 2.f);
		ImGui::SliderFloat3("Rotation ", &m_Rotation.x, -1.f, 1.f);
	}

	void TestLight::OnUpdate(float deltaTime)
	{

	}

}

