#include "pch.h"

#include"NuggetApplication.h"
#include"NuggetWindow.h"
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"stb_image.h"
#include"Image.h"



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
		
		const char* vertexShaderSource = R"(
			#version 330 core
			layout (location = 0) in vec2 aPos;
			layout (location = 1) in vec2 aTexCoord;

			out vec2 TexCoord;

			void main()
			{
				gl_Position = vec4(aPos.x, aPos.y, 0, 1.0);
				TexCoord = aTexCoord;
			}
			)";
		
		const char* fragmentShaderSource = R"(
			#version 330 core
			out vec4 FragColor;

			in vec2 TexCoord;

			uniform sampler2D myTex;

			void main()
			{
				FragColor = texture(myTex, TexCoord);
			}
			)";

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			NUGGET_ERROR("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog)
		}

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			NUGGET_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog)
		}

		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			NUGGET_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog)
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Texture //

		Nugget::Image pic{ "C:\\Users\\xchen\\source\\repos\\S24_Xing_Chen\\Nugget\\Assets\\Textures\\Test.png" };

		Initialize();

		while (true) 
		{
			OnUpdate();

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// draw first triangle
			glUseProgram(shaderProgram);
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
