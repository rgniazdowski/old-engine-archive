print("STARTING SCRIPT CHAIN REACTION MAIN\n")

testmenu = WidgetManager:getWidget("TestMenu")

-- #FIXME - this will need fixing, now it's needed to add widget callbacks
-- separately, however it should be possible to add one global callback/event

function widgetMenuActivated(widget)
	local widgetName = widget:getName()
	io.write("Widget activated: ", widgetName, "\n")

	local start_cnt = WidgetManager:getWidget("StartGameContainer");
	local high_cnt = WidgetManager:getWidget("HighscoresContainer");
	local stats_cnt = WidgetManager:getWidget("StatsContainer");

	if(widgetName == "XXStartGameButton") then
		start_cnt:setVisible(1)
		high_cnt:setVisible(0)
		stats_cnt:setVisible(0)
	elseif(widgetName == "XXHighscoresButton") then
		start_cnt:setVisible(0)
		high_cnt:setVisible(1)
		stats_cnt:setVisible(0)

	elseif(widgetName == "XXStatsButton") then
		start_cnt:setVisible(0)
		high_cnt:setVisible(0)
		stats_cnt:setVisible(1)

	elseif(widgetName == "XXOptionsButton") then
		start_cnt:setVisible(0)
		high_cnt:setVisible(0)
		stats_cnt:setVisible(0)
	end
end


GuiMain.addWidgetCallback("XXStartGameButton", "onActivate", widgetMenuActivated)
GuiMain.addWidgetCallback("XXHighscoresButton", "onActivate", widgetMenuActivated)
GuiMain.addWidgetCallback("XXStatsButton", "onActivate", widgetMenuActivated)
GuiMain.addWidgetCallback("XXOptionsButton", "onActivate", widgetMenuActivated)

