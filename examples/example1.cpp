#include "caveEngine.hpp"
#include <AL/al.h>
#include <AL/alc.h>

namespace cave {

	class Example1 : public Application {
	public:
		Example1() = default;
		~Example1() = default;
		virtual void UserStartUp(World& world) noexcept override {
		}

		virtual void UserShutDown(World& world) noexcept override {
		}
		virtual void UserUpdate(World& world, float timeStep) noexcept override {
		}

	};
}

	int main(int argc, char* argv[])
	{
		std::cout << "Example main." << std::endl;
		cave::Example1 example1;
		cave::Engine engine(example1);
		engine.StartMainLoop();
		return 0;
	}

