set(Utf8_stringTargetName utf8_string)

project(${Utf8_stringTargetName})

add_library(${Utf8_stringTargetName} STATIC
            src/utf8_string.hpp
            src/utf8_string.cpp
            src/utf8_iterator.hpp
            src/utf8_iterator.cpp
)

target_include_directories(${Utf8_stringTargetName}
        PUBLIC
            src
)

