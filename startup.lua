
-- This is the main startup code
--
-- $Id: startup.lua,v 1.10 2003-08-26 22:17:28 bernard Exp $

copyright = "Sword of Cydonia (c) Bernard Schmitz 2003";

-- function to add n enemies in random positions
function rand_enemy(n) 
   for i=1,n do
      x = 10.0-math.random()*20.0
      y = 10.0-math.random()*20.0
      Enemy(x, y)
      print("adding enemy at ",x,",",y)
   end
end



function enemy_grid(x, y, w, h, s)
   yy = y - s*h/2.0
   for i=1, h do
      xx = x - s*w/2.0
      for j=1, w do
         Enemy(xx, yy)
         xx = xx + s
      end
      yy = yy + s
   end
end


-- show the copyright notice in the console
print(copyright)


-- add some enemies
--rand_enemy(2)

--enemy_grid(0.0, -15.0, 20, 10, 2.1)         
--enemy_grid(0.0, -15.0, 40, 10, 2.1)         

print("")
print("for more enemies call enemy_grid(x, y, w, h, s)")
print("where x,y is the middle of the grid,")
print("w,h is the width and height of the grid and")
print("s is the distance between each enemy in both directions.")
print("eg: enemy_grid(0.0, -15.0, 20, 10, 2.5)")
print("")

--Enemy(5,5)

enemy_grid(0.0, -25.0, 30, 20, 2.1)         

