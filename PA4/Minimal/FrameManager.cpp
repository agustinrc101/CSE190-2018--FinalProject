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
bool newSecondPlayer = true;
double lTTime = 0;
double rTTime = 0;

//SoundManager
SoundManager* soundManager;
SoundBox* src;
SoundEar* lis;
unsigned int music;
unsigned int explode;
unsigned int gunshot;
unsigned int impact;
SoundBox * backgroundMusic;
SoundBox * lGunSrc;
SoundBox * rGunSrc;
SoundBox * otherLGunSrc;
SoundBox * otherRGunSrc;
SoundBox * hitPoint1;
SoundBox * hitPoint2;
SoundBox * hitPoint3;

//Initializing the FrameManager Object *********************************************************************
FrameManager::FrameManager() {
	initShaders();
	initSkybox();
	initObjects();
	sceneGraph = new Scene();
	initSoundManager();
	server = new Networking();

	std::cout << "Size of internet packets: " << sizeof(Packet) << std::endl;
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
	Geometry * geom = new Geometry(); geom->init(MODEL_MASK, TEXTURE_MASK);
	otherPlayerHead->addChild(geom);
	otherPlayerHead->extraRot = glm::rotate(glm::mat4(1.0f), 180.0f / 180.0f * glm::pi<float>(), glm::vec3(0, 1, 0)) * otherPlayerHead->extraRot;
	otherPlayerHead->scale(0.01f);
	otherPlayerHead->translate(0, -10, 0);
	otherPlayerLH->toWorld[3] = glm::vec4(0, -10, 0, 1);
	otherPlayerRH->toWorld[3] = glm::vec4(0, -10, 0, 1);
}

void FrameManager::initSoundManager() {
	soundManager = new SoundManager();
	src = soundManager->createSource();
	backgroundMusic = soundManager->createSource();
	lGunSrc = soundManager->createSource();
	rGunSrc = soundManager->createSource();
	otherLGunSrc = soundManager->createSource();
	otherRGunSrc = soundManager->createSource();
	hitPoint1 = soundManager->createSource();
	hitPoint2 = soundManager->createSource();
	hitPoint3 = soundManager->createSource();

	lis = soundManager->createListener();
	music = backgroundMusic->loadSound(SOUND_MUSIC_SWEETWATER);
	explode = src->loadSound(SOUND_FX_EXPLOSION);
	gunshot = src->loadSound(SOUND_FX_GUNSHOT);
	impact = src->loadSound(SOUND_FX_BULLET_IMPACT);

	backgroundMusic->playSound(music);
}

FrameManager::~FrameManager() {
	delete(skybox);
	delete(server);
	delete(sceneGraph);
	delete(leftHand);
	delete(rightHand);
}

//Update method (called before draw)*********************************************************************
void FrameManager::update(double deltTime) {
	updateTime(deltTime);

	//std::cout << "isCOnnected: " << server->isConnected << ", other in session: " << server->checkIfOtherPlayerConnected() << std::endl;

	//Get and send updates from and to the server
	if (server->isConnected)
		server->sendPlayerBodyInfo(_head, _leftHand, _rightHand, grabbedObjL, grabbedObjR);
	if (server->checkIfOtherPlayerConnected()) {
		getNetworkData();

			if (newSecondPlayer) {
				server->sendImHerePacket();
				sceneGraph->resetCans();
				newSecondPlayer = false;
			}
	}
	else
			newSecondPlayer = true;
	//do non-network things
		//Proximity
		moveGrabbedObj();
		checkProximity();

		//Sound
		sceneGraph->update((double)deltTime);

		lis->setPos(_head[3]);
		lis->setOrien(_head);
		lis->setOrien(playerFW, playerUP);
}

