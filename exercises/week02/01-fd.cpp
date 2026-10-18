/*
写一个 FileDescriptor 类，只管理一个 Linux 文件描述符：
构造接收 fd，析构释放，禁止拷贝，支持移动；移动后原对象不再拥有 fd。
*/
#include <iostream>
#include <fcntl.h> // open()
#include <unistd.h> // read(), write(), close()
#include <memory>
using namespace std;

class FileDescriptor{
    unique_ptr<int> fp;
    
public:
    FileDescriptor(char *path){
        int fd = open(path, O_RDONLY);
        if (fd == -1) perror("open");
        fp = make_unique<int>(fd);
    }

    FileDescriptor(FileDescriptor && other){
        fp = std::move(other.fp);
    }

    FileDescriptor& operator=(FileDescriptor&& other) noexcept {
        /*
        注意，这里要关闭this已有fp指向的文件。
        如果不先关闭文件，unique_ptr<int> 的移动赋值只会删除存放 4 的那个整数，
        操作系统中的文件仍然开着，导致资源泄漏。
        构造函数不需要关，因为构造函数正在创建一个新对象，这个对象还没有持有文件
        */
        if (this != &other) {
            // 先关闭当前对象持有的文件
            if (fp && *fp >= 0) {
                close(*fp);
            }

            // 接管 other 的资源，other.fp 随后为空
            fp = std::move(other.fp);
        }

        return *this;
    }

    void print_file_content(){
        if(fp == nullptr)   return;
        char buffer[128];
        ssize_t bytes = read(*fp, buffer, sizeof(buffer) - 1);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            std::cout << buffer;
        }
    }

    int get() const{
        //获取fd
        if(fp == nullptr)   return -1;
        return *(this->fp);
    }

    ~FileDescriptor(){
        //注意：析构函数有坑，移动赋值之后原来的指针变成空的，需要判断一下是否为空
        if(fp == nullptr)   return;
        close(*fp);
    }
};

int main(void){
    char path[] = "/home/butterknight/cpp-learning/cpp-learning/template.cpp";
    FileDescriptor f1(path);
    //FileDescriptor f2(std::move(f1));
    FileDescriptor f2 = std::move(f1);

    cout << "-------------------\n";
    f1.print_file_content();
    cout << "-------------------\n";
    f2.print_file_content();
    /*
    FileDescriptor f2 = f1;
    编译报错：function "FileDescriptor::FileDescriptor(const FileDescriptor &)" (declared implicitly) cannot be referenced -- it is a deleted function
    */
    return 0;
}