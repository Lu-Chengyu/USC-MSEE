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

#define SERVER_S_PORT 41886
#define SERVER_L_PORT 42886
#define SERVER_H_PORT 43886
#define SERVER_M_UDP_PORT "44886"
#define SERVER_M_TCP_PORT "45886"
#define HOST_NAME "127.0.0.1"
#define MAXBUFLEN 1000
#define BACKLOG 10

// refers to Beej's guide
void sigchld_handler(int s)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main()
{
    // Seting up UDP socket
    int sockfdUDP;
    struct addrinfo hintsUDP, *servinfoUDP, *pUDP;
    int rvUDP;
    int numbytesUDP;

    struct sockaddr_storage their_addrUDP;
    char bufUDP[MAXBUFLEN];
    socklen_t addr_lenUDP;

    memset(&hintsUDP, 0, sizeof hintsUDP);
    hintsUDP.ai_family = AF_INET;
    hintsUDP.ai_socktype = SOCK_DGRAM;

    if ((rvUDP = getaddrinfo(HOST_NAME, SERVER_M_UDP_PORT, &hintsUDP, &servinfoUDP)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rvUDP));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (pUDP = servinfoUDP; pUDP != NULL; pUDP = pUDP->ai_next)
    {
        if ((sockfdUDP = socket(pUDP->ai_family, pUDP->ai_socktype, pUDP->ai_protocol)) == -1)
        {
            perror("listener: socket");
            continue;
        }
        if (bind(sockfdUDP, pUDP->ai_addr, pUDP->ai_addrlen) == -1)
        {
            close(sockfdUDP);
            perror("listener: bind");
            continue;
        }
        break;
    }

    if (pUDP == NULL)
    {
        fprintf(stderr, "listener: failed to bind socket\n");
        return 2;
    }

    freeaddrinfo(servinfoUDP);

    printf("Main Server is up and running.\n");

    std::map<std::string, int> bookMap;

    for (int i = 0; i < 3; i++)
    {
        addr_lenUDP = sizeof their_addrUDP;
        if ((numbytesUDP = recvfrom(sockfdUDP, bufUDP, MAXBUFLEN - 1, 0, (struct sockaddr *)&their_addrUDP, &addr_lenUDP)) == -1)
        {
            perror("recvfrom");
            exit(1);
        }
        bufUDP[numbytesUDP] = '\0';

        // Parse the binary message into a std::map
        size_t index = 0;
        while (index < static_cast<size_t>(numbytesUDP))
        {
            // Extract the key size
            uint16_t keySize;
            memcpy(&keySize, bufUDP + index, sizeof(uint16_t));
            keySize = ntohs(keySize);
            index += sizeof(uint16_t);
            // Extract the key
            std::string key(bufUDP + index, keySize);
            index += keySize;
            // Extract the value
            int value;
            memcpy(&value, bufUDP + index, sizeof(int));
            value = ntohl(value);
            index += sizeof(int);
            // Insert the key-value pair into the std::map
            bookMap[key] = value;
        }
        // if (bufUDP[0 + sizeof(uint16_t)] == 'H')
        // {
        //     printf("Main Server received the username list from serverH using UDP over port %s\n", SERVER_M_UDP_PORT);
        // }
        // else if (bufUDP[0 + sizeof(uint16_t)] == 'L')
        // {
        //     printf("Main Server received the username list from serverL using UDP over port %s\n", SERVER_M_UDP_PORT);
        // }
        // else if (bufUDP[0 + sizeof(uint16_t)] == 'S')
        // {
        //     printf("Main Server received the username list from serverS using UDP over port %s\n", SERVER_M_UDP_PORT);
        // }
    }

    // close(sockfdUDP);

    std::string filename = "member.txt";
    std::ifstream file(filename);
    std::map<std::string, std::string> memberMap;
    std::string line;

    while (getline(file, line))
    {
        std::istringstream iss(line);
        std::string username;
        std::string password;

        if (!(iss >> username >> password))
        {
            std::cerr << "file error: " << line << std::endl;
            continue;
        }
        username.pop_back();
        memberMap[username] = password;
    }

    file.close();
    std::cout << "Main Server loaded the member list." << std::endl;

    // setting up TCP server socket
    int sockfdTCP, new_fd;
    int numbytesTCP;
    struct addrinfo hintsTCP, *servinfoTCP, *pTCP;
    struct sockaddr_storage their_addrTCP;
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    int rvTCP;
    char bufTCP[MAXBUFLEN];

    memset(&hintsTCP, 0, sizeof hintsTCP);
    hintsTCP.ai_family = AF_UNSPEC;
    hintsTCP.ai_socktype = SOCK_STREAM;
    hintsTCP.ai_flags = AI_PASSIVE; //??????

    if ((rvTCP = getaddrinfo(NULL, SERVER_M_TCP_PORT, &hintsTCP, &servinfoTCP)) != 0) // why using NULL: p22    ??????
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rvTCP));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (pTCP = servinfoTCP; pTCP != NULL; pTCP = pTCP->ai_next)
    {
        if ((sockfdTCP = socket(pTCP->ai_family, pTCP->ai_socktype, pTCP->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }
        if (setsockopt(sockfdTCP, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }
        if (bind(sockfdTCP, pTCP->ai_addr, pTCP->ai_addrlen) == -1)
        {
            close(sockfdTCP);
            perror("server: bind");
            continue;
        }
        break;
    }

    freeaddrinfo(servinfoTCP); // all done with this structure

    if (pTCP == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfdTCP, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    // deal with all dead processes
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    // accept() loop
    while (1)
    {
        sin_size = sizeof their_addrTCP;
        new_fd = accept(sockfdTCP, (struct sockaddr *)&their_addrTCP, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }

        // receiving Login and confirmation requests from client
        while (1)
        {
            numbytesTCP = recv(new_fd, bufTCP, MAXBUFLEN - 1, 0);
            if (numbytesTCP == -1)
            {
                perror("recv");
                exit(1);
            }
            else if (numbytesTCP == 0)
            {
                break;
            }
            bufTCP[numbytesTCP] = '\0';
            std::cout << "Main Server received the username and password from the client using TCP over port " << SERVER_M_TCP_PORT << "." << std::endl;
            std::string received = std::string(bufTCP);
            size_t delim_pos = received.find(" ");
            std::string username = received.substr(0, delim_pos);
            std::string password = received.substr(delim_pos + 1);

            std::string response;
            // s for success, n for not found, p for password not match
            if (memberMap.find(username) != memberMap.end())
            {
                if (memberMap[username] == password)
                {
                    std::cout << "Password " << password << " matches the username. Send a reply to the client." << std::endl;
                    response = "s";
                    if (send(new_fd, response.c_str(), response.size(), 0) == -1)
                    {
                        perror("send");
                    }
                    while (1)
                    {
                        if ((numbytesTCP = recv(new_fd, bufTCP, MAXBUFLEN - 1, 0)) == -1)
                        {
                            perror("recv");
                            exit(1);
                        }
                        bufTCP[numbytesTCP] = '\0';
                        std::cout << "Main Server received the book request from client using TCP over port " << SERVER_M_TCP_PORT << "." << std::endl;
                        std::string bookCode(bufTCP);
                        char serverType = bookCode[0];
                        int udpPort;
                        bool sendStatus = false;
                        if (serverType == 'S')
                        {
                            udpPort = SERVER_S_PORT;
                            std::cout << "Found " << bookCode << " located at ServerS. Send to ServerS." << std::endl;
                            sendStatus = true;
                        }
                        else if (serverType == 'L')
                        {
                            udpPort = SERVER_L_PORT;
                            std::cout << "Found " << bookCode << " located at ServerL. Send to ServerL." << std::endl;

                            sendStatus = true;
                        }
                        else if (serverType == 'H')
                        {
                            udpPort = SERVER_H_PORT;
                            std::cout << "Found " << bookCode << " located at ServerH. Send to ServerH." << std::endl;
                            sendStatus = true;
                        }
                        else
                        {
                            std::cout << "Did not find " << bookCode << " in the book code list." << std::endl;
                            strcpy(bufUDP, "-1");
                        }
                        if (sendStatus)
                        {
                            struct sockaddr_in M_addr;
                            M_addr.sin_family = AF_INET;
                            M_addr.sin_port = htons(udpPort);
                            inet_aton(HOST_NAME, &M_addr.sin_addr);

                            std::string udpMessage = std::string(bufTCP) + " " + username;
                            strcpy(bufTCP, udpMessage.c_str());
                            if ((numbytesUDP = sendto(sockfdUDP, bufTCP, strlen(bufTCP), 0, (sockaddr *)&M_addr, sizeof(M_addr))) == -1)
                            {
                                perror("talker: sendto");
                                exit(1);
                            }

                            if ((numbytesUDP = recvfrom(sockfdUDP, bufUDP, MAXBUFLEN - 1, 0, (struct sockaddr *)&their_addrUDP, &addr_lenUDP)) == -1)
                            {
                                perror("recvfrom");
                                exit(1);
                            }
                            bufUDP[numbytesUDP] = '\0';
                            std::cout << "Main Server received from server " << bookCode[0] << " the book status result using UDP over port " << SERVER_M_UDP_PORT << ":" << std::endl;
                            if (username == "firns")
                            {
                                std::cout << "Number of books " << bookCode << " available is: " << atoi(bufUDP) << "." << std::endl;
                            }
                            else
                            {
                                if (atoi(bufUDP) > 0)
                                {
                                    std::cout << bookCode << " is available." << std::endl;
                                }
                                else
                                {
                                    std::cout << bookCode << " is NOT available." << std::endl;
                                }
                            }
                        }
                        if (send(new_fd, bufUDP, strlen(bufUDP), 0) == -1)
                        {
                            perror("send");
                        }
                        std::cout << "Main Server sent the book status to the client." << std::endl;
                    }
                }
                else
                {
                    std::cout << "Password " << password << " does not match the username. Send a reply to the client." << std::endl;
                    response = "p";
                    if (send(new_fd, response.c_str(), response.size(), 0) == -1)
                    {
                        perror("send");
                    }
                }
            }
            else
            {
                std::cout << username << " is not registered. Send a reply to the client." << std::endl;
                response = "n";
                if (send(new_fd, response.c_str(), response.size(), 0) == -1)
                {
                    perror("send");
                }
            }
        }
    }
    close(sockfdTCP);
    close(new_fd);

    close(sockfdUDP);

    return 0;
}