void FrameManager::updateTime(double dT) {
	lTTime += dT;
	rTTime += dT;
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

	//Get triggers
	bool left, right;
	server->receiveTriggerInfo(left, right);
	if (left) {
		otherLGunSrc->setPos(otherLH[3]);
		otherLGunSrc->playSound(gunshot);
	}
	if (right) {
		otherRGunSrc->setPos(otherRH[3]);
		otherRGunSrc->playSound(gunshot);
	}

	server->resetTriggers();

	//Gets the can hit data
	std::vector<int> canHitData;
	server->receiveCanHitData(canHitData);

	for (int i = 0; i < canHitData.size(); i++)
		sceneGraph->removeLastHit(canHitData[i]);
	server->clearPacketVector();

	//Gets info stuff
	glm::vec3 hp;
	server->receiveHitInfo(hp);
	//TODO this breaks the audio buffer
	//hitPoint3->setPos(hp);
	//hitPoint3->playSound(impact);
}

//TODO if the other player is grabbing A and replaces it with B,
//		A will be in different positions for the client and the other user
void FrameManager::setOtherPlayerInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh) {
	//Update the other player's position, rotation
	otherPlayerHead->setToWorld(hmd, false);
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
	if (f > MINPRESS) {
		if (grabbedObjL > 1 && lTTime > COOLDOWN) {
			server->sendTriggerInfo(false);	//Tells other player that a gun was fire
			
			//Get pos
			glm::vec3 pos = sceneGraph->getPosition(grabbedObjL);
			{	//Play sound
				lGunSrc->setPos(pos);
				lGunSrc->playSound(gunshot);
			}
			//Get forwards direction
			glm::vec3 dir = sceneGraph->getForwardVector(grabbedObjL);
			glm::vec3 hitPoint = sceneGraph->shootRaycast(dir, pos);
			int lastHit = sceneGraph->lastHit;

			if (lastHit != -1 && sceneGraph->getCheckIfHit(lastHit)) {
				if (sceneGraph->removeLastHit(lastHit)) {
					server->sendCanHitData(lastHit); //send packet with the index that got hit
				}
				sceneGraph->lastHit = -1;
			}
			if (hitPoint.x > -10) {
				server->sendHitInfo(hitPoint); //send packet notifying pos that got hit
				
				//TODO (this breaks the sound buffer)play sound hitPoint
				//hitPoint1->setPos(hitPoint);
				//hitPoint1->playSound(impact);
			}
			lTTime = 0;
		}
	}
	else {}
}

void FrameManager::pressRTrigger(float f) {
	if (f > MINPRESS) {
		if (grabbedObjR > 1 && rTTime > COOLDOWN) {
			server->sendTriggerInfo(true);	//Tells other player that a gun was fire

			//Get pos
			glm::vec3 pos = sceneGraph->getPosition(grabbedObjR);
			{	//Play sound
				rGunSrc->setPos(pos);
				rGunSrc->playSound(gunshot);
			}
			//Get forwards direction
			glm::vec3 dir = sceneGraph->getForwardVector(grabbedObjR);
			glm::vec3 hitPoint = sceneGraph->shootRaycast(dir, pos);
			int lastHit = sceneGraph->lastHit;

			if (lastHit != -1 && sceneGraph->getCheckIfHit(lastHit)) {
				if (sceneGraph->removeLastHit(lastHit)) {
					server->sendCanHitData(lastHit); //send packet with the index that got hit
				}
				sceneGraph->lastHit = -1;
			}
			if (hitPoint.x > -10) {
				server->sendHitInfo(hitPoint); //send packet notifying pos that got hit

				//TODO (this breaks the sound buffer)play sound hitPoint
				//hitPoint2->setPos(hitPoint);
				//hitPoint2->playSound(impact);
			}
			rTTime = 0;
		}
	}
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

void FrameManager::setUpVector(float x, float y, float z) {
	playerUP = glm::vec3(x, y, z);
}

void FrameManager::setFwVector(float x, float y, float z) {
	playerFW = glm::vec3(x, y, z);
}
