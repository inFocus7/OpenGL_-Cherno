#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

/* Shaders */
static unsigned int Compileshader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl; //if/else
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = Compileshader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = Compileshader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	//Shows user's OpenGL Version
	std::cout << "By Fabian. (Following TheChernoProject's Tutorials!)" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	/* Vertex Buffer */ 
	//Give OpenGL data points/vertices
	float positions[] = {
		-0.5f, -0.5f, // 0
		 0.5f, -0.5f, // 1
		 0.5f, 0.5f,  // 2
		 -0.5f, 0.5f, // 3
	}; //Array with point positions

	/* Index Buffer */
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer); //Create a Buffer w/ ID of generated buffer.
	glBindBuffer(GL_ARRAY_BUFFER, buffer); //An array buffer bounded to use/work
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW); //6 values * size in bytes
	
	glEnableVertexAttribArray(0); //enables attrib starting at index 0
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); //0 since no other attributes 

	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n"
		"}\n";
	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";
	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	unsigned int ibo; //Index Buffer Object
	glGenBuffers(1, &ibo); //Create a Buffer w/ ID of generated buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); //An array bugger bounded to use/work
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW); //6 values * size in bytes

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//begin code
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		//end of code

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}

/*
INFORMATION:
___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
Vertex Buffer: Buffer inside GPU
Shader: Program in GPU
OpenGL is a "State Machine". Bind what you want to work on (like Photoshop's layer system)
Stride: distance (in bytes) from initial poisition to next vertex.

Steps For Drawing in OpenGL:
	1) Create Vertex Buffer w/ Data (and enable vertex attrib once made)
	2) Send to OpenGL VRAM
	3) Draw Call

Shaders: Need vertex & fragment shaders and bindings.
*/