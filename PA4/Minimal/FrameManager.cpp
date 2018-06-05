#include "FrameManager.h"

#define SHADER_COLOR_VERT_PATH "../assets/shaders/ColorShader.vert"
#define SHADER_COLOR_FRAG_PATH "../assets/shaders/ColorShader.frag"
#define SHADER_TEX_VERT_PATH "../assets/shaders/TextureShader.vert"
#define SHADER_TEX_FRAG_PATH "../assets/shaders/TextureShader.frag"
#define SHADER_SKY_VERT_PATH "../assets/shaders/SkyboxShader.vert"
#define SHADER_SKY_FRAG_PATH "../assets/shaders/SkyboxShader.frag"

#define CUBE_TEX_PATH "../assets/textures/pattern.ppm"
#define SKY_TEX_PATH "../assets/textures/sky/"

//Shaders
Shader colorShader;
Shader textureShader;
Shader skyboxShader;

//Skyboxes
Skybox* skybox;

//Networking
Networking * server;

FrameManager::FrameManager() {
	init();
	server = new Networking();
}

void FrameManager::init() {
	initShaders();

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

void FrameManager::initShaders() {
	skyboxShader = Shader(SHADER_SKY_VERT_PATH, SHADER_SKY_FRAG_PATH);
	colorShader = Shader(SHADER_COLOR_VERT_PATH, SHADER_COLOR_FRAG_PATH);
	textureShader = Shader(SHADER_TEX_VERT_PATH, SHADER_TEX_FRAG_PATH);
}

FrameManager::~FrameManager() {
	delete(skybox);
	delete(server);
}

//Update method (called before draw)
void FrameManager::update(double deltaTime) {
	
}

//Draw Methods (Called in order: drawSkybox, drawBody, draw)
void FrameManager::drawSkybox(glm::mat4 projection, glm::mat4 view) {
	//Draws the skybox(es)
	skybox->draw(&skyboxShader, projection, view);
}

void FrameManager::drawBody(glm::mat4 projection, glm::mat4 view) {
	//Draws the player(s) head(s) and hands

}

void FrameManager::draw(glm::mat4 projection, glm::mat4 view) {
	//Draws the scene normally	
}

//Setters
void FrameManager::setLeftMat(glm::mat4 m) {
	_leftRift = m;
}

void FrameManager::setRightMat(glm::mat4 m) {
	_rightRift = m;
}

void FrameManager::setHMDMat(glm::mat4 m) {
	_hmdRift = m;
}

//Buttons
const float MINPRESS = 0.7f;	//Strength of press needed for a valid grip/index button press

void FrameManager::pressA() {

}

void FrameManager::pressB() {

}

void FrameManager::pressX() {
	
}

void FrameManager::pressY() {
	
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
	if (f > MINPRESS) {}
	else {}
}

void FrameManager::pressRTrigger(float f) {
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
