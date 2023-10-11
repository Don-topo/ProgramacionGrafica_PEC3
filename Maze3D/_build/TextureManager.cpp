#include "TextureManager.h"
#include <malloc.h>
#include <raymath.h>

TextureManager::TextureManager() {}

void TextureManager::InitTextures()
{
	logoTexture = LoadTexture("resources/Menu/Logo.png");
	titleTexture = LoadTexture("resources/Menu/Title.jpg");
    fullAtlasTexture = LoadTexture("resources/cubemap_atlas_full.png");
	castleTexture = LoadTexture("resources/models/obj/castle_diffuse.png");
	houseTexture = LoadTexture("resources/models/obj/house_diffuse.png");
	wellTexture = LoadTexture("resources/models/obj/well_diffuse.png");
}

void TextureManager::UnloadTextures()
{
	UnloadTexture(logoTexture);
	UnloadTexture(titleTexture);
	UnloadTexture(fullAtlasTexture);
	UnloadTexture(castleTexture);
	UnloadTexture(houseTexture);
	UnloadTexture(wellTexture);
}

Texture2D& TextureManager::GetTexture(TextureType texture)
{
	switch (texture)
	{
	case TextureType::Logo:
		return logoTexture;
		break;
	case TextureType::Title:
		return titleTexture;
		break;
	case TextureType::Atlas:
		return fullAtlasTexture;
		break;
	case TextureType::Castle:
		return castleTexture;
		break;
	case TextureType::House:
		return houseTexture;
		break;
	case TextureType::Well:
		return wellTexture;
		break;
	default:
		break;
	}
}