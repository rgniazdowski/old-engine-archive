io.write("STARTING SCRIPT CHAIN REACTION MAIN\n")

testmenu = fg.WidgetManager:getWidget("TestMenu")

-- #FIXME - this will need fixing, now it's needed to add widget callbacks
-- separately, however it should be possible to add one global callback/event

function widgetMenuActivated(widget)
	local widgetName = widget:getName()
	io.write("Widget activated: ", widgetName, "\n")

	local start_cnt = fg.WidgetManager:getWidget("StartGameContainer");
	local high_cnt = fg.WidgetManager:getWidget("HighscoresContainer");
	local stats_cnt = fg.WidgetManager:getWidget("StatsContainer");

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


fg.GuiMain.addWidgetCallback("XXStartGameButton", "onActivate", widgetMenuActivated)
fg.GuiMain.addWidgetCallback("XXHighscoresButton", "onActivate", widgetMenuActivated)
fg.GuiMain.addWidgetCallback("XXStatsButton", "onActivate", widgetMenuActivated)
fg.GuiMain.addWidgetCallback("XXOptionsButton", "onActivate", widgetMenuActivated)

