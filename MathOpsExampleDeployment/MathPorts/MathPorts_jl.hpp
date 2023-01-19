#include <jluna.hpp>

#include "MathOpsExampleDeployment/MathTypes/MathOpEnumAc.hpp"

struct MathOpsExample_MathOp
{
  MathOpsExample_MathOp() = default;
  MathOpsExample_MathOp(int _portNum, float _lhs, MathOpsExample::MathOp _op, float _rhs)
    : portNum(_portNum), lhs(_lhs), op(_op), rhs(_rhs)
  {

  }

  int portNum;
  float lhs, rhs;
  MathOpsExample::MathOp op;
};

set_usertype_enabled(MathOpsExample_MathOp);
