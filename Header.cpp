#include "Header.h"
#include <fstream>

glm::mat4 getRotationMatrix(double radians, glm::vec3 axis)
{
	axis = glm::normalize(axis);

	glm::mat4 m = glm::mat4(1.0f); //Identity matrix

	double c = cos(radians);
	double s = sin(radians);
	double t = 1 - c;

	m[0][0] = ((float)(t * axis[0] * axis[0] + c));
	m[1][0] = ((float)(t * axis[0] * axis[1] - s * axis[2]));
	m[2][0] = ((float)(t * axis[0] * axis[2] + s * axis[1]));

	m[0][1] = ((float)(t * axis[0] * axis[1] + s * axis[2]));
	m[1][1] = ((float)(t * axis[1] * axis[1] + c));
	m[2][1] = ((float)(t * axis[1] * axis[2] - s * axis[0]));

	m[0][2] = ((float)(t * axis[0] * axis[2] - s * axis[1]));
	m[1][2] = ((float)(t * axis[1] * axis[2] + s * axis[0]));
	m[2][2] = ((float)(t * axis[2] * axis[2] + c));

	return m;
}


void voxelParse(string path, vector<vector<vector<int>>>* voxels, int* width, int* height, int* depth) {
	ifstream file;
	file.open(path.c_str());

	string line, aux = "", row = "", voxel = "";
	int i = 0, k=0, q=0;

	if (!file.is_open()) {
		cout << "Cannot read file " << path << endl;
		getchar();
		exit(EXIT_FAILURE);
	}

	//First line contains width, height and depth, in that order
	//For example: 12 5 6
	getline(file, line);

	//Get Width
	while (line[i] != ' ') {
		aux += line[i];
		i++;
	}
	i++;
	*width = stoi(aux);
	
	//Get Depth
	aux = "";
	while (line[i] != ' ') {
		aux += line[i];
		i++;
	}
	i++;
	*depth = stoi(aux);

	//Get Height
	aux = "";
	while (i < line.size()) {
		aux += line[i];
		i++;
	}
	*height = stoi(aux);

	//Init vector and reserve memory
	*voxels = vector<vector<vector<int>>>(*width, 
		vector<vector<int>>(*depth,
			vector<int>(*height)
		)
	);

	//For each layer
	for (int i = 0; i < *width; ++i) {
		getline(file, line);
		k = 0;

		//For each row (depth row)
		for (int j = 0; j < *depth; ++j) {
			row = "";
			while (line[k] != '|' && k < line.size()) {
				row += line[k];
				k++;
			}
			k+=2;
			q = 0;

			//For each voxel in that row
			for (int t = 0; t < *height; ++t) {
				voxel = "";
				while (row[q] != ' ' && q < row.size()) {
					voxel += row[q];
					q++;
				}
				q++;

				//Save its reference
				(*voxels)[i][j][t] = stoi(voxel);
			}
		}
	}
}

void printVoxels(vector<vector<vector<int>>> voxels, int width, int height, int depth) {
	cout << width << " " << height << " " << depth << endl;
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			for (int t = 0; t < depth; ++t) {
				cout << voxels[i][j][t] << " ";
			}
			cout << "| ";
		}
		cout << endl;
	}
}
