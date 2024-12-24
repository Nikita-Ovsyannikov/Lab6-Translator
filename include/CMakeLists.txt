set(target ${TRANSLATOR_CUSTOM_PROJECT})
project(${target})

file(GLOB TRANSLATOR_HEADERS "*.h*")

add_custom_target(${target} SOURCES ${TRANSLATOR_HEADERS})