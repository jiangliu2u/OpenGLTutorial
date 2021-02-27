#include "TestBox.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
namespace test {

	Testbox::Testbox() :m_TranslationA(0, 0, 0),
		m_TranslationB(100.f, 100.f, 0.f),
		m_lightColor(1.f, 1.f, 1.f),
		m_Proj(glm::perspective(glm::radians(45.0f), 1.f, 0.1f, 100.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)))
	{
		m_Shader = std::make_unique<Shader>("res/shader/Cube.shader");
		float vertices[] = {
			0.f,0.f,0.f,0.0f,1.0f,1.f,
			0.f,0.5f,0.f,0.2f,0.5,1.0f,
			0.f,0.5f,-0.5f,1.0f,0.f,0.f,
			0.f,0.f,-0.5f,0.f,0.f,0.f,
			0.5f,0.f,-0.5f,1.f,1.f,1.f,
			0.5f,0.5f,-0.5f,1.f,0.f,1.f,
			0.5f,0.f,0.f,0.5f,0.9f,0.2f,
			0.5f,0.5f,0.f,0.f,1.f,0.1f,
		};
		
		unsigned int indices[] = {
			0,1,2,
			0,2,3,
			0,3,6,
			4,3,6,
			4,5,6,
			7,5,6,
			2,3,5,
			4,3,5,
			1,0,7,
			6,0,7,
			2,1,5,
			7,1,5
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

	Testbox::~Testbox()
	{

	}

	void Testbox::OnRender()
	{
		glEnable(GL_DEPTH_TEST);
		GLCall(glClearColor(0.f,0.f,0.f,1.f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Renderer renderer;
		glm::mat4 model = glm::translate(glm::mat4(1), m_TranslationA);
		model  = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void Testbox::OnImGuiRender()
	{
		//ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, -0.5f, 0.5f);
		ImGui::SliderFloat3("lightColor", &m_lightColor.x, 0.f, 1.f);
	}

	void Testbox::OnUpdate(float deltaTime)
	{

	}

}

