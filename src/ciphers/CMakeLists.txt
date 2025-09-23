add_library(ciphers SHARED atbash.cpp caesar.cpp cipher_factory.cpp cipher.cpp)
target_include_directories(ciphers PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")