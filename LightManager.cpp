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
	types = new GLint[0];
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

	GLfloat* newpos = new GLfloat[n * N_AXIS];
	GLfloat* newint = new GLfloat[n];
	GLfloat* newcol = new GLfloat[n * N_AXIS];
	GLint*   newtyp = new GLint[n];

	memcpy(newpos, positions,   size * N_AXIS * sizeof(GLfloat));
	memcpy(newint, intensities, size * sizeof(GLfloat));
	memcpy(newcol, colors,      size * N_AXIS * sizeof(GLfloat));
	memcpy(newtyp, types,       size * sizeof(GLint));

	delete[] positions;
	delete[] intensities;
	delete[] colors;
	delete[] types;

	positions = newpos;
	intensities = newint;
	colors = newcol;
	types = newtyp;

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
		positions[i * N_AXIS + 0] = lights[i]->GetPosition()[0];
		positions[i * N_AXIS + 1] = lights[i]->GetPosition()[1];
		positions[i * N_AXIS + 2] = lights[i]->GetPosition()[2];

		intensities[i] = lights[i]->GetIntensity();

		aux = clamp(lights[i]->GetColor());
		colors[i * N_AXIS + 0] = aux.r;
		colors[i * N_AXIS + 1] = aux.g;
		colors[i * N_AXIS + 2] = aux.b;

		types[i] = lights[i]->GetType();
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

GLint* LightManager::GetTypes() {
	return types;
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
