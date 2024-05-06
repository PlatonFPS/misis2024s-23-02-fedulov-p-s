add_executable(timing_q timing_q.cpp)
target_link_libraries(timing_q timer queuelstt queuearrt)

target_compile_options(timing_q PRIVATE
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
