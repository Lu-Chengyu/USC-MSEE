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

#define SERVER_L_PORT "42886"
#define SERVER_M_UDP_PORT 44886
#define HOST_NAME "127.0.0.1"
#define MAXBUFLEN 1000

int main()
{
   std::string filename = "literature.txt";
   std::ifstream file(filename);
   std::map<std::string, int> bookMap;
   std::string line;

   while (getline(file, line))
   {
      std::istringstream iss(line);
      std::string bookNumber;
      int count;
      if (!(iss >> bookNumber >> count))
      {
         std::cerr << "file error: " << line << std::endl;
         continue;
      }
      bookNumber.pop_back();
      bookMap[bookNumber] = count;
   }
   file.close();

   // refers to Beej's guide
   int sockfd;
   struct addrinfo hints, *servinfo, *p;
   int rv;

   int yes = 1;
   int numbytes;
   struct sockaddr_storage their_addr;
   char buf[MAXBUFLEN];
   socklen_t addr_len;

   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_DGRAM;

   if ((rv = getaddrinfo(HOST_NAME, SERVER_L_PORT, &hints, &servinfo)) != 0)
   {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      return 1;
   }

   // loop through all the results and make a socket
   for (p = servinfo; p != NULL; p = p->ai_next)
   {
      if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
      {
         perror("talker: socket");
         continue;
      }
      if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
      {
         perror("setsockopt");
         exit(1);
      }
      if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
      {
         close(sockfd);
         perror("server: bind");
         continue;
      }
      break;
   }

   if (p == NULL)
   {
      fprintf(stderr, "talker: failed to create socket\n");
      return 2;
   }

   printf("ServerL is up and running using UDP on port %s.\n", SERVER_L_PORT);

   std::string message;
   for (const auto &pair : bookMap)
   {
      // Serialize the key
      uint16_t keySize = htons(pair.first.size());
      message.append(reinterpret_cast<const char *>(&keySize), sizeof(uint16_t));
      message.append(pair.first);
      // Serialize the value
      int value = htonl(pair.second);
      message.append(reinterpret_cast<const char *>(&value), sizeof(int));
   }
   const char *msg = message.c_str();

   struct sockaddr_in M_addr;
   M_addr.sin_family = AF_INET;
   M_addr.sin_port = htons(SERVER_M_UDP_PORT);
   inet_aton(HOST_NAME, &M_addr.sin_addr);

   if ((numbytes = sendto(sockfd, msg, message.size(), 0, (sockaddr *)&M_addr, sizeof(M_addr))) == -1)
   {
      perror("talker: sendto");
      exit(1);
   }

   freeaddrinfo(servinfo);

   // processing requests from the main server
   while (1)
   {
      if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0, (struct sockaddr *)&their_addr, &addr_len)) == -1)
      {
         perror("recvfrom");
         exit(1);
      }
      buf[numbytes] = '\0';
      std::string receivedData(buf);
      size_t spacePos = receivedData.find(' ');
      std::string bookCode = receivedData.substr(0, spacePos);
      std::string username = receivedData.substr(spacePos + 1);
      if (username == "firns")
      {
         std::cout << "ServerL received an inventory status request for code " << bookCode << "." << std::endl;
      }
      else
      {
         std::cout << "ServerL received " << bookCode << " code from the Main Server." << std::endl;
      }
      int response = -1;
      if (bookMap.find(bookCode) != bookMap.end())
      {
         response = bookMap[bookCode];
         if (bookMap[bookCode] > 0)
         {
            bookMap[bookCode] -= 1;
         }
      }
      if ((numbytes = sendto(sockfd, std::to_string(response).c_str(), std::to_string(response).size(), 0, (sockaddr *)&M_addr, sizeof(M_addr))) == -1)
      {
         perror("talker: sendto");
         exit(1);
      }
      if (username == "firns")
      {
         std::cout << "ServerL finished sending the inventory status to the Main server using UDP on port " << SERVER_L_PORT << "." << std::endl;
      }
      else
      {
         std::cout << "ServerL finished sending the availability status of code " << bookCode << " to the Main Server using UDP on port " << SERVER_L_PORT << "." << std::endl;
      }
   }

   close(sockfd);

   return 0;
}