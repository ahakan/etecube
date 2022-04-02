/**
 * @file utilities.h
 * @author ahc (info@ahakan.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef UTILITIES_H
#define UTILITIES_H


// Standard library includes
#include <iostream>
#include <chrono>
#include <string.h>


// Openssl includes
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>


// Definitions
#define KEY_LENGTH       2048
#define PUBLIC_EXPONENT  59     
#define PUBLIC_KEY_PEM   1
#define PRIVATE_KEY_PEM  0



class Utilities
{
    private:
        RSA                 *private_key;
        RSA                 *public_key;

        char                private_key_file[27] = "../../OHMsH4Fxz4zmFDGQOnFv";
        char                public_key_file[27]  = "../../9zvH6LpEkW22UVsZicni";

        RSA                 *read_RSA(int pem_type, char *file_name);
        int                 public_encrypt(int flen, unsigned char* from, unsigned char *to, RSA* key, int padding);
        int                 private_decrypt(int flen, unsigned char* from, unsigned char *to, RSA* key, int padding);

    protected:  
                            Utilities();
                            ~Utilities();

    public:
                            Utilities(const Utilities&)               = delete;       // Singletons should not be cloneable.
                            Utilities& operator=(const Utilities&)    = delete;       // Singletons should not be assignable.

        static Utilities    *instance();
        
        std::string         getTimestamp();
        std::string         convertToString(char* buf);

        void                init();
        char                *encrypt(const char *message);
        char                *decrypt(char *message);
        
};

#endif