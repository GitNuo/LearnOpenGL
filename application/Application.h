#pragma once
#include <iostream>

/*
	*target: 
	OpenGL当中实现Application封装
	1. 单例类
	2. 成员变量 + 成员函数
		2.1成员函数-init（初始化）
		2.2成员函数-update（每一帧执行）
		2.3成员函数-destroy（结尾执行）
	3. 响应回调函数(OnResize)
		3.1 声明一个函数指针ResizeCallback
		3.2 声明一个ResizeCallback类型的成员变量
		3.3 声明一个SetResizeCallback的函数设置窗体变化响应回调函数
		3.4 声明一个static的静态函数，用于响应glfw窗体变化
		3.5 将静态函数设置到g1fw的监听Resize监听当中
		* 3.6 学会glfw 的UserPointer
	4. 响应键盘消息函数(OnKeyBoard)
		3.1 声明一个static的静态函数，用于响应glfw的键盘事件
		3.2 将静态函数设置到glfw的监听KeyCallback监听当中
		3.3 声明一个函数指针KeyBoardCal1back
		3.4 声明一个KeyBoardCallback类型的成员变量
		3.5 声明一个SetkeyBoardCallback的函数，设置键盘响应回调函数
		* 3.6 学会glfw 的UserPointer
*/

#define app Application::getInstance()

struct GLFWwindow;

using ResizeCallBack = void(*)(int width, int height);
using KeyBoardCallBack = void(*)(int key, int scancode, int action, int mods);
typedef void(*MouseCallBack)(int button, int action, int mods);

class Application
{
public:
	~Application();

	static Application* getInstance();

	uint32_t getWidth() const { return m_nWidth; }
	uint32_t getHeight() const { return m_nHeight; }

	bool init(const int& width = 800, const int& height = 600);

	bool update();

	void destroy();

	void setResizeCallBack(ResizeCallBack callback) { m_ResizeCallBack = callback; }
	void setKeyBoardCallBack(KeyBoardCallBack callback) { m_KeyBoardCallBack = callback; }
	void setMouseCallBack(MouseCallBack callback) { m_MouseCallBack = callback; }

private:
	static void frameBufferSizeCallBack(GLFWwindow* window, int width, int height);
	static void keyBoardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallBack(GLFWwindow* window, int button, int action, int mods);

private:
	static Application* m_Instance;
	
	Application();

	uint32_t m_nWidth{ 0 };
	uint32_t m_nHeight = 0;
	GLFWwindow* m_window{ nullptr };

	ResizeCallBack m_ResizeCallBack{ nullptr };
	KeyBoardCallBack m_KeyBoardCallBack{ nullptr };
	MouseCallBack m_MouseCallBack{ nullptr };
};