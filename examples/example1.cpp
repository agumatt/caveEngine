#include "caveEngine.hpp"



class Example1 : public cave::Application {
public:
	Example1() = default;
	~Example1() = default;
	virtual void UserStartUp(cave::World & world) noexcept override {
		world.getRenderingManager().configureCamera(Ogre::Vector3(0, 0, 15), Ogre::Vector3(0, 0, -1));
		world.getRenderingManager().loadResourcesFolder("Meshes", "Example1Resources");
		auto sinbadModel = cave::Model("Sinbad1.mesh", "Example1Resources", "sinbad1");
		std::vector<cave::Model> models = { sinbadModel };
		world.getRenderingManager().addResourcesToScene(models);
	}

	virtual void UserShutDown(cave::World& world) noexcept override {
	}
	virtual void UserUpdate(cave::World & world, float timeStep) noexcept override {
	}

};
int main()
{
	std::cout << "Example main.";
	Example1 example1;
	cave::Engine engine(example1);
	engine.StartMainLoop();
}