#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <assert.h>

#include "wrapper/checkError.h"
#include "application/Application.h"

/*
	*target:
	1 vbo �Ĵ���/���٣�һ����һ�ѣ�
	2 ��ϰ�� vbo ����ϰ�� vbo ���д�������
    	-glBindBuffer
		-glBufferData
	3 ��ϰ vbo ����������ݵĴ洢
		-SingleBuffer ��ÿһ�����Է���һ�������� vbo ����
		-InterleavedBuffer �����������Զ��洢��һ�� vbo ���У����������ǽ����
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

void prepareVBO()
{
	GLuint vbo = 0;
	// 1. ������vbo,��û���������仺��
	GL_CALL(glGenBuffers(1, &vbo));
	// 2 ����һ�� vbo
	GL_CALL(glDeleteBuffers(1, &vbo));
	// 3 ���� n �� vbo
	GLuint vboArr[] = { 0,0,0 };
	GL_CALL(glGenBuffers(3, vboArr));
	// 4 ���� n �� vbo
	GL_CALL(glDeleteBuffers(3, vboArr));

}

void prepare()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	// 1 ����һ�� vbo
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);

	// 2 �󶨵�ǰ vbo ���� opengl ״̬���ĵ�ǰ vbo �����
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// 3 ��ǰ vbo �������ݣ�Ҳ���ڿ����Դ� 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void prepareSingleBuffer()
{
	// 1 ׼������λ����������ɫ����
	float positions[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
	float colors[] = {
	 1.0f, 0.0f, 0.0f,
	 0.0f, 1.0f, 0.0f,
	 0.0f,  0.0f, 1.0f
	};

    // 2 Ϊλ��&��ɫ���ݸ�������һ�� vbo
	GLuint posVbo = 0, colorVbo = 0;
	GL_CALL(glGenBuffers(1, &posVbo));
	GL_CALL(glGenBuffers(1, &colorVbo));

	// 3 �������ֿ��� vbo �����������
	//position �������
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
	
	// color�������
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
}

void prapareInterleavedBuffer()
{
	float positionsColors[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f, 0.0f,  0.0f, 1.0f
	};

	GLuint pcVbo = 0;
	GL_CALL(glGenBuffers(1, &pcVbo));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, pcVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positionsColors), positionsColors, GL_STATIC_DRAW));
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

	prapareInterleavedBuffer();
// 3. execute a window loop
	while (app->update())
	{
		// Execute opengl canvas cleaning operation
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

		// ��Ⱦ����
	}

// 4. Perform relevant cleaning before exiting the program
	app->destroy();
	return 0;
}