local overseer = require("overseer")

---@type TermExecute
local term = My.term.TermExecute:new()

local src_dir = vim.fn.getcwd() .. "/api/"
local test_dir = src_dir .. "test/"
local add_test_exe = test_dir .. "add_test.py"
local test_exe = test_dir .. "test.py"
local cpp_dir = src_dir .. "cpp/"
local run_exe = cpp_dir .. "run.py"

local function SolutionDir()
    return My.nvim.Dir()
end

function CmakeSDir()
    local dir = My.nvim.Dir()
    while vim.fn.filereadable(dir .. "/CMakeLists.txt") ~= 1 do
        dir = vim.fn.fnamemodify(dir, ":h")
    end
    return dir
end

function CdToCmakeDir()
    term:ChangeDir(CmakeSDir())
end

overseer.register_template({
    name = "c++ - run",
    builder = function()
        local solution_dir = SolutionDir()
        local run = {
            run_exe,
            solution_dir,
        }
        CdToCmakeDir()
        local opts = My.term.SendConfig:new()
        opts.check_error = true
        term:Send(run)
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
        local solution_dir = SolutionDir()
        local build = {
            build_exe,
            solution_dir,
        }
        local test = {
            test_exe,
            solution_dir,
        }
        CdToCmakeDir()
        local opts = My.term.SendConfig:new()
        opts.check_error = true
        term:Send(build)
        term:Send(test)
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
        }
        CdToCmakeDir()
        local opts = My.term.SendConfig:new()
        opts.check_error = true
        term:Send(add_test)
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
