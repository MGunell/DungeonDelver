#pragma once
#include "stdafx.h"

class Slime : public BaseNpc
{
public:
	using BaseNpc::BaseNpc;
	friend bool loadSlimeMedia(SDL_Renderer* gRenderer);
	using BaseNpc::gSpriteSheetTexture2;
};

