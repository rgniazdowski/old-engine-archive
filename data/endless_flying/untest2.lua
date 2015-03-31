print("Stating main script FG\n")

texture1 = fg.ResourceManager.request("MainBackgroundTexture")

name = texture1:getName()
path = texture1:getFilePath()

io.write("name of the texture: ", name, "\n")
io.write("path to the texture: ", path, "\n")
texture1 = nil

sparks = fg.ResourceManager.request("ExplosionSparks")
loadedFont = fg.ResourceManager.request("Loaded")

loadedFontRef = loadedFont

sparksTexName = sparks:getTextureName()
sparks:setFacingVelocity(1)
vec2 = fg.Vector2f()
vec2.x = 10.0
vec2.y = 15.1111
yolo1 = vec2
sparks:setLifeRange(yolo1)

ssize = sparks:getStartSize()
ssize.x = 300.0
ssize.y = 300.0
ssize.z = 300.0

sparks:getStartSize().x = 100.0
sparks:getStartSize().y = 100.0

debris = fg.ResourceManager.request("ExplosionDebris")

vec3 = fg.Vector3f()
vec3.x = 300.0
vec3.y = 300.0
vec3.z = 300.0

vec2.x = 15.0
vec2.y = 20.1111

debris:setFacingVelocity(1)
debris:setSpreadSpeed(vec3)
debris:setLifeRange(vec2)
debris:setEndColor4i(255,50,0,0)

io.write("Creating YOLANTA\n")
button1 = fg.Button()
io.write("After creation YOLANTA\n")
button1:setName("YOLANTA1")
button1:getPosition().x = 200
button1:getPosition().y = 400
button1:setText("SKRYPT LUA POZDRAWIA")
button1:setStyleName("RelButton")

mainmenu = fg.WidgetManager:getWidget("MainMenu")
mainmenu:addChild(button1)
fg.WidgetManager:addWidgetWithFather(button1, mainmenu)
b1name = button1:getName()
io.write("Button 1 new name: ", b1name, "\n")

buttonxx = fg.WidgetManager:getWidget("YOLANTA1")
buttonxx:getName()
buttonxx = nil

function testxxxx()
	io.write("Button YOLANTA local GET\n")
	local buttonxxxxx = fg.WidgetManager:getWidget("YOLANTA1")
end

io.write("Calling localized get YOLANTA1\n")
testxxxx()
io.write("Calling GC collect after local YOLANTA\n")
collectgarbage("collect")

stylenone = button1:getStyleContent(fg.GUI_WIDGET_STATE_NONE)
backgroundstyle = stylenone:getBackground()
backgroundstyle.color.r = 0.5
backgroundstyle.color.g = 0.5
backgroundstyle.color.b = 0.0
backgroundstyle.color.a = 1.0
button1:setVisible(1)

mainmenu:getStyleContent(fg.GUI_WIDGET_STATE_NONE):getBackground().color.r = 1.0

backgroundstyle2 = stylenone:getBackground()
stylenone:getForeground().color.z = 1.0

function testCallback1(event)
--	io.write("TEST CALLBACK FOR TAP EVENT: LUA! \n")
	if(event.eventType == fg.EVENT_TOUCH_TAP_FINISHED) then
		io.write("LUA TOUCH: X: ", event.touch.x, " Y: ", event.touch.y, "\n")
	end
	local x = event.touch.x;
	local y = event.touch.y;
--	fg.SoundManager:play("explode.wav")
	--local some_sound = fg.SoundManager:request("explode.wav")
	--some_sound:play()
--	io.write("EXPLODE: NAME: '", some_sound:getName(), "' ...\n")
	if(x < 100 and y < 100) then
		fg.SoundManager:play("shot.wav")
	end
	if(x > 100 and x < 200) then
		fg.SoundManager:play("shot2.wav")
	end
	if(x > 200 and x < 300) then
		fg.SoundManager:play("empty.wav")
	end
	if(x > 300 and x < 400) then
		fg.SoundManager:play("shot.wav")
	end
--	fg.SoundManager:play("mod.shamrip.mod")
	local mus = "mod.dragonsfunk.mp3"
--	fg.SoundManager:setMusicVolume(0.5)
	if(fg.SoundManager:isPlaying(mus) == 0) then
		io.write("MUSIC IS NOT PLAYING! GOING TO PLAY\n")
