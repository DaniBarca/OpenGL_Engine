#pragma once
#include "Header.h"

#ifndef V_UP
#define V_UP glm::vec3(0,1,0)
#endif

class Engine
{
	static Engine* Instance;
	
	GLFWwindow* window;

	Engine();
	~Engine();

	static void reshape(GLFWwindow* window, int width, int height);

	function<void(int,int,int,int)> OnKeyPress;
	function<void(int, int, int)> OnMousePress;
	function<void(double, double)> OnMouseMove;

	static void Key(GLFWwindow* window, int k, int s, int action, int mods);
	static void MPress(GLFWwindow* window, int b, int a, int m);
	static void MMove(GLFWwindow* window, double x, double y);

public:
	static Engine* GetInstance();
	Engine* InitGLFW();
	Engine* NewWindow(int width, int height, string title, function<void(int, int, int, int)> OnKeyPress, function<void(int,int,int)> OnMousePress, function<void(double,double)> OnMouseMove);
	Engine* InitGLEW();
	Engine* InitEngine();
	Engine* Loop(function<void()>Init, function<void(double)> Update, function<void()> Draw);
	Engine* Terminate();

	Engine* LoadShader(string vertex_path, string fragment_path, int point_num, int spot_num, int dir_num, std::map<string, string> parse_dict, GLuint* out_shader_id);
	Engine* LoadShader(std::vector<std::string> paths, std::vector<GLenum> types, int point_num, int spot_num, int dir_num, std::map<string,string> parse_dict, GLuint* out_shader_id);
};
