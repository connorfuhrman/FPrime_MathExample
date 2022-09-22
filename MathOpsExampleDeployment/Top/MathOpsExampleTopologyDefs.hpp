#ifndef MathOpsExampleTopologyDefs_HPP
#define MathOpsExampleTopologyDefs_HPP

#include "Fw/Types/MallocAllocator.hpp"

namespace MathOpsExample {
  namespace Alloction {
    extern Fw::MallocAllocator mallocator;
  }

  struct TopologyState {
    TopologyState() : TopologyState("", 0)
    {
      
    }

    TopologyState(const char* _hostname, U32 _portNumber) :
      hostName(_hostname), portNumber(_portNumber)
    {

    }

    const char* hostName;
    U32 portNumber;
  };
}

#endif
