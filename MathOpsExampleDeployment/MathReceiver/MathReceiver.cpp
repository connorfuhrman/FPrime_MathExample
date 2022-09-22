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
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void MathReceiver::mathOpReqIn_handler(const NATIVE_INT_TYPE portNum,
					F32 lhs,
                                        const MathOpsExample::MathOp &op,
                                        F32 rhs)
{
  F32 result = 0.0;
  // Perform the requested operation
  switch (op.e) {
  case MathOp::ADD: result = lhs + rhs; break;
  case MathOp::SUB: result = lhs - rhs; break;
  case MathOp::MUL: result = lhs * rhs; break;
  case MathOp::DIV: result = lhs / rhs; break;
  default:
    FW_ASSERT(false, op.e);  
  }
  // Send the result over the output port
  mathOpRespOut_out(0, result);
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
