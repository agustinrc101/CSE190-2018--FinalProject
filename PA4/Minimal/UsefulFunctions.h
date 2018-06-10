#pragma once

//OpenGL
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>

class UsefulFunctions {
public:
	static void printMatrix(glm::mat4 m) {
		std::cout << "============\n";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << m[j][i] << ", ";
			}
			std::cout << "\n";
		}
		std::cout << "============\n";
	}

	static void printVector(glm::vec2 v) {
		std::cout << "(" << v.x << ", " 
			<< v.y << ")" << std::endl;
	}

	static void printVector(glm::vec3 v) {
		std::cout << "(" << v.x << ", " 
			<< v.y << ", " << v.z << ")" 
			<< std::endl;
	}

	static void printVector(glm::vec4 v) {
		std::cout << "(" << v.x << ", " 
			<< v.y << ", " << v.z << ", " 
			<< v.w << ")" << std::endl;
	}


};