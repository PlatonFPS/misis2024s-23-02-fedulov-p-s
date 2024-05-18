add_library(commands commands.cpp commands.hpp)
set_property(TARGET commands PROPERTY CXX_STANDARD 20)
target_include_directories(commands PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS commands)