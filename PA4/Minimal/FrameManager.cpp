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

//Scenegraph
Scene * sceneGraph;

//PlayerBody
TexturedCube * leftHand;
TexturedCube * rightHand;

//OtherPlayer
Transform * otherPlayerHead;
TexturedCube * otherPlayerLH;
TexturedCube * otherPlayerRH;

//Vars
int closeObjL = -1;
int closeObjR = -1;
int grabbedObjL = -1;
int grabbedObjR = -1;
int otherPlayerGrabL = -1;
int otherPlayerGrabR = -1;

//Test objects
TexturedCube * soundCube;

//SoundManager
SoundManager* soundManager;
SoundBox* src;
SoundEar* lis;
unsigned int explode;

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
	textureShader = Shader(SHADER_TEX_VERT_PATH, SHADER_TEX_FRAG_PATH);

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
	leftHand = new TexturedCube(0.1f, TEXTURE_CUBE);
	rightHand = new TexturedCube(0.1f, TEXTURE_CUBE);
	otherPlayerLH = new TexturedCube(0.1f, TEXTURE_CUBE);
	otherPlayerRH = new TexturedCube(0.1f, TEXTURE_CUBE);
	otherPlayerHead = new Transform();
	Geometry * geom = new Geometry(); geom->init(MODEL_HORSE, TEXTURE_HORSE);
	otherPlayerLH->toWorld[3] = glm::vec4(0, -10, 0, 1);
	otherPlayerRH->toWorld[3] = glm::vec4(0, -10, 0, 1);

	soundCube = new TexturedCube(1.0f, TEXTURE_MATTHEW);
}

void FrameManager::initSoundManager() {
	soundManager = new SoundManager();
	src = soundManager->createSource();
	lis = soundManager->createListener();
	explode = src->loadSound(SOUND_FX_EXPLOSION);
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
		if (server->isConnected)
			server->sendPlayerBodyInfo(_head, _leftHand, _rightHand, grabbedObjL, grabbedObjR);
		if(server->otherInSession)
			getNetworkData();

	//do non-network things
		//Proximity
		moveGrabbedObj();
		checkProximity();

		//Sound
		sceneGraph->update((double)deltaTime);
	//	UsefulFunctions::printVector(_head[3]);
		lis->setPos(_head[3]);
		lis->setOrien(_head);
		glm::vec3 pos = glm::vec3(-soundCube->toWorld[3][0], soundCube->toWorld[3][1], -soundCube->toWorld[3][2]);
		src->setPos(soundCube->toWorld[3]);
}

//Draw Methods (Called in order: drawSkybox, drawBody, draw)********************************************
void FrameManager::drawSkybox(glm::mat4 projection, glm::mat4 view) {
	//Draws the skybox(es)
	skybox->draw(projection, view, skyboxShader);
}

void FrameManager::drawBody(glm::mat4 projection, glm::mat4 view) {
	//Draws the player(s) head(s) and hands
	//Draw this player
	if(grabbedObjL == -1)
		leftHand->draw(projection, view, texShader, glm::mat4(1.0f));
	if(grabbedObjR == -1)
		rightHand->draw(projection, view, texShader, glm::mat4(1.0f));
	//Draw other player
	textureShader.use();
	textureShader.setMat4("projection", projection);
	textureShader.setMat4("view", view);
	otherPlayerHead->draw(glm::mat4(1.0f), &textureShader);
	if (otherPlayerGrabL == -1)
		otherPlayerLH->draw(projection, view, texShader, glm::mat4(1.0f));
	if (otherPlayerGrabR == -1)
		otherPlayerRH->draw(projection, view, texShader, glm::mat4(1.0f));
}

void FrameManager::draw(glm::mat4 projection, glm::mat4 view) {
	//Draws the scene normally	
	//soundCube->draw(projection, view, texShader, (glm::mat4(1.0f)));
	sceneGraph->drawStaticObjects(projection, view, &textureShader);
	sceneGraph->drawObjects(projection, view, &textureShader, &colorShader, closeObjL, closeObjR);
}

//Network Helpers *************************************************************************************
void FrameManager::getNetworkData() {//Gets information for the other player's location
	//These values are obtained from the network
	//Gets other player's position
	glm::mat4 otherHmd, otherLH, otherRH;
	server->receivePlayerBodyInfo(otherHmd, otherLH, otherRH, otherPlayerGrabL, otherPlayerGrabR);
	setOtherPlayerInfo(otherHmd, otherLH, otherRH);

	//Gets object position (if affected by the other user)
	std::vector<Packet> objData;
	server->receiveObjectData(objData);

	//TODO --Play a sound whenever one of these objects are hit
	for (int i = 0; i < objData.size(); i++) {
		if (objData[i].objectId == -1)	//Ignore when objectId = -1
			continue;
		//objData[i].objectId : index of the object in the scenegraph
		// objData[i].m1      : new toWorld matrix of the object
	}

	server->clearPacketVector();
}

