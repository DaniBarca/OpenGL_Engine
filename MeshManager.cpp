#include "MeshManager.h"

MeshManager::MeshManager()
{
	meshList = std::unordered_map<string, Mesh*>();
}

MeshManager::~MeshManager()
{
}

MeshManager* MeshManager::GetInstance()
{
	static MeshManager* Instance = new MeshManager();
	return Instance;
}

Mesh * MeshManager::LoadOBJ(
	const char * path
) {
	std::vector<glm::vec3>* out_vertices = new std::vector<glm::vec3>();
	std::vector<glm::vec2>* out_uvs = new std::vector<glm::vec2>();
	std::vector<glm::vec3>* out_normals = new std::vector<glm::vec3>();

	std::vector<uint> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE * file;
	fopen_s(&file, path, "r");
	if (file == NULL) {
		//printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		//fscanf();

		int res = fscanf_s(file, "%s", lineHeader, 128);

		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			uint vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (uint i = 0; i<vertexIndices.size(); i++) {

		// Get the indices of its attributes
		uint vertexIndex = vertexIndices[i];
		uint uvIndex = uvIndices[i];
		uint normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];

		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices->push_back(vertex);
		out_uvs->push_back(uv);
		out_normals->push_back(normal);

	}

	return new Mesh((GLfloat*)&(*out_vertices)[0][0], (GLfloat*)&(*out_normals)[0][0], (GLfloat*)&(*out_uvs)[0][0], (uint)out_vertices->size(), (uint)out_normals->size(), (uint)out_uvs->size());
}

void MeshManager::GenerateBin(const char* path, Mesh* m) {
	string binpath = string(path);// +".bin";
	FILE* fp;
	fopen_s(&fp, binpath.c_str(), "wb+");

	fwrite(&m->numVertices, sizeof(uint), 1, fp);
	fwrite(&m->numNormals, sizeof(uint), 1, fp);
	fwrite(&m->numUvs, sizeof(uint), 1, fp);

	cout << (uint)sizeof(uint) << endl;
	cout << (uint)sizeof(GLfloat) << endl;
	
	fwrite(m->vertices, sizeof(GLfloat) * 3 * m->numVertices, 1, fp);
	fwrite(m->normals, sizeof(GLfloat) * 3 * m->numNormals, 1, fp);
	fwrite(m->uvs, sizeof(GLfloat) * 2 * m->numUvs, 1, fp);

	fclose(fp);
}

Mesh * MeshManager::LoadMesh_OBJ(const char* path)
{
	//Check cache
	static std::unordered_map<string, Mesh*>::iterator memit;
	if ((memit = meshList.find(string(path))) != meshList.end()) {
		return memit->second;
	}

	Mesh* m;
	m = LoadOBJ(path);

	meshList[path] = m;

	// We generate a .bin equivalent file to be loaded with LoadMesh_BIN
	string pathbin = string(path) + ".bin";
	GenerateBin(pathbin.c_str(), m);

	return m; 
}

Mesh * MeshManager::LoadMesh_BIN(const char* path) {
	static std::unordered_map<string, Mesh*>::iterator memit;
	if ((memit = meshList.find(path)) != meshList.end()) {
		return memit->second;
	}

	FILE* fp;
	fopen_s(&fp, path, "rb");
	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp);
	rewind(fp);

	char* buffer;
	buffer = new char[file_size];
	fread(buffer, file_size, 1, fp);
	fclose(fp);

	int n_vertices, n_normals, n_uvs;
	GLfloat* vertices;
	GLfloat* normals;
	GLfloat* uvs;

	memcpy(&n_vertices, buffer, sizeof(uint));
	memcpy(&n_normals, buffer += sizeof(uint), sizeof(uint));
	memcpy(&n_uvs, buffer += sizeof(uint), sizeof(uint));

	size_t size_ver = sizeof(GLfloat) * 3 * n_vertices;
	size_t size_nor = sizeof(GLfloat) * 3 * n_normals;
	size_t size_uvs = sizeof(GLfloat) * 2 * n_uvs;

	vertices = new GLfloat[n_vertices * 3];
	normals = new GLfloat[n_normals * 3];
	uvs = new GLfloat[n_uvs * 2];

	memcpy(vertices, buffer += sizeof(uint), size_ver);
	memcpy(normals, buffer += size_ver, size_nor);
	memcpy(uvs, buffer += size_nor, size_uvs);

	Mesh * m = new Mesh(vertices, normals, uvs, n_vertices, n_normals, n_uvs);
	meshList[path] = m;
	return m;
}
