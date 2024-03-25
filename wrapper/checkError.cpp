#include "checkError.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <iostream>
#include <string>

void checkError()
{
	GLenum errorCode = glGetError();
	std::string error = "";
	if (errorCode != GL_NO_ERROR)
	{
		switch (errorCode)
		{
		case GL_INVALID_ENUM:
			error = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			error = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			error = "GL_INVALID_OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			error = "GL_OUT_OF_MEMORY";
			break;
		default:
			error = "UNKNOWN";
			break;
		}

		std::cout << "error:" << error << std::endl;
		assert(false);
	}

}