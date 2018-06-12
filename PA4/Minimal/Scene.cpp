#include "Scene.h"

void Scene::update(float deltaTime) {
	dynamicsWorld->stepSimulation(1.0f / 90.0f, 10);

	for (int i = 0; i < objects.size(); i++)
		objects[i]->update();
	for (int i = 0; i < cans.size(); i++)
		cans[i]->update();
}

void Scene::drawStaticObjects(glm::mat4 projection, glm::mat4 modelview, Shader* shaderProgram) {
	shaderProgram->use();
	shaderProgram->setMat4("projection", projection);
	shaderProgram->setMat4("view", modelview);

	for (int i = 0; i < staticObjects.size(); i++)
		staticObjects[i]->draw(glm::mat4(1.0f), shaderProgram);

	for (int i = 0; i < cans.size() && i < 15; i++) {
		if(drawCan[i])
			cans[i]->draw(glm::mat4(1.0f), shaderProgram);
	}

}

void Scene::drawObjects(glm::mat4 projection, glm::mat4 modelview, Shader* shaderProgram, Shader* colorShader, int indexL, int indexR) {
	for (int i = 0; i < objects.size(); i++) {
		if (i == indexL || i == indexR) {
			colorShader->use();
			colorShader->setMat4("projection", projection);
			colorShader->setMat4("view", modelview);
			colorShader->setVec3("rgb", glm::vec3(1.0f, 1.0f, 0.6f));
			objects[i]->draw(glm::mat4(1.0f), colorShader);
		}
		else {
			shaderProgram->use();
			shaderProgram->setMat4("projection", projection);
			shaderProgram->setMat4("view", modelview);
			objects[i]->draw(glm::mat4(1.0f), shaderProgram);
		}
	}

}

Scene::~Scene() {
	delete(dynamicsWorld);
	delete(solver);
	delete(dispatcher);
	delete(collisionConfiguration);
	delete(broadphase);
}

Scene::Scene(){
	initBullet();
	initObjects();

	for (int i = 0; i < 15; i++)
		drawCan[i] = true;
}

void Scene::initBullet() {
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, 0, 0));
}

std::vector<glm::vec3> Scene::getListOfPositions() {
	std::vector<glm::vec3> pos;
	
	for (int i = 0; i < objects.size(); i++)
		pos.push_back(objects[i]->getToWorld()[3]);

	return pos;
}

void Scene::setObjMatrix(int index, glm::mat4 m) {
	objects[index]->setToWorld(m);
}

glm::mat4 Scene::getObjMatrix(int index) {
	return objects[index]->getToWorld();
}

void Scene::resetObj(int index) {
	objects[index]->resetTranslate();
}

glm::vec3 Scene::getForwardVector(int index) {
	if (index <= 1)
		return glm::vec3(0, 0, 0);
	return objects[index]->getForwardVector();
}

glm::vec3 Scene::getPosition(int index) {
	return objects[index]->getPositionWithMat(objects[index]->getToWorld());
}

glm::vec3 Scene::shootRaycast(glm::vec3 dir, glm::vec3 startPos) {
	glm::vec3 endPos = startPos + (dir * 1000.0f);
	btCollisionWorld::ClosestRayResultCallback raycastHit(
		btVector3(startPos.x, startPos.y, startPos.z),
		btVector3(endPos.x, endPos.y, endPos.z)
	);
	dynamicsWorld->rayTest(
		btVector3(startPos.x, startPos.y, startPos.z),
		btVector3(endPos.x, endPos.y, endPos.z),
		raycastHit
	);

	if (raycastHit.hasHit()) {
		//ids Plane 28 Sphere 8 Cylinder 13
		if (raycastHit.m_collisionObject->getCollisionShape()->getShapeType() == 13) {	//13 is id for cylinders
			//Hit a can
			int * canHit = (int *)raycastHit.m_collisionObject->getCollisionShape()->getUserPointer();
			if (canHit != nullptr)
				lastHit = *canHit;
			else
				std::cout << "nullptr, dang\n";
		}

		btVector3 hitPoint = raycastHit.m_hitPointWorld;
		return glm::vec3(hitPoint.getX(), hitPoint.getY(), hitPoint.getZ());
	}

	return glm::vec3(-100);
}

bool Scene::removeLastHit(int index) {
	if (drawCan[index]) {
		drawCan[index] = false;

		int count = 0;
		for (int i = 0; i < 15; i++) {
			if (drawCan[i])
				count++;
		}
		if (count != 1)
			std::cout << count << " cans remain!" << std::endl;
		else if(count == 0)
			std::cout << "conglaturations! you done it!" << std::endl;
		else
			std::cout << count << " can remains!" << std::endl;

		return true;
	}
	else
		return false;
}

bool Scene::getCheckIfHit(int index) {
	if (index < 0)
		return false;

	return drawCan[index];
}

void Scene::resetCans() {
	int count = 0;
	for (int i = 0; i < 15; i++) {
		if (drawCan[i])
			count++;

		drawCan[i] = true;
	}
	if(count == 15)
		std::cout << "The cans have been reset!" << std::endl;
	std::cout << "15 cans remain!" << std::endl;
}

void Scene::initObjects(){
	Transform * child;
	Geometry * geom;
	std::string path1, path2;
	glm::vec3 yRot = glm::vec3(0, 1, 0);
	glm::vec3 xRot = glm::vec3(1, 0, 0);
	//STATIC OBJECTS
		//Ground Plane
		child = new Transform();
		geom = new Geometry();
		path1 = MODEL_SHAPE_PLANE;
		path2 = TEXTURE_GROUND1;
		geom->init(path1, path2);
		child->rotate(glm::vec3(1, 0, 0), 90);
		child->scale(100, 100, 100);
		child->translate(0, -1.5f, 0);
		child->setCollisionShapePlane();
		dynamicsWorld->addRigidBody(child->getRigidbody());
		child->addChild(geom);
		staticObjects.push_back(child);
		//Objects
		//Matthew
		child = new Transform();
		geom = new Geometry();
		path1 = MODEL_MATTHEW;
		path2 = TEXTURE_MATTHEW;
		geom->init(path1, path2);
		child->rotate(xRot, 270);child->translate(4, -1.5, -6); child->scale(0.001f);
		child->addChild(geom);
		staticObjects.push_back(child);
		//Houses
		child = new Transform();
		geom = new Geometry();
		path1 = MODEL_HOUSE1;
		path2 = TEXTURE_HOUSE;
		geom->init(path1, path2);
		child->translate(5, -1.5, -7); child->scale(0.05f);
		child->addChild(geom);
		staticObjects.push_back(child);
		
		child = new Transform();
		child->rotate(yRot, 135); child->translate(-7, -1.5, -16); child->scale(0.05f);
		child->addChild(geom);
		staticObjects.push_back(child);

		child = new Transform();
		child->rotate(yRot, 270); child->translate(0, -1.5, 6); child->scale(0.05f);
		child->addChild(geom);
		staticObjects.push_back(child);

		child = new Transform();
		child->rotate(yRot, 90); child->translate(-20, -1.5, 0); child->scale(0.05f);
		child->addChild(geom);
		staticObjects.push_back(child);
		//Rocks
		child = new Transform();
		geom = new Geometry();
		path1 = MODEL_ROCKS;
		path2 = TEXTURE_ROCKS;
		geom->init(path1, path2);
		child->rotate(yRot, 85); child->translate(-10, -1.5, -3); child->scale(0.01f);
		child->addChild(geom);
		staticObjects.push_back(child);
		//Barrels
		child = new Transform();
		geom = new Geometry();
		path1 = MODEL_BARREL;
		path2 = TEXTURE_BARREL;
		geom->init(path1, path2);
		child->translate(0, -1, -3); child->scale(0.35f, 0.4f, 0.35f);
		child->addChild(geom);
		staticObjects.push_back(child);

		child = new Transform();
		child->translate(-2.5, -1, 7); child->scale(0.35f, 0.4f, 0.35f);
		child->addChild(geom);
		staticObjects.push_back(child);

		child = new Transform();
		child->translate(-3, -1, 7.6f); child->scale(0.35f, 0.4f, 0.35f);
		child->addChild(geom);
		staticObjects.push_back(child);

		child = new Transform();
		child->translate(16, -1, -4); child->scale(0.35f, 0.4f, 0.35f);
		child->addChild(geom);
		staticObjects.push_back(child);
		//Barriers
		child = new Transform();
		geom = new Geometry();
		path1 = MODEL_BARRIER;
		path2 = TEXTURE_BARRIER;
		geom->init(path1, path2);
		child->rotate(yRot, 45); child->translate(-15, -1.5, -8); child->scale(0.01f);
		child->addChild(geom);
		staticObjects.push_back(child);

		child = new Transform();
		child->rotate(yRot, 45);child->translate(15, -1.5, -3); child->scale(0.01f);
		child->addChild(geom);
		staticObjects.push_back(child);

		child = new Transform();
		child->rotate(yRot, 45); child->translate(11, -1.5, 1); child->scale(0.01f);
		child->addChild(geom);
		staticObjects.push_back(child);
		//Metal container
		child = new Transform();
		geom = new Geometry();
		path1 = MODEL_CONTAINER;
		path2 = TEXTURE_CONTAINER_GREEN;
		geom->init(path1, path2);
		child->rotate(yRot, 315);child->translate(20, 0, 2); child->scale(0.01f);
		child->addChild(geom);
		staticObjects.push_back(child);

		child = new Transform();
		child->rotate(yRot, 45);child->translate(24, 0, -8); child->scale(0.01f);
		child->addChild(geom);
		staticObjects.push_back(child);
		//Ammo box
		child = new Transform();
		geom = new Geometry();
		path1 = MODEL_AMMOBOX;
		path2 = TEXTURE_AMMOBOX;
		geom->init(path1, path2);
		child->translate(-2.5, -.5f, 7); child->scale(0.0025f);
		child->addChild(geom);
		staticObjects.push_back(child);

		child = new Transform();
		child->translate(16, -.5f, -4); child->scale(0.0025f);
		child->addChild(geom);
		staticObjects.push_back(child);

		child = new Transform();
		child->translate(-14, -.75, -7); child->scale(0.0025f);
		child->addChild(geom);
		staticObjects.push_back(child);
		//Ladders
		child = new Transform();
		geom = new Geometry();
		path1 = MODEL_LADDER_SMALL;
		path2 = TEXTURE_LADDER;
		geom->init(path1, path2);
		child->rotate(yRot, 180);child->translate(-17.5, -1.5, 1.5); child->scale(0.01f);
		child->addChild(geom);
		staticObjects.push_back(child);


	//DYNAMIC OBJECTS
		//Grenades
		child = new Transform();
		geom = new Geometry();
		path1 = MODEL_GRENADE;
		path2 = TEXTURE_GRENADE;
		geom->init(path1, path2);
		child->translate(0, -.5f, -3);child->scale(0.005f);
		child->setCollisionShapeSphere(0.1);
		dynamicsWorld->addRigidBody(child->getRigidbody());
		child->addChild(geom);
		objects.push_back(child);

		child = new Transform();
		child->translate(0, 50, 0);
		child->setCollisionShapeSphere(10.0);
		dynamicsWorld->addRigidBody(child->getRigidbody());
		child->addChild(geom);
		objects.push_back(child);

		//GUN
		Transform * dirChild;
		geom = new Geometry();
		path1 = MODEL_WEAPON_PISTOL;
		path2 = TEXTURE_WEAPON_PISTOL;
		geom->init(path1, path2);

		child = new Transform();
		child->translate(16, -.5f, -4);
		child->extraRot = glm::rotate(glm::mat4(1.0f), 90.0f / 180.0f * glm::pi<float>(), glm::vec3(0,1,0)) * child->extraRot;
		child->setCollisionShapeSphere(0.1f);
		dynamicsWorld->addRigidBody(child->getRigidbody());
		child->addChild(geom);
		objects.push_back(child);
		dirChild = new Transform();
		dirChild->translate(1, 0, 0);
		child->addChild(dirChild);

		child = new Transform();
		child->translate(-2.5, -.5f, 7);
		child->extraRot = glm::rotate(glm::mat4(1.0f), 90.0f / 180.0f * glm::pi<float>(), glm::vec3(0, 1, 0)) * child->extraRot;
		child->setCollisionShapeSphere(0.1f);
		dynamicsWorld->addRigidBody(child->getRigidbody());
		child->addChild(geom);
		objects.push_back(child);
		dirChild = new Transform();
		dirChild->translate(1, 0, 0);
		child->addChild(dirChild);

		child = new Transform();
		child->translate(-14, -.75, -7);
		child->extraRot = glm::rotate(glm::mat4(1.0f), 90.0f / 180.0f * glm::pi<float>(), glm::vec3(0, 1, 0)) * child->extraRot;
		child->setCollisionShapeSphere(0.1f);
		dynamicsWorld->addRigidBody(child->getRigidbody());
		child->addChild(geom);
		objects.push_back(child);
		dirChild = new Transform();
		dirChild->translate(1, 0, 0);
		child->addChild(dirChild);

		child = new Transform();
		child->translate(4, 0, -6.5);
		child->extraRot = glm::rotate(glm::mat4(1.0f), 90.0f / 180.0f * glm::pi<float>(), glm::vec3(0, 1, 0)) * child->extraRot;
		child->setCollisionShapeSphere(0.1f);
		child->rotate(yRot, 90);dynamicsWorld->addRigidBody(child->getRigidbody());
		child->addChild(geom);
		objects.push_back(child);
		dirChild = new Transform();
		dirChild->translate(1, 0, 0);
		child->addChild(dirChild);
	
	//CANS
		//Cans
		int id = 0;
		geom = new Geometry();
		path1 = MODEL_CAN;
		path2 = TEXTURE_CAN;
		geom->init(path1, path2);
		btVector3 colliderSize(0.1f, 0.125f, 0.1f);

		child = new Transform();
		child->translate(-.1, -.5f, -2.8);child->scale(0.002f);
		child->id = id++;
		child->setCollisionShapeCylinder(colliderSize);
		dynamicsWorld->addRigidBody(child->getRigidbody());
		child->addChild(geom);
		cans.push_back(child);

		child = new Transform();
		child->translate(-3, -.5f, 7.5);child->scale(0.002f);
		child->id = id++;
		child->setCollisionShapeCylinder(colliderSize);
		dynamicsWorld->addRigidBody(child->getRigidbody());
		child->addChild(geom);
		cans.push_back(child);

		//TODO add 13 more cans

}