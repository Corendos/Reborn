#
# MIT Licence
# Copyright (c) 2022 Corentin Godeau (@Corendos)
# More details at https://github.com/Corendos/Reborn
#

add_executable(reborn_tests)

target_sources(reborn_tests PRIVATE all.cpp)
target_compile_definitions(reborn_tests PRIVATE ${PLATFORM_DEFINES})
target_link_libraries(reborn_tests PRIVATE libreborn_static)

set_target_properties(reborn_tests PROPERTIES
                                 RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/tests
                                 PDB_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/tests)

if (DEFINED CMAKE_BUILD_TYPE)
set_target_properties(reborn_tests PROPERTIES
                                 RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/tests/Debug
                                 PDB_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/tests/Debug
                                 RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/tests/Release
                                 PDB_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/tests/Release)
endif()

add_test(reborn_tests COMMAND reborn_tests)