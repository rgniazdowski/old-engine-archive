----------------------------------
-- Main script for endless flying
--

fg.GameLogic:stopGame()

function protect_table(tbl)
    return setmetatable({}, {
        __index = tbl,
        __newindex = function(t, key, value)
            error("attempting to change constant " .. tostring(key) .. " to " .. tostring(value), 2)
        end
    })
end -- function

DEMO_MODE = {
    NONE = 0,
    PHYSICS_CUBES = 1,
    PHYSICS_STAIRS_RAGDOLLS = 2,
    PHYSICS_RAGDOLLING = 3,
    MESH_SKINNING = 4,
    SCENE_TRIGGERS = 5,
    EXPLOSION_PARTICLES = 6,
    NUM_DEMO_MODES = 7
}
DEMO_MODE = protect_table(DEMO_MODE)
DEMO_MODE_NAME = {}
DEMO_MODE_NAME[0] = "NONE"
DEMO_MODE_NAME[1] = "PHYSICS CUBES"
DEMO_MODE_NAME[2] = "PHYSICS STAIRS RAGDOLLS"
DEMO_MODE_NAME[3] = "PHYSICS RAGDOLLING"
DEMO_MODE_NAME[4] = "MESH SKINNING"
DEMO_MODE_NAME[5] = "SCENE TRIGGERS"
DEMO_MODE_NAME[6] = "EXPLOSION PARTICLES"

CURRENT_DEMO_MODE = DEMO_MODE.NONE

-- Game Entity actor is a special node type (NodeObject) - it has physical properties 
-- and can be animated. It also has AI traits.
fg.Scene3D:setDefaultNodeObjectType(fg.GAME_ENTITY_ACTOR);

ENEMY1_NEW_HEIGHT=100.0
ENEMY2_NEW_HEIGHT=100.0

tmpObject = fg.Scene3D:addFromModel("Enemy2", "Enemy2_one")
tmpObject:getModel():applyResize(-1.0, ENEMY2_NEW_HEIGHT, -1.0)
tmpObject:rebuildRagdoll()

--tmpObject:applyResize(-1.0, 100.0, -1.0)
--tmpObject:setAnimation("dead_by_headshotF", 0)
--tmpObject:setAnimation("crooked_runF", 0)
tmpObject:setAnimation("claw_runF", 0)
--tmpObject:setAnimation("claw_attackF", 1)
--tmpObject:setAnimation("crooked_attackre", 1)
--tmpObject:translate(-90.0, 100.0, -200.0)
tmpObject:translate(-90.0, 100.0+ENEMY2_NEW_HEIGHT/2.0, -100.0)

--tmpObject:getChildByIndex(0):setScale(0.2,0.2,0.2)
--tmpObject:getChildByIndex(1):setScale(0.2,0.2,0.2)
tmpObject:rotate(0.57, 0.0, 1.0, 0.0)

tmpObject = fg.Scene3D:addFromModel("Enemy2", "Enemy2_two")
tmpObject:setAnimation("claw_runF", 0)
tmpObject:setAnimation("claw_attackF", 1)
tmpObject:translate(-90, 180.0+ENEMY2_NEW_HEIGHT/2.0, -150.0)

tmpObject = fg.Scene3D:addFromModel("Enemy2", "Enemy2_three")
tmpObject:setAnimation("claw_attackF", 0)
tmpObject:setAnimation("claw_runF", 1)
tmpObject:translate(-250, 300.0+ENEMY2_NEW_HEIGHT/2.0, -102.0)

ragdollVictim = fg.Scene3D:addFromModel("Enemy2", "ragdollVictim")
ragdollVictim:setAnimation("claw_runF", 0)
ragdollVictim:setAnimation("claw_attackF", 1)

-------------------------------------------------------------------------------
-- ENEMY 1 (two inner meshes)
--

