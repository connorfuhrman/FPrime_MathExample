module MathOpsExample {
   @ Component for sending a math operation
   active component MathSender {
      # --------------------------------------------------
      # Ports
      # --------------------------------------------------

      @ Port for sending the math operation request
      output port mathOpReqOut: MathOp

      @ Port for receivng the math operaion result
      async input port mathOpRespIn: MathRes
      
   }
}