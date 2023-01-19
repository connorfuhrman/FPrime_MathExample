// ======================================================================
// \title  MathReceiver.cpp
// \author connorfuhrman
// \brief  cpp file for MathReceiver component implementation class
// ======================================================================

#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"

#include "MathOpsExampleDeployment/MathTypes/MathOpEnumAc.hpp"
#include <MathOpsExampleDeployment/MathReceiver/MathReceiver.hpp>

#include <iostream>

#include <jluna.hpp>
#include <fmt/core.h>

#include <MathPorts_jl.hpp>

namespace MathOpsExample {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

MathReceiver::MathReceiver(const char *const compName)
    : MathReceiverComponentBase(compName)
{  
  std::cout << "MathReceiver constructed!" << "\n";

}

void MathReceiver ::init(const NATIVE_INT_TYPE queueDepth,
                         const NATIVE_INT_TYPE instance)
{
  MathReceiverComponentBase::init(queueDepth, instance);

  std::cout << "Initializing MathReceiver Julia module..." << std::endl;
  jluna::Main.safe_eval("module MathReceiver end");
  jluna::Module jl_module = jluna::Main.safe_eval("return MathReceiver");

  

  // Define all variables which are used in the component's
  // Julia impl file first
  jl_module.create_or_assign("mathOpRespOut_out",
			     jluna::as_julia_function<void(int, F32)>(
			       [this](int portNum, F32 res) {
				 this->mathOpRespOut_out(portNum, res);
			       }));
    
  // Then the file can be evaluted
  jl_module.safe_eval_file("/home/connorfuhrman/projects/fprime.jl/FPrime_MathExample/MathOpsExampleDeployment/MathReceiver/MathReceiver.jl");
  mathOpReqIn_handler_proxy = jl_module["mathOpReqIn_handler"];
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void MathReceiver::mathOpReqIn_handler(const NATIVE_INT_TYPE portNum,
					F32 lhs,
                                        [[maybe_unused]] const MathOpsExample::MathOp &op,
                                        F32 rhs)
{
  mathOpReqIn_handler_proxy(MathOpsExample_MathOp(portNum, lhs, op, rhs));
}

void MathReceiver::schedIn_handler(const NATIVE_INT_TYPE portNum,
                                    NATIVE_UINT_TYPE context)
{
  // Flush the entire queue of messages
  while(m_queue.getNumMsgs() > 0)
  {
    FW_ASSERT(doDispatch() == MsgDispatchStatus::MSG_DISPATCH_OK);
  }
}

} // end namespace MathOpsExample
