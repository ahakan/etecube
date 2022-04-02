#include "utilities.h"


/**
 * @brief Construct a new Utilities:: Utilities object
 * 
 */
Utilities::Utilities()
{
    init();
}


/**
 * @brief Destroy the Utilities:: Utilities object
 * 
 */
Utilities::~Utilities()
{
    free(private_key);
    free(public_key);
}


/**
 * @brief Utilities instance
 * 
 * @return Utilities* 
 */
Utilities* Utilities::instance()
{
    static Utilities *pInstance;

    if (pInstance == NULL)
    {
        pInstance = new Utilities();
    }

    return pInstance;
}


/**
 * @brief Get the Timestamp object
 * 
 * @return std::string 
 */
std::string Utilities::getTimestamp() {
	long long ms_since_epoch = std::chrono::duration_cast
                                <std::chrono::milliseconds>
                                (std::chrono::system_clock::now().time_since_epoch())
                                .count();
                                
	return std::to_string(ms_since_epoch);
}


/**
 * @brief Convert char to string
 * 
 * @param buf 
 * @return std::string 
 */
std::string Utilities::convertToString(char* buf)
{
    std::string str(buf);

    return str;
}


/**
 * @brief Read RSA
 * 
 * @param keypair 
 * @param pem_type 
 * @param file_name 
 * @return RSA* 
 */
RSA *Utilities::read_RSA(int pem_type, char *file_name) {

    RSA   *rsa = NULL;
    FILE  *fp  = NULL;

    if (pem_type == PUBLIC_KEY_PEM) 
    {
        fp = fopen(file_name, "r");
        PEM_read_RSAPublicKey(fp, &rsa, NULL, NULL);
        fclose(fp);
    }
    else if (pem_type == PRIVATE_KEY_PEM) 
    {
        fp = fopen(file_name, "r");
        PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);
        fclose(fp);
    }

    return rsa;
}


/**
 * @brief Public encrypt
 * 
 * @param flen 
 * @param from 
 * @param to 
 * @param key 
 * @param padding 
 * @return int 
 */
int Utilities::public_encrypt(int flen, unsigned char* from, unsigned char* to, RSA* key, int padding) {
    
    int result = RSA_public_encrypt(flen, from, to, key, padding);

    return result;
}


/**
 * @brief Private decrypt
 * 
 * @param flen 
 * @param from 
 * @param to 
 * @param key 
 * @param padding 
 * @return int 
 */
int Utilities::private_decrypt(int flen, unsigned char* from, unsigned char* to, RSA* key, int padding) {

    int result = RSA_private_decrypt(flen, from, to, key, padding);

    return result;
}


void Utilities::init()
{
    private_key = read_RSA(PRIVATE_KEY_PEM, private_key_file);

    public_key  = read_RSA(PUBLIC_KEY_PEM, public_key_file);
}


char *Utilities::encrypt(const char *message)
{
    char * encrypt      = (char*)malloc(RSA_size(public_key));

    int encrypt_length  = public_encrypt(strlen(message)+1, (unsigned char*)(message), (unsigned char*)encrypt, public_key, RSA_PKCS1_PADDING);
    
    if(encrypt_length == -1) 
    {
        std::cout << "Failed to encryption. ";
    }

    return encrypt;
}


char *Utilities::decrypt(char *message)
{    
    char * decrypt      = (char *)malloc(256);

    int decrypt_length  = private_decrypt(256, (unsigned char*)message, (unsigned char*)decrypt, private_key, RSA_PKCS1_PADDING);
    
    if (decrypt_length == -1) 
    {
        std::cout << "Failed to decryption. ";
    }

    return decrypt;
}