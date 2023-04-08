#pragma once

#include "pgr.h"

class BoxCollider
{
private:
	glm::vec3 m_size;
public:
	BoxCollider(glm::vec3 size) {
		m_size = size;
	}
};