void FrameManager::setOtherPlayerInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh) {
	//Update the other player's position, rotation
	otherPlayerHead->setToWorld(hmd);
	otherPlayerLH->toWorld = lh;
	otherPlayerRH->toWorld = rh;

	if (otherPlayerGrabL != -1)
		sceneGraph->setObjMatrix(otherPlayerGrabL, lh);
	if (otherPlayerGrabR != -1)
		sceneGraph->setObjMatrix(otherPlayerGrabR, rh);

}

//Buttons *********************************************************************************************
void FrameManager::pressA() {
}

void FrameManager::pressB() {

}

void FrameManager::pressX() {
	src->playSound(explode);
}

void FrameManager::pressY() {
	server->retryConnection();	//If client is not connected, try to reconnect
}

void FrameManager::pressLJoystick() {

}

void FrameManager::pressRJoystick() {

}

void FrameManager::moveLJoystick(glm::vec2 xy) {
	soundCube->toWorld[3][0] += xy.x / 10.0f;
	soundCube->toWorld[3][2] -= xy.y / 10.0f;
}

void FrameManager::moveRJoystick(glm::vec2 xy) {

}

void FrameManager::pressLTrigger(float f) {
	if (f > MINPRESS) {
		if (grabbedObjL > 1) {
			//Get forwards direction
			glm::vec3 dir = sceneGraph->getForwardVector(grabbedObjL);
			//Get pos
			glm::vec3 pos = sceneGraph->getPosition(grabbedObjL);
			std::cout << "===\n";
			UsefulFunctions::printVector(dir);
			UsefulFunctions::printVector(pos);
			UsefulFunctions::printVector(_leftHand[3]);
		}
	}
	else {}
}

void FrameManager::pressRTrigger(float f) {
	if (f > MINPRESS) {}
	else {}
}

bool lGripIsPressed = false;
bool rGripIsPressed = false;

void FrameManager::pressLGrip(float f) {
	if (f > MINPRESS) { 
		pressedLeftGrip = true; 
	
		if (!lGripIsPressed) {
			lGripIsPressed = true;
			if (closeObjL != -1) {
				if (grabbedObjL == -1)
					grabbedObjL = closeObjL;
				else {
					//store obj pos
					glm::mat4 oldGrab = sceneGraph->getObjMatrix(grabbedObjL);
					glm::mat4 newGrab = sceneGraph->getObjMatrix(closeObjL);
					//set new pos for objs
					sceneGraph->setObjMatrix(grabbedObjL, newGrab);
					sceneGraph->setObjMatrix(closeObjL, oldGrab);
					//switch grabbedObj var
					grabbedObjL = closeObjL;
				}
			}
		}
	}
	else { pressedLeftGrip = false; lGripIsPressed = false; }
}

void FrameManager::pressRGrip(float f) {
	if (f > MINPRESS) { 
		pressedRightGrip = true; 

		if (!rGripIsPressed) {
			rGripIsPressed = true;
			if (closeObjR != -1) {
				if (grabbedObjR == -1)
					grabbedObjR = closeObjR;
				else {
					//store obj pos
					glm::mat4 oldGrab = sceneGraph->getObjMatrix(grabbedObjR);
					glm::mat4 newGrab = sceneGraph->getObjMatrix(closeObjR);
					//set new pos for objs
					sceneGraph->setObjMatrix(grabbedObjR, newGrab);
					sceneGraph->setObjMatrix(closeObjR, oldGrab);
					//switch grabbedObj var
					grabbedObjR = closeObjR;
				}
			}
		}
	}
	else { pressedRightGrip = false; rGripIsPressed = false; }
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

//Proximity *********************************************************************************************
const float maxDist = 0.25f;	//distance between hand and object
	
void FrameManager::checkProximity() {
	std::vector<glm::vec3> pos = sceneGraph->getListOfPositions();
	glm::vec3 lpos = _leftHand[3];
	glm::vec3 rpos = _rightHand[3];
	closeObjL = closeObjR = -1;

	for (int i = 0; i < pos.size(); i++) {
		if (glm::distance(lpos, pos[i]) <= maxDist) {
			if (closeObjL == -1 && i != grabbedObjL && i != grabbedObjR
				&& i != otherPlayerGrabL && i != otherPlayerGrabR)
				closeObjL = i;
		}
		if (glm::distance(rpos, pos[i]) <= maxDist) {
			if (closeObjR == -1 && i != grabbedObjL && i != grabbedObjR
				&& i != otherPlayerGrabL && i != otherPlayerGrabR)
				closeObjR = i;
		}

	}
}

void FrameManager::moveGrabbedObj() {
	if (grabbedObjL != -1)
		sceneGraph->setObjMatrix(grabbedObjL, _leftHand);
	if (grabbedObjR != -1)
		sceneGraph->setObjMatrix(grabbedObjR, _rightHand);
}

//Setters *********************************************************************************************
void FrameManager::setPlayer(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh) {
	//These values are obtained from MAIN
	_head = hmd;
	_leftHand = lh;
	_rightHand = rh;
	leftHand->toWorld = lh;
	rightHand->toWorld = rh;
}

