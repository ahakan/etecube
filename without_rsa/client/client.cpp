/**
 * @file client.cpp
 * @author ahc (info@ahakan.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */


// Standard library includes
#include <iostream>
#include <string>
#include <chrono>
#include <map>


// Socket includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


// Using && namespaces
using MessagesMap = std::map<int, std::string>;


/**
 * @brief Main
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    struct sockaddr_in  address;
    int                 sock = 0, 
                        port;
    char                buffer[256] = {0};

    if(argc != 2)
    {
        std::cerr << "Usage: ./client <port>\n";

        exit(EXIT_FAILURE);
    }

    port = std::atoi(argv[1]);

    // Creating socket file descriptor
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
    {
        std::cout << "Socket failed." << std::endl;

        exit(EXIT_FAILURE);
    }
   
    address.sin_family  = AF_INET;
    address.sin_port    = htons(port);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr)<=0) 
    {
        std::cout << "Invalid address. Address not supported." << std::endl;

        exit(EXIT_FAILURE);
    }
   
    if (connect(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cout << "Connection Failed." << std::endl;

        exit(EXIT_FAILURE);
    }
    
    std::string userInput;

    do
	{
		// Prompt the user for some text
		std::cout << "Client > ";

		getline(std::cin, userInput);

		if (userInput.size() > 0)
		{
            // Send the text
            send(sock, userInput.c_str(), strlen(userInput.c_str()), 0);
			
            // Wait for response
            int bytesReceived = recv(sock, buffer, 256, 0);

            if (bytesReceived > 0)
            {
                // Echo response to console
                std::cout << "Server > " << std::string(buffer, 0, bytesReceived) << std::endl;

                memset(buffer, 0, sizeof buffer);
            }
		}
	} while (userInput.size() > 0);

    close(sock);

    return 0;
}