tmpObject = fg.Scene3D:addFromModel("Enemy1", "Enemy1_one")
tmpObject:getModel():applyResize(-1.0, ENEMY1_NEW_HEIGHT, -1.0)
--tmpObject:applyResize(-1.0, 90.0, -1.0)
--tmpObject:setAnimation("dead_by_headshotF", 0)
tmpObject:setAnimation("crooked_runF", 0)
tmpObject:translate(-60.0, 120.0, 100.0)
tmpObject:rotate(1.57, 0.0, 1.0, 0.0)

tmpObject = fg.Scene3D:addFromModel("Enemy1", "Enemy1_two")
--tmpObject:applyResize(-1.0, 50.0, -1.0)
--tmpObject:setAnimation("dead_by_headshotF", 0)
tmpObject:setAnimation("crooked_runF", 0)
tmpObject:setAnimation("crooked_attackre", 1)
tmpObject:translate(-60.0, 120.0, 250)
tmpObject:rotate(1.57, 0.0, 1.0, 0.0)

tmpObject = fg.Scene3D:addFromModel("Enemy1", "Enemy1_three")
--tmpObject:setScale(2.0, 2.0, 2.0)
--tmpObject:applyResize(-1.0, 190.0, -1.0)
--tmpObject:setAnimation("dead_by_headshotF", 0)
tmpObject:setAnimation("crooked_runF", 0)
tmpObject:setAnimation("crooked_attackre", 1)
tmpObject:translate(-60.0, 120.0, 400)
tmpObject:rotate(1.57, 0.0, 1.0, 0.0)

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
fg.Scene3D:setDefaultNodeObjectType(fg.GAME_ENTITY);

stairsXBegin=250.0
stairsYBegin=20.0
stairsZBegin=150.0

stairStepWidth=100.0
stairStepHeight=45.0

stairIndex=0
stairsCount=10

for xCount = 1, stairsCount do
	yHeight = xCount
	stairNodeName="stair_"..stairIndex
	stairIndex=stairIndex+1
	io.write("Creating stair step: '", stairNodeName, "', index: ", stairIndex, " XY:(",xCount,",",yHeight,")\n")

	cubeHeight=stairStepHeight*yHeight -- Y
	cubeDepth=stairStepHeight -- X
	cubeWidth=stairStepWidth+cubeHeight/2.0 -- Z

	cubeXOffset=0.0
	if(xCount == stairsCount) then
		cubeDepth=cubeDepth*4.0
		cubeXOffset=cubeDepth/2.0-stairStepHeight/2.0
	end

	cubeXOffset=cubeXOffset+(xCount-1)*stairStepHeight
	cube = fg.Scene3D:addFromModel("builtinCube1x1", stairNodeName)
	cube:translate(stairsXBegin+cubeXOffset, stairsYBegin+cubeHeight/2.0, stairsZBegin)
	cubeChild = cube:getChildByIndex(0)

	if(xCount == stairsCount) then
		ragdollVictim:translate(stairsXBegin+cubeXOffset, stairsYBegin+cubeHeight+ENEMY2_NEW_HEIGHT/2.0+10, stairsZBegin)
		ragdollVictim:rotate(-1.57, 0.0, 1.0, 0.0)
	end

	if(cubeChild:isValid()) then
		hasCollisionBody = cubeChild:hasCollisionBody()
		collisionBody = cubeChild:getCollisionBody()
		if(collisionBody:isValid()) then
			collisionBody:setMass(0.0)
		end
		-- cubeChild:setHalfSize(10.0, 0.5, 10.0)
		-- collisionBody:setHalfSize(40.0, 0.5, 40.0)
		-- collisionBody:setLocalScaling(200.0, 10.0, 200.0)
		cubeChild:setScale(cubeDepth, cubeHeight, cubeWidth)
	end -- if
end -- for

-------------------------------------------------------------------------------
-- fg.Scene3D:setDefaultNodeObjectType(fg.SCENE_NODE_OBJECT);

