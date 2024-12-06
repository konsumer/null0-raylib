find_package(PhysFS REQUIRED)
find_package(raylib REQUIRED)

add_executable(${PROJECT_NAME} src/main.c)

if (EMSCRIPTEN)
  target_link_libraries(${PROJECT_NAME} physfs-static raylib)
  target_link_options(${PROJECT_NAME} PUBLIC -sASSERTIONS=0 -DNDEBUG -sMALLOC=emmalloc -sENVIRONMENT=web -Oz -sSINGLE_FILE -sFORCE_FILESYSTEM -sEXPORTED_RUNTIME_METHODS=FS -sASYNCIFY -sALLOW_MEMORY_GROWTH)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/docs/"
    RUNTIME_OUTPUT_NAME "host"
    SUFFIX ".mjs"
  )
else()
  find_package(wamr REQUIRED)
  target_link_libraries(${PROJECT_NAME} wamr physfs-static m raylib)
endif()
