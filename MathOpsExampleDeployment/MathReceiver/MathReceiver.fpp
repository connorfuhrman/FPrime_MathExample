module MathOpsExample {
   @ Component for performing a math opeartion
   queued component MathReceiver {
      # --------------------------------------------------
      # Ports 
      # --------------------------------------------------

      @ Port for receing the MathOp request
      async input port mathOpReqIn: MathOp

      @ Port for returning the MathOp result
      output port mathOpRespOut: MathRes

      @ Rate scheduler input
      sync input port schedIn: Svc.Sched
   }
}