baseLayerObj = fg.Scene3D:addFromModel("builtinCube1x1", "baseLayer")
baseLayerObj:translate(0.0, 0.0, 27)
baseLayerObjChild = baseLayerObj:getChildByIndex(0)
if(baseLayerObjChild:isValid()) then
	io.write("CUBE5 IS VALID TRUE\n")
	hasCollisionBody = baseLayerObjChild:hasCollisionBody()
	io.write("CUBE5 COLLIDE BODY: ", tostring(hasCollisionBody), "\n")
	collisionBody = baseLayerObjChild:getCollisionBody()
	if(collisionBody:isValid()) then
		collisionBody:setMass(0.0) -- make a static body
	end
	-- baseLayerObjChild:setHalfSize(10.0, 0.5, 10.0)
	-- collisionBody:setHalfSize(40.0, 0.5, 40.0)
	-- collisionBody:setLocalScaling(200.0, 10.0, 200.0)
	baseLayerObjChild:setScale(4400.0, 10.0, 4400.0)
	-- collisionBody:setHalfSize()
end -- if

justTesting = 0
victimizeRagdoll = false
throwBoxes = false

function throwBoxesFunc()
	if(throwBoxes == true) then
		return
	end
	local numBoxes = 25
    local boxIdx = 0
    local cube, cubeChild
	for boxIdx = 1, numBoxes do
		boxName="boxID_"..boxIdx
		cube = fg.Scene3D:addFromModel("builtinCube1x1", boxName)
		cubeChild = cube:getChildByIndex(0)
		cubeChild:setScale(15.0, 15.0, 15.0)
		cubeChild:getCollisionBody():setMass(10.0)
		cube:translate(stairsXBegin+100.0+boxIdx*1, stairsYBegin+150.0+ENEMY2_NEW_HEIGHT+boxIdx*10, stairsZBegin)		
	end -- for
	throwBoxes = true
end -- function

--
-- CLICK EVENT (TAP FINISHED)
--
function tapFinished(event)
    
end -- function
fg.EventManager:addEventCallback(fg.EVENT_TOUCH_TAP_FINISHED, tapFinished) 

--
-- SCENE MANAGER QUICK SETUP
--

fg.Scene3D:setPickSelectionOnClick(fg.TRUE)
--fg.Scene3D:setPickSelectionOnHover(fg.TRUE)
fg.Scene3D:setPickSelectionGroup(fg.TRUE)
fg.Scene3D:setPickSelectionToggle(fg.TRUE)
fg.Scene3D:setPickSelectionBox(fg.TRUE)
fg.Scene3D:setIgnoreCollisions(fg.TRUE)

fg.Scene3D:setShowGroundGrid(fg.FALSE) -- do not show the grid
fg.Scene3D:setHideSkyBox(fg.FALSE)
fg.Scene3D:setSkyBoxFollowsCamera(fg.FALSE)

fg.Scene3D:setPickSelectionAABBTriangles(fg.TRUE)
--fg.Scene3D:setHideNodes(FG_TRUE)
fg.Scene3D:setLinearTraverse(fg.FALSE)

--
-- DEMO EXECUTION CODE
--

function executeDemoPhysicsCubes()
    -- nothing to return
    io.write("EXECUTING executeDemoPhysicsCubes\n")
    throwBoxesFunc()
    throwBoxes = true
end

function executeDemoPhysicsStairsRagdolls()
    io.write("EXECUTING executeDemoPhysicsStairsRagdolls\n")
    if(victimizeRagdoll == false) then
		ragdollVictim:startRagdolling()
		ragdollVictim:getRagdollCollisionBody():setGravity(0.0, -10.0, 0.0)
		ragdollVictim:getRagdollCollisionBody():setMass(350.0)
		ragdollVictim:getRagdollCollisionBody():applyCentralImpulse(-9500, 4500.0, 250.0)
		victimizeRagdoll=true
		-- How about throwing some cubes? :)
	end
end

ragdollingStatus = false

enemiesArray = {
    fg.Scene3D:get("Enemy1_one"),
    fg.Scene3D:get("Enemy1_two"),
    fg.Scene3D:get("Enemy1_three"),
    fg.Scene3D:get("Enemy2_one"),
    fg.Scene3D:get("Enemy2_two"),
    fg.Scene3D:get("Enemy2_three")
}

