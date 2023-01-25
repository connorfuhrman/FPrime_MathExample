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

void MathReceiver::init(const NATIVE_INT_TYPE queueDepth,
			const NATIVE_INT_TYPE instance)
{
  MathReceiverComponentBase::init(queueDepth, instance);

  std::cout << "Initializing MathReceiver Julia module..." << std::endl;
  const auto mod_name = fmt::format("MathReceiver_{}", instance);
  jluna::Main.safe_eval(fmt::format("module {} end", mod_name));
  jluna::Module jl_module = jluna::Main.safe_eval(fmt::format("return {}", mod_name));

  jl_module.create_or_assign("mathOpRespOut_out",
			     jluna::as_julia_function<void(MathResPort)> (
			       [this](MathResPort p) {
				 this->mathOpRespOut_out(p.portNum, p.result);
			       }));

  // Then the file can be evaluted
  jl_module.safe_eval_file("/home/connorfuhrman/projects/fprime.jl/FPrime_MathExample/MathOpsExampleDeployment/MathReceiver/MathReceiver.jl");

  // Precompile all handler functions
  jl_module.safe_eval(R"(
     precompile(mathOpReqIn_handler, (MathOpPort,))
     precompile(mathOpRespOut_out, (MathResPort,))
   )");
  
  mathOpReqIn_handler_proxy = jl_module["mathOpReqIn_handler"];
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void MathReceiver::mathOpReqIn_handler(const NATIVE_INT_TYPE portNum,
				       F32 lhs,
				       const MathOpsExample::MathOp &op,
				       F32 rhs)
{
  mathOpReqIn_handler_proxy(MathOpPort(portNum, lhs, op, rhs));
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
