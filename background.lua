current_color_index = 1

colors = {}
colors[1] = {0,0,0}
colors[2] = {255,0,0}
colors[3] = {0,255,0}
colors[4] = {0,0,255}
colors[5] = {255,255,255}

function tablelength(T)
  local count = 0
  for _ in pairs(T) do count = count + 1 end
  return count
end

function getElementByIndex(T, i)
    local count = 0
    for e in pairs(T) do
        if count == i then return e end
        count = count + 1
    end
    
    return nil
end

function handle_input (input)  
    print('[LUA] handling input')
    
    if input == 1 then
        local tcolor = colors[current_color_index]
        print('[LUA] detected mouse click')
        print('[LUA] changing bg color')
        
        setBGColor(tcolor[1], tcolor[2], tcolor[3])
        current_color_index = current_color_index + 1
        if current_color_index > tablelength(colors) then current_color_index = 1 end
    end
    
    return 0
 end