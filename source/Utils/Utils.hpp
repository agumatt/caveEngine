
namespace cave {


	struct caveVec3f {
		float x;
		float y;
		float z;

		caveVec(float x, float y, float z);
		~caveVec();
	};


	struct caveQuat {
		float fW;
		float fX;
		float fY;
		float fZ;

		caveQuat(float fW, float fX, float fY, float fZ);
		~caveQuat();
	};


}