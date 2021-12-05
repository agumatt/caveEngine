#include "caveEngine.hpp"
#include <AL/al.h>
#include <AL/alc.h>

namespace cave {

	class Example1 : public Application {
	public:
		Example1() = default;
		~Example1() = default;
		virtual void UserStartUp(World& world) noexcept override {
			RenderingManager::configureCamera(caveVec3f(0, 0, 80), caveVec3f(0, 0, -1));
			RenderingManager::loadResourcesFolder("Resources/Meshes");
			RenderingManager::loadResourcesFolder("Resources/Fonts");
			RenderingManager::loadFont("exFont", "DejaVuSerifCondensedItalic.ttf");
			AudioManager::loadSound("Resources/Audio/survival.wav", "survival");
			EntityComponentManager::createEntity("sinbad1");
			EntityComponentManager::createEntity("sinbad2");
			EntityComponentManager::addComponent<SkeletalMeshComponent>("sinbad1", "exSinbad.mesh", "sinbad1");
			EntityComponentManager::addComponent<SkeletalMeshComponent>("sinbad2", "exSinbad.mesh", "sinbad2");
			EntityComponentManager::addComponent<AudioSourceComponent>("sinbad1", 0.3f, 1.0f, 100.0f);
			SkeletalMeshComponent& sinbad1Mesh = EntityComponentManager::getComponent<SkeletalMeshComponent>("sinbad1");
			SkeletalMeshComponent& sinbad2Mesh = EntityComponentManager::getComponent<SkeletalMeshComponent>("sinbad2");
			AudioSourceComponent& sinbad2Audio = EntityComponentManager::getComponent<AudioSourceComponent>("sinbad1");
			EntityComponentManager::addComponent<TextComponent>("sinbad1", 0.0f, 0.0f, 1.0f, 1.0f);
			EntityComponentManager::addComponent<TextComponent>("sinbad2", 0.0f, 0.0f, 1.0f, 1.0f);
			TextComponent& sinbad1Text = EntityComponentManager::getComponent<TextComponent>("sinbad1");
			TextComponent& sinbad2Text = EntityComponentManager::getComponent<TextComponent>("sinbad2");
			std::string textElementName = "textElement";
			std::string caption1 = "soy un OGRO";
			std::string caption2 = "soy otro OGRO";
			sinbad1Text.addTextElement(textElementName, 0.0f, 0.0f, 1.0f, 1.0f);
			sinbad2Text.addTextElement(textElementName, 0.0f, 0.5f, 1.0f, 1.0f);
			sinbad1Text.configureTextElement(textElementName, 0.09f, "exFont", caveColour(1.0f,0.0f,0.0f));
			sinbad2Text.configureTextElement(textElementName, 0.09f, "exFont", caveColour(0.0f, 1.0f, 0.0f));
			sinbad1Text.displayText(textElementName, caption1);
			sinbad2Text.displayText(textElementName, caption2);
			//sinbad1Text.hideTextContainer();
			sinbad1Mesh.setScaling(caveVec3f(5, 5, 5));
			sinbad2Mesh.setTranslation(caveVec3f(5, 15, 0));
			sinbad2Audio.setPosition(caveVec3f(0, 0, 0));
			sinbad2Audio.play("survival");
			EntityComponentManager::initEntities();
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

