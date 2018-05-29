#pragma once
#include "Element.h"
#include "stdafx.h"

class PlayingElement : public Element {
	std::unique_ptr<b2Body> body;
};