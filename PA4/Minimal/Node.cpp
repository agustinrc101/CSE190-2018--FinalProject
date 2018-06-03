#include "Node.h"

Node::Node()
{
	manualDelete = true;
}

Node::~Node()
{
}

Node& Node::setManualDelete()
{
	manualDelete = true;
	return *this;
}

bool Node::isManualDelete()
{
	return manualDelete;
}

glm::vec3 Node::getPositionWithMat(glm::mat4 C)
{
	glm::vec4 position = C * glm::vec4(0, 0, 0, 1);
	return glm::vec3(position.x / position.w, position.y / position.w, position.z / position.w);
}
