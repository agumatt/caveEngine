#include "Utils.hpp"



namespace cave {

	caveVec3f::caveVec(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	caveQuat::caveQuat(float fW, float fX, float fY, float fZ) {
		this->fW = fW;
		this->fX = fX;
		this->fY = fY;
		this->fZ = fZ;
	}

}