function executeDemoPhysicsRagdolling() 
    io.write("EXECUTING executeDemoPhysicsRagdolling\n")
    local enemyIdx, tmpObject
    if(ragdollingStatus == true) then
        for enemyIdx = 1, 4 do
            tmpObject = enemiesArray[enemyIdx]
            if(tmpObject:isValid()) then
                tmpObject:stopRagdolling()
            end
        end -- for
        ragdollingStatus = false;
    elseif(ragdollingStatus == false) then
        ragdollingStatus = true
        for enemyIdx = 1, 4 do
            tmpObject = enemiesArray[enemyIdx]
            if(tmpObject:isValid()) then
                tmpObject:stopAnimations()
                tmpObject:startRagdolling()
            end
        end -- for
    end
end -- function

function executeDemoMeshSkinning()
    io.write("EXECUTING executeDemoMeshSkinning\n")
    local enemyIdx, tmpObject
    for enemyIdx = 1, 6 do
        tmpObject = enemiesArray[enemyIdx]
        if(tmpObject:isValid()) then
            tmpObject:playAnimations()
        end
    end -- for
    --cube18:getAnimationInfoBySlot(0):loop(10, fg.TRUE)
    --cube18:getAnimationInfoBySlot(1):loop(2, fg.TRUE)
end -- function

function executeDemoSceneTriggers()
    io.write("EXECUTING executeDemoSceneTriggers\n")
end

function executeDemoExplosionParticles()
    io.write("EXECUTING executeDemoExplosionParticles\n")
end

-- match strings to functions! name of current demo mode (presentation)
demoExecutionArray = {
    [DEMO_MODE_NAME[1]] = executeDemoPhysicsCubes,
    [DEMO_MODE_NAME[2]] = executeDemoPhysicsStairsRagdolls,
    [DEMO_MODE_NAME[3]] = executeDemoPhysicsRagdolling,
    [DEMO_MODE_NAME[4]] = executeDemoMeshSkinning,
    [DEMO_MODE_NAME[5]] = executeDemoSceneTriggers,
    [DEMO_MODE_NAME[6]] = executeDemoExplosionParticles
}

function executeDemo(demoModeId)
    local demoFunction = demoExecutionArray[DEMO_MODE_NAME[demoModeId]]
    local isFunction = type(demoFunction) == "function"
    if(isFunction) then
        demoFunction()
    else
        io.write(">> WARNING: could not execute demo function [",demoModeId,"]\n")
    end
    -- nothing to return (or boolean status maybe?)
end

--
-- KEYBOARD CONFIGURATION - KEY UP/DOWN EVENT HANDLING
--
function keyEvent(event)
    if(event.code == fg.EVENT_KEY_UP) then
        local demoModeId, keyCode, eventKeyCode
        eventKeyCode = event.key.keyCode
        -- check keys 0, 1, ..., 6 and others
        for demoModeId = 0, (DEMO_MODE.NUM_DEMO_MODES-1) do
            keyCode = fg.key.KEY_0 + demoModeId
            if(eventKeyCode == keyCode) then
                CURRENT_DEMO_MODE = demoModeId
                io.write(">> CURRENT DEMO MODE set to: ", DEMO_MODE_NAME[CURRENT_DEMO_MODE], "\n")
                break
            end
        end
        
        if(eventKeyCode == fg.key.RETURN) then
            executeDemo(CURRENT_DEMO_MODE)
        end
        
       --if(event.key.keyCode == fg.key.KEY_1) then
           --fg.setDebugConfig("gfxTreeBBoxShow", not fg.getDebugConfig("gfxTreeBBoxShow"))           
       --end
    end    
end

--fg.EventManager:addEventCallback(fg.EVENT_KEY_DOWN, keyEvent)
fg.EventManager:addEventCallback(fg.EVENT_KEY_UP, keyEvent);


fg.ShaderManager:request("sGfxMeshSkinning")
collectgarbage("collect")
