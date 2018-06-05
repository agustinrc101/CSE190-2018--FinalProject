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

FrameManager::FrameManager() {
	init();
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

void FrameManager::init() {
	initShaders();
}

void FrameManager::initShaders() {
	skyboxShader = Shader(SHADER_SKY_VERT_PATH, SHADER_SKY_FRAG_PATH);
	colorShader = Shader(SHADER_COLOR_VERT_PATH, SHADER_COLOR_FRAG_PATH);
	textureShader = Shader(SHADER_TEX_VERT_PATH, SHADER_TEX_FRAG_PATH);
}

FrameManager::~FrameManager() {
	delete(skybox);
}

void FrameManager::update(double deltaTime) {
	
}




//Draw Methods
void FrameManager::drawSkybox(glm::mat4 projection, glm::mat4 view) {
	skybox->draw(&skyboxShader, projection, view);
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
