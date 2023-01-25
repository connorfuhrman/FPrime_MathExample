#include <jluna.hpp>

#include "MathOpsExampleDeployment/MathTypes/MathOpEnumAc.hpp"



  struct MathOpPort
  {
    MathOpPort() = default;
    MathOpPort(int _portNum, float _lhs, MathOpsExample::MathOp _op, float _rhs)
      : portNum(_portNum), lhs(_lhs), rhs(_rhs), op(_op) {}

    int portNum;
    float lhs, rhs;
    MathOpsExample::MathOp op;
  };

  struct MathResPort
  {
    MathResPort() = default;
    MathResPort(int _portNum, float _result)
      : portNum(_portNum), result(_result) {}

    int portNum;
    float result;
  };

set_usertype_enabled(MathOpPort);
set_usertype_enabled(MathResPort);
