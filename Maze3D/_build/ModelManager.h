#pragma once
#include "raylib.h"

enum class ModelType {
	castle = 0,
	house,
	well
};

class ModelManager
{
public:
	ModelManager();
	void InitModels();
	void UnloadModels();
	Model& GetModel(ModelType model);
private:
	Model castleModel;
	Model house;
	Model well;
};

