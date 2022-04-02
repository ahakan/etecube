include_directories(../src)

add_executable(server server.cpp ../src/utilities.cpp)

target_link_libraries(server ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY})

set_target_properties(server PROPERTIES COMPILE_DEFINITIONS "server")