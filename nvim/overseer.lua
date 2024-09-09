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

local src_dir = "./other/"

local function configure_build()
    local cmd = src_dir .. "cpp/configure_build.*"
    execute_cmd(cmd)
end
function Run()
    local cmd = src_dir .. "cpp/run.*"
    execute_cmd(cmd)
end

local function configure_debug()
    local cmd = src_dir .. "cpp/configure_debug.*"
    execute_cmd(cmd)
end
function Debug()
    local cmd = src_dir .. "cpp/debug.*"
    execute_cmd(cmd)
end

function Test()
    local cmd = src_dir .. "test.*"
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

function SetUp()
    CdToCmakeSDir()
end

overseer.register_template({
    name = "g++ - build",
    builder = function()
        SetUp()
        configure_build()
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
        SetUp()
        configure_build()
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
        SetUp()
        configure_build()
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
    name = "c++ - debug",
    builder = function()
        SetUp()
        configure_debug()
        Debug()
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
