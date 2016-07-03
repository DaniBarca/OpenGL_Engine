#include "LightManager.h"

LightManager::LightManager()
{
	ambient_intensity = 0.0f;
	specular_exponent = 1.0f;

	lights = vector<Light*>();

	size = 0;

	positions = new GLfloat[0];
	intensities = new GLfloat[0];
	colors = new GLfloat[0];
}

LightManager::~LightManager()
{
	for (unsigned int i = 0; i < lights.size(); ++i) {
		delete lights[i];
	}
}

LightManager* LightManager::AllocLights(int n) {
	// If new size is smaller we will delete all data after n
	if (size > n)
		size = n;

	lights.resize(n);

	GLfloat* newpos = new GLfloat[n * 3];
	GLfloat* newint = new GLfloat[n];
	GLfloat* newcol = new GLfloat[n * 3];

	memcpy(newpos, positions,   size * 3 * sizeof(GLfloat));
	memcpy(newint, intensities, size * sizeof(GLfloat));
	memcpy(newcol, colors,      size * 3 * sizeof(GLfloat));

	delete[] positions;
	delete[] intensities;
	delete[] colors;

	positions = newpos;
	intensities = newint;
	colors = newcol;

	size = n;

	return GetInstance();
}

LightManager* LightManager::GetInstance(){
	static LightManager* Instance = new LightManager();
	return Instance;
}

LightManager* LightManager::Push(Light* l) {
	static int count = 0;

	if (count == size) {
		std::cout << "WARNING! Lights reallocation taking place" << std::endl;
		AllocLights(size + 1);
	}

	lights[count++] = l;

	return this;
}

Light* LightManager::GetLight(unsigned int pos){
	return lights[pos];
}

size_t LightManager::GetNLights() {
	return size;
}

void LightManager::Update(double dt) {
	for (unsigned int i = 0; i < lights.size(); ++i) {
		lights[i]->Update(dt);
	}

	Compile();
}

void LightManager::Compile() {
	glm::vec4 aux;
	for (unsigned int i = 0; i < lights.size(); ++i) {
		positions[i * 3 + 0] = lights[i]->GetPosition()[0];
		positions[i * 3 + 1] = lights[i]->GetPosition()[1];
		positions[i * 3 + 2] = lights[i]->GetPosition()[2];

		intensities[i] = lights[i]->GetIntensity();

		aux = clamp(lights[i]->GetColor());
		colors[i * 3 + 0] = aux.r;
		colors[i * 3 + 1] = aux.g;
		colors[i * 3 + 2] = aux.b;
	}
}

GLfloat* LightManager::GetPositions() {
	return positions;
}

GLfloat* LightManager::GetIntensities(){
	return intensities;
}

GLfloat* LightManager::GetColors() {
	return colors;
}

GLfloat * LightManager::GetAmbientItensity()
{
	return &ambient_intensity;
}

GLfloat * LightManager::GetSpecularExponent()
{
	return &specular_exponent;
}

LightManager * LightManager::SetAmbientItensity(float i)
{
	ambient_intensity = i;
	return GetInstance();
}

LightManager * LightManager::SetSpecularExponent(float e)
{
	specular_exponent = e;
	return GetInstance();
}
