#include "LightManager.h"

LightManager::LightManager()
{
	ambient_intensity = 0.0f;

	point_lights = vector<Light*>();
	spot_lights = vector<Light*>();
	directional_lights = vector<Light*>();

	point_size = spot_size = directional_size = 0;
	point_count = spot_count = directional_count = 0;

	point_positions   = new GLfloat[0];
	point_intensities = new GLfloat[0];
	point_colors      = new GLfloat[0];
	point_shininess   = new GLfloat[0];

	spot_positions   = new GLfloat[0];
	spot_intensities = new GLfloat[0];
	spot_colors      = new GLfloat[0];
	spot_shininess   = new GLfloat[0];
	spot_directions  = new GLfloat[0];
	spot_angles      = new GLfloat[0];

	directional_positions   = new GLfloat[0];
	directional_intensities = new GLfloat[0];
	directional_colors      = new GLfloat[0];
	directional_shininess   = new GLfloat[0];
	directional_directions  = new GLfloat[0];

	ambient_color = new GLfloat[3];
	ambient_color[0] = ambient_color[1] = ambient_color[2] = 0.0f;
}

LightManager::~LightManager()
{
	for (uint i = 0; i < point_lights.size(); ++i) {
		delete point_lights[i];
	}
	for (uint i = 0; i < spot_lights.size(); ++i) {
		delete spot_lights[i];
	}
	for (uint i = 0; i < directional_lights.size(); ++i) {
		delete directional_lights[i];
	}

	delete[] point_positions;
	delete[] point_intensities;
	delete[] point_colors;
	delete[] point_shininess;

	delete[] spot_positions;
	delete[] spot_intensities;
	delete[] spot_colors;
	delete[] spot_shininess;
	delete[] spot_directions;
	delete[] spot_angles;

	delete[] directional_positions;
	delete[] directional_intensities;
	delete[] directional_colors;
	delete[] directional_shininess;
	delete[] directional_directions;

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	glGenFramebuffers(1, &shadow_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, shadow_framebuffer);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.

						   // Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "DepthBuffer error" << std::endl;
		getchar();
		exit(-1);
	}
}

LightManager* LightManager::AllocLights(uint point_n, uint spot_n, uint directional_n) {
	GLfloat* newpos;
	GLfloat* newint;
	GLfloat* newcol;
	GLfloat* newshi;
	GLfloat* newdir;
	GLfloat* newang;

	/***********/
	/** Point **/
	/***********/
	if (point_size < point_n){
		point_lights.resize(point_n);
		
		newpos = new GLfloat[point_n * N_AXIS];
		newint = new GLfloat[point_n];
		newcol = new GLfloat[point_n * N_AXIS];
		newshi = new GLfloat[point_n];

		memcpy(newpos, point_positions,   point_size * N_AXIS * sizeof(GLfloat));
		memcpy(newint, point_intensities, point_size * sizeof(GLfloat));
		memcpy(newcol, point_colors,      point_size * N_AXIS * sizeof(GLfloat));
		memcpy(newshi, point_shininess,   point_size * sizeof(GLfloat));

		delete[] point_positions;
		delete[] point_intensities;
		delete[] point_colors;
		delete[] point_shininess;

		point_positions   = newpos;
		point_intensities = newint;
		point_colors      = newcol;
		point_shininess   = newshi;
	}

	for (uint i = point_size; i < point_n; ++i) {
		point_lights[i] = new Light(glm::vec4(0.0f), glm::vec3(0.0f), 0.0f, 0.0f, LIGHT_TYPE::POINT);
	}

	point_size = point_n;

	/**********/
	/** Spot **/
	/**********/
	if (spot_size < spot_n){
		spot_lights.resize(spot_n);

		newpos = new GLfloat[spot_n * N_AXIS];
		newint = new GLfloat[spot_n];
		newcol = new GLfloat[spot_n * N_AXIS];
		newshi = new GLfloat[spot_n];
		newdir = new GLfloat[spot_n * N_AXIS];
		newang = new GLfloat[spot_n * 2];

		memcpy(newpos, spot_positions,   spot_size * N_AXIS * sizeof(GLfloat));
		memcpy(newint, spot_intensities, spot_size * sizeof(GLfloat));
		memcpy(newcol, spot_colors,      spot_size * N_AXIS * sizeof(GLfloat));
		memcpy(newshi, spot_shininess,   spot_size * sizeof(GLfloat));
		memcpy(newdir, spot_directions,  spot_size * N_AXIS * sizeof(GLfloat));
		memcpy(newang, spot_angles,      spot_size * sizeof(GLfloat) * 2);

		delete [] spot_positions;
		delete [] spot_intensities;
		delete [] spot_colors;
		delete [] spot_shininess;
		delete [] spot_directions;
		delete [] spot_angles;

		spot_positions   = newpos;
		spot_intensities = newint;
		spot_colors      = newcol;
		spot_shininess   = newshi;
		spot_directions  = newdir;
		spot_angles      = newang;
	}

	for (uint i = spot_size; i < spot_n; ++i) {
		spot_lights[i] = new SpotLight(glm::vec4(0.0f), glm::vec3(0.0f), 0.0f, 0.0f,glm::vec3(0.0f),0.0f,0.0f);
	}

	spot_size = spot_n;

	/*****************/
	/** Directional **/
	/*****************/
	if (directional_size < directional_n){
		directional_lights.resize(directional_n);

		newpos = new GLfloat[directional_n * N_AXIS];
		newint = new GLfloat[directional_n];
		newcol = new GLfloat[directional_n * N_AXIS];
		newshi = new GLfloat[directional_n];
		newdir = new GLfloat[directional_n * N_AXIS];

		memcpy(newpos, directional_positions,   directional_size * N_AXIS * sizeof(GLfloat));
		memcpy(newint, directional_intensities, directional_size * sizeof(GLfloat));
		memcpy(newcol, directional_colors,      directional_size * N_AXIS * sizeof(GLfloat));
		memcpy(newshi, directional_shininess,   directional_size * sizeof(GLfloat));
		memcpy(newdir, directional_directions,  directional_size * N_AXIS * sizeof(GLfloat));

		delete [] directional_positions;
		delete [] directional_intensities;
		delete [] directional_colors;
		delete [] directional_shininess;
		delete [] directional_directions;

		directional_positions   = newpos;
		directional_intensities = newint;
		directional_colors      = newcol;
		directional_shininess   = newshi;
		directional_directions  = newdir;
	}

	for (uint i = directional_size; i < directional_n; ++i) {
		directional_lights[i] = new DirectionalLight(glm::vec4(0.0f), glm::vec3(0.0f), 0.0f, 0.0f, glm::vec3(0.0f));
	}

	directional_size = directional_n;

	return GetInstance();
}

LightManager* LightManager::GetInstance(){
	static LightManager* Instance = new LightManager();
	return Instance;
}

LightManager* LightManager::Push(Light* l, LIGHT_TYPE type) {
	if (type == LIGHT_TYPE::UNDEFINED)
		type = l->GetType();

	if (type == LIGHT_TYPE::POINT && point_count == point_size) {
		std::cout << "warning: reallocating lights is expensive. Initializing LightManager with a higher light count is preferred" << std::endl;
		AllocLights(point_size + 1, spot_size, directional_size);
	}
	if (type == LIGHT_TYPE::SPOT && spot_count == spot_size) {
		std::cout << "warning: reallocating lights is expensive. Initializing LightManager with a higher light count is preferred" << std::endl;
		AllocLights(point_size, spot_size + 1, directional_size);
	}
	if (type == LIGHT_TYPE::DIRECTIONAL && directional_count == directional_size) {
		std::cout << "warning: reallocating lights is expensive. Initializing LightManager with a higher light count is preferred" << std::endl;
		AllocLights(point_size, spot_size, directional_size + 1);
	}

	switch (type) {
		case LIGHT_TYPE::POINT:
			delete point_lights[point_count];
			point_lights[point_count++] = l;
			break;
		case LIGHT_TYPE::SPOT:
			delete spot_lights[spot_count];
			spot_lights[spot_count++] = l;
			break;
		case LIGHT_TYPE::DIRECTIONAL:
			delete directional_lights[directional_count];
			directional_lights[directional_count++] = l;
			break;
	}

	return this;
}

size_t LightManager::GetNPointLights() {
	return point_size;
}

size_t LightManager::GetNSpotLights() {
	return spot_size;
}

size_t LightManager::GetNDirectionalLights() {
	return directional_size;
}

void LightManager::Update(double dt) {
	for (uint i = 0; i < point_count; ++i) {
		point_lights[i]->Update(dt);
	}
	for (uint i = 0; i < spot_count; ++i) {
		spot_lights[i]->Update(dt);
	}
	for (uint i = 0; i < directional_count; ++i) {
		directional_lights[i]->Update(dt);
	}

	Compile();
}

//@TODO set update state to Light so we can know if the arrays should be re-compilled
void LightManager::Compile() {
	glm::vec4 aux;
	for (uint i = 0; i < point_size; ++i) {
		point_positions[i * N_AXIS + 0] = point_lights[i]->GetPosition()[0];
		point_positions[i * N_AXIS + 1] = point_lights[i]->GetPosition()[1];
		point_positions[i * N_AXIS + 2] = point_lights[i]->GetPosition()[2];

		point_intensities[i] = point_lights[i]->GetIntensity();

		aux = clamp(point_lights[i]->GetColor());
		point_colors[i * N_AXIS + 0] = aux.r;
		point_colors[i * N_AXIS + 1] = aux.g;
		point_colors[i * N_AXIS + 2] = aux.b;

		point_shininess[i] = point_lights[i]->GetShininess();
	}

	for (uint i = 0; i < spot_size; ++i) {
		spot_positions[i * N_AXIS + 0] = spot_lights[i]->GetPosition()[0];
		spot_positions[i * N_AXIS + 1] = spot_lights[i]->GetPosition()[1];
		spot_positions[i * N_AXIS + 2] = spot_lights[i]->GetPosition()[2];

		spot_intensities[i] = spot_lights[i]->GetIntensity();

		aux = clamp(spot_lights[i]->GetColor());
		spot_colors[i * N_AXIS + 0] = aux.r;
		spot_colors[i * N_AXIS + 1] = aux.g;
		spot_colors[i * N_AXIS + 2] = aux.b;

		spot_shininess[i] = spot_lights[i]->GetShininess();

		spot_directions[i * N_AXIS + 0] = ((SpotLight *)spot_lights[i])->GetDirection()[0];
		spot_directions[i * N_AXIS + 1] = ((SpotLight *)spot_lights[i])->GetDirection()[1];
		spot_directions[i * N_AXIS + 2] = ((SpotLight *)spot_lights[i])->GetDirection()[2];

		spot_angles[i * 2 + 0] = ((SpotLight *)spot_lights[i])->GetAngle();
		spot_angles[i * 2 + 1] = ((SpotLight *)spot_lights[i])->GetAngleSoft();
	}

	for (uint i = 0; i < directional_size; ++i) {
		directional_positions[i * N_AXIS + 0] = directional_lights[i]->GetPosition()[0];
		directional_positions[i * N_AXIS + 1] = directional_lights[i]->GetPosition()[1];
		directional_positions[i * N_AXIS + 2] = directional_lights[i]->GetPosition()[2];

		directional_intensities[i] = directional_lights[i]->GetIntensity();

		aux = clamp(directional_lights[i]->GetColor());
		directional_colors[i * N_AXIS + 0] = aux.r;
		directional_colors[i * N_AXIS + 1] = aux.g;
		directional_colors[i * N_AXIS + 2] = aux.b;

		directional_shininess[i] = directional_lights[i]->GetShininess();
		
		directional_directions[i * N_AXIS + 0] = ((DirectionalLight *)directional_lights[i])->GetDirection()[0];
		directional_directions[i * N_AXIS + 1] = ((DirectionalLight *)directional_lights[i])->GetDirection()[1];
		directional_directions[i * N_AXIS + 2] = ((DirectionalLight *)directional_lights[i])->GetDirection()[2];
	}
}

void LightManager::GenerateShadows(std::vector<MeshObject*> items) {
	//glBindFramebuffer(GL_FRAMEBUFFER, shadow_framebuffer);
	glViewport(0, 0, 1024, 1024);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 inv_mat = glm::inverse(*directional_lights[0]->Transform());
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);

	glm::mat4 lightmat = depthProjectionMatrix * inv_mat;

	for (uint i = 0; i < items.size(); ++i) {
		items[i]->DrawDepthMap(lightmat); 

		//for (uint j = 0; j < point_size; ++j) {

		//}

		//for (uint j = 0; j < spot_size; ++j) {

		//}

		//for (uint j = 0; j < directional_size; ++j) {

		//}
	}
}

/**
 * Get Point Data
 * */
GLfloat* LightManager::GetPointPositions() {
	return point_positions;
}

GLfloat* LightManager::GetPointIntensities() {
	return point_intensities;
}

GLfloat* LightManager::GetPointColors() {
	return point_colors;
}

GLfloat * LightManager::GetPointShininess() {
	return point_shininess;
}

/**
 * Get Spot Data
 * */
GLfloat* LightManager::GetSpotPositions() {
	return spot_positions;
}

GLfloat* LightManager::GetSpotIntensities() {
	return spot_intensities;
}

GLfloat* LightManager::GetSpotColors() {
	return spot_colors;
}

GLfloat * LightManager::GetSpotShininess() {
	return spot_shininess;
}

GLfloat * LightManager::GetSpotDirections() {
	return spot_directions;
}

GLfloat * LightManager::GetSpotAngles() {
	return spot_angles;
}

/**
 * Get Directional Data
 * */
GLfloat* LightManager::GetDirectionalPositions() {
	return directional_positions;
}

GLfloat* LightManager::GetDirectionalIntensities() {
	return directional_intensities;
}

GLfloat* LightManager::GetDirectionalColors() {
	return directional_colors;
}

GLfloat * LightManager::GetDirectionalShininess() {
	return directional_shininess;
}

GLfloat * LightManager::GetDirectionalDirections() { //Such lovely redundancy
	return directional_directions;
}

GLfloat * LightManager::GetAmbientColor()
{
	return ambient_color;
}

GLfloat * LightManager::GetAmbientItensity()
{
	return &ambient_intensity;
}

LightManager * LightManager::SetAmbientColor(glm::vec3 color)
{
	ambient_color[0] = color[0] * I_256;
	ambient_color[1] = color[1] * I_256;
	ambient_color[2] = color[2] * I_256;

	return GetInstance();
}

LightManager * LightManager::SetAmbientItensity(float i)
{
	ambient_intensity = i;
	return GetInstance();
}

std::vector<Light*> LightManager::GetPointLights()
{
	return point_lights;
}

std::vector<Light*> LightManager::GetSpotLights()
{
	return spot_lights;
}

std::vector<Light*> LightManager::GetDirectionalLights()
{
	return directional_lights;
}
