#include "unique_fd.hpp"
#include <iostream>
#include <fcntl.h> // open()
#include <unistd.h> // read(), write(), close()
#include <memory>
using namespace std;

UniqueFd::UniqueFd(int fd){
    if(fd >= 0) this->fd_ = fd;
}

UniqueFd::UniqueFd(UniqueFd && other){
    this->fd_ = std::move(other.fd_);
    //move不会改变原来的值
    other.fd_ = kInvalidFd;
}

UniqueFd& UniqueFd::operator=(UniqueFd&& other){
    /*
    注意，这里要关闭this已有fd指向的文件。
    如果不先关闭文件，移动赋值只会删除存放 4 的那个整数，
    操作系统中的文件仍然开着，导致资源泄漏。
    构造函数不需要关，因为构造函数正在创建一个新对象，这个对象还没有持有文件
    */
    if (this != &other) {
        // 先关闭当前对象持有的文件
        if (this->fd_ >= 0) {
            //在linux中，socket的fd也能通过close关闭
            close(this->fd_);
        }

        // 接管 other 的资源，other.fp 随后为空
        this->fd_ = std::move(other.fd_);
        other.fd_ = kInvalidFd;
    }

    return *this;
}

int UniqueFd::get() const{
    return this->fd_;
}

UniqueFd::~UniqueFd(){
    //注意：析构函数有坑，移动赋值之后原来的指针变成空的，需要判断一下是否为空
    if(this->fd_ == kInvalidFd)   return;
    close(this->fd_);
}