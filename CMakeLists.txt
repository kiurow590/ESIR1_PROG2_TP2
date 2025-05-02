cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0135 NEW)
project(LISTE_TP2)
# activation de la vérification des assertions
set(CMAKE_CXX_STANDARD 23)
add_compile_definitions(NREALEASE)

SET(CMAKE_C_FLAGS CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(LISTE Liste.h copier.h cyclicNode.h memory.cxx main.cpp)
add_executable(LISTE_test Liste.h copier.h cyclicNode.h test/main_test.cc test/common_p1.cc test/test_p1.cc test/common_p1.h test/common_p2.h test/common_p24.h test/test_p2.cc test/test_p24.cc test/test_p3.cc test/test_p32.cc test/test_p4.cc )
target_link_libraries(LISTE_test gtest_main)
target_compile_options(LISTE PRIVATE -UNDEBUG)
target_compile_options(LISTE_test PRIVATE -UNDEBUG)