--		fg.SoundManager:play(mus)
	else
		io.write("MUSIC IS ALREADY PLAYING!\n")
	end
end

function resourceCallback(event)
	if(event.eventType == fg.EVENT_RESOURCE_CREATED) then
		io.write("LUA RESOURCE: NAME: ", event.resource.resource:getName(), "\n")
	end
end

function testCallback2()
	io.write("TESTING SECOND CALLBACK: SCRIPT TYPE! No args\n")
end

function testCallback3(event)
	io.write("XXXX\n")
end

fg.EventManager.addEventCallback(fg.EVENT_TOUCH_TAP_FINISHED, testCallback1, 1)
fg.EventManager.addEventCallback(fg.EVENT_TOUCH_TAP_FINISHED, "testCallback2()", 0)
--fg.EventManager.addEventCallback(fg.EVENT_TOUCH_MOTION, testCallback3, 1)
fg.EventManager.addEventCallback(fg.EVENT_RESOURCE_CREATED, resourceCallback)

repeats = 9

function gameStarted()
	io.write(">> >> >> GAME STARTED\n");
end

function gamePaused()
	io.write(">> >> >> GAME PAUSED\n");
end

function gameStopped()
	io.write(">> >> >> GAME STOPPED\n");
end

function nodeCollision(nodeA, nodeB)
	nameA = nodeA:getName()
	nameB = nodeB:getName()
	pos1 = nodeA:getPosition()
	pos2 = nodeB:getPosition()
	x = (pos1.x + pos2.x) / 2.0
	y = (pos1.y + pos2.y) / 2.0
	z = (pos1.z + pos2.z) / 2.0
	io.write("NODEA POS: ", pos1.x, " ", pos1.y, " ", pos1.z, " NODEB POS", pos2.x, " ", pos2.y, " ", pos2.z , "CENTER: ", x, " ", y, " ", z, "\n")
	fg.ParticleSystem:addParticles("ExplosionDebris", 20, x, y, z)
	fg.ParticleSystem:addParticles("ExplosionFlash", 2, x, y, z)
	fg.ParticleSystem:addParticles("ExplosionRoundSparks", 6, x, y, z)
	fg.ParticleSystem:addParticles("ExplosionShockwave", 1, x, y, z)
	fg.ParticleSystem:addParticles("ExplosionSmoke", 20, x, y, z)
	fg.ParticleSystem:addParticles("ExplosionSmokeTrails", 32, x, y, z)
	fg.ParticleSystem:addParticles("ExplosionSparks", 48, x, y, z)
	io.write("NODEA NAME: ", nameA, " NODEB NAME: ", nameB, "\n")
	if string.find(nameA, "cubeyolo") or string.find(nameB, "cubeyolo") then
		fg.SoundManager:play("menu2.wav")
	else
		fg.SoundManager:play("explosion.wav")
	end

	
	if string.find(nameA, "box") and string.find(nameB, "box") then
		if not string.find(nameA, "_sx") and not string.find(nameB, "_sx") then
		local newNameA = nameA .. "_sx"
			local newNameB = nameB .. "_sx"
	
			local scaleDelim = 1.35

			local scaleA = nodeA:getScale()
			local scaleB = nodeB:getScale()
			scaleA.x = scaleA.x / scaleDelim
			scaleA.y = scaleA.y / scaleDelim
			scaleA.z = scaleA.z / scaleDelim

			scaleB.x = scaleB.x / scaleDelim
			scaleB.y = scaleB.y / scaleDelim
			scaleB.z = scaleB.z / scaleDelim

			local posA = nodeA:getPosition()
			local posB = nodeB:getPosition()

			newNodeA1 = fg.Scene3D:addDuplicate(nameA, newNameA .. "1")
			newNodeA2 = fg.Scene3D:addDuplicate(nameA, newNameA .. "2")

			newNodeA1:setScale(scaleA.x, scaleA.y, scaleA.z)
			newNodeA2:setScale(scaleA.x, scaleA.y, scaleA.z)

			newNodeA1:setPosition(posA.x - 5.0, posA.y + 10.0, posA.z - 15.0)
			newNodeA2:setPosition(posA.x + 5.0, posA.y - 10.0, posA.z + 15.0)
		
			----------------------------------------------------------
			newNodeB1 = fg.Scene3D:addDuplicate(nameB, newNameB .. "1")
			newNodeB2 = fg.Scene3D:addDuplicate(nameB, newNameB .. "2")

			newNodeB1:setScale(scaleB.x, scaleB.y, scaleB.z)
			newNodeB2:setScale(scaleB.x, scaleB.y, scaleB.z)

			newNodeB1:setPosition(posB.x - 10.0, posB.y - 15.0, posB.z + 10.0)
			newNodeB2:setPosition(posB.x + 10.0, posB.y + 15.0, posB.z - 10.0)
		end
	end
