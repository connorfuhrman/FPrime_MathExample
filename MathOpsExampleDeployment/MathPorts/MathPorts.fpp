module MathOpsExample {
   @ Port to request a math operation
   port MathOp (
      lhs: F32 @< Left-hand-side of the operation
      op: MathOp @< Operand
      rhs: F32 @< Right-hand-side of the operation
   )

   @ Port to serve the response of the math operation
   port MathRes(
      result: F32 @< Result of the operation
   )
}