#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <assert.h>

#include "wrapper/checkError.h"
#include "application/Application.h"

/*
	*target:
	1. 编写一个单例类的Application
    2. 编写一个OnResize, 响应窗体发生变化
*/

void OnResize(int width, int height)
{
	GL_CALL(glViewport(0, 0, width, height));
	//std::cout << "OnResize:" << std::endl;
}

void OnKeyBoard(int key, int scancode, int action, int mods)
{
	std::cout << "keyBoard:" << key << std::endl;
}

void OnMouseBoard(int button, int action, int mods)
{
	std::cout << "----------------[in]---------------" << std::endl;
	std::cout << "button:" << button << std::endl;
	std::cout << "action:" << action << std::endl;
	std::cout << "mods:" << mods << std::endl;

}

int main()
{
	if (!app->init())
	{
		return -1;
	}

	//set up listening to listen for messages about changes in window size
	app->setResizeCallBack(OnResize);


	// set keyboard listening
	app->setKeyBoardCallBack(OnKeyBoard);

	// set mouse
	app->setMouseCallBack(OnMouseBoard);

	// set openal View and clear color
	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 0.0));


// 3. execute a window loop
	while (app->update())
	{
		// Execute opengl canvas cleaning operation
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

		// 渲染操作
	}

// 4. Perform relevant cleaning before exiting the program
	app->destroy();
	return 0;
}