end

function nodeCollision2(event)
	io.write("NODE COLLISION CODE: ", event.code, "\n")
	nameA = event.collision.nodeA:getName()
	nameB = event.collision.nodeB:getName()
	io.write("EVENT NODEA NAME: ", nameA, " NODEB NAME: ", nameB, "\n")
end

fg.Scene3D:addEventCallback(fg.SCENE_NODE_COLLISION, nodeCollision, 2)
fg.Scene3D:addEventCallback(fg.SCENE_NODE_COLLISION, nodeCollision2, 1)
--fg.Scene3D:addEventCallback(fg.SCENE_NODE_TRIGGER_FIRED, gameStarted, 0)

fg.EventManager.addEventCallback(fg.EVENT_GAME_STARTED, gameStarted, 0)
fg.EventManager.addEventCallback(fg.EVENT_GAME_PAUSED, gamePaused, 0)
fg.EventManager.addEventCallback(fg.EVENT_GAME_STOPPED, gameStopped, 0)

playerFighter = nil
playerSecond = nil

repeatrepeats = 4
moverepeat = 50
direction = -10.0

function specialTriggerCB(nodeA, nodeB)
	nameA = nodeA:getName()
	nameB = nodeB:getName()
	io.write("SPECIAL TRIGGER BEGIN GAME XD NODEA NAME: ", nameA, " NODEB NAME: ", nameB, "\n")

	fg.SoundManager:play("shot.wav")

end

trigger = fg.Scene3D:addTriggerWithExtent("yoloxtrigger", 250.0, 20.0, 10.0, 50.0, 50.0, 25.0)
--ARGS: [1]SELF [2]ACTIVATION [3]TRIGGER_NAME [4]FUNCTION/SCRIPT [5] ARGC (optional)

fg.Scene3D:addTriggerCallback(fg.ON_COLLISION_BEGIN, "yoloxtrigger", specialTriggerCB, 2)

function cyclicSceneCallback()
	io.write("CYCLIC SCENE CALLBACK every 25ms \n")
	moverepeat = moverepeat - 1

	--cubeyolo1 = fg.Scene3D:get("cubeyolo1")
--	scal = cubeyolo1:getScale()
--	scal.x = scal.x + 0.1
--	scal.y = scal.y + 0.1
--	scal.z = scal.z + 0.1
--	cubeyolo1:setScale(scal.x, scal.y, scal.z)

	sceneNode = fg.Scene3D:get("PlayerBullshit")
	sceneNode:translate(direction,0.0,0.0)
	sceneNode:rotate(0.1, 0.5, 0.5, 0.5)

	trigger:translate(0.1,0.0,0.0)

	if(moverepeat == 0) then
		direction = direction * -1.0
		moverepeat = 50
		repeatrepeats = repeatrepeats - 1
		if repeatrepeats >= 0 then
			fg.EventManager.addCyclicCallback(cyclicSceneCallback, moverepeat, 50)
		end
	end

end

cubeIdx = 1
rockIdx = 1

function cyclicCallback()
	repeats = repeats - 1
	io.write("CYCLIC CALLBACK YOLO! every 1500ms: ", repeats, " more calls\n")

	cubename = "cubeyolo" .. cubeIdx
	rockname = "Rock" .. rockIdx
--	rockname = "builtinSphere"
	rockname = "builtinCube1x1"
	cubeIdx = cubeIdx + 1
	rockIdx = rockIdx + 1
	if rockIdx == 4 then
		rockIdx = 5
	end
	if rockIdx == 7 then
		rockIdx = 1
	end

	local newCube = nil

