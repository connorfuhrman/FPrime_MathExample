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

#include <MathPorts_jl.hpp>

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

void setup_jl_types()
{ 
  // Allow (un)boxing of MathOpPort
  jluna::Usertype<MathOpPort>::add_property<int> (
    "portNum",
    [](MathOpPort& in) -> int {
      return in.portNum;
    },
    [](MathOpPort& out, int _portNum) {
      out.portNum = _portNum;
    });
  
  jluna::Usertype<MathOpPort>::add_property<F32> (
    "lhs",
    [](MathOpPort& in) -> F32 {
      return in.lhs;
    },
    [](MathOpPort& out, F32 _lhs) -> void {
      out.lhs = _lhs;
    });

  jluna::Usertype<MathOpPort>::add_property<F32> (
    "rhs",
    [](MathOpPort& in) -> F32 {
      return in.rhs;
    },
    [](MathOpPort& out, F32 _rhs) -> void {
      out.rhs = _rhs;
    });

  jluna::Usertype<MathOpPort>::add_property<int> (
    "op",
    [](MathOpPort& in) -> int { return static_cast<int>(in.op.e); },
    [](MathOpPort& out, int _op) -> void {
      out.op = static_cast<MathOpsExample::MathOp::t>(_op);
    });

  jluna::Usertype<MathOpPort>::implement();

  // Provide Julia-side external constructor
  jluna::Main.safe_eval(R"(
    function MathOpPort(portNum::Int32, rhs::Float32, op::Int32, lhs::Float32)::MathOpPort
       out = MathOpPort()
       out.portNum = portNum
       out.rhs = rhs
       out.op = op
       out.lhs = lhs

       return out
    end

    precompile(MathOpPort, (Int32, Float32, Int32, Float32,))

    )");
  

  // Allow (un)boxing of MathResPort
  jluna::Usertype<MathResPort>::add_property<int> (
    "portNum",
    [](MathResPort& in) -> int {
      return in.portNum;
    },
    [](MathResPort& out, int _portNum) {
      out.portNum = _portNum;
    });

  jluna::Usertype<MathResPort>::add_property<float> (
    "result",
    [](MathResPort& in) -> float {
      return in.result;
    },
    [](MathResPort& out, float _result) {
      out.result = _result;
    });

  jluna::Usertype<MathResPort>::implement();

  // Provide Julia-side external constructor
  jluna::Main.safe_eval(R"(
    function MathResPort(portNum::Int32, result::Float32)::MathResPort
	out = MathResPort()
	out.portNum = portNum
	out.result = result

	return out
     end


     precompile(MathResPort, (Int32, Float32, ))

     )");
  
}


int main()
{
  fmt::print("Setting up topology...\n");
  setup_jl_types();
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
