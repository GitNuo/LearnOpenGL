#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <assert.h>

#include "wrapper/checkError.h"
#include "application/Application.h"

/*
	*target:
	1 生成 VAO ，绑定 VAO
	2 使用 SingleBuffer 策略，进行 VAO 的构建
	3 使用 InterleavedBuffer 策略，进行 VAO 的构建
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
	// 1. 创建了vbo,还没有真正分配缓存
	GL_CALL(glGenBuffers(1, &vbo));
	// 2 销毁一个 vbo
	GL_CALL(glDeleteBuffers(1, &vbo));
	// 3 创建 n 个 vbo
	GLuint vboArr[] = { 0,0,0 };
	GL_CALL(glGenBuffers(3, vboArr));
	// 4 销毁 n 个 vbo
	GL_CALL(glDeleteBuffers(3, vboArr));

}

void prepare()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	// 1 生成一个 vbo
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);

	// 2 绑定当前 vbo ，到 opengl 状态机的当前 vbo 插槽上
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// 3 向当前 vbo 传输数据，也是在开辟显存 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void prepareSingleBuffer()
{
	// 1 准备顶点位置数据与颜色数据
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

    // 2 为位置&颜色数据各自生成一个 vbo
	GLuint posVbo = 0, colorVbo = 0;
	GL_CALL(glGenBuffers(1, &posVbo));
	GL_CALL(glGenBuffers(1, &colorVbo));

	// 3 给两个分开的 vbo 各自填充数据
	//position 填充数据
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
	
	// color填充数据
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

	// 4 生成vao并且绑定
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 4 分别将位置/颜色属性的描述信息加入 vao 当中|
	// 4.1 描述位置属性
	glBindBuffer(GL_ARRAY_BUFFER, posVbo); //只有绑定了 posVb 下面的属性描述才会与此vbo 相关
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// 4.2 描述颜色属性
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
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

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, pcVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	//glBindBuffer(GL_ARRAY_BUFFER, pcVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

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

		// 渲染操作
	}

// 4. Perform relevant cleaning before exiting the program
	app->destroy();
	return 0;
}