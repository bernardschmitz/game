
-- This is the main startup code
--
-- $Id: startup.lua,v 1.13 2003-08-29 00:00:06 bernard Exp $

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


-- add some enemies
--rand_enemy(2)

--enemy_grid(0.0, -15.0, 20, 10, 2.1)         
--enemy_grid(0.0, -15.0, 40, 10, 2.1)         

function help()
   print("")
   print("for more enemies call enemy_grid(x, y, w, h, s)")
   print("where x,y is the middle of the grid,")
   print("w,h is the width and height of the grid and")
   print("s is the distance between each enemy in both directions.")
   print("eg: enemy_grid(0.0, -15.0, 20, 10, 2.5)")
   print("")
   print("jelly_fish(x,y,r,g,b,tail) where x,y is the position,")
   print("r,g,b is the color and tail is the length of the tail")
   print("eg: jelly_fish(-5, -5, 0, 0, 0, 5)")
   print("")
end

--Enemy(5,5)

--enemy_grid(0.0, -25.0, 40, 20, 2.1)
--enemy_grid(0.0, -25.0, 20, 5, 2.1)


--jelly_fish(-20,0, 0.8,0,0, 10)
--jelly_fish(20,0, 0,0.8,0, 10)
--jelly_fish(0,20,0,0,0.8, 10)
--jelly_fish(0,-20, 0.8,0.8,0, 10)

enemy_grid(-50, 0, 10, 10, 2.1)

print(copyright)
help()

