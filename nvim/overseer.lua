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

vim.keymap.set("n", "<leader>cr", "<cmd>OverseerRun<cr>", { desc = "Overseer Run" })

overseer.register_template({
    name = "g++ build - normal",
    builder = function()
        local outdirname = "out"
        local outdir = Dir() .. "/" .. outdirname
        print(outdir)
        local filebasename = vim.fn.fnamemodify(File(), ":t:r")
        print(filebasename)
        local targetfile = outdir .. "/" .. filebasename

        vim.cmd("silent !mkdir -p " .. outdir)

        return {
            cmd = { "g++" },
            args = { File(), "-o", targetfile },
            components = { { "on_output_quickfix", open = true }, "default" },
        }
    end,
    condition = {
        filetype = { "cpp" },
        dir = vim.fn.getcwd(),
    },
})
