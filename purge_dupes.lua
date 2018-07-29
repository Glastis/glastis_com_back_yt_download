local args = {...}

function file_exists(file)
    local f

    f = io.open(file, "rb")
    if f then
        f:close()
    end
    return f ~= nil
end

function is_in_list(list, elem)
    local i

    i = 1
    while list and list[i] do
        if list[i] == elem then
            return true
        end
        i = i + 1
    end
    return false
end

function main(filename)
    local lines
    local i

    if not file_exists(filename) then
        return false
    end
    lines = {}
    i = 1
    for line in io.lines(filename) do
        if not is_in_list(lines, line) then
            lines[#lines + 1] = line
        end
    end
    os.remove(filename)
    io.output(filename)
    while lines and lines[i] do
        io.write(lines[i] .. '\n')
        i = i + 1
    end
end

if not args[1] then
    print('Provide file')
else
    main(args[1])
end