# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    # GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    # GIT_TAG "master"
    # GIT_PROGRESS TRUE
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
)

FetchContent_MakeAvailable(raylib)