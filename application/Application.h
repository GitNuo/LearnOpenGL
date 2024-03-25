#pragma once
#include <iostream>

/*
	*target: 
	OpenGL����ʵ��Application��װ
	1. ������
	2. ��Ա���� + ��Ա����
		2.1��Ա����-init����ʼ����
		2.2��Ա����-update��ÿһִ֡�У�
		2.3��Ա����-destroy����βִ�У�
	3. ��Ӧ�ص�����(OnResize)
		3.1 ����һ������ָ��ResizeCallback
		3.2 ����һ��ResizeCallback���͵ĳ�Ա����
		3.3 ����һ��SetResizeCallback�ĺ������ô���仯��Ӧ�ص�����
		3.4 ����һ��static�ľ�̬������������Ӧglfw����仯
		3.5 ����̬�������õ�g1fw�ļ���Resize��������
		* 3.6 ѧ��glfw ��UserPointer
	4. ��Ӧ������Ϣ����(OnKeyBoard)
		3.1 ����һ��static�ľ�̬������������Ӧglfw�ļ����¼�
		3.2 ����̬�������õ�glfw�ļ���KeyCallback��������
		3.3 ����һ������ָ��KeyBoardCal1back
		3.4 ����һ��KeyBoardCallback���͵ĳ�Ա����
		3.5 ����һ��SetkeyBoardCallback�ĺ��������ü�����Ӧ�ص�����
		* 3.6 ѧ��glfw ��UserPointer
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