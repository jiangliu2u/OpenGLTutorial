#pragma once
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
#include "Test.h"

namespace test {
	class Testbox :public Test {

	public:
		Testbox();
		~Testbox();
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
		virtual void OnUpdate(float deltaTime) override;
	private:
		glm::vec3 m_TranslationA, m_TranslationB,m_lightColor;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Texture> m_Texture;
		glm::mat4 m_Proj;
		glm::mat4 m_View;
	};
}