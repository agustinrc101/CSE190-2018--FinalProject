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
Transform * leftHand;
Transform * rightHand;
int leftLocomotionDir;
int rightLocomotionDir;

//OtherPlayer
Transform * otherPlayerHead;
Transform * otherPlayerLH;
Transform * otherPlayerRH;

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
float LEFTGUNCOOLDOWN = COOLDOWN;
float RIGHTGUNCOOLDOWN = COOLDOWN;
unsigned int leftWeapon;
unsigned int rightWeapon;

//SoundManager
SoundManager* soundManager;
SoundBox* src;
SoundEar* lis;
unsigned int music;
unsigned int explode;
unsigned int gunshot;
unsigned int impact;
unsigned int slap;
unsigned int submachineshot;
unsigned int playerHurt;
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
	sceneGraph = new Scene();

	Geometry * geom = new Geometry(); geom->init(MODEL_HAND, "");

	leftHand = new Transform();
	rightHand = new Transform();

	otherPlayerLH = new Transform();
	otherPlayerRH = new Transform();
	
	
	leftHand->addChild(geom); rightHand->addChild(geom); otherPlayerLH->addChild(geom); otherPlayerRH->addChild(geom);
	
	otherPlayerHead = new Transform();
	geom = new Geometry(); geom->init(MODEL_MASK, TEXTURE_MASK);
	otherPlayerHead->addChild(geom);

	otherPlayerHead->extraRot = glm::rotate(glm::mat4(1.0f), 180.0f / 180.0f * glm::pi<float>(), glm::vec3(0, 1, 0)) * otherPlayerHead->extraRot;
	otherPlayerHead->scale(0.01f);
	otherPlayerHead->translate(0, -10, 0);
	leftHand->extraRot = glm::rotate(glm::mat4(1.0f), 180.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)) * leftHand->extraRot;
	leftHand->scale(0.5f); leftHand->scale(1, -1, 1);
	leftHand->translate(0, -10, 0);
	rightHand->extraRot = glm::rotate(glm::mat4(1.0f), 180.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)) * rightHand->extraRot;
	rightHand->scale(0.5f); rightHand->scale(-1, -1, 1);
	rightHand->translate(0, -10, 0);
	otherPlayerLH->extraRot = glm::rotate(glm::mat4(1.0f), 180.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)) * otherPlayerLH->extraRot;
	otherPlayerLH->scale(0.5f); otherPlayerLH->scale(1, -1, 1);
	otherPlayerLH->translate(0, -10, 0);
	otherPlayerRH->extraRot = glm::rotate(glm::mat4(1.0f), 180.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)) * otherPlayerRH->extraRot;
	otherPlayerRH->scale(0.5f); otherPlayerRH->scale(-1, -1, 1);
	otherPlayerRH->translate(0, -10, 0);


	otherPlayerHead->id = -2;
	otherPlayerHead->setCollisionShapeSphere(0.25f);
	sceneGraph->setRigitBody(otherPlayerHead->getRigidbody());
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
	slap = src->loadSound(SOUND_FX_SLAP);
	submachineshot = src->loadSound(SOUND_FX_GUN_SUBMACHINE);
	playerHurt = src->loadSound(SOUND_FX_PLAYER_HURT);

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
		//lis->setOrien(playerFW, playerUP);

		soundManager->update();
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
	textureShader.use();
	textureShader.setMat4("projection", projection);
	textureShader.setMat4("view", view);
	//Draws the player(s) head(s) and hands
	//Draw other player
	otherPlayerHead->draw(glm::mat4(1.0f), &textureShader);
	
	colorShader.use();
	colorShader.setMat4("projection", projection);
	colorShader.setMat4("view", view);
	colorShader.setVec3("rgb", glm::vec3(210.0f / 255.0f, 249.0f / 255.0f, 37.0f / 255.0f));

	if (otherPlayerGrabL == -1)
		otherPlayerLH->draw(glm::mat4(1.0f), &colorShader);
	if (otherPlayerGrabR == -1)
		otherPlayerRH->draw(glm::mat4(1.0f), &colorShader);

	//Draw this player
	if(grabbedObjL == -1)
		leftHand->draw(glm::mat4(1.0f), &colorShader);
	if(grabbedObjR == -1)
		rightHand->draw(glm::mat4(1.0f), &colorShader);
}

void FrameManager::draw(glm::mat4 projection, glm::mat4 view) {
	//Draws the scene normally	
	sceneGraph->drawStaticObjects(projection, view, &textureShader);
	sceneGraph->drawObjects(projection, view, &textureShader, &colorShader, closeObjL, closeObjR);
}

