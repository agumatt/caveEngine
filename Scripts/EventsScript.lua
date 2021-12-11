-- Events = {{name=event1,timeOut=float timeOut(default=0)}, {name=event1,timeOut=float timeOut(default=0)}, ...} --> Event names and optional timeOut per event
-- EventsPerEntity = {entity1Name = {event3, event2, ...}, ...} --> Named events assigned to entities
-- EventTriggers = {eventName = {trigger1, trigger2, ...}, ...}
-- EventReactions[eventName] = {targetEntitiesByName = {entity1Name, entity2Name,...}, 
-- targetEntitiesByComponents = {Component1Name, Component2Name,...},  affectTriggerEntity = boolean affectTriggerEntity (default=false)
-- , modifiersByComponent = {SkeletalMeshComponent=function modifier1(), TextComponent = function modifier2(), ...}, callback = function callback} -->Decide which entities (by name and by owned components) are affected and how
-- modifiersByComponent can hold one function per component. No reciben argumentos y entregan los valores a setear.

-- functions

function tableContains(table, element)
  for _, value in pairs(table) do
    if value == element then
      return true
    end
  end
  return false
end

function entityReachedPlayerTrigger()
	return cpp_entityReachedPlayer()
end

function entityInSightTrigger()
	return cpp_entitiesInSight()
end


function entityOutOfSightTrigger()
	local entitiesInSight = cpp_entitiesInSight()
	local entities = cpp_getEntityNames()
	result = {}
	local index = 0
	for _, entity in pairs(entities) do
		if entity~="player" and not tableContains(enitityInSight, entity) then
			result[index] = entity
			index = index + 1
		end
	end
	return result
end

numberOfTimesCaught = 0 
function entityReachedPlayerTextComponentModifier()
	numberOfTimesCaught = numberOfTimesCaught + 1
	textElementName_ = "vecesAtrapado"
	caption_ = "Veces atrapado: " .. numberOfTimesCaught
	fontSize_=0.06*numberOfTimesCaught
	fontName_="exFont"
	textColour_ ={r=1,g=1,b=0,alpha=1}
	return {{textElementName=textElementName_, caption=caption_, fontSize=fontSize_, fontName=fontName_, textColour=textColour_}}
end




function entityInSightCallback()
	local entitiesInSight = cpp_entitiesInSight();
	for _, entity in pairs(entitiesInSight) do
		if entity=="sinbad1" then 
			cpp_updateChasePlayer(entity)
		elseif entity=="sinbad2" then
			cpp_stopChasePlayer(entity)
		end
	end
end

function entityOutOfSightCallback()
	local entitiesInSight = cpp_entitiesInSight()
	local entities = cpp_getEntityNames()
	entitiesOutOfSight = {}
	local index = 0
	for _, entity in pairs(entities) do
		if entity~="player" and not tableContains(enitityInSight, entity) then
			entitiesOutOfSight[index] = entity
			index = index + 1
		end
	end
	for _, entity in pairs(entitiesOutOfSight) do
		if entity=="sinbad1" then 
			cpp_stopChasePlayer(entity)
		elseif entity=="sinbad2" then
			cpp_updateChasePlayer(entity)
		end
	end
end

--

Events = {}
EventsPerEntity = {}
EventTriggers = {}
EventReactions = {}
--
Events[1] = {name = "entityReachedPlayer", timeOut = 2}
Events[2] = {name = "entityInSight"}
Events[3] = {name = "entityOutOfSight"}

EventsPerEntity["player"] = {Events[1]["name"], Events[2]["name"], Events[3]["name"]}
EventsPerEntity["sinbad1"] = {Events[1]["name"], Events[2]["name"], Events[3]["name"]}
EventsPerEntity["sinbad2"] = {Events[1]["name"], Events[2]["name"], Events[3]["name"]}

EventReactions["entityReachedPlayer"] = {}
EventReactions["entityReachedPlayer"]["targetEntitiesByName"] = {"player"};
EventReactions["entityReachedPlayer"]["timeOut"] = 2;
EventReactions["entityReachedPlayer"]["modifiersByComponent"]={}
EventReactions["entityReachedPlayer"]["modifiersByComponent"]["TextComponent"] = entityReachedPlayerTextComponentModifier

EventReactions["entityInSight"] = {}
EventReactions["entityInSight"]["affectTriggerEntity"] = true;
EventReactions["entityInSight"]["modifiersByComponent"] = {};
EventReactions["entityInSight"]["callback"] = entityInSightCallback;

EventReactions["entityOutOfSight"] = {}
EventReactions["entityOutOfSight"]["affectTriggerEntity"] = true;
EventReactions["entityOutOfSight"]["modifiersByComponent"] = {};
EventReactions["entityOutOfSight"]["callback"] = entityOutOfSightCallback;


EventTriggers["entityReachedPlayer"] = {entityReachedPlayerTrigger}
EventTriggers["entityInSight"] = {entityInSightTrigger}
EventTriggers["entityOutOfSight"] = {entityOutOfSightTrigger}


