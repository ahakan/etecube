cmake_minimum_required(VERSION 3.0.0)

project(etecube VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion-null")


find_package(OpenSSL) 
if(OPENSSL_FOUND)
    message(STATUS "Found OpenSSL version: ${OPENSSL_VERSION}")
    message(STATUS "Using OpenSSL include dir(s): ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "Using OpenSSL lib(s): ${OPENSSL_LIBRARIES}")
    include_directories(${OPENSSL_INCLUDE_DIR})
else()
    message(WARNING "Could not find libssl and libcrypto. This dependency will be downloaded. To avoid this you can install curl yourself using the standard methods for your platform.")
endif()


add_subdirectory(client)
add_subdirectory(server)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
