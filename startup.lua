
-- This is the main startup code
--
-- $Id: startup.lua,v 1.4 2003-08-15 20:38:13 bernard Exp $

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


-- show the copyright notice in the console
print(copyright)


-- add some enemies
rand_enemy(2)

