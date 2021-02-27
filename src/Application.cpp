#include "Glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include "test/TestClearColor.h"
#include "test/TestTexture2D.h"
#include "test/TestBox.h"
#include "test/TestLight.h"
void framebuffer_size_callback(GLFWwindow* w, int width, int height);




int main(void)
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit()) {
		return -1;
	}

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/* Make the window's context current */

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*if (glewInit() != GLEW_OK)
		std::cout << "Glew init Error!" << std::endl;*/

	//ImGui_ImplOpenGL3_Init(GL_VERSION);
	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		
		const char* glsl_version = "#version 430";
		//IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);


		test::Test* currentTest = nullptr;
		test::TestMenu * testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<test::Testbox>("Testbox");
		testMenu->RegisterTest<test::TestLight>("TestLight");

		test::TestClearColor testClearColor;


		while (!glfwWindowShouldClose(window))
		{
			GLCall(glClearColor(0.f,0.f,0.f,0.f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest) {
				currentTest->OnRender();
				currentTest->OnUpdate(0.1f);
				ImGui::Begin("test");
				if (currentTest != testMenu && ImGui::Button("<-")) {
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();

				ImGui::End();
			}
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);
			glfwPollEvents();
			
		}
		delete currentTest;
		if (currentTest != testMenu) {
			delete testMenu;
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}