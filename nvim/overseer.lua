local overseer = require("overseer")

---@type TermExecute
local term = My.term.TermExecute:new()

local api_dir = vim.fn.getcwd() .. "/api/"
local src_dir = api_dir
local test_dir = api_dir
local add_test_exe = test_dir .. "add_test.py"
local test_exe = test_dir .. "test.py"
local run_exe = src_dir .. "run.py"
local run_only_exe = src_dir .. "run_only.py"
local build_exe = src_dir .. "build.py"

local function SolutionDir()
    return My.nvim.Dir()
end

overseer.register_template({
    name = "c++ - run",
    builder = function()
        local file = My.nvim.File()
        local build = {
            build_exe,
            file,
        }
        local run = {
            run_only_exe,
            file,
        }
        local opts = My.term.SendConfig:new()
        opts.check_error = false
        term:Send(build, opts)
        opts.check_error = true
        term:Send(run, opts)
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
    name = "test",
    builder = function()
        local test = {
            test_exe,
            My.nvim.File(),
        }
        local opts = My.term.SendConfig:new()
        opts.check_error = false
        term:Send(test, opts)
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
    name = "add test",
    builder = function()
        local add_test = {
            add_test_exe,
            My.nvim.File(),
        }
        local opts = My.term.SendConfig:new()
        opts.check_error = false
        term:Send(add_test, opts)
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
