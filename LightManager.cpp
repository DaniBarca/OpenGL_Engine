#include "LightManager.h"

LightManager::LightManager()
{
	ambient_intensity = 0.0f;

	point_lights = vector<Light*>();
	spot_lights = vector<Light*>();
	directional_lights = vector<Light*>();

	point_size = spot_size = directional_size = 0;

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
}

LightManager::~LightManager()
{
	for (unsigned int i = 0; i < point_lights.size(); ++i) {
		delete point_lights[i];
	}
	for (unsigned int i = 0; i < spot_lights.size(); ++i) {
		delete spot_lights[i];
	}
	for (unsigned int i = 0; i < directional_lights.size(); ++i) {
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
}

LightManager* LightManager::AllocLights(int point_n, int spot_n, int dir_n) {
	GLfloat* newpos;
	GLfloat* newint;
	GLfloat* newcol;
	GLfloat* newshy;
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
		newshy = new GLfloat[point_n];

		memcpy(newpos, point_positions,   point_size * N_AXIS * sizeof(GLfloat));
		memcpy(newint, point_intensities, point_size * sizeof(GLfloat));
		memcpy(newcol, point_colors,      point_size * N_AXIS * sizeof(GLfloat));
		memcpy(newshy, point_shininess,   point_size * sizeof(GLfloat));

		delete[] point_positions;
		delete[] point_intensities;
		delete[] point_colors;
		delete[] point_shininess;

		point_positions   = newpos;
		point_intensities = newint;
		point_colors      = newcol;
		point_shininess   = newshy;
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
		newshy = new GLfloat[spot_n];
		newdir = new GLfloat[spot_n * N_AXIS];
		newang = new GLfloat[spot_n];

		memcpy(newpos, spot_positions,   spot_size * N_AXIS * sizeof(GLfloat));
		memcpy(newint, spot_intensities, spot_size * sizeof(GLfloat));
		memcpy(newcol, spot_colors,      spot_size * N_AXIS * sizeof(GLfloat));
		memcpy(newshy, spot_shininess,   spot_size * sizeof(GLfloat));
		memcpy(newdir, spot_directions,  spot_size * N_AXIS * sizeof(GLfloat));
		memcpy(newang, spot_angles,      spot_size * sizeof(GLfloat));

		delete [] spot_positions;
		delete [] spot_intensities;
		delete [] spot_colors;
		delete [] spot_shininess;
		delete [] spot_directions;
		delete [] spot_angles;

		spot_positions   = newpos;
		spot_intensities = newint;
		spot_colors      = newcol;
		spot_shininess   = newshy;
		spot_directions  = newdir;
		spot_angles      = newang;
	}

	spot_size = spot_n;

	/*****************/
	/** Directional **/
	/*****************/
	if (directional_size < dir_n){
		directional_lights.resize(dir_n);

		newpos = new GLfloat[dir_n * N_AXIS];
		newint = new GLfloat[dir_n];
		newcol = new GLfloat[dir_n * N_AXIS];
		newshy = new GLfloat[dir_n];
		newdir = new GLfloat[dir_n * N_AXIS];

		memcpy(newpos, directional_positions,   directional_size * N_AXIS * sizeof(GLfloat));
		memcpy(newint, directional_intensities, directional_size * sizeof(GLfloat));
		memcpy(newcol, directional_colors,      directional_size * N_AXIS * sizeof(GLfloat));
		memcpy(newshy, directional_shininess,   directional_size * sizeof(GLfloat));
		memcpy(newdir, directional_directions,  directional_size * N_AXIS * sizeof(GLfloat));

		delete [] directional_positions;
		delete [] directional_intensities;
		delete [] directional_colors;
		delete [] directional_shininess;
		delete [] directional_directions;

		directional_positions   = newpos;
		directional_intensities = newint;
		directional_colors      = newcol;
		directional_shininess   = newshy;
		directional_directions  = newdir;
	}

	directional_size = dir_n;

	return GetInstance();
}

