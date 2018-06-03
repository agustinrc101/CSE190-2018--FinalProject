#include "FrameManager.h"

#define SHADER_COLOR_VERT_PATH "../assets/shaders/BasicShader.vert"
#define SHADER_COLOR_FRAG_PATH "../assets/shaders/BasicShader.frag"
#define SHADER_TEX_VERT_PATH "../assets/shaders/TextureShader.vert"
#define SHADER_TEX_FRAG_PATH "../assets/shaders/TextureShader.frag"
#define SHADER_RTEX_VERT_PATH "../assets/shaders/RTexShader.vert"
#define SHADER_RTEX_FRAG_PATH "../assets/shaders/RTexShader.frag"
#define SHADER_SKY_VERT_PATH "../assets/shaders/SkyboxShader.vert"
#define SHADER_SKY_FRAG_PATH "../assets/shaders/SkyboxShader.frag"

#define CUBE_TEX_PATH "../assets/textures/pattern.ppm"
#define SKY_TEX_LEFT_PATH "../assets/textures/cubemap/leftm/"
#define SKY_TEX_RIGHT_PATH "../assets/textures/cubemap/rightm/"
#define SKY_TEX_CUSTOM_PATH "../assets/textures/custommap/"

//Shaders
GLint colorShader;
GLint textureShader;
GLint skyboxShader;
GLint RTexShader;

//Skyboxes
Skybox * customSkybox;

FrameManager::FrameManager() {
	init();
}

void FrameManager::init() {
	initShaders();
}

void FrameManager::initShaders() {
	skyboxShader = LoadShaders(SHADER_SKY_VERT_PATH, SHADER_SKY_FRAG_PATH);
	colorShader = LoadShaders(SHADER_COLOR_VERT_PATH, SHADER_COLOR_FRAG_PATH);
	textureShader = LoadShaders(SHADER_TEX_VERT_PATH, SHADER_TEX_FRAG_PATH);
	RTexShader = LoadShaders(SHADER_RTEX_VERT_PATH, SHADER_RTEX_FRAG_PATH);
}

FrameManager::~FrameManager() {
	delete(customSkybox);

	glDeleteProgram(colorShader);
	glDeleteProgram(textureShader);
	glDeleteProgram(skyboxShader);
	glDeleteProgram(RTexShader);
}

void FrameManager::update(double deltaTime) {
	
}




//Draw Methods
void FrameManager::drawSkybox(glm::mat4 projection, glm::mat4 headPose) {
	customSkybox->draw(projection, headPose, skyboxShader);
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
