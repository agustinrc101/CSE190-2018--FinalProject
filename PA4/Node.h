#ifndef NODE_H
#define NODE_H

#include<glm/glm.hpp>
#include"shader.h"

class Node
{
public:
	Node();
	~Node();
	virtual int draw(glm::mat4 C, Shader* shaderProgram, int n = 0) = 0;
	virtual void update() = 0;
	Node& setManualDelete();
	bool isManualDelete();
	virtual glm::mat4 getToWorld(glm::mat4 C = glm::mat4(1.0f)) = 0;
	
	Node* parent;

	static glm::vec3 getPositionWithMat(glm::mat4 C);

protected:

private:
	bool manualDelete;

};

#endif
