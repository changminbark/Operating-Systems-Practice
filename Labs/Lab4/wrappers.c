#include "wrappers.h"

/* Error handling function */
void err_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

pid_t Fork(void) {
    pid_t pid;
    if ((pid = fork()) < 0) {
        err_exit("Fork error");
    }
    return pid;
}

void Pipe(int pipefd[2]) {
    if (pipe(pipefd) < 0) {
        err_exit("Pipe error");
    }
}

pid_t Wait(int *wstatus) {
    pid_t pid;
    if ((pid = wait(wstatus)) < 0) {
        err_exit("Wait error");
    }
    return pid;
}

pid_t Waitpid(pid_t pid, int *wstatus, int options) {
    pid_t ret_pid;
    if ((ret_pid = waitpid(pid, wstatus, options)) < 0) {
        err_exit("Waitpid error");
    }
    return ret_pid;
}

int Open(const char *pathname, int flags, mode_t mode) {
    int fd;
    if ((fd = open(pathname, flags, mode)) < 0) {
        err_exit("Open error");
    }
    return fd;
}

void Close(int fd) {
    if (close(fd) < 0) {
        err_exit("Close error");
    }
}

ssize_t Write(int fd, const void *buf, size_t count) {
    ssize_t bytes;
    if ((bytes = write(fd, buf, count)) < 0) {
        err_exit("Write error");
    }
    return bytes;
}

ssize_t Read(int fd, void *buf, size_t count) {
    ssize_t bytes;
    if ((bytes = read(fd, buf, count)) < 0) {
        err_exit("Read error");
    }
    return bytes;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    if (connect(sockfd, addr, addrlen) < 0) {
        err_exit("Connect error");
    }
    return 0;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    if (bind(sockfd, addr, addrlen) < 0) {
        err_exit("Bind error");
    }
    return 0;
}

int Listen(int sockfd, int backlog) {
    if (listen(sockfd, backlog) < 0) {
        err_exit("Listen error");
    }
    return 0;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int connfd;
    if ((connfd = accept(sockfd, addr, addrlen)) < 0) {
        err_exit("Accept error");
    }
    return connfd;
}

ssize_t Send(int sockfd, const void *buf, size_t len, int flags) {
    ssize_t bytes;
    if ((bytes = send(sockfd, buf, len, flags)) < 0) {
        err_exit("Send error");
    }
    return bytes;
}

ssize_t Recv(int sockfd, void *buf, size_t len, int flags) {
    ssize_t bytes;
    // Only receive message/string without null terminator
    if ((bytes = recv(sockfd, buf, len - 1, flags)) < 0) {
        err_exit("Recv error");
    }
    // Manually add null terminator
    ((char *)buf)[bytes] = '\0';
    return bytes;
}
