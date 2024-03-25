#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
	*target:
	-create glfw window system
	-add window change callback function
*/

// Declare and implement a function that responds to changes in window size
void farmeBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	std::cout << "width:" << width << "height:" << height << std::endl;
}

// Declare and implement a function keyboard msg 
void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W)
	{
		std::cout << "press:" << key << std::endl;
	}
}

int main()
{
// 1. init GLFW 
	glfwInit();
	// 1.1 set glfw major version and minor version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// 1.2 set opengl enable core type (非立即渲染模式) 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// 2. create window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLStudy", NULL, NULL);
	// set the current window object to OpenGL's drawing stage
	glfwMakeContextCurrent(window);

	// set up listening to listen for messages about changes in window size
	glfwSetFramebufferSizeCallback(window, farmeBufferSizeCallBack);

	// set keyboard listening
	glfwSetKeyCallback(window, keyCallBack);

// 3. execute a window loop
	while (!glfwWindowShouldClose(window))
	{
		// receive and send msg

		/* Check if there are any mouse, keyboard, or other messages 
		   that need to be processed in the message queue*/
		// If available, batch process the messages and clear the queue
		glfwPollEvents();
	}

// 4. Perform relevant cleaning before exiting the program
	glfwTerminate();
	return 0;
}