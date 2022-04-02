include_directories(../src)

add_executable(client client.cpp ../src/utilities.cpp)

target_link_libraries(client ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY})

set_target_properties(client PROPERTIES COMPILE_DEFINITIONS "client")
