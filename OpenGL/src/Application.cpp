#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
	std::cout << glGetString(GL_VERSION) << std::endl;

	/* Vertex Buffer */ 
		//normally also need "index buffer".
	//Give OpenGL data points
	float positions[6] = {
		-0.5f, -0.5f,
		 0.0f, 0.5f,
		 0.5f, -0.5f
	}; //Array with point positions
	unsigned int buffer;
	glGenBuffers(1, &buffer); //Create a Buffer w/ ID of generated buffer.
	glBindBuffer(GL_ARRAY_BUFFER, buffer); //An array bugger bounded to use/work
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); //6 values * size in bytes
	
	glEnableVertexAttribArray(0); //enables attrib starting at index 0
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); //0 since no other attributes 

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//begin code
		glDrawArrays(GL_TRIANGLES, 0, 3); //Draw Call, when you don't have index buffer
		//end of code

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

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
*/