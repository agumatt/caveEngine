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

		caveVec3f() = default;
	};

	/**Cuaternion.
*
*/
	struct caveQuat {
		float x;
		float y;
		float z;
		float w;

		caveQuat(float x, float y, float z, float w) {
			this->w = w;
			this->x = x;
			this->y = y;
			this->z = z;
		}

		caveQuat() = default;
	};

	/**Color rgba.
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

		caveColour() = default;
	};


}


#endif