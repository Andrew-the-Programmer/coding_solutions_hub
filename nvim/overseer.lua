-- nvim/overseer/cpp_build.lua

-- print("Loading nvim/overseer/cpp_build.lua")

local overseer = require("overseer")

function Dir()
    local dir = vim.fn.expand("%:p:h")
    return dir
end

function File()
    local file = vim.fn.expand("%:p")
    return file
end

local function Filebasename()
    return vim.fn.fnamemodify(File(), ":t:r")
end

local execute_cmd = My.toggleterm.execute.execute_cmd
local term_execute = My.toggleterm.execute.term_execute

-- execute_cmd("ls")

function Configure()
    local cmd = "./other/configure.sh"
    execute_cmd(cmd)
end

function Build()
    local cmd = "./other/build.sh"
    execute_cmd(cmd)
end

function Run()
    local cmd = "./other/run.sh"
    execute_cmd(cmd)
end

function Test()
    local cmd = "./other/test.sh"
    execute_cmd(cmd)
end

function CmakeSDir()
    local dir = Dir()
    while vim.fn.filereadable(dir .. "/CMakeLists.txt") ~= 1 do
        dir = vim.fn.fnamemodify(dir, ":h")
    end
    return dir
end

function CdToCmakeSDir()
    execute_cmd("cd " .. CmakeSDir())
end

function BuildDone()
    CdToCmakeSDir()
    Configure()
    Build()
end

overseer.register_template({
    name = "g++ - build",
    builder = function()
        BuildDone()
        return {
            name = "Done",
            cmd = { "echo" },
            args = { "Done" },
        }
    end,
    condition = {
        filetype = { "cpp" },
        dir = vim.fn.getcwd(),
    },
})

overseer.register_template({
    name = "g++ - run",
    builder = function()
        BuildDone()
        Run()
        return {
            name = "Done",
            cmd = { "echo" },
            args = { "Done" },
        }
    end,
    condition = {
        filetype = { "cpp" },
        dir = vim.fn.getcwd(),
    },
})

overseer.register_template({
    name = "g++ - test",
    builder = function()
        BuildDone()
        Test()
        return {
            name = "Done",
            cmd = { "echo" },
            args = { "Done" },
        }
    end,
    condition = {
        filetype = { "cpp" },
        dir = vim.fn.getcwd(),
    },
})

overseer.register_template({
    name = "g++ - normal",
    builder = function()
        local outdirname = "out"
        local outdir = Dir() .. "/" .. outdirname
        print(outdir)
        local filebasename = vim.fn.fnamemodify(File(), ":t:r")
        print(filebasename)
        local targetfile = outdir .. "/" .. filebasename

        vim.cmd("silent !mkdir -p " .. outdir)

        return {
            name = "g++",
            cmd = { "g++" },
            args = { File(), "-o", targetfile, "-std=c++20" },
            components = { { "on_output_quickfix", open = true }, "default" },
        }
    end,
    condition = {
        filetype = { "cpp" },
        dir = vim.fn.getcwd(),
    },
})
