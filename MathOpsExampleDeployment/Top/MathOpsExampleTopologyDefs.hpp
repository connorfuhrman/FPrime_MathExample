#ifndef MathOpsExampleTopologyDefs_HPP
#define MathOpsExampleTopologyDefs_HPP

#include "Fw/Types/MallocAllocator.hpp"

namespace MathOpsExample {
  namespace Alloction {
    extern Fw::MallocAllocator mallocator;
  }

  struct TopologyState {
    TopologyState() = default;
  };
}

#endif
