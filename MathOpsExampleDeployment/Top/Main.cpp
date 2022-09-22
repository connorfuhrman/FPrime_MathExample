#include "MathOpsExampleDeployment/MathTypes/MathOpEnumAc.hpp"
#include "MathOpsExampleTopologyDefs.hpp"
#include "MathSender.hpp"
#include <MathOpsExampleDeployment/Top/MathOpsExampleTopologyAc.hpp>

#include <csignal>
#include <iostream>

MathOpsExample::TopologyState state;

volatile sig_atomic_t running = 1;

static void sighandler(int)
{
  std::cout << "\nGot end signal. Shutting down ..." << "\n";
  MathOpsExample::teardown(state);
  running = 0;
}

namespace MathOpsExample {
  struct MathOpPortPkg {
    F32 rhs, lhs;
    MathOp op;
  };
}

static inline auto get_random_mathop()
{
  return MathOpsExample::MathOpPortPkg{1, 2, MathOpsExample::MathOp::ADD};
}

static inline void do_cycle()
{
  auto op_to_invoke = get_random_mathop();
  MathOpsExample::mathSender.do_mathOpReq(0,
					  op_to_invoke.lhs,
					  op_to_invoke.op,
					  op_to_invoke.rhs);
  
  MathOpsExample::blockDrv.callIsr();
  Os::Task::delay(5000); // delay for 5s
}



int main()
{
  std::cout << "Setting up topology..." << "\n";
  state =  MathOpsExample::TopologyState();
  MathOpsExample::setup(state);
  std::cout << "Topology initialized!" << "\n";

  std::signal(SIGINT, sighandler);
  std::signal(SIGTERM, sighandler);

  while (running) do_cycle();

  std::cout << "Exiting!!" << "\n";
  
  
  return 0;
}
