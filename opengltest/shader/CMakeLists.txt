add_library(shader shader.cpp shader.hpp)
set_property(TARGET shader PROPERTY CXX_STANDARD 20)
target_include_directories(shader PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS shader)
target_link_libraries(shader glad)