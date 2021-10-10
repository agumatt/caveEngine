#include "caveEngine.hpp"



class Example1 : public cave::Application {
public:
	Example1() = default;
	~Example1() = default;
	virtual void UserStartUp(cave::World & world) noexcept override {
	

	}

	virtual void UserShutDown(cave::World& world) noexcept override {
	}
	virtual void UserUpdate(cave::World & world, float timeStep) noexcept override {
	}

};
int main()
{
	Example1 example1;
	cave::Engine engine(example1);
	engine.StartMainLoop();
}