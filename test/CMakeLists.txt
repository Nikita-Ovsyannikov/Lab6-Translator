set(target ${TRANSLATOR_TESTS})

file(GLOB TRANSLATOR_HEADERS "*.h*")
file(GLOB TRANSLATOR_SOURCES "*.cpp")

add_executable(${target} ${TRANSLATOR_SOURCES} ${TRANSLATOR_HEADERS})
target_link_libraries(${target} gtest)
target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/gtest ${TRANSLATOR_INCLUDE})
add_test(${target} ${target})