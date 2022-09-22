module MathOpsExample {

   topology MathOpsExample {

      # --------------------------------------------------
      # Instances used in this topology
      # --------------------------------------------------

      instance blockDrv
      instance rateGroupComp
      instance rateGroupDriverComp

      instance mathSender
      instance mathReceiver

      connections RateGroups {
         blockDrv.CycleOut -> rateGroupDriverComp.CycleIn
         rateGroupDriverComp.CycleOut[0] -> rateGroupComp.CycleIn
         rateGroupComp.RateGroupMemberOut[0] -> mathReceiver.schedIn
      }

      connections Math {
         mathSender.mathOpReqOut -> mathReceiver.mathOpReqIn
         mathReceiver.mathOpRespOut -> mathSender.mathOpRespIn
      }
   }

}