//Blame @DaniBarca for this

//This is the main class of a project made with this engine

#pragma once

#include "Header.h"
#include "MeshObject.h"
#include "Camera.h"

#include "BasicMesh.h"

#include "RotatingLight.h"
#include "LightManager.h"

class World
{
	World();
	~World();

	aiScene asScene;
	BasicMesh* testmesh;
	BasicMesh* testmeshB;

	std::vector<MeshObject*> items;

	uint pressed_keys;
	bool clicking;

	///////////////////////////////////////////

	static std::map<string, string> parse_dict;

	GLuint shadow_framebuffer;
	GLuint depthTexture;

	GLuint shaderID;

	GLuint projectionID;
	GLuint viewID;
	GLuint transformID;

	GLuint point_positionsID;
	GLuint point_colorsID;
	GLuint point_intensitiesID;
	GLuint point_shininessID;

	GLuint spot_positionsID;
	GLuint spot_colorsID;
	GLuint spot_directionsID;
	GLuint spot_intensitiesID;
	GLuint spot_shininessID;
	GLuint spot_anglesID;

	GLuint directional_positionsID;
	GLuint directional_colorsID;
	GLuint directional_directionsID;
	GLuint directional_intensitiesID;
	GLuint directional_shininessID;

	GLuint cameraPositionID;
	GLuint reflectivityDiffuseID;
	GLuint reflectivitySpecularID;
	GLuint reflectivityAmbientID;

	GLuint ambientColorID;
	GLuint ambientIntensityID;

	GLuint textureID;

	GLuint shadow_shaderID;
	GLuint shadow_PVID;
	GLuint shadow_MID;

	std::vector<std::string> shaderPaths;
	std::vector<GLenum> shaderTypes;

	///////////////////////////////////////////

public:
	static World* GetInstance();

	void Init();

	void Update(double dt);

	void Draw();

	void OnKeyPress(int key, int scancode, int action, int mods);

	void OnMousePress(int button, int action, int mods);

	void OnMouseMove(double x, double y);

	void LoadUniforms();
};
