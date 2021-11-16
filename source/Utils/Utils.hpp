#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

namespace cave {

	/**Vector de tres componentes.
*
*/
	struct caveVec3f {
		float x;
		float y;
		float z;

		caveVec3f(float x, float y, float z) {
				this->x = x;
				this->y = y;
				this->z = z;
		}
	};

	/**Cuaternion.
*
*/
	struct caveQuat {
		float fW;
		float fX;
		float fY;
		float fZ;

		caveQuat(float fW, float fX, float fY, float fZ) {
			this->fW = fW;
			this->fX = fX;
			this->fY = fY;
			this->fZ = fZ;
		}
	};


}


#endif