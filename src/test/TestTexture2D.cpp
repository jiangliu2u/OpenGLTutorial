#include "imgui.h"
#include "TestTexture2D.h"
namespace test {

	TestTexture2D::TestTexture2D() :m_TranslationA(200, 0, 0),
		m_TranslationB(100.f, 100.f, 0.f),
		m_Proj(glm::ortho(0.0f, 2000.0f, 0.0f, 2000.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
	{



		float position[] = {
				-150.0f,-150.0f, 0.0f, 0.0f,
				150.0f,-150.0f, 1.0f, 0.0f,
				150.0f,150.0f, 1.0f, 1.0f,
				-150.0f,150.0f, 0.0f, 1.0f,
		};
		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_Shader = std::make_unique<Shader>("res/shader/Basic.shader");
		m_VAO = std::make_unique<VertexArray>();
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices));
		m_VBO = std::make_unique<VertexBuffer>(position, sizeof(position));


		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VBO, layout);
		m_Shader->Bind();
		m_Texture = std::make_unique<Texture>("res/textures/knight.png");
		m_Texture->Bind();
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.f,0.f,0.f,1.f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		m_Texture->Bind();
		Renderer renderer;
		glm::mat4 model = glm::translate(glm::mat4(1), m_TranslationA);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.f, 960.f);
		ImGui::SliderFloat3("TranslationA", &m_TranslationB.x, 0.f, 960.f);
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}
}



