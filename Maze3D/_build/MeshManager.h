#pragma once
#include "raylib.h"
#include "TextureManager.h"
#include "ModelManager.h"

struct Object
{
	Vector3 position;
	TextureType textureType;
	ModelType modelType;
};

class MeshManager
{
public:
	MeshManager();
	Mesh GenerateMesh(Image cubicmap, Vector3 cubeSize);
	Object* GetObjects() { return objects; };
	int GetObjectCounter() { return numObjects; };
	void UnloadObjects();
private:
	Object* objects = nullptr;
	int numObjects = 0;
};

