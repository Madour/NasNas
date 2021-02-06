file(GLOB_RECURSE Src *.cpp)
file(GLOB_RECURSE Inc *.hpp)
set(source_files ${Src} ${Inc})

add_example_target(custom_components  SRC "${source_files}" )
