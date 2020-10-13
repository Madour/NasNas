file(GLOB_RECURSE Src *.cpp)
file(GLOB_RECURSE Inc *.hpp)
set(source_files ${Src} ${Inc})

add_example_target(split_view  SRC "${source_files}" )