//Network Helpers *************************************************************************************
void FrameManager::getNetworkData() {
	//Gets information for the other player's location
	//These values are obtained from the network
	//Gets other player's position
	glm::mat4 otherHmd, otherLH, otherRH;
	server->receivePlayerBodyInfo(otherHmd, otherLH, otherRH, otherPlayerGrabL, otherPlayerGrabR);
	setOtherPlayerInfo(otherHmd, otherLH, otherRH);

	//Get triggers
	bool left, right;
	unsigned int weapon;
	server->receiveTriggerInfo(left, right, leftWeapon, rightWeapon);
	/*
	if (left) {
		otherLGunSrc->setPos(otherLH[3]);
		switch(leftWeapon)
		{
			case WeaponType::HAND:
			{
				otherLGunSrc->playSound(slap);
				break;
			}
			case WeaponType::GRENADE:
			{
				otherLGunSrc->playSound(explode);
				break;
			}
			case WeaponType::PISTOL:
			{
				otherLGunSrc->playSound(gunshot);
				break;
			}
			case WeaponType::SUBMACHINE:
			{
				otherLGunSrc->playSound(submachineshot);
				break;
			}
		}
	}
	if (right) {
		otherRGunSrc->setPos(otherRH[3]);
		otherRGunSrc->playSound(gunshot);
		switch(rightWeapon)
		{
			case WeaponType::HAND:
			{
				otherRGunSrc->playSound(slap);
				break;
			}
			case WeaponType::GRENADE:
			{
				otherRGunSrc->playSound(explode);
				break;
			}
			case WeaponType::PISTOL:
			{
				otherRGunSrc->playSound(gunshot);
				break;
			}
			case WeaponType::SUBMACHINE:
			{
				otherRGunSrc->playSound(submachineshot);
				break;
			}
		}
	}
	*/
	server->resetTriggers();

	//Gets the can hit data
	std::vector<int> canHitData;
	server->receiveCanHitData(canHitData);
	bool hitPlayer = false;

	for (int i = 0; i < canHitData.size(); i++) {
		if (canHitData[i] >= 0)
			sceneGraph->removeLastHit(canHitData[i]);
		else if (canHitData[i] == -2)
			hitPlayer = true;
	}
	server->clearPacketVector();

	//Gets info stuff
	glm::vec3 hp;
	server->receiveHitInfo(hp);

	/*
	if (hitPlayer) {
		hitPoint3->setPos(_head[3]);
		hitPoint3->playSound(playerHurt);
	}
	else {
		hitPoint3->setPos(hp);
		hitPoint3->playSound(impact, 3);
	}
	*/
}

//TODO if the other player is grabbing A and replaces it with B,
//		A will be in different positions for the client and the other user
void FrameManager::setOtherPlayerInfo(glm::mat4 hmd, glm::mat4 lh, glm::mat4 rh) {
	//Update the other player's position, rotation
	otherPlayerHead->setToWorld(hmd);
	otherPlayerLH->setToWorld(lh, false);
	otherPlayerRH->setToWorld(rh, false);

	if (otherPlayerGrabL != -1)
		sceneGraph->setObjMatrix(otherPlayerGrabL, lh);
	if (otherPlayerGrabR != -1)
		sceneGraph->setObjMatrix(otherPlayerGrabR, rh);

}

//Buttons *********************************************************************************************
void FrameManager::pressA() {
	//soundManager->testing(SOUND_FX_EXPLOSION);
	if (grabbedObjR != -1)
	{
		glm::mat4 oldGrab = sceneGraph->getObjMatrix(grabbedObjR);
		sceneGraph->setObjMatrix(grabbedObjR, oldGrab);
		grabbedObjR = -1;
	}
}

void FrameManager::pressB() {
	sceneGraph->resetCans();
}

void FrameManager::pressX() {
	if (grabbedObjL != -1)
	{
		glm::mat4 oldGrab = sceneGraph->getObjMatrix(grabbedObjL);
		sceneGraph->setObjMatrix(grabbedObjL, oldGrab);
		grabbedObjL = -1;
	}
}

void FrameManager::pressY() {
	server->retryConnection();	//If client is not connected, try to reconnect
}

void FrameManager::pressLJoystick() {

}

void FrameManager::pressRJoystick() {

}

void FrameManager::moveLJoystick(glm::vec2 xy) {
	if (xy.y < 0)
	{
		leftLocomotionDir = -1;
	}
	else
	{
		leftLocomotionDir = 1;
	}
}

