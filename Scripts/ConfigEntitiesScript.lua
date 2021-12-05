-- Estructura para la configuracion de entidades:
-- name = string entityName
-- SkeletalMeshComponent = { rotation = quat rotation(default=(0,0,0,1)), translation = vec translation(default=(0,0,0)), scaling = vec scaling(default=(1,1,1)) }
-- TextComponents[i] = {  name = string name, positionLeft=float positionLeft, float positionTop=positionTop, width=float width, height=float height,
-- fontSize = float fontSize, fontName = string fontName, textColour =colourVec textColour, caption = string caption} --> config text elements
-- AudioSourceComponent = { audioClipName = string audioClipName} --> audioClip to play


Entities = {}

Entities[0]["name"] = "player"
Entities[0]["TextComponents"][0] = {positionLeft= 0, positionTop=0, width =1, height = 1, fontSize=0.09, 
fontName="exFont", textColour ={r=1,g=0,b=0,alpha=1}, caption = "Escapa de los ogros!!!!"}

Entities[1]["name"] = "sinbad1"
Entities[1]["SkeletalMeshComponent"] = {translation={x=0,y=0,z=0}, rotation={x=0f,y=0,z=0,w=1}, scaling={x=5,y=5,z=5} }
Entities[1]["AudioSourceComponent"] = {audioClipName = "survival"}

Entities[2]["name"] = "sinbad2"
Entities[2]["SkeletalMeshComponent"] = {translation={x=5,y=15,z=0}}