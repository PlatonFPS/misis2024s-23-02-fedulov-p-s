add_library(timer timer.cpp timer.hpp)
set_property(TARGET timer PROPERTY CXX_STANDARD 20)
target_include_directories(timer PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS timer)

target_compile_options(timer PRIVATE
    $<$<CONFIG:Debug>:
        /Od;
        /ZI
    >
    $<$<CONFIG:Release>:
        /O2;
        /Oi;
        /Gy;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
    >
    $<$<CONFIG:Dist>:
        /O2;
        /Oi;
        /Gy;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
    >
    /W3;
    ${DEFAULT_CXX_EXCEPTION_HANDLING}
)