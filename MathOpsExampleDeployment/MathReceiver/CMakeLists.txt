set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/MathReceiver.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/MathReceiver.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/MathReceiver.cpp")

set(MOD_DEPS "Fw")

register_fprime_module()


target_include_directories(MathOpsExampleDeployment_MathReceiver SYSTEM PUBLIC
  $ENV{JLUNA_INCLUDE_DIR}
  $ENV{JULIA_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../MathPorts
)

set_property(TARGET MathOpsExampleDeployment_MathReceiver PROPERTY CXX_STANDARD 20)
