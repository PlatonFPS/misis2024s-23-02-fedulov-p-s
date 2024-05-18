add_subdirectory(commands)

add_executable(robocrawl robocrawl.cpp "Commands/commands.cpp")
target_link_libraries(robocrawl commands)