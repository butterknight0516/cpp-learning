#include <iostream>
#include <fcntl.h> // open()
#include <unistd.h> // read(), write(), close()
using namespace std;

class FileDescriptor{
    
};

int main(void){
    int fd = open("/home/butterknight/cpp-learning/cpp-learning/template.cpp", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[128];
    ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        std::cout << buffer;
    }

    close(fd);
    return 0;
}