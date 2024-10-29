add_library(ptl
    src/hash.c
    src/list.c
    src/map.c
    src/array.c)
target_compile_options(ptl PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(ptl PUBLIC "include")
