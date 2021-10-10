#include <Ogre.h>
#include <OgreException.h>
#include <OgreRoot.h>

namespace cave {

	public class RenderingManager() {

		public{
			Ogre::Root* m_root;
			Ogre::RenderWindow* m_window;
			Ogre::SceneManager* m_sceneManager;
			Ogre::Viewport* m_viewport;
			Ogre::Camera* m_camera;
			Ogre::SceneNode* m_cameraNode;
			//incluir arreglo de modelos, con path, transformaciones iniciales, nombre, etc.

			void loadModels();

			void loadTerrain();

			void StartUp();

			void render();

		}

		private{
			RenderingManager();
			~RenderingManager();

		}


	}

}