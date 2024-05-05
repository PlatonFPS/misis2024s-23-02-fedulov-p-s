add_library(decorator  decorator.hpp)
set_property(TARGET decorator PROPERTY CXX_STANDARD 20)
target_include_directories(decorator PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS decorator)
target_link_libraries(decorator timer)