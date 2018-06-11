#include "Scene.h"

void Scene::update(float deltaTime) {
	dynamicsWorld->stepSimulation(1.0f / 90.0f, 10);

	std::list<Transform*>::iterator it = objects.begin();
	std::list<Transform*>::iterator end = objects.end();
	for (it; it != end; ++it)
		(*it)->update();
	

}

void Scene::draw(glm::mat4 projection, glm::mat4 modelview, Shader* shaderProgram) {
	shaderProgram->use();
	shaderProgram->setMat4("projection", projection);
	shaderProgram->setMat4("view", modelview);

	std::list<Transform*>::iterator it = objects.begin();
	std::list<Transform*>::iterator end = objects.end();	
	for (it; it != end; ++it) {
		(*it)->draw(glm::mat4(1.0f), shaderProgram);
	}

	it = staticObjects.begin();
	end = staticObjects.end();
	for (it; it != end; ++it) {
		(*it)->draw(glm::mat4(1.0f), shaderProgram);
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
}

void Scene::initBullet() {
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
}

void Scene::initObjects(){
	Transform * child;
	Geometry * geom;
	std::string path1, path2;
	
	//STATIC OBJECTS
		//Ground Plane
		child = new Transform();
		geom = new Geometry();
		path1 = MODEL_SHAPE_CUBE;
		path2 = TEXTURE_CUBE_PPM;
		geom->init(path1, path2);
		
		child->translate(0, -1, 0);

		child->setCollisionShapePlane();
		dynamicsWorld->addRigidBody(child->getRigidbody());
		child->addChild(geom);
		staticObjects.push_back(child);
	//DYNAMIC OBJECTS
		//Test sphere
		child = new Transform();
		geom = new Geometry();
		path1 = MODEL_SHAPE_CUBE;
		path2 = TEXTURE_CUBE_PPM;
		geom->init(path1, path2);

		child->translate(0, 50, 0);
		child->setCollisionShapeSphere(1.0);
		dynamicsWorld->addRigidBody(child->getRigidbody()); 
		child->addChild(geom);
		objects.push_back(child);
}