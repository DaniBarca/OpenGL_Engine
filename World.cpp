#include "World.h"

std::map<string, string> World::parse_dict;

World::World()
{
	pressed_keys = 0;
	clicking = false;
}

World::~World()
{}

World* World::GetInstance() {
	static World* Instance = new World();
	return Instance;
}

void World::Init() {
	LightManager::GetInstance()
		->AllocLights(0, 0, 1)
		->SetAmbientColor(glm::vec3(256.0f,256.0f,256.0f))
		->SetAmbientItensity(0.0f);

	//LightManager::GetInstance()->Push(
	//	new SpotLight(
	//		glm::vec4(256.0f, 256.0f, 256.0f, 0.0f), 
	//		glm::vec3(0.0f, 3.0f, 0.0f),
	//		10.0f, 
	//		0.3f, 
	//		glm::vec3(0.0f, -1.0f, 0.0f), 
	//		0.15f,
	//		0.18f
	//	)
	//);
    //
	//LightManager::GetInstance()->Push(
	//	new Light(
	//		glm::vec4(256.0f, 256.0f, 256.0f, 0.0f), 
	//		glm::vec3(-10.0f,3.0f,0.0f),
	//		10.0f, 
	//		0.3f
	//	)
	//);

	LightManager::GetInstance()->Push(
		new DirectionalLight(
			glm::vec4(256.0f,256.0f,256.0f, 0.0f),
			glm::vec3(0.0f,20.0f,0.0f),
			10.0f,
			0.5f,
			glm::vec3(0.0f,-1.0f,0.0f)
		)
	);

	parse_dict = std::map<string, string>({});

	shaderPaths = std::vector<std::string>({
		"shaders/phong.vertex",
		"shaders/phong.fragment"
	});

	shaderTypes = std::vector<GLenum>({
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	});

	/*for (int p = 1; p <= DEFAULT_N_POINT_LIGHTS; ++p) {
	for (int s = 1; s <= DEFAULT_N_SPOT_LIGHTS; ++s) {
	for (int d = 1; d <= DEFAULT_N_DIRECTIONAL_LIGHTS; ++d) {
	Engine::GetInstance()->LoadShader(shaderPaths, shaderTypes, p, s, d, parse_dict, &shaderID);
	}
	}
	}*/

	Engine::GetInstance()->LoadShader(shaderPaths, shaderTypes,
		(int)LightManager::GetInstance()->GetNPointLights(),
		(int)LightManager::GetInstance()->GetNSpotLights(),
		(int)LightManager::GetInstance()->GetNDirectionalLights(),
		parse_dict, &shaderID
	);

	// SHADOWMAP shader
	Engine::GetInstance()->LoadShader(
		"shaders/shadowmap.vertex",
		"shaders/shadowmap.fragment",
		0, 0, 0,
		parse_dict,
		&shadow_shaderID
	);

	LoadUniforms();

	// Load items

	items = std::vector<MeshObject*>();

	items.push_back(new BasicMesh("models/suzanne.obj.bin", "models/monaco.bmp"));
	items.push_back(new BasicMesh("models/BOLLOFLAT.obj.bin", "models/monaco.bmp"));

	for (uint i = 0; i < items.size(); ++i) {
		items[i]->Init();
	}

	Camera::GetInstance(); 
}

void World::Update(double dt) {
	//LightManager::GetInstance()->GetDirectionalLights()[0]->Transform = *LightManager::GetInstance()->GetDirectionalLights()[0]->Transform;

	//*LightManager::GetInstance()->GetDirectionalLights()[0]->Transform() = glm::rotate((float)(dt), glm::vec3(1, 0, 0))*(*LightManager::GetInstance()->GetDirectionalLights()[0]->Transform());


	LightManager::GetInstance()->Update(dt);

	for (uint i = 0; i < items.size(); ++i) {
		items[i]->Update(dt);
	}
}

void World::Draw() {
	/********* SHADOWS *********/
	//glBindFramebuffer(GL_FRAMEBUFFER, shadow_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0, 0, 1024, 1024);

//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	
//
//	std::cout << ((DirectionalLight*)LightManager::GetInstance()->GetDirectionalLights()[0])->GetUp()[0] << " -- " << ((DirectionalLight*)LightManager::GetInstance()->GetDirectionalLights()[0])->GetUp()[1] << " -- " << ((DirectionalLight*)LightManager::GetInstance()->GetDirectionalLights()[0])->GetUp()[2] << std::endl;
//
//	glm::mat4 depth_V =
//		//glm::inverse(
//		glm::lookAt(
//		((DirectionalLight*)LightManager::GetInstance()->GetDirectionalLights()[0])->GetDirection(),
//			((DirectionalLight*)LightManager::GetInstance()->GetDirectionalLights()[0])->GetPosition(),
//			((DirectionalLight*)LightManager::GetInstance()->GetDirectionalLights()[0])->GetUp()
//		);
//		//);
//
//	//glm::mat4 inv_mat = glm::inverse(*directional_lights[0]->Transform());
//	glm::mat4 depth_P = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
//
//	glm::mat4 shadow_PV = depth_P * depth_V;
//
//	Engine::GetInstance()->LoadShader(
//		"shaders/shadowmap.vertex",
//		"shaders/shadowmap.fragment",
//		0, 0, 0,
//		parse_dict,
//		&shadow_shaderID
//	);
//
//	glUseProgram(shadow_shaderID);
//
//	glUniformMatrix4fv(shadow_PVID, 1, GL_FALSE, &shadow_PV[0][0]);
//
//	for (int i = 0; i < items.size(); ++i) {
//		items[i]->DrawDepthMap(shadow_MID);
//	}


	/********* OBJECTS *********/
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	static int preShaderID;

	preShaderID = shaderID;
	Engine::GetInstance()->LoadShader(
		shaderPaths,
		shaderTypes,
		(int)LightManager::GetInstance()->GetNPointLights(),
		(int)LightManager::GetInstance()->GetNSpotLights(),
		(int)LightManager::GetInstance()->GetNDirectionalLights(),
		parse_dict,
		&shaderID
	);

	if (preShaderID != shaderID) {
		LoadUniforms();
	}

	glUseProgram(shaderID);

	glUniformMatrix4fv(projectionID, 1, GL_FALSE, &(Camera::GetInstance()->getP())[0][0]);
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &(Camera::GetInstance()->getV())[0][0]);

	GLsizei n_point_lights = (GLsizei)LightManager::GetInstance()->GetNPointLights();
	glUniform3fv(point_positionsID,   n_point_lights, LightManager::GetInstance()->GetPointPositions());
	glUniform3fv(point_colorsID,      n_point_lights, LightManager::GetInstance()->GetPointColors());
	glUniform1fv(point_intensitiesID, n_point_lights, LightManager::GetInstance()->GetPointIntensities());
	glUniform1fv(point_shininessID,   n_point_lights, LightManager::GetInstance()->GetPointShininess());

	GLsizei n_spot_lights = (GLsizei)LightManager::GetInstance()->GetNSpotLights();
	glUniform3fv(spot_positionsID,   n_spot_lights, LightManager::GetInstance()->GetSpotPositions());
	glUniform3fv(spot_colorsID,      n_spot_lights, LightManager::GetInstance()->GetSpotColors());
	glUniform3fv(spot_directionsID,  n_spot_lights, LightManager::GetInstance()->GetSpotDirections());
	glUniform1fv(spot_intensitiesID, n_spot_lights, LightManager::GetInstance()->GetSpotIntensities());
	glUniform1fv(spot_shininessID,   n_spot_lights, LightManager::GetInstance()->GetSpotShininess());
	glUniform2fv(spot_anglesID,      n_spot_lights, LightManager::GetInstance()->GetSpotAngles());

	GLsizei n_directional_lights = (GLsizei)LightManager::GetInstance()->GetNDirectionalLights();
	glUniform3fv(directional_positionsID,   n_directional_lights, LightManager::GetInstance()->GetDirectionalPositions());
	glUniform3fv(directional_colorsID,      n_directional_lights, LightManager::GetInstance()->GetDirectionalColors());
	glUniform3fv(directional_directionsID,  n_directional_lights, LightManager::GetInstance()->GetDirectionalDirections());
	glUniform1fv(directional_intensitiesID, n_directional_lights, LightManager::GetInstance()->GetDirectionalIntensities());
	glUniform1fv(directional_shininessID,   n_directional_lights, LightManager::GetInstance()->GetDirectionalShininess());


	glUniform3fv(ambientColorID,     1, LightManager::GetInstance()->GetAmbientColor());
	glUniform1fv(ambientIntensityID, 1, LightManager::GetInstance()->GetAmbientItensity());

	glUniform3fv(cameraPositionID, 1, &Camera::GetInstance()->GetPosition()[0]);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	for (uint i = 0; i < items.size(); ++i) {
		items[i]->Draw(transformID, textureID, reflectivityDiffuseID, reflectivitySpecularID, reflectivityAmbientID);
	}
}

void World::OnKeyPress(int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS)
		++pressed_keys;
	if (action == GLFW_RELEASE)
		--pressed_keys;

	switch (key) {
		case GLFW_KEY_UP:
			Camera::GetInstance()->ZoomIN();
			break;
		case GLFW_KEY_DOWN:
			Camera::GetInstance()->ZoomOUT();
			break;
		case GLFW_KEY_RIGHT:
			Camera::GetInstance()->Closer();
			break;
		case GLFW_KEY_LEFT:
			Camera::GetInstance()->Beyond();
			break;
		case GLFW_KEY_L:
			if (action == GLFW_RELEASE) {
				LightManager::GetInstance()->Push(new Light(glm::vec4(0.0f, 0.0f, 256.0f, 0.0f), glm::vec3(-10.0f, -2.0f + 10.0f, 0.0f), 0.3f));
			}
			break;
	}
}

void World::OnMousePress(int button, int action, int mods) {
	clicking = button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS;
}

void World::OnMouseMove(double x, double y) {
	if (clicking) {
		Camera::GetInstance()->Orbit(-x * 2.0f * PI * I_SCREEN_WIDTH, -PI * 0.5f + y * PI * I_SCREEN_HEIGHT);
	}
}

void World::LoadUniforms() {
	projectionID = glGetUniformLocation(shaderID, "P");
	viewID = glGetUniformLocation(shaderID, "V");
	transformID = glGetUniformLocation(shaderID, "M");

	point_positionsID = glGetUniformLocation(shaderID, "point_positions");
	point_colorsID = glGetUniformLocation(shaderID, "point_colors");
	point_intensitiesID = glGetUniformLocation(shaderID, "point_intensities");
	point_shininessID = glGetUniformLocation(shaderID, "point_shininess");

	spot_positionsID = glGetUniformLocation(shaderID, "spot_positions");
	spot_colorsID = glGetUniformLocation(shaderID, "spot_colors");
	spot_directionsID = glGetUniformLocation(shaderID, "spot_directions");
	spot_intensitiesID = glGetUniformLocation(shaderID, "spot_intensities");
	spot_shininessID = glGetUniformLocation(shaderID, "spot_shininess");
	spot_anglesID = glGetUniformLocation(shaderID, "spot_angles");

	directional_positionsID = glGetUniformLocation(shaderID, "directional_positions");
	directional_colorsID = glGetUniformLocation(shaderID, "directional_colors");
	directional_directionsID = glGetUniformLocation(shaderID, "directional_directions");
	directional_intensitiesID = glGetUniformLocation(shaderID, "directional_intensities");
	directional_shininessID = glGetUniformLocation(shaderID, "directional_shininess");

	cameraPositionID = glGetUniformLocation(shaderID, "camera_position");

	reflectivityDiffuseID = glGetUniformLocation(shaderID, "reflectivity_diffuse");
	reflectivitySpecularID = glGetUniformLocation(shaderID, "reflectivity_specular");
	reflectivityAmbientID = glGetUniformLocation(shaderID, "reflectivity_ambient");

	ambientColorID = glGetUniformLocation(shaderID, "ambient_color");
	ambientIntensityID = glGetUniformLocation(shaderID, "ambient_intensity");

	textureID = glGetUniformLocation(shaderID, "albedo");

	shadow_PVID = glGetUniformLocation(shadow_shaderID, "PV");
	shadow_MID = glGetUniformLocation(shadow_shaderID, "M");
}
