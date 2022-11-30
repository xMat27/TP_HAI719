// OPENGL includes
#include <GL/glew.h>
#include <GL/glut.h>
// STD includes
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <float.h>
#include <queue>
// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
// Local includes
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include "UnlitMaterial.h"
#include "Context.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "SceneLoader.h"




// -------------------------------------------
// OpenGL/GLUT application code.
// -------------------------------------------

static GLint window;

void init() {
	// Context::camera.initPos();
	Context::camera.resize(SCREENWIDTH, SCREENHEIGHT);
	Context::camera.initPos();
	Context::camera.setPos(1.0, 1.0, 1.0);
	Context::camera.lookAt(0.0, 0.0, 0.0);

	std::cerr << "view:" << glm::to_string(Context::view) << std::endl;
	// initLight ();
	// glCullFace (GL_BACK);
	// glEnable (GL_CULL_FACE);
	// glDepthFunc (GL_LESS);
	// glEnable (GL_DEPTH_TEST);
	glClearColor (0.2f, 0.2f, 0.3f, 1.0f);
	// glEnable(GL_COLOR_MATERIAL);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return;
	}
}


void draw() {
	if (Context::refreshMatrices) {
		Context::projection = Context::camera.getProjectionMatrix();
		Context::view = Context::camera.getViewMatrix();

		Context::projection = glm::perspective(
			glm::radians(65.0f),
			(float)SCREENWIDTH/(float)SCREENHEIGHT,
			0.001f,
			10000.0f);
			Context::view = glm::lookAt(glm::vec3(0.25, 0.25, 0.25), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			// std::cerr << "projection:" << glm::to_string(Context::projection) << std::endl;
			// std::cerr << "view:" << glm::to_string(Context::view) << std::endl;
			Context::refreshMatrices = false;
		}
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0; i < Context::instances.size(); ++i) {
			Instance& inst = Context::instances[i];
			Material* material = inst.material;
			Mesh* mesh = inst.mesh;
			material->bind();
			material->setMatrices(Context::projection, Context::view, inst.matrix);
			mesh->draw();
		}
	}


	void display() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw();
		glFlush();
		glutSwapBuffers();
	}




	int main (int argc, char ** argv) {
		if (argc < 2) {
			std::cerr << "Missing parameter: <path-to-model>" << std::endl;
			exit (EXIT_FAILURE);
		}
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
		glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
		window = glutCreateWindow("TP");

		init();
		glutIdleFunc(idle);
		glutDisplayFunc(display);
		glutKeyboardFunc(key);
		glutReshapeFunc(reshape);
		glutMotionFunc(motion);
		glutMouseFunc(mouse);
		key('?', 0, 0);

		std::string path(argv[1]);
		loadDataWithAssimp(path);

		// Dark blue background
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glutMainLoop();
		clearContext();
		return EXIT_SUCCESS;
	}
