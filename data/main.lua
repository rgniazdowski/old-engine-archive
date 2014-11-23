print("Stating main script FG\n")

texture1 = ResourceManager.request("MainBackgroundTexture")

name = texture1:getName()
path = texture1:getFilePath()

io.write("name of the texture: ", name, "\n")
io.write("path to the texture: ", path, "\n")
texture1 = nil

sparks = ResourceManager.request("ExplosionSparks")
loadedFont = ResourceManager.request("Loaded")

loadedFontRef = loadedFont

sparksTexName = sparks:getTextureName()
sparks:setFacingVelocity(1)
vec2 = Vector2f()
vec2.x = 10.0
vec2.y = 15.0
yolo1 = vec2
sparks:setLifeRange(yolo1)

ssize = sparks:getStartSize()
ssize.x = 300.0
ssize.y = 300.0
ssize.z = 300.0

sparks:getStartSize().x = 100.0
sparks:getStartSize().y = 100.0

debris = ResourceManager.request("ExplosionDebris")

vec3 = Vector3f()
vec3.x = 300.0
vec3.y = 300.0
vec3.z = 300.0

vec2.x = 15.0
vec2.y = 20.0

debris:setFacingVelocity(1)
debris:setSpreadSpeed(vec3)
debris:setLifeRange(vec2)
debris:setEndColor4i(255,50,0,0)

button1 = Button()
button1:setName("YOLANTA1")
button1:getPosition().x = 200
button1:getPosition().y = 400
button1:setText("SKRYPT LUA POZDRAWIA")
button1:setStyleName("RelButton")

mainmenu = WidgetManager:getWidget("MainMenu")
mainmenu:addChild(button1)
WidgetManager:addWidgetWithFather(button1, mainmenu)
b1name = button1:getName()
io.write("Button 1 new name: ", b1name, "\n")

stylenone = button1:getStyleContent(FG_GUI_WIDGET_STATE_NONE)
backgroundstyle = stylenone:getBackground()
backgroundstyle.color.r = 0.5
backgroundstyle.color.g = 0.5
backgroundstyle.color.b = 0.0
backgroundstyle.color.a = 1.0
button1:setVisible(0)

mainmenu:getStyleContent(FG_GUI_WIDGET_STATE_NONE):getBackground().color.r = 1.0

backgroundstyle2 = stylenone:getBackground()
stylenone:getForeground().color.z = 1.0

function testCallback1(event)
--	io.write("TEST CALLBACK FOR TAP EVENT: LUA! \n")
	if(event.eventType == FG_EVENT_TOUCH_TAP_FINISHED) then
		io.write("LUA TOUCH: X: ", event.touch.x, " Y: ", event.touch.y, "\n")
	end
	SoundManager:play("explode.wav")
--	SoundManager:play("mod.shamrip.mod")
	local mus = "mod.dragonsfunk.mp3"
	if(SoundManager:isPlaying(mus) == 0) then
--		SoundManager:play(mus)
	end
end

function resourceCallback(event)
	if(event.eventType == FG_EVENT_RESOURCE_CREATED) then
		io.write("LUA RESOURCE: NAME: ", event.resource.resource:getName(), "\n")
	end
end

function testCallback2()
	io.write("TESTING SECOND CALLBACK: SCRIPT TYPE! No args\n")
end

EventManager.addEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, testCallback1, 1)
EventManager.addEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, "testCallback2()", 0)
EventManager.addEventCallback(FG_EVENT_RESOURCE_CREATED, resourceCallback)

repeats = 3

function cyclicCallback()
	repeats = repeats - 1
	io.write("CYCLIC CALLBACK YOLO! every 1500ms: ", repeats, " more calls\n");
end

function timeoutCallback()
	io.write("TIMEOUT CALLBACK TEST - 2500ms\n");
end

EventManager.addTimeoutCallback(timeoutCallback, 2500)
EventManager.addCyclicCallback(cyclicCallback, repeats, 1500)

function widgetClicked(widget)
	io.write("Widget clicked: ", widget:getName(), "\n")
end

function widgetActivated(widget)
	io.write("Widget activated: ", widget:getName(), "\n")
end

function widgetFocus(widget)
	io.write("Widget focused: ", widget:getName(), "\n")
end

GuiMain.addWidgetCallback("HighscoresButton", "onFocus", widgetFocus)
GuiMain.addWidgetCallback("HighscoresButton", "onClick", widgetClicked)
GuiMain.addWidgetCallback("HighscoresButton", FG_GUI_WIDGET_CALLBACK_ON_ACTIVATE, widgetActivated)
GuiMain.addWidgetCallback("Test2Button", "onClick", widgetClicked)

yolo1 = nil
vec2 = nil
sparksTexName = nil
sparks = nil

print("End script main\n")
collectgarbage("collect")

