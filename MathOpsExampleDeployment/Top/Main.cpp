#include "BasicTypes.hpp"
#include "MathOpsExampleDeployment/MathTypes/MathOpEnumAc.hpp"
#include "MathOpsExampleTopologyDefs.hpp"
#include "MathSender.hpp"
#include "Task.hpp"
#include <MathOpsExampleDeployment/Top/MathOpsExampleTopologyAc.hpp>

#include <csignal>
#include <thread>
#include <functional>
#include <random>

#include <fmt/core.h>


MathOpsExample::TopologyState state;

volatile sig_atomic_t running = 1;



static void sighandler(int)
{
  fmt::print("\nGot end signal. Shutting down ...\n");
  MathOpsExample::teardown(state);
  running = 0;

}

static void blockDrv_th_entrypoint(const volatile sig_atomic_t& running,
				   std::function<void()> do_cycle)
{
  while(running) do_cycle();
}


int main()
{
  fmt::print("Setting up topology...\n");
  state =  MathOpsExample::TopologyState();
  MathOpsExample::setup(state);
  fmt::print("Topology initialized!\n");

  std::signal(SIGINT, sighandler);
  std::signal(SIGTERM, sighandler);

  // Launch thread to call the block driver
  // manually so the MathReceiver will flush
  // its queue
  std::thread blockDrv_th(blockDrv_th_entrypoint,
			  std::ref(running),
			  [] () {
			    MathOpsExample::blockDrv.callIsr();
			    Os::Task::delay(500);
			  });


  // While running give random invocations of the
  // MathSender's output MathOpsReqOut port
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<unsigned int> op_distrib(0, 3);
  std::uniform_real_distribution<F32> val_distrib(1, 100);
  const auto make_random_op = [&op_distrib, &gen]() {
    return static_cast<MathOpsExample::MathOp::t>(op_distrib(gen));
  };
  
  const auto print_req = [] (auto lhs, auto op, auto rhs) {
    std::string op_str;
    switch(op) {
    case MathOpsExample::MathOp::ADD: op_str = "+"; break;
    case MathOpsExample::MathOp::SUB: op_str = "-"; break;
    case MathOpsExample::MathOp::DIV: op_str = "/"; break;
    case MathOpsExample::MathOp::MUL: op_str = "*"; break;
    }
    fmt::print("Requesting {} {} {}\n", lhs, op_str, rhs);
  };

 
  while (running)
  {
    auto op = make_random_op();
    auto lhs = val_distrib(gen);
    auto rhs = val_distrib(gen);
    print_req(lhs, op, rhs);
    MathOpsExample::mathSender.do_mathOpReq(0, lhs, op, rhs);
    Os::Task::delay(1000);
  }

  blockDrv_th.join();

  fmt::print("Exiting!!\n");
  
  
  return 0;
}