--	if rockIdx == 3 then
--		newCube = fg.Scene3D:addFromModel("CobraBomber", cubename)
--	else
--		newCube = fg.Scene3D:addFromModel(rockname, cubename)
--	end
--	newCube:setAutoScale(1)
--	if rockIdx == 3 then
--		newCube:activateCollisionBody(fg.BODY_BOX)
--	else
--		newCube:activateCollisionBody(fg.BODY_BOX)
--	end
--	newpos = 200.0 + 30.0*cubeIdx
--	newCube:setPosition(10.0, newpos, 10.0)
--	newCube:setVelocity(3,2,-3)
--	newCube:setRotation(0.06*cubeIdx, 0.07*cubeIdx, 0.1*cubeIdx)
--	newCube:setAcceleration(0.0, -10.0, 0.0)
----	newCube:setHalfSizeAndMass(6.0,6.0,5.0,20.0)
--	newCube:setScale(10,10,10)
--	if rockIdx == 3 then
--		newCube:setScale(1.2,1.2,1.2)
--	end
--	newCube:setRadius(10+rockIdx)
--	newCube:setMass(100.0)
--	newCube:update(0.0)

--	if(repeats == 1) then
---		--fg.Scene3D:destroyNode("PlayerBullshit")
--	end

	if(repeats == 3) then
		playerSecond = fg.Scene3D:addFromModel("CobraBomber", "PlayerBullshit")
		playerSecond:translate(100.0, 0.0, 0.0)
		playerFighter = fg.Scene3D:addFromModel("CobraBomber", "PlayerFighter")
		playerFighter:translate(-100.0, 105.0, 0.0)
		playerFighter:activateCollisionBody(fg.BODY_BOX)
		playerFighter:setVelocity(0.0, 0.0, 0.0)
		playerSecond:rotate(0.4, 0.3, 0.2, 0.8)
		fg.EventManager.addCyclicCallback(cyclicSceneCallback, moverepeat, 50)
--		fg.GameLogic:startGameDefault()
	end
	if(repeats == 2) then
		fg.GameLogic:pauseGame()
	--	playerFighter = fg.Scene3D:addFromModel("CobraBomber", "PlayerFighter")
		playerFighter:rotate(0.8, 0.3, 1.0, 0.5)
		--playerFighter:translate(150.0, 50.0, -150.0)
	end
	if(repeats == 1) then
		fg.GameLogic:stopGame()
		playerFighter:rotate(0.2, 0.0, 1.0, 0.0)
		playerFighter:setScale(1.2, 1.2, 1.2)
	end
end

function timeoutCallback()
	io.write("TIMEOUT CALLBACK TEST - 2500ms\n");
end

fg.EventManager.addTimeoutCallback(timeoutCallback, 2500)
fg.EventManager.addCyclicCallback(cyclicCallback, repeats, 1000)

function widgetClicked(widget)
	io.write("Widget clicked: ", widget:getName(), "\n")
--	scale = playerFighter:getScale()
end

function widgetActivated(widget)
	io.write("Widget activated: ", widget:getName(), "\n")
end

function widgetFocus(widget)
	io.write("Widget focused: ", widget:getName(), "\n")
end

--fg.GuiMain.addWidgetCallback("HighscoresButton", "onFocus", widgetFocus)
--fg.GuiMain.addWidgetCallback("HighscoresButton", "onClick", widgetClicked)
--fg.GuiMain.addWidgetCallback("HighscoresButton", fg.GUI_WIDGET_CALLBACK_ON_ACTIVATE, widgetActivated)
--fg.GuiMain.addWidgetCallback("Test2Button", "onClick", widgetClicked)


function lastLevelActivated(widget)
	local widgetName = widget:getName()
	io.write("Widget activated: ", widgetName, "\n")

	if(widgetName == "LastLevelButton") then
		fg.GameLogic:startGameDefault()
	end
end

fg.GuiMain.addWidgetCallback("LastLevelButton", "onActivate", lastLevelActivated)

--some_sound = fg.SoundManager:request("explode.wav")
--io.write("EXPLODE: NAME: '", some_sound:getName(), "' ...\n")
--some_sound:play()

print("End script main\n")
collectgarbage("collect")

