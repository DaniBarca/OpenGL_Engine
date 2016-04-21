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
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	Init();
	double currentFrame, delta, lastFrame = glfwGetTime() , currentFPS;
	int count = 0;
	do {
		if (count > 1000000)count = 0;
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
		count++;
		currentFPS = 1 / (glfwGetTime() - currentFrame);
		if (count % 10 == 0)
			cout << currentFPS << endl;
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
	const char* vertex_file_path = vertex_path.c_str();
	const char* fragment_file_path = fragment_path.c_str();
	
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	*out_shader_id = ProgramID;
	
	return Instance;
}
