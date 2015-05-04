----------------------------------
-- Main script for endless flying
--

fg.GameLogic:stopGame()

playerSecond = fg.Scene3D:addFromModel("CobraBomber", "PlayerBullshit")
playerSecond:translate(100.0, 0.0, 0.0)

playerSecond = fg.Scene3D:addFromModel("CobraBomber", "PlayerYolanta")
playerSecond:translate(-50.0, 20.0, 50.0)


fg.Scene3D:setPickSelectionOnClick(fg.TRUE)
--fg.Scene3D:setPickSelectionOnHover(fg.TRUE)
fg.Scene3D:setPickSelectionGroup(fg.TRUE)
fg.Scene3D:setPickSelectionToggle(fg.TRUE)
fg.Scene3D:setPickSelectionBox(fg.TRUE)

fg.Scene3D:setPickSelectionAABBTriangles(fg.TRUE)
--fg.Scene3D:setHideNodes(FG_TRUE)

collectgarbage("collect")
