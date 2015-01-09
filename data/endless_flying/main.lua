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
	fg.SoundManager:play("explode.wav")
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

fg.EventManager.addEventCallback(fg.EVENT_TOUCH_TAP_FINISHED, testCallback1, 1)
fg.EventManager.addEventCallback(fg.EVENT_TOUCH_TAP_FINISHED, "testCallback2()", 0)
fg.EventManager.addEventCallback(fg.EVENT_RESOURCE_CREATED, resourceCallback)

repeats = 4

function gameStarted()
	io.write(">> >> >> GAME STARTED\n");
end

function gamePaused()
	io.write(">> >> >> GAME PAUSED\n");
end

function gameStopped()
	io.write(">> >> >> GAME STOPPED\n");
end

fg.EventManager.addEventCallback(fg.EVENT_GAME_STARTED, gameStarted, 0)
fg.EventManager.addEventCallback(fg.EVENT_GAME_PAUSED, gamePaused, 0)
fg.EventManager.addEventCallback(fg.EVENT_GAME_STOPPED, gameStopped, 0)

function cyclicCallback()
	repeats = repeats - 1
	io.write("CYCLIC CALLBACK YOLO! every 1500ms: ", repeats, " more calls\n");

	if(repeats == 3) then
		fg.GameLogic:startGameDefault()
	end
	if(repeats == 2) then
		fg.GameLogic:pauseGame()
		fg.Scene3D:addFromModel("CobraBomber", "PlayerFighter")
	end
	if(repeats == 1) then
		fg.GameLogic:stopGame()
	end
end

function timeoutCallback()
	io.write("TIMEOUT CALLBACK TEST - 2500ms\n");
end

fg.EventManager.addTimeoutCallback(timeoutCallback, 2500)
fg.EventManager.addCyclicCallback(cyclicCallback, repeats, 1500)

function widgetClicked(widget)
	io.write("Widget clicked: ", widget:getName(), "\n")
end

function widgetActivated(widget)
	io.write("Widget activated: ", widget:getName(), "\n")
end

function widgetFocus(widget)
	io.write("Widget focused: ", widget:getName(), "\n")
end

fg.GuiMain.addWidgetCallback("HighscoresButton", "onFocus", widgetFocus)
fg.GuiMain.addWidgetCallback("HighscoresButton", "onClick", widgetClicked)
fg.GuiMain.addWidgetCallback("HighscoresButton", fg.GUI_WIDGET_CALLBACK_ON_ACTIVATE, widgetActivated)
fg.GuiMain.addWidgetCallback("Test2Button", "onClick", widgetClicked)

yolo1 = nil
vec2 = nil
sparksTexName = nil
sparks = nil

print("End script main\n")
collectgarbage("collect")

