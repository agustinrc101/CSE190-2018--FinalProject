#include "FrameManager.h"
#include "FilepathsAndDefinitions.h"

//Shaders
Shader colorShader;
Shader textureShader;
GLuint skyboxShader;
GLuint texShader;


//Skyboxes
Skybox* skybox;

//Networking
Networking * server;

<<<<<<< HEAD
//Scenegraph
Scene * sceneGraph;

//PlayerBody
TexturedCube * leftHand;
TexturedCube * rightHand;
//SoundManager
SoundManager* soundManager;

//Initializing the FrameManager Object *********************************************************************
FrameManager::FrameManager() {
	initShaders();
	initSkybox();
	initObjects();
	sceneGraph = new Scene();
	initSoundManager();
	server = new Networking();
}

void FrameManager::initShaders() {
	colorShader = Shader(SHADER_COLOR_VERT_PATH, SHADER_COLOR_FRAG_PATH);
	textureShader = Shader(SHADER_TEXTURE_VERT_PATH, SHADER_TEXTURE_FRAG_PATH);

	skyboxShader = LoadShaders(SHADER_SKY_VERT_PATH, SHADER_SKY_FRAG_PATH);
	texShader = LoadShaders(SHADER_TEX_VERT_PATH, SHADER_TEX_FRAG_PATH);
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

	skybox = new Skybox(SKY_TEX_PATH);
}

void FrameManager::initObjects() {
	leftHand = new TexturedCube(0.1f, TEXTURE_CUBE_PPM);
	rightHand = new TexturedCube(0.1f, TEXTURE_CUBE_PPM);
}

void FrameManager::initSoundManager() {
	soundManager = new SoundManager();
}

FrameManager::~FrameManager() {
	delete(skybox);
	delete(server);
	delete(sceneGraph);
	delete(leftHand);
	delete(rightHand);
}

//Update method (called before draw)*********************************************************************
void FrameManager::update(double deltaTime) {
	//Get and send updates from and to the server
	if (server->isConnected) {
		getNetworkData();
		server->sendPlayerBodyInfo(_head, _leftHand, _rightHand, _leftTrigger, _rightTrigger);
	}

	//do non-network things
	sceneGraph->update(deltaTime);
}

//Draw Methods (Called in order: drawSkybox, drawBody, draw)********************************************
void FrameManager::drawSkybox(glm::mat4 projection, glm::mat4 view) {
	//Draws the skybox(es)
	skybox->draw(projection, view, skyboxShader);
}

void FrameManager::drawBody(glm::mat4 projection, glm::mat4 view) {
	//Draws the player(s) head(s) and hands
	//Draw this player
	leftHand->draw(projection, view, texShader, glm::mat4(1.0f));
	rightHand->draw(projection, view, texShader, glm::mat4(1.0f));
	//Draw other player
		//draw head
		//draw lh
		//draw rh
}

void FrameManager::draw(glm::mat4 projection, glm::mat4 view) {
	//Draws the scene normally	
	sceneGraph->draw(projection, view, &textureShader);
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
	soundManager->testing(SOUND_FX_BULLET_FLYBY);
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
	if (f > MINPRESS) { pressedLeftGrip = true; }
	else { pressedLeftGrip = false; }
}

void FrameManager::pressRGrip(float f) {
	if (f > MINPRESS) { pressedRightGrip = true; }
	else { pressedRightGrip = false; }
}

//Locomotion ******************************************************************************************
	float _time = 0.0f;
	float _coolDown = 0.0f;
	float _minHandDistance = 0.25f;

	bool _curHigh = false;	//false for left, true for right
	float _leftY;
	float _rightY;

	bool isGetData = true;

	bool FrameManager::locomotion(float deltaTime) {
		if (pressedLeftGrip && pressedRightGrip) {
			_leftY = _leftHand[3][1];
			_rightY = _rightHand[3][1];

			_time += deltaTime;
			if (_time > 0.3f) {
				setUpLocomotionData();
				if (!_curHigh)
					locomotionHelper(_leftY, _rightY);
				else
					locomotionHelper(_rightY, _leftY);
			}
		}
		else {
			_time = 0.0f;
			isGetData = true;
		}

		if (_coolDown > 0.0f) {
			_coolDown -= deltaTime;
			return true;
		}
		
		return false;
	}

	void FrameManager::setUpLocomotionData() {
		if (isGetData) {
			isGetData = false;
			if (_leftY > _rightY)
				_curHigh = false;	//current highest hand is left
			else
				_curHigh = true;	//current highest hand is right
		}
	}

	void FrameManager::locomotionHelper(float higher, float lower) {
		float diff = glm::abs(higher - lower);
		if (diff < _minHandDistance) {
			if (!_curHigh) {
				if (_leftY < _rightY) {
					_curHigh = !_curHigh;
					_coolDown = 0.3f;
				}
			}
			else{
				if (_rightY < _leftY) {
					_curHigh = !_curHigh;
					_coolDown = 0.3f;
				}
			}
		}
	}
//Setters *********************************************************************************************
void FrameManager::setPlayer(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh) {
	//These values are obtained from MAIN
	_head = hmd;
	_leftHand = lh;
	_rightHand = rh;
}

void FrameManager::setPlayerHandPosition(glm::mat4 lh, glm::mat4 rh) {
	leftHand->toWorld = lh;
	leftHand->toWorld[3][0] = -leftHand->toWorld[3][0];
	leftHand->toWorld[3][2] = -leftHand->toWorld[3][2];
	rightHand->toWorld = rh;
	rightHand->toWorld[3][0] = -rightHand->toWorld[3][0];
	rightHand->toWorld[3][2] = -rightHand->toWorld[3][2];
}

