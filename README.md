# caveEngine
## Instrucciones de uso
1) Clonar el repositorio y hacer prebuild usando CMake con Visual Studio 16 2019.
2) Compilar en modo "Release x64".
3) Dentro de la carpeta de build, en "examples\Release" se encontrará el archivo de prueba "Example1.exe".
4) Para hacerlo funcionar, copiar ahí el contenido de la carpeta "thirdParty/ogre/bin/release".
5) Agregar también la carpeta "Resources", que se encuentra en la carpeta source.
6) La documentacion generada por doxygen se encuentra en la carpeta source -> documentation/html/index.html.

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

  - **void Overlay::configureContainer(float positionLeft, float positionTop, float width, float height)**:
  Configura las dimensiones y posición de la caja contenedora de textos.
  - **void Overlay::addTextElement(std::string& textElementName, float positionLeft, float positionTop, float width, float height)**:
  Agrega un elemento de texto a la caja contenedora de textos.
  - **void Overlay::configureTextElement(std::string& textElementName, int fontSize, std::string fontName, Ogre::ColourValue colour)**:
  Configura fuente, tamaño de fuente y color de un elemento de texto.
