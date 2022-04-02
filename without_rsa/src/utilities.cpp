#include "utilities.h"


/**
 * @brief Construct a new Utilities:: Utilities object
 * 
 */
Utilities::Utilities()
{
}


/**
 * @brief Destroy the Utilities:: Utilities object
 * 
 */
Utilities::~Utilities()
{
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
