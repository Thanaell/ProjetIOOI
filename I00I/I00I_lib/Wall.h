#pragma once

#include "GameObject.h"
#include "stdafx.h"
#include "constantes.h"

class Wall : public GameObject {
public:
	Wall(b2Vec2 point1, b2Vec2 point2);
};