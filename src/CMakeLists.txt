file(GLOB_RECURSE CPPS  ./*.cpp )

add_executable(src ${CPPS})

target_link_libraries(src nodes)
