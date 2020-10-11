file(GLOB_RECURSE Src *.cpp)
file(GLOB_RECURSE Inc *.hpp)
set(source_files ${Src} ${Inc})

add_example_target(demo  SRC "${source_files}" RES_DIR assets)
