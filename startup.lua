
-- This is the main startup code
--
-- $Id: startup.lua,v 1.2 2003-08-07 01:26:19 bernard Exp $

copyright = "Sword of Cydonia (c) Bernard Schmitz 2003";

-- example lua function
function fac(x)
   if x == 0 then
      return 1
   else
      return x * fac(x-1)
   end
end

-- show the copyright notice in the console
print(copyright)

