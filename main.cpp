#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <assert.h>

#include "wrapper/checkError.h"

/*
	*target:
	1. ����glGetError
	2. ��װ�����麯��
	3. �����������ŵ�������cpp�ļ�
	4. ������GL_CALL����꣬��ݽ���g1�������
	5. ��� Ԥ�����, ��CMakeLists.txt�п���
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
	// 1.2 set opengl enable core type (��������Ⱦģʽ) 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// 2. create window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLStudy", NULL, NULL);
	// set the current window object to OpenGL's drawing stage
	glfwMakeContextCurrent(window);

	// set up listening to listen for messages about changes in window size
	glfwSetFramebufferSizeCallback(window, farmeBufferSizeCallBack);

	// set keyboard listening
	glfwSetKeyCallback(window, keyCallBack);

// ********loading all current version opengl's function by glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed  load" << std::endl;
		return -1;
	}

	// set openal View and clear color
	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 0.0));


// 3. execute a window loop
	while (!glfwWindowShouldClose(window))
	{
		// receive and send msg

		/* Check if there are any mouse, keyboard, or other messages 
		   that need to be processed in the message queue*/
		// If available, batch process the messages and clear the queue
		glfwPollEvents();

		// Execute opengl canvas cleaning operation
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));


		// Rendering operations

		// exchange double cache
		glfwSwapBuffers(window);
	}

// 4. Perform relevant cleaning before exiting the program
	glfwTerminate();
	return 0;
}