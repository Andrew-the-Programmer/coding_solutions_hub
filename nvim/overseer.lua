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

local function Execute(cmd)
    local opts = {
        ask_input = false,
        go_back = false,
        error = false,
    }
    execute_cmd(cmd, opts)
end

local src_dir = "./other/"

local function configure_build()
    local cmd = src_dir .. "cpp/configure_build.*"
    Execute(cmd)
end
function Run()
    local cmd = src_dir .. "cpp/run.*"
    Execute(cmd)
end

local function configure_debug()
    local cmd = src_dir .. "cpp/configure_debug.*"
    Execute(cmd)
end
function Debug()
    local cmd = src_dir .. "cpp/debug.*"
    Execute(cmd)
end

function Test()
    local cmd = src_dir .. "test.*"
    Execute(cmd)
end

function CmakeSDir()
    local dir = Dir()
    while vim.fn.filereadable(dir .. "/CMakeLists.txt") ~= 1 do
        dir = vim.fn.fnamemodify(dir, ":h")
    end
    return dir
end

function CdToCmakeDir()
    Execute("cd " .. CmakeSDir())
end

overseer.register_template({
    name = "g++ - build",
    builder = function()
        CdToCmakeDir()
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
        CdToCmakeDir()
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
    name = "g++ - run",
    builder = function()
        CdToCmakeDir()
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
        CdToCmakeDir()
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
        CdToCmakeDir()
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
        local filebasename = Filebasename()
        local execfile = outdir .. "/" .. filebasename
        local file = File()

        local args = {
            "g++",
            "-std=c++20",
            "-I/usr/local/include",
            "-L/usr/local/lib",
            "-lboost_system",
            "-lboost_coroutine",
            "-lboost_context",
            "-o " .. execfile,
            file,
        }
        local cmd = ""

        for _, v in pairs(args) do
            cmd = cmd .. " " .. v
        end

        Execute("mkdir -p " .. outdir)
        Execute(cmd)
        Execute(execfile)

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
