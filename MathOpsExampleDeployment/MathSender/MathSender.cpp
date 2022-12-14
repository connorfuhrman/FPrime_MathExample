// ======================================================================
// \title  MathSender.cpp
// \author connorfuhrman
// \brief  cpp file for MathSender component implementation class
// ======================================================================


#include <MathOpsExampleDeployment/MathSender/MathSender.hpp>
#include "Fw/Types/BasicTypes.hpp"

#include <fmt/core.h>

namespace MathOpsExample {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  MathSender ::
    MathSender(
        const char *const compName
    ) : MathSenderComponentBase(compName)
  {
    std::cout << "MathSender constructed!!" << "\n";
  }

  void MathSender ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    MathSenderComponentBase::init(queueDepth, instance);
  }


  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void MathSender ::
    mathOpRespIn_handler(
        const NATIVE_INT_TYPE portNum,
        F32 result
    )
  {
    fmt::print("Got math result {}\n", result);
  }

} // end namespace MathOpsExample
