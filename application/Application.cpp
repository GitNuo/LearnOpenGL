#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Application* Application::m_Instance = nullptr;

Application::~Application()
{

}

Application* Application::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new Application();
	}

	return m_Instance;
}



bool Application::init(const int& width, const int& height)
{
	m_nWidth = width;
	m_nHeight = height;

	// 1. init GLFW 
	glfwInit();
	// 1.1 set glfw major version and minor version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// 1.2 set opengl enable core type (��������Ⱦģʽ) 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 2. create window object
    m_window = glfwCreateWindow(width, height, "OpenGLStudy", NULL, NULL);
	if (m_window == NULL)
	{
		return false;
	}
	// set the current window object to OpenGL's drawing stage
	glfwMakeContextCurrent(m_window);

	// ********loading all current version opengl's function by glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed  load" << std::endl;
		return false;
	}

	// set up listening to listen for messages about changes in window size
	glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallBack);

	// keyBoard listening 
	glfwSetKeyCallback(m_window, keyBoardCallBack);

	// mouse
	glfwSetMouseButtonCallback(m_window, mouseCallBack);
	//this���ǵ�ǰȫ��Ψһ��Application����
	glfwSetWindowUserPointer(m_window, this);

	return true;
}

bool Application::update()
{
	if (glfwWindowShouldClose(m_window))
	{
		return false;
	}

	glfwPollEvents();

	// exchange double cache
	glfwSwapBuffers(m_window);
	return true;
}

void Application::destroy()
{
	glfwTerminate();
}

void Application::frameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	//if (app->m_ResizeCallBack != nullptr)
	//{
	//	app->m_ResizeCallBack(width, height);
	//}

	// ���������init()�е� glfwSetWindowUserPointer(m_window, this)��Ӧ
	// ����ʱ�����userָ�뱣��,��get`````()ȡ����,�������Ƚ�����
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self != nullptr)
	{
		self->m_ResizeCallBack(width, height);
	}
}

void Application::keyBoardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self != nullptr)
	{
		self->m_KeyBoardCallBack(key, scancode, action, mods);
	}
}

void Application::mouseCallBack(GLFWwindow* window, int button, int action, int mods)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self != nullptr)
	{
		self->m_MouseCallBack(button, action, mods);
	}
}

Application::Application()
{

}

