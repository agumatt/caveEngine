# caveEngine
## Instrucciones de uso
1) Clonar el repositorio.
2) Clonar el submodulo de Ogre (se tiene como submodulo para evitar errores de compilacion pasados).
3) Hacer prebuild usando CMake con Visual Studio 16 2019.
4) Compilar en modo "Release x64". El modo debug puede generar errores en la compilacion de assimp y ogre.
5) Dentro de la carpeta de build, en "examples\Release" se encontrará el archivo de prueba "Example1.exe".
6) Para hacerlo funcionar, copiar ahí el contenido de la carpeta "thirdParty/ogre/bin/release".
7) Agregar también las carpetas "Resources" y "Scripts", que se encuentra en la carpeta source.
8) La documentacion generada por doxygen se encuentra en la carpeta source -> documentation/html/index.html.
