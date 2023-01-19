# abstract type MathOp end

# struct ADD <: MathOp end
# struct SUB <: MathOp end
# struct MUL <: MathOp end
# struct DIV <: MathOp end



function mathOpReqIn_handler(op::Main.MathOpsExample_MathOp)
    mathOpRespOut_out(0, op.lhs + op.rhs)
end


# precompile(mathOpReqIn_handler, (MathOpsExample_MathOp,))


# // in namespace scope
# struct RGBA
# {
#     float _red;
#     float _green;
#     float _blue;
#     float _alpha;
    
#     RGBA(float r, float g, float b)
#         : _red(r), _green(g), _blue(b), _alpha(1)
#     {}
    
#     RGBA() 
#         : _red(0), _green(0), _blue(0), _alpha(1)
#     {}
# };
# set_usertype_enabled(RGBA);
