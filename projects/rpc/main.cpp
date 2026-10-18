#include "unique_fd.hpp"
#include <iostream>
#include <fcntl.h> // open()
#include <unistd.h> // read(), write(), close()
using namespace std;

int main(int argc, char* argv[]){
    if (argc < 2){
        cout << "请至少输入一个文件路径\n";
        return 0;
    }
    for (int i = 1;i < argc;i++){
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1) perror("open");
        UniqueFd f1(fd);
        cout << f1.get() << endl;
        UniqueFd f2 = std::move(f1);
        cout << f1.get() << endl;
        cout << f2.get() << endl;
    }

    return 0;
}