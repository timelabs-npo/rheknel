cmake_minimum_required(VERSION 3.15)
project(rheknel VERSION 4.0.0 LANGUAGES C)

option(RHEKNEL_SANITIZE "Enable address and undefined-behavior sanitizers" OFF)

add_library(rheknel STATIC
    src/rhea.c
    src/omnia_bus.c
    src/platform.c
    src/sha256.c
)
target_include_directories(rheknel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(rheknel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_target_properties(rheknel PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)

add_executable(rhea kernel.c)
target_link_libraries(rhea PRIVATE rheknel)
set_target_properties(rhea PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)

if(MSVC)
    target_compile_options(rheknel PRIVATE /W4 /WX)
    target_compile_options(rhea PRIVATE /W4 /WX)
else()
    target_compile_options(rheknel PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(rhea PRIVATE -Wall -Wextra -Wpedantic -Werror)
    if(RHEKNEL_SANITIZE)
        target_compile_options(rheknel PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_compile_options(rhea PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(rhea PRIVATE -fsanitize=address,undefined)
    endif()
endif()

include(CTest)
if(BUILD_TESTING)
    add_executable(omnia_bus_tests tests/test_omnia_bus.c)
    target_link_libraries(omnia_bus_tests PRIVATE rheknel)
    target_include_directories(omnia_bus_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    target_compile_definitions(omnia_bus_tests PRIVATE OMNIA_FIXTURE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/tests/fixtures")
    set_target_properties(omnia_bus_tests PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
    if(MSVC)
        target_compile_options(omnia_bus_tests PRIVATE /W4 /WX)
    else()
        target_compile_options(omnia_bus_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
        if(RHEKNEL_SANITIZE)
            target_compile_options(omnia_bus_tests PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
            target_link_options(omnia_bus_tests PRIVATE -fsanitize=address,undefined)
        endif()
    endif()
    add_test(NAME omnia_bus_adversarial COMMAND omnia_bus_tests)
    add_test(
        NAME omnia_bus_cli_pass
        COMMAND rhea ${CMAKE_CURRENT_SOURCE_DIR}/tests/fixtures/omnia-dns-macos.omnb 1786665600
    )
endif()
