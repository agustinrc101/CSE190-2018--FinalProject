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
GLint colorShader;
GLint textureShader;
GLint skyboxShader;

//Skyboxes
Skybox * skybox;

FrameManager::FrameManager() {
	init();
	skybox = new Skybox(SKY_TEX_PATH);
}

void FrameManager::init() {
	initShaders();
}

void FrameManager::initShaders() {
	skyboxShader = LoadShaders(SHADER_SKY_VERT_PATH, SHADER_SKY_FRAG_PATH);
	colorShader = LoadShaders(SHADER_COLOR_VERT_PATH, SHADER_COLOR_FRAG_PATH);
	textureShader = LoadShaders(SHADER_TEX_VERT_PATH, SHADER_TEX_FRAG_PATH);
}

FrameManager::~FrameManager() {
	delete(skybox);

	glDeleteProgram(colorShader);
	glDeleteProgram(textureShader);
	glDeleteProgram(skyboxShader);
}

void FrameManager::update(double deltaTime) {
	
}




//Draw Methods
void FrameManager::drawSkybox(glm::mat4 projection, glm::mat4 headPose) {
	skybox->draw(projection, headPose, skyboxShader);
}

void FrameManager::drawControllers(glm::mat4 projection, glm::mat4 headPose) {

}

void FrameManager::draw(glm::mat4 projection, glm::mat4 headPose) {
	
}






//Setters
void FrameManager::setControllerPositions(glm::vec3 l, glm::vec3 r) {

}

void FrameManager::setHMDPos(glm::vec3 pos) {
	
}


//Buttons
void FrameManager::pressA() {

}

void FrameManager::pressB() {

}

void FrameManager::pressX() {
	
}

void FrameManager::pressY() {
	
}
