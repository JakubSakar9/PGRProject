#pragma once

#include "pgr.h"

class BoxCollider {
private:
	glm::vec3 m_lBound;
	glm::vec3 m_uBound;
public:
	inline BoxCollider(glm::vec3 size) {
		m_lBound = -size * 0.5f;
		m_uBound = size * 0.5f;
	}
	inline BoxCollider(glm::vec3 lBound, glm::vec3 uBound) {
		m_lBound = lBound;
		m_uBound = uBound;
	}
	inline BoxCollider *Scale(glm::mat4 mat) {
		glm::vec4 lBoundH = mat * glm::vec4(m_lBound, 1.0f);
		glm::vec4 uBoundH = mat * glm::vec4(m_uBound, 1.0f);
		return new BoxCollider(glm::vec3(lBoundH) / lBoundH.w, glm::vec3(uBoundH) / uBoundH.w);
	}

	inline glm::vec3 LBound() { return m_lBound; }
	inline glm::vec3 UBound() { return m_uBound; }
};
