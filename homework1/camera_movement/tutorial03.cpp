#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>

int main( void )
{
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( 1024, 768, "Task 2 - Camera motion", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint RedProgramID = LoadShaders("SimpleTransform.vertexshader", "SimpleRedFragmentShader.fragmentshader");
	GLuint GreenProgramID = LoadShaders("SimpleTransform.vertexshader", "SimpleGreenFragmentShader.fragmentshader");

	GLuint MatrixID = glGetUniformLocation(RedProgramID, "MVP");

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	
	glm::mat4 View       = glm::lookAt(
								glm::vec3(4,3,3),
								glm::vec3(0,0,0),
								glm::vec3(0,1,0)
						   );
	glm::mat4 Model      = glm::mat4(1.0f);
	glm::mat4 MVP        = Projection * View * Model;

	static const GLfloat g_vertex_buffer_data1[] = {
		-0.9f, 0.3f, -1.0f,
		 0.6f, -0.3f, 0.0f,
		 0.0f,  0.7f, 0.0f,
	};

	static const GLfloat g_vertex_buffer_data2[] = {
		-0.5f, -0.8f, 0.0f,
		 0.9f, -0.7f, 0.0f,
		 0.6f,  0.6f, 0.0f,
	};

	GLuint vertexbuffers[2];
	glGenBuffers(2, vertexbuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data1), g_vertex_buffer_data1, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data2), g_vertex_buffer_data2, GL_STATIC_DRAW);

	uint16_t RADIUS = 2;
	uint32_t TICKS_PER_ROTATION = 3000;
	uint32_t current_time = 0;
	do{
		View = glm::lookAt(
			glm::vec3(
				RADIUS * glm::sin(2 * glm::pi<double>() / TICKS_PER_ROTATION * current_time),
				3,
				RADIUS * glm::cos(2 * glm::pi<double>() / TICKS_PER_ROTATION * current_time)
			),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
		);
		current_time = (current_time + 1) % TICKS_PER_ROTATION;
		MVP = Projection * View * Model;

		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glUseProgram(RedProgramID);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffers[0]);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glUseProgram(GreenProgramID);

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffers[1]);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	glDeleteBuffers(2, vertexbuffers);
	glDeleteProgram(RedProgramID);
	glDeleteProgram(GreenProgramID);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return 0;
}

