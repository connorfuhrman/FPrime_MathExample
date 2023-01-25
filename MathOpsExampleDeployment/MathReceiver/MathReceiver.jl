
module ThreadsafeUtils

#= ThreadSafeUtils: thread-safe utility functions.

This module provides various thread-safe functions for use within
a F' component and/or topology. 
=#

export println

using Base.Threads: SpinLock

const printlock = SpinLock()

"""
    println(str...)

Threadsafe println function. Locks a `SpinLock` before calling
Core.println(str...).
"""
function println(str::String)
    lock(printlock) do
        Core.println(str)
    end
end


end

# Type defined in jluna's Main module
using Main: MathOpPort, MathResPort

function mathOpReqIn_handler(arg::MathOpPort)
    # ThreadsafeUtils.println("typeof(op) = $(typeof(op))")

    dispatch_op = Dict(0 => +, 1 => -, 2 => *, 3 => /)
    f = dispatch_op[arg.op]
    
    mathOpRespOut_out(MathResPort(Int32(0), f(arg.lhs, arg.rhs)))
end
