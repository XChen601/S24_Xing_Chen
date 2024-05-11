#include "pch.h"

#include"NuggetApplication.h"
#include"NuggetWindow.h"
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"stb_image.h"
#include"Image.h"
#include"Shader.h"


namespace Nugget {
	void NuggetApplication::Initialize()
	{

	}
	void NuggetApplication::OnUpdate()
	{
	}

	void NuggetApplication::Shutdown()
	{
	}
	void NuggetApplication::Run()
	{
		NuggetWindow::Init();
		NuggetWindow::GetWindow()->Create(1000, 800);
		
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			NUGGET_ERROR("Failed to initialize GLAD");
			return;
		}
		
		// Blending //
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Vertext data //

		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		float vertices[] = {
			-0.5f, -0.5f, 0.0, 0.0, // left
			0.5f, -0.5f, 1.0, 0.0, // right
			-0.5f, 0.5f, 0.0, 1.0, // top
			0.5f, 0.5f, 1.0, 1.0, // left? i think it should be bottom
		};

		unsigned int indices[] = {
			0, 1, 2, // first triangle
			1, 2, 3 // second triangle
		};

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Shaders //
		
		Shader sProg{ "C:\\Users\\xchen\\source\\repos\\S24_Xing_Chen\\Nugget\Assets\Shaders\\DefaultVertexShader.glsl",
		"C:\\Users\\xchen\\source\\repos\\S24_Xing_Chen\\Nugget\\Assets\\Shaders\\DefaultFrahmentShader.glsl" };


		// Texture //

		Nugget::Image pic{ "C:\\Users\\xchen\\source\\repos\\S24_Xing_Chen\\Nugget\\Assets\\Textures\\Test.png" };

		Initialize();

		while (true) 
		{
			OnUpdate();

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// draw first triangle
			sProg.Bind();
			glBindVertexArray(VAO);
			pic.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			NuggetWindow::GetWindow()->SwapBuffers();
			NuggetWindow::GetWindow()->PollEvents();

		}

		Shutdown();

		NuggetWindow::Shutdown();

	}
}