void FrameManager::moveRJoystick(glm::vec2 xy) {
	if (xy.y < 0)
	{
		rightLocomotionDir = -1;
	}
	else
	{
		rightLocomotionDir = 1;
	}
}

void FrameManager::pressLTrigger(float f) {
	if (f > MINPRESS) {
		if (grabbedObjL > -1 && lTTime > LEFTGUNCOOLDOWN) {
			
			//Get pos
			glm::vec3 pos = sceneGraph->getPosition(grabbedObjL);
			{	//Play sound
				lGunSrc->setPos(pos);
				// selecting the correct sound to play
				if (grabbedObjL > 5)
				{
					server->sendTriggerInfo(false, leftWeapon, rightWeapon);	//Tells other player that a gun was fire
					lGunSrc->playSound(submachineshot);
				}
				else if (grabbedObjL > 1)
				{
					server->sendTriggerInfo(false, leftWeapon, rightWeapon);	//Tells other player that a gun was fire
					lGunSrc->playSound(gunshot);
				}
				else
				{
					lGunSrc->playSound(explode);
				}
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
				if (lastHit == -2) {
					hitPoint2->setPos(hitPoint);
					hitPoint2->playSound(playerHurt);
				}
				else {
					hitPoint2->setPos(hitPoint);
					hitPoint2->playSound(impact, 3);
				}
			}
			lTTime = 0;
		}
		else if(lTTime > LEFTGUNCOOLDOWN)
		{
			lGunSrc->setPos(_leftHand[3]);
			lGunSrc->playSound(slap);
			lTTime = 0;
		}
	}
	else {}
}

void FrameManager::pressRTrigger(float f) {
	if (f > MINPRESS) {
		if (grabbedObjR > -1 && rTTime > RIGHTGUNCOOLDOWN) {

			//Get pos
			glm::vec3 pos = sceneGraph->getPosition(grabbedObjR);
			{	//Play sound
				rGunSrc->setPos(pos);
				//std::cerr << grabbedObjR << std::endl;
				// selecting the correct sound to play
				if (grabbedObjR > 5)
				{
					server->sendTriggerInfo(true, leftWeapon, rightWeapon);	//Tells other player that a gun was fire
					rGunSrc->playSound(submachineshot);
				}
				else if(grabbedObjR > 1)
				{
					server->sendTriggerInfo(true, leftWeapon, rightWeapon);	//Tells other player that a gun was fire
					rGunSrc->playSound(gunshot);
				}
				else
				{
					rGunSrc->playSound(explode);
				}
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
				if (lastHit == -2) {
					hitPoint2->setPos(hitPoint);
					hitPoint2->playSound(playerHurt);
				}
				else {
					hitPoint2->setPos(hitPoint);
					hitPoint2->playSound(impact, 3);
				}
			}
			rTTime = 0;
		}
		else if(rTTime > RIGHTGUNCOOLDOWN)
		{
			rGunSrc->setPos(_rightHand[3]);
			rGunSrc->playSound(slap);
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
			// Changing Cooldown based on weapon
			// submachines
			if (grabbedObjL > 5)
			{
				LEFTGUNCOOLDOWN = 0.1f;
			}
			// pistols
			else if (grabbedObjL > 1)
			{
				LEFTGUNCOOLDOWN = 1.0f;
			}
			// grenades
			else if (grabbedObjL > -1)
			{
				LEFTGUNCOOLDOWN = 2.0f;
			}
			// hand
			else
			{
				LEFTGUNCOOLDOWN = 0.7f;
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
			// Changing Cooldown based on weapon
			// submachines
			if (grabbedObjR > 5)
			{
				RIGHTGUNCOOLDOWN = 0.1f;
			}
			// pistols
			else if (grabbedObjR > 1)
			{
				RIGHTGUNCOOLDOWN = 1.0f;
			}
			// grenades
			else if (grabbedObjR > -1)
			{
				RIGHTGUNCOOLDOWN = 2.0f;
			}
			// hand
			else
			{
				RIGHTGUNCOOLDOWN = 0.7f;
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

int FrameManager::locomotion(float deltaTime) {
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
			return leftLocomotionDir | rightLocomotionDir;
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
	leftHand->setToWorld(lh, false);
	rightHand->setToWorld(rh, false);
}

void FrameManager::setUpVector(float x, float y, float z) {
	playerUP = glm::vec3(x, y, z);
}

void FrameManager::setFwVector(float x, float y, float z) {
	playerFW = glm::vec3(x, y, z);
}
