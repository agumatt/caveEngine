-- Estructura para la creacion de entidades:
-- name = string entityName
-- SkeletalMeshComponent = { meshFileName=string meshFileName, nodeName=string nodeName, parentNodeName=string parentNodeName(default="RootSceneNode") }
-- TextComponent = { positionLeft=float positionLeft, float positionTop=positionTop, width=float width, height=float height }
-- CameraComponent = {position=vec position, lookAt=vec lookAt, nearClipDistance=float nearClipDistance(default=1.0f), farClipDistance=float farClipDistance(default=1000.0f) }
-- AudioSourceComponent = { volume=float volume, pitch=float pitch, radius=float radius, setLoop=bool setLoop(default=true), position=caveVec3f pos(default=(0,0,0)) }
-- EventRegistryComponent = {}


Entities = {}

Entities[0]["name"] = "player"
Entities[0]["CameraComponent"] = {position={x=0, y=0, z=80}, lookAt={x=0, y=0, z=-1}}
Entities[0]["TextComponent"] = {positionLeft= 0, positionTop=0, width =1, height = 1}
Entities[0]["AudioSourceComponent"] = {volume= 0 , pitch=1, radius=100}
Entities[0]["EventRegistryComponent"] = {}

Entities[1]["name"] = "sinbad1"
Entities[1]["SkeletalMeshComponent"] = {meshFileName= "exSinbad.mesh", nodeName="sinbad1", translation={x=0,y=0,z=0}, rotation={x=0f,y=0,z=0,w=1}, scaling={x=5,y=5,z=5} }
Entities[1]["TextComponent"] = {positionLeft= 0, positionTop=0, width =1, height = 1}
Entities[1]["AudioSourceComponent"] = {volume= 0 , pitch=1, radius=100}
Entities[1]["EventRegistryComponent"] = {}

Entities[2]["name"] = "sinbad2"
Entities[2]["SkeletalMeshComponent"] = {meshFileName= "exSinbad.mesh", nodeName="sinbad2", translation={x=5,y=15,z=0}}
Entities[2]["AudioSourceComponent"] = {volume= 0 , pitch=1, radius=100}
Entities[2]["EventRegistryComponent"] = {}