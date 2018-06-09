#include "FrameManager.h"
#include "FilepathsAndDefinitions.h"

//Shaders
Shader colorShader;
Shader textureShader;
Shader skyboxShader;

//Skyboxes
Skybox* skybox;

//Networking
Networking * server;

//Initializing the FrameManager Object *********************************************************************
FrameManager::FrameManager() {
	initShaders();
	initSkybox();
	initObjects();
	server = new Networking();
}

void FrameManager::initShaders() {
	skyboxShader = Shader(SHADER_SKY_VERT_PATH, SHADER_SKY_FRAG_PATH);
	colorShader = Shader(SHADER_COLOR_VERT_PATH, SHADER_COLOR_FRAG_PATH);
	textureShader = Shader(SHADER_TEX_VERT_PATH, SHADER_TEX_FRAG_PATH);
}

void FrameManager::initSkybox() {

	std::vector<std::string> faces
	{
		std::string(SKY_TEX_PATH) + "nz.tga",
		std::string(SKY_TEX_PATH) + "pz.tga",
		std::string(SKY_TEX_PATH) + "py.tga",
		std::string(SKY_TEX_PATH) + "ny.tga",
		std::string(SKY_TEX_PATH) + "px.tga",
		std::string(SKY_TEX_PATH) + "nx.tga",
	};

	skybox = new Skybox(faces, &skyboxShader);
}

void FrameManager::initObjects() {

}

FrameManager::~FrameManager() {
	delete(skybox);
	delete(server);
}

//Update method (called before draw)*********************************************************************
void FrameManager::update(double deltaTime) {
	//Get and send updates from and to the server
	if (server->isConnected) {
		getNetworkData();
		server->sendPlayerBodyInfo(_head, _leftHand, _rightHand, _leftTrigger, _rightTrigger);
	}

	//do non-network things
	//
}

//Draw Methods (Called in order: drawSkybox, drawBody, draw)********************************************
void FrameManager::drawSkybox(glm::mat4 projection, glm::mat4 view) {
	//Draws the skybox(es)
	skybox->draw(&skyboxShader, projection, view);
}

void FrameManager::drawBody(glm::mat4 projection, glm::mat4 view) {
	//Draws the player(s) head(s) and hands
	//Draw this player
		//draw lh
		//draw rh
	//Draw other player
		//draw head
		//draw lh
		//draw rh
}

void FrameManager::draw(glm::mat4 projection, glm::mat4 view) {
	//Draws the scene normally	
	//scenegraph1->draw(projection, view);
	//scenegraph2->draw(projection, view);
}

//Network Helpers *************************************************************************************
void FrameManager::getNetworkData() {//Gets information for the other player's location
	//These values are obtained from the network
	//Gets other player's position
	glm::mat4 otherHmd, otherLH, otherRH;
	float triggerL, triggerR;
	server->receivePlayerBodyInfo(otherHmd, otherLH, otherRH, triggerL, triggerR);
	setOtherPlayerInfo(otherHmd, otherLH, otherRH, triggerL, triggerR);

	//Gets object position (if affected by the other user)
	std::vector<Packet> objData;
	server->receiveObjectData(objData);

	//TODO
	for (int i = 0; i < objData.size(); i++) {
		if (objData[i].objectId == -1)	//Ignore when objectId = -1
			continue;
		//objData[i].objectId : index of the object in the scenegraph
		// objData[i].m1      : new toWorld matrix of the object
	}

	server->clearPacketVector();
}

void FrameManager::setOtherPlayerInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh, float lT, float rT) {
	//TODO
	//When only one player is in the session, the server sets all matrices to the 
	//	identity matrix and the trigger values to -1 so...
	if (lT == -1 || rT == -1) {
		//Place obj wherever we want (or disable drawing)
		return;
	}

	//Update the other player's position, rotation, and trigger values

}

//Buttons *********************************************************************************************
void FrameManager::pressA() {
}

void FrameManager::pressB() {
	
}

void FrameManager::pressX() {
	
}

void FrameManager::pressY() {
	server->retryConnection();	//If client is not connected, try to reconnect
}

void FrameManager::pressLJoystick() {

}

void FrameManager::pressRJoystick() {

}

void FrameManager::moveLJoystick(glm::vec2 xy) {

}

void FrameManager::moveRJoystick(glm::vec2 xy) {

}

void FrameManager::pressLTrigger(float f) {
	_leftTrigger = f;

	if (f > MINPRESS) {}
	else {}
}

void FrameManager::pressRTrigger(float f) {
	_rightTrigger = f;

	if (f > MINPRESS) {}
	else {}
}

void FrameManager::pressLGrip(float f) {
	if (f > MINPRESS) {}
	else {}
}

void FrameManager::pressRGrip(float f) {
	if (f > MINPRESS) {}
	else {}
}

//Setters *********************************************************************************************
void FrameManager::setPlayer(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh) {
	//These values are obtained from MAIN
	_head = hmd;
	_leftHand = lh;
	_rightHand = rh;
}

