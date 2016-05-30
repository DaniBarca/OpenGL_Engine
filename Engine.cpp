#include "Engine.h"

Engine* Engine::Instance = 0;

Engine* Engine::GetInstance() {
	if (!Instance)
		Instance = new Engine();
	return Instance;
}

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::reshape(GLFWwindow* window, int width, int height) {
	GLfloat h = (GLfloat)height / (GLfloat)width;
	GLfloat xmax, znear, zfar;

	znear = 5.0f;
	zfar = 30.0f;
	xmax = znear * 0.5f;

	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-xmax, xmax, -xmax*h, xmax*h, znear, zfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -20.0);
}

/********************************************************************************************/
/* I would like us to stop for a moment to reflect on how much I hate SteelSeries keyboards.*/
/* Thank you,  Daniel                                                                       */
/********************************************************************************************/

void Engine::Key(GLFWwindow* window, int k, int s, int action, int mods) {
	GetInstance()->OnKeyPress(k, s, action, mods);
}

void Engine::MPress(GLFWwindow* window, int b, int a, int m) {
	GetInstance()->OnMousePress(b, a, m);
}

void Engine::MMove(GLFWwindow* window, double x, double y) {
	GetInstance()->OnMouseMove(x, y);
}

Engine* Engine::InitGLFW() {
	if (!glfwInit()) {
		cout << "Failed to initialize GLFW" << endl;
		getchar();
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return Instance;
}

Engine* Engine::NewWindow(int width, int height, string title, function<void(int, int, int, int)> OnKeyPress, function<void(int, int, int)> OnMousePress, function<void(double, double)> OnMouseMove) {
	window = glfwCreateWindow(width,height,title.c_str(),NULL,NULL);
	if (window == NULL) {
		cout << "Failed to create window " << title << endl;
		glfwTerminate();
		getchar();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	this->OnKeyPress = OnKeyPress;
	this->OnMousePress = OnMousePress;
	this->OnMouseMove = OnMouseMove;

	glfwSetKeyCallback(window, Key);
	glfwSetMouseButtonCallback(window, MPress);
	glfwSetCursorPosCallback(window, MMove);

	//glfwSetFramebufferSizeCallback(window, reshape);
	glfwSwapInterval(1);
	//glfwGetFramebufferSize(window, &width, &height);
	//reshape(window, width, height);

	return Instance;
}

Engine* Engine::InitGLEW() {
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		cout << "Failed to initialize GLEW" << endl;
		glfwTerminate();
		getchar();
		exit(EXIT_FAILURE);
	}
	return Instance;
}

Engine* Engine::InitEngine() {
	glEnable(GL_CULL_FACE);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_NORMALIZE);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	return Instance;
}

Engine* Engine::Loop(function<void()> Init, function<void(double)> Update, function<void()> Draw) {
#ifdef PRINT_FPS
	double currentFPS;
	int count = 0;
#endif

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	Init();
	double currentFrame, delta, lastFrame = glfwGetTime();
	do {
		//Clear color buffer  
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Calculate delta between frames
		currentFrame = glfwGetTime();
		delta = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Call Update and Draw
		Update(delta);
		Draw();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

#ifdef PRINT_FPS
		currentFPS = 1 / (glfwGetTime() - currentFrame);
		count++;
		if (count > 60) {
			count = 0;
			cout << currentFPS << endl;
		}
#endif
		
	} while (!glfwWindowShouldClose(window));

	return Instance;
}

Engine* Engine::Terminate() {
	glfwTerminate();
	exit(EXIT_SUCCESS);
	return Instance;
}

//Directly adapted from opengl-tutorial.com
Engine* Engine::LoadShader(string vertex_path, string fragment_path, GLuint* out_shader_id) {
	return LoadShader(std::vector<std::string>({
		vertex_path,
		fragment_path
	}), std::vector<GLenum>({
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	}), out_shader_id);
}

Engine* Engine::LoadShader(std::vector<std::string> paths, std::vector<GLenum> types, GLuint* out_shader_id) {
	if (paths.size() != types.size() || paths.size() < 1) {
		std::cout << "ERROR: number of paths and number of types must be the same." << std::endl;
		getchar();
		exit(-1);
	}

	static map<string, GLuint> mem = map<string, GLuint>();
	static map<string, GLuint>::iterator memit;

	//Check if we had already loaded it previously
	std::string memcode = "";
	for (std::string i : paths)
		memcode += i;
	if ((memit = mem.find(memcode)) != mem.end()) {
		*out_shader_id = memit->second;
		return Instance;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;
	std::vector<GLuint> shaderIDs = std::vector<GLuint>();

	for (int i = 0; i < paths.size(); ++i) {
		std::string path = paths[i];
		GLenum type = types[i];

		const char* file_path = path.c_str();
		GLuint ShaderID = glCreateShader(type);

		// Read code from the file
		std::string ShaderCode;
		std::ifstream ShaderStream(file_path, std::ios::in);
		if (ShaderStream.is_open()) {
			std::string Line = "";
			while (getline(ShaderStream, Line))
				ShaderCode += "\n" + Line;
			ShaderStream.close();
		}
		else {
			printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", file_path);
			getchar();
			exit(-1);
		}

		// Compile Shader
		printf("Compiling shader : %s\n", file_path);
		char const * SourcePointer = ShaderCode.c_str();
		glShaderSource(ShaderID, 1, &SourcePointer, NULL);
		glCompileShader(ShaderID);

		// Check Shader
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}

		shaderIDs.push_back(ShaderID);
	}

	GLuint ProgramID = glCreateProgram();
	for (GLuint ShaderID : shaderIDs){
		// Attach
		glAttachShader(ProgramID, ShaderID);
	}

	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	for (GLuint ShaderID : shaderIDs) {
		//Detach
		glDetachShader(ProgramID, ShaderID);
	}

	for (GLuint ShaderID : shaderIDs) {
		//Delete
		glDeleteShader(ShaderID);
	}

	//END
	*out_shader_id = ProgramID;

	mem[memcode] = *out_shader_id;

	return Instance;
}
