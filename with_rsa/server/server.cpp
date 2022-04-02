/**
 * @file server.cpp
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
#include <iterator>


// Socket includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


// Headers
#include "../src/utilities.h"


// Using && namespaces
using MessageMap        = std::map<std::string, std::string>;
using AllMessagesMap    = std::map<std::string, MessageMap>;


/**
 * @brief main
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    Utilities           *pUtil = Utilities::instance();

    MessageMap          message;
    AllMessagesMap      messages;

    struct sockaddr_in  address;
    int                 sockfd, 
                        newsockfd, 
                        port;
    int                 addrlen = sizeof(address);
    char                buffer[256] = {0};

    if(argc != 2)
    {
        std::cerr << "Usage: ./server <port>\n";

        exit(EXIT_FAILURE);
    }

    port = std::atoi(argv[1]);

       
    // Creating socket file descriptor
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == 0)
    {
        std::cout << "Socket failed." << std::endl;

        exit(EXIT_FAILURE);
    }
       
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( port );
       
    // Forcefully attaching socket to the port 8080
    if (bind(sockfd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        std::cout << "Bind failed." << std::endl;

        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 3) < 0)
    {
        std::cout << "Listen failed." << std::endl;

        exit(EXIT_FAILURE);
    }

    if ((newsockfd = accept(sockfd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        std::cout << "Accept failed." << std::endl;

        exit(EXIT_FAILURE);
    }

	while(true)
	{
        // Do-while loop to send and receive data
	    std::string userInput;

        // Wait for response
        int bytesReceived = recv(newsockfd, buffer, 256, 0);

        if (bytesReceived > 0)
        {
            // Echo response to console after dectryption
            std::cout << "Client > " << pUtil->decrypt(buffer)<< std::endl;
            
            // Add message to map
            std::string timestamp = pUtil->getTimestamp();

            message.emplace("Client", pUtil->convertToString(buffer));

            messages.emplace(timestamp, message);

            message.clear();

            // Prompt the user for some text
            std::cout << "Server > ";

            getline(std::cin, userInput);

            if (userInput.size() > 0)
            {
                char * encrypted = pUtil->encrypt(userInput.c_str());
                
                // Send the text
                send(newsockfd , encrypted, strlen(encrypted), 0);

                // Add message to map
                std::string timestamp = pUtil->getTimestamp();

                message.emplace("Server", userInput);

                messages.emplace(timestamp, message);

                message.clear();

                memset(buffer, 0, sizeof buffer);
            }
        }
        else 
        {
            break;
        }
	}

    std::cout << "All Messages - Map" << std::endl;

    for (AllMessagesMap::iterator i = messages.begin(); i != messages.end(); i++)
    {
        std::cout << i->first << " - " << i->second.begin()->first << " > " << i->second.begin()->second << std::endl;
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}