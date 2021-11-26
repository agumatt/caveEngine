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

	/**Cuaternion.
*
*/
	struct caveColour {
		float r;
		float g;
		float b;
		float alpha;

		caveColour(float r=1.0f, float g=1.0f, float b=1.0f, float alpha=1.0f) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->alpha = alpha;
		}
	};


}


#endif