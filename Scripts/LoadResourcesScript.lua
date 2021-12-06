-- Estructura para la carga de recursos:
-- Audio[i] = {audioFilePath = string audioFilePath, uniqueName = string uniqueName}
-- ResourcesFolders[i] = {folderPath=string folderPath} --> for fonts and meshes
-- Fonts[i] = {fontFileName = string fontFileName, uniqueName = string uniqueName} --> Contained in a resources folder


Audio = {}
Fonts = {}
ResourcesFolders = {}

Audio[1] = {audioFilePath = "Resources/Audio/survival.wav", uniqueName ="survival"};
ResourcesFolders[1] = {folderPath = "Resources/Fonts"}
ResourcesFolders[2] = {folderPath = "Resources/Meshes"}
Fonts[1] = {fontFileName = "DejaVuSerifCondensedItalic.ttf", uniqueName ="exFont"};