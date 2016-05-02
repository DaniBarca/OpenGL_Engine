#pragma once

#include "Header.h"
#include "MeshObject.h"

class MeshObject;

bool Import3D(const string& path, MeshObject*& meshes);
