#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

#define SERVER_M_TCP_PORT "45886"
#define HOST_NAME "127.0.0.1"
#define MAXDATASIZE 100

// refers to Beej's guide
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

// encrypt the username and password
std::string encrypt(const std::string &text)
{
    std::string encryptedText = "";

    for (char c : text)
    {
        if (isalpha(c))
        {
            char base = islower(c) ? 'a' : 'A';
            encryptedText += static_cast<char>((c - base + 5) % 26 + base);
        }
        else if (isdigit(c))
        {
            encryptedText += static_cast<char>((c - '0' + 5) % 10 + '0');
        }
        else
        {
            encryptedText += c;
        }
    }
    return encryptedText;
}

int main()
{
    int sockfd, numbytes;
    char buf[MAXDATASIZE], bookBuf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(HOST_NAME, SERVER_M_TCP_PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("client: connect");
            continue;
        }
        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    std::cout << "Client is up and running." << std::endl;

    freeaddrinfo(servinfo);

    // get the dynamic port
    struct sockaddr_in local_addr;
    socklen_t addr_len = sizeof(local_addr);
    memset(&local_addr, 0, sizeof(local_addr));
    if (getsockname(sockfd, (struct sockaddr *)&local_addr, &addr_len) == -1)
    {
        perror("getsockname");
        exit(1);
    }

    while (1)
    {
        std::string username;
        std::string password;

        std::cout << "Please enter the username: ";
        getline(std::cin, username);

        std::cout << "Please enter the password: ";
        getline(std::cin, password);

        // encrypt the username and password with a single space between them
        std::string message = encrypt(username) + " " + encrypt(password);

        const char *msg = message.c_str();
        int len = strlen(msg);
        if (send(sockfd, msg, len, 0) == -1)
        {
            perror("send");
        }

        std::cout << username << " sent an authentication request to the Main Server." << std::endl;

        if ((numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0)) == -1)
        {
            perror("recv");
            exit(1);
        }
        buf[numbytes] = '\0';
        // s for success, n for not found, p for password not match
        if (buf[0] == 's')
        {
            std::cout << username << " received the result of authentication from Main Server using TCP over port " << ntohs(local_addr.sin_port) << ". Authentication is successful." << std::endl;
            while (1)
            {
                std::string bookCode;
                std::cout << "Please enter book code to query:";
                getline(std::cin, bookCode);
                const char *query = bookCode.c_str();
                int queryLen = strlen(query);
                if (send(sockfd, query, queryLen, 0) == -1)
                {
                    perror("send");
                }
                if (username == "admin")
                {
                    std::cout << "Request sent to the Main Server with Admin rights." << std::endl;
                }
                else
                {
                    std::cout << username << " sent the request to the Main Server." << std::endl;
                }

                if ((numbytes = recv(sockfd, bookBuf, MAXDATASIZE - 1, 0)) == -1)
                {
                    perror("recv");
                    exit(1);
                }
                bookBuf[numbytes] = '\0';
                std::cout << "Response received from the Main Server on TCP port: " << ntohs(local_addr.sin_port) << "." << std::endl;
                int bookCount = atoi(bookBuf);
                if (bookCount > 0)
                {
                    if (username == "admin")
                    {
                        std::cout << "Total number of book " << bookCode << " available = " << bookCount << std::endl;
                    }
                    else
                    {
                        std::cout << "The requested book " << bookCode << " is available in the library." << std::endl;
                    }
                }
                else if (bookCount == 0)
                {
                    if (username == "admin")
                    {
                        std::cout << "Total number of book " << bookCode << " available = " << bookCount << std::endl;
                    }
                    else
                    {
                        std::cout << "The requested book " << bookCode << " is NOT available in the library." << std::endl;
                    }
                }
                else if (bookCount == -1)
                {
                    if (username == "admin")
                    {
                        std::cout << "Not able to find the book-code " << bookCode << " in the system." << std::endl;
                    }
                    else
                    {
                        std::cout << "Not able to find the book-code " << bookCode << " in the system." << std::endl;
                    }
                }
                std::cout << "—- Start a new query —-" << std::endl;
            }
        }
        else if (buf[0] == 'n')
        {
            std::cout << username << " received the result of authentication from Main Server using TCP over port " << ntohs(local_addr.sin_port) << ". Authentication failed: Username not found." << std::endl;
        }
        else if (buf[0] == 'p')
        {
            std::cout << username << " received the result of authentication from Main Server using TCP over port " << ntohs(local_addr.sin_port) << ". Authentication failed: Password does not match." << std::endl;
        }
    }

    close(sockfd);
    return 0;
}