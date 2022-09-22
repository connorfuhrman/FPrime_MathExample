// ======================================================================
// \title  MathSender.hpp
// \author connorfuhrman
// \brief  hpp file for MathSender component implementation class
// ======================================================================

#ifndef MathSender_HPP
#define MathSender_HPP

#include "BasicTypes.hpp"
#include "MathOpsExampleDeployment/MathReceiver/MathReceiverComponentAc.hpp"
#include "MathOpsExampleDeployment/MathSender/MathSenderComponentAc.hpp"
#include "MathOpsExampleDeployment/MathTypes/MathOpEnumAc.hpp"

#include <iostream>

namespace MathOpsExample {

  class MathSender :
    public MathSenderComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object MathSender
      //!
      MathSender(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object MathSender
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object MathSender
      //!
    ~MathSender() = default;

    // Do the mathOpReqOut port invocation
    void do_mathOpReq(NATIVE_INT_TYPE portNum,
		      F32 lhs,
		      const MathOpsExample::MathOp& op,
		      F32 rhs)
    {
      mathOpReqOut_out(portNum, lhs, op, rhs);
    }

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for mathOpRespIn
      //!
      void mathOpRespIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 result /*!< 
      Result of the operation
      */
      );


    };

} // end namespace MathOpsExample

#endif
