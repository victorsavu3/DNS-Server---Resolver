#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include "dnsfunctions.h"

char dns_server[20];
int main(int argc, char const *argv[])
{
    unsigned char hostname[100];
    int reqtype;
    ghreply hostdetails, tmphd;
    hostdetails.type = -2;
    if(argc < 4) {
        fprintf(stderr, "Usage:  %s <DNS Server> <Hostname>"
                "<Type (A, NS, MX, SOA)>\n", argv[0]);
        exit(1);
    }
    strncpy(dns_server,argv[1],20);
    strncpy(hostname,argv[2],100);

    if(strcmp("MX", argv[3]) == 0)
        reqtype = T_MX;
    else if (strcmp("A", argv[3]) == 0)
        reqtype = T_A;
    else if (strcmp("SOA", argv[3]) == 0)
        reqtype = T_SOA;
    else if (strcmp("NS", argv[3]) == 0)
        reqtype = T_NS;

    hostdetails = ngethostbyname(hostname,dns_server,reqtype,1);
    hostname[strlen(hostname)-1] = '\0';
    return 0;
}

