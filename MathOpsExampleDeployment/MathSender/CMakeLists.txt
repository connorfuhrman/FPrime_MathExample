set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/MathSender.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/MathSender.cpp")

find_package(fmt REQUIRED)
set(MOD_DEPS fmt::fmt)

register_fprime_module()
