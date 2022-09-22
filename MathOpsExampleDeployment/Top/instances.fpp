module MathOpsExample {

   # --------------------------------------------------
   # Default values
   # --------------------------------------------------
   module Default {
      constant queueSize = 10
      constant stackSize = 64 * 1024
   }

   # --------------------------------------------------
   # Active Components:
   # --------------------------------------------------

   instance blockDrv: Drv.BlockDriver base id 0x0100 \
      queue size Default.queueSize \
      stack size Default.stackSize \
      priority 140

   instance mathSender: MathSender base id 0x0200 \
      queue size Default.queueSize \
      stack size Default.stackSize \
      priority 100

   instance rateGroupComp: Svc.ActiveRateGroup base id 0x0300 \
    queue size Default.queueSize \
    stack size Default.stackSize \
    priority 120 \
  {

    phase Fpp.ToCpp.Phases.configObjects """
    NATIVE_INT_TYPE context[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    """

    phase Fpp.ToCpp.Phases.configComponents """
    rateGroupComp.configure(
        ConfigObjects::rateGroupComp::context,
        FW_NUM_ARRAY_ELEMENTS(ConfigObjects::rateGroupComp::context)
    );
    """
  }

   # --------------------------------------------------
   # Queued Components:
   # --------------------------------------------------

   instance mathReceiver: MathReceiver base id 0x0400 \
      queue size Default.queueSize

   # --------------------------------------------------
   # Passive Components:
   # --------------------------------------------------
   instance rateGroupDriverComp: Svc.RateGroupDriver base id 0x4600 {

    phase Fpp.ToCpp.Phases.configObjects """
    NATIVE_INT_TYPE rgDivs[Svc::RateGroupDriver::DIVIDER_SIZE] = { 1, 2, 4 };
    """
    
    phase Fpp.ToCpp.Phases.configComponents """
    rateGroupDriverComp.configure(
        ConfigObjects::rateGroupDriverComp::rgDivs,
        FW_NUM_ARRAY_ELEMENTS(ConfigObjects::rateGroupDriverComp::rgDivs)
    );
    """

  }
}