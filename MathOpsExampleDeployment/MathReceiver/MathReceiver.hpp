// ======================================================================
// \title  MathReceiver.hpp
// \author connorfuhrman
// \brief  hpp file for MathReceiver component implementation class
// ======================================================================

#ifndef MathReceiver_HPP
#define MathReceiver_HPP

#include "MathOpsExampleDeployment/MathReceiver/MathReceiverComponentAc.hpp"

#include <jluna.hpp>

namespace MathOpsExample {

class MathReceiver : public MathReceiverComponentBase {

public:
  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  //! Construct object MathReceiver
  //!
  MathReceiver(const char *const compName /*!< The component name*/
  );

  //! Initialize object MathReceiver
  //!
  void init(const NATIVE_INT_TYPE queueDepth,  /*!< The queue depth*/
            const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
  );

  //! Destroy object MathReceiver
  //!
  ~MathReceiver() = default;

PRIVATE:

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  //! Handler implementation for mathOpReqIn
  //!
  void
  mathOpReqIn_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
		      F32 lhs, /*!< Left-hand-side of the operation */
		      const MathOpsExample::MathOp &op, /*!< Operand */
		      F32 rhs /*!< Right-hand-side of the operation */
    );

  //! Handler implementation for schedIn
  //!
  void schedIn_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                       NATIVE_UINT_TYPE context       /*!< The call order */
  );

  // proxies for dispatch to Julia
  jluna::Proxy mathOpReqIn_handler_proxy;
};

} // end namespace MathOpsExample

#endif
