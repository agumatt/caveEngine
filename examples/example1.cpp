#include "caveEngine.hpp"



class Example1 : public cave::Application {
public:
	Example1() = default;
	~Example1() = default;
	virtual void UserStartUp(cave::World & world) noexcept override {
		cave::RenderingManager::configureCamera(Ogre::Vector3(0, 0, 80), Ogre::Vector3(0, 0, -1),OgreBites::CameraStyle::CS_FREELOOK);
		cave::RenderingManager::loadResourcesFolder("Meshes", "Example1Resources");
		auto sinbadModel1 = cave::Model("exSinbad.mesh", "sinbad1", "Example1Resources");
		auto sinbadModel2 = cave::Model("exSinbad.mesh", "sinbad2", "Example1Resources");
		sinbadModel1.setInitialScaling(Ogre::Vector3(5, 5, 5));
		sinbadModel2.setInitialTranslation(Ogre::Vector3(5, 15, 0));
		std::vector<cave::Model> models = { sinbadModel1, sinbadModel2 };
		cave::RenderingManager::addResourcesToScene(models);
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