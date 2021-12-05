-- Estructura para la creacion de entidades:
-- name = string entityName
-- SkeletalMeshComponent = { meshFileName=string meshFileName, nodeName=string nodeName, rotation = quat rotation(default=(0,0,0,1))
-- , translation = vec translation(default=(0,0,0)), scaling = vec scaling(default=(1,1,1)), parentNodeName=string parentNodeName(default="RootSceneNode") }
-- TextComponent = { positionLeft=float positionLeft, float positionTop=positionTop, width=float width, height=float height }
-- CameraComponent = {position=vec position, lookAt=vec lookAt, nearClipDistance=float nearClipDistance(default=1.0f), farClipDistance=float farClipDistance(default=1000.0f) }
-- AudioSourceComponent = { volume=float volume, pitch=float pitch, radius=float radius, setLoop=bool setLoop(default=true), position=caveVec3f pos(default=(0,0,0)) }
-- EventRegistryComponent = {}


entities = {}

entities[0]["name"] = "player"
entities[0]["CameraComponent"] = {position=, lookAt=}
entities[0]["TextComponent"] = {positionLeft= 0.0f, positionTop=0.0f, width =1.0f, height = 1.0f}
entities[0]["AudioSourceComponent"] = {volume= 0.3f , pitch=1.0f, radius=100.0f}
entities[0]["EventRegistryComponent"] = {}

entities[1]["name"] = "sinbad1"
entities[1]["SkeletalMeshComponent"] = {meshFileName= "exSinbad.mesh", nodeName="sinbad1"}, translation={x=0.0f,y=0.0f,z=0.0f}, rotation={x=0.0f,y=0.0f,z=0.0f,w=1.0f}, scaling={x=1.0f,y=1.0f,z=1.0f} }
entities[1]["TextComponent"] = {positionLeft= 0.0f, positionTop=0.0f, width =1.0f, height = 1.0f}
entities[1]["AudioSourceComponent"] = {volume= 0.3f , pitch=1.0f, radius=100.0f}
entities[1]["EventRegistryComponent"] = {}

entities[2]["name"] = "sinbad2"
entities[2]["SkeletalMeshComponent"] = {meshFileName= "exSinbad.mesh", nodeName="sinbad2"}
entities[2]["AudioSourceComponent"] = {volume= 0.3f , pitch=1.0f, radius=100.f}
entities[2]["EventRegistryComponent"] = {}