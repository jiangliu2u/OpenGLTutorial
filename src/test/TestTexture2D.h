#pragma once
#include "Test.h"
#include "Glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include <memory>
namespace test {
	class TestTexture2D :public Test {

	public:
		TestTexture2D();
		~TestTexture2D();
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
		virtual void OnUpdate(float deltaTime) override;
	private:
		glm::vec3 m_TranslationA, m_TranslationB;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Texture> m_Texture;
		glm::mat4 m_Proj;
		glm::mat4 m_View;
	};
}