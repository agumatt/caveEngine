# caveEngine


## Modulo de Rendering

### clase RenderingManager
Se encargar de setear los aspectos relacionados a rendering y carga de modelos.

  - **void RenderingManager::StartUp()**:
    seteo de viewport y ventana. Llamado por la clase World para poder empezar a renderizar.

  - **void RenderingManager::loadResourcesFolder(std::string path, std::string resourcesGroupName)**:
    Permite agregar una carpeta al registro de carpetas con recursos (como fonts y modelos). El "resourcesGroupName" permite acceder a estos recursos mas adelante. Múltiples         carpetas pueden incluirse en un mismo grupo.

  - **void RenderingManager::configureTextResources(std::vector(Font)& fonts)**:
    Se carga un conjunto fuentes para ser utilizadas mas tarde al renderizar texto.
  
  
  - **void RenderingManager::addResourcesToScene(std::vector(Model) &models)**:
    Se agrega un conjunto de modelos a la escena, con lo que quedan listos para ser renderizados.
  
  - **void RenderingManager::drawText(Overlay& overlay, std::string& textElementName, std::string& caption)**:
    Se setea el texto a ser dibujado en una caja de texto previamente configurada con la clase Overlay. 
  
  - **void RenderingManager::render()**
    Metodo llamado desde la clase World para dibujar un frame.  
  
  - **void RenderingManager::configureCamera(Ogre::Vector3 position, Ogre::Vector3 lookAt, OgreBites::CameraStyle cameraStyle, float nearClipDistance, float farClipDistance)**:
    Configura aspectos básicos de la cámara. CameraStyle puede ser CS_MANUAL, CS_ORBIT y CS_FREELOOK. Estos estilos determinan distintos tipos de control de la vista con teclado     (teclas WASD) y mouse.

### clase Model
Guarda la información necesaria para añadir luego el modelo a la escena.
  
  - **void Model::setInitialRotation(Ogre::Quaternion initialRotation)**:
    La rotacion inicial que se asigna al modelo.

  - **void Model::setInitialTranslation(Ogre::Vector3 initialTranslation)**:
    La traslación que se asigna al modelo.

  - **void Model::setInitialScaling(Ogre::Vector3 initialScaling)**:
    El escalamineto inicial que se aigna al modelo.

  - **void Model::setParentNodeName(std::string parentNodeName)**:
    Permite asignar un nodo padre al nodo del modelo en la jerarquía de nodos de escena.
  
### clase Font
Guarda la información necesaria para añadir una fuente.
  
### clase Overlay
Base para añadir texto usando una de las fuentes previamente configuradas.