LightManager* LightManager::GetInstance(){
	static LightManager* Instance = new LightManager();
	return Instance;
}

LightManager* LightManager::Push(Light* l, LIGHT_TYPE type) {
	static int p_count = 0, s_count = 0, d_count = 0;

	if (p_count == point_size) {
		AllocLights(point_size + 1, spot_size, directional_size);
	}
	if (s_count == spot_size) {
		AllocLights(point_size, spot_size + 1, directional_size);
	}
	if (d_count == directional_size) {
		AllocLights(point_size, spot_size, directional_size + 1);
	}

	switch (type) {
		case LIGHT_TYPE::POINT:
			point_lights[p_count++] = l;
			break;
		case LIGHT_TYPE::SPOT:
			spot_lights[s_count++] = l;
			break;
		case LIGHT_TYPE::DIRECTIONAL:
			directional_lights[d_count++] = l;
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
	for (unsigned int i = 0; i < point_size; ++i) {
		point_lights[i]->Update(dt);
	}
	for (unsigned int i = 0; i < spot_size; ++i) {
		spot_lights[i]->Update(dt);
	}
	for (unsigned int i = 0; i < directional_size; ++i) {
		directional_lights[i]->Update(dt);
	}

	Compile();
}

void LightManager::Compile() {
	glm::vec4 aux;
	for (unsigned int i = 0; i < point_size; ++i) {
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

	for (unsigned int i = 0; i < spot_size; ++i) {
		spot_positions[i * N_AXIS + 0] = spot_lights[i]->GetPosition()[0];
		spot_positions[i * N_AXIS + 1] = spot_lights[i]->GetPosition()[1];
		spot_positions[i * N_AXIS + 2] = spot_lights[i]->GetPosition()[2];

		spot_intensities[i] = spot_lights[i]->GetIntensity();

		aux = clamp(spot_lights[i]->GetColor());
		spot_colors[i * N_AXIS + 0] = aux.r;
		spot_colors[i * N_AXIS + 1] = aux.g;
		spot_colors[i * N_AXIS + 2] = aux.b;

		spot_shininess[i] = spot_lights[i]->GetShininess();

		spot_directions[i] = ((SpotLight *)spot_lights[i])->GetDirection();
		spot_angles[i]     = ((SpotLight *)spot_lights[i])->GetAngle();
	}

	for (unsigned int i = 0; i < directional_size; ++i) {
		directional_positions[i * N_AXIS + 0] = directional_lights[i]->GetPosition()[0];
		directional_positions[i * N_AXIS + 1] = directional_lights[i]->GetPosition()[1];
		directional_positions[i * N_AXIS + 2] = directional_lights[i]->GetPosition()[2];

		directional_intensities[i] = directional_lights[i]->GetIntensity();

		aux = clamp(directional_lights[i]->GetColor());
		directional_colors[i * N_AXIS + 0] = aux.r;
		directional_colors[i * N_AXIS + 1] = aux.g;
		directional_colors[i * N_AXIS + 2] = aux.b;

		directional_shininess[i] = directional_lights[i]->GetShininess();
		
		directional_directions = ((DirectionalLight *)directional_lights[i])->GetDirection();
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
	return point_positions;
}

GLfloat* LightManager::GetDirectionalIntensities() {
	return point_intensities;
}

GLfloat* LightManager::GetDirectionalColors() {
	return point_colors;
}

GLfloat * LightManager::GetDirectionalShininess() {
	return point_shininess;
}

GLfloat * LightManager::GetDirectionalDirections() { //Such lovely redundancy
	return directional_directions;
}

GLfloat * LightManager::GetAmbientItensity()
{
	return &ambient_intensity;
}

LightManager * LightManager::SetAmbientItensity(float i)
{
	ambient_intensity = i;
	return GetInstance();
}
