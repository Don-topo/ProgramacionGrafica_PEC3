#include "ModelManager.h"

ModelManager::ModelManager(){}

void ModelManager::InitModels()
{
    castleModel = LoadModel("resources/models/obj/castle.obj");
	house = LoadModel("resources/models/obj/house.obj");
	well = LoadModel("resources/models/obj/well.obj");
}

void ModelManager::UnloadModels()
{
    UnloadModel(castleModel);
	UnloadModel(house);
	UnloadModel(well);
}

Model& ModelManager::GetModel(ModelType model)
{
	switch (model)
	{
	case ModelType::castle:
		return castleModel;
		break;
	case ModelType::house:
		return house;
		break;
	case ModelType::well:
		return well;
		break;
	default:
		break;
	}
}
