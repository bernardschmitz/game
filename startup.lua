
-- This is the main startup code
--
-- $Id: startup.lua,v 1.1 2003-08-06 23:45:22 bernard Exp $

copyright = "Sword of Cydonia (c) Bernard Schmitz 2003";

-- example lua function
function fac(x)
   if x == 0 then
      return 1
   else
      return x * fax(x-1)
   end
end

-- show the copyright notice in the console
print(copyright)

