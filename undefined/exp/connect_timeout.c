/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file connect_timeout.c
 * @author gaowei08(com@baidu.com)
 * @date 2014/05/19 18:05:47
 * @brief 
 *  
 **/
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd;
    struct sockaddr_in addr;
    struct timeval timeo = {3, 0};
    socklen_t len = sizeof(timeo);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (argc == 4)
        timeo.tv_sec = atoi(argv[3]);
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeo, len);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        if (errno == EINPROGRESS) {
            fprintf(stderr, "timeout\n");
            return -1;
        }
        perror("connect");
        return 0;
    }
    printf("connected\n");

    return 0;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
