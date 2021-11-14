#include "caveEngine.hpp"

namespace cave {

	class Example1 : public Application {
	public:
		Example1() = default;
		~Example1() = default;
		virtual void UserStartUp(World& world) noexcept override {
			RenderingManager::configureCamera(caveVec3f(0, 0, 80), caveVec3f(0, 0, -1), OgreBites::CameraStyle::CS_FREELOOK);
			RenderingManager::loadResourcesFolder("Meshes", "Example1Resources");
			EntityComponentManager::createEntity("sinbad1");
			EntityComponentManager::createEntity("sinbad2");
			EntityComponentManager::addComponent<SkeletalMeshComponent>("sinbad1", "exSinbad.mesh", "sinbad1", "Example1Resources");
			EntityComponentManager::addComponent<SkeletalMeshComponent>("sinbad2", "exSinbad.mesh", "sinbad2", "Example1Resources");
			SkeletalMeshComponent& sinbad1Mesh = EntityComponentManager::getComponent<SkeletalMeshComponent>("sinbad1");
			SkeletalMeshComponent& sinbad2Mesh = EntityComponentManager::getComponent<SkeletalMeshComponent>("sinbad2");
			sinbad1Mesh.setScaling(caveVec3f(5, 5, 5));
			sinbad2Mesh.setTranslation(caveVec3f(5, 15, 0));
			EntityComponentManager::initEntities();
		}

		virtual void UserShutDown(World& world) noexcept override {
		}
		virtual void UserUpdate(World& world, float timeStep) noexcept override {
		}

	};
	int main()
	{
		std::cout << "Example main.";
		Example1 example1;
		Engine engine(example1);
		engine.StartMainLoop();
	}

}