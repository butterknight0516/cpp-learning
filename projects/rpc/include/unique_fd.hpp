#pragma once


class UniqueFd{
    static constexpr int kInvalidFd = -1; // 所有对象共用的常量
    int fd_ = kInvalidFd; 
    
public:
    explicit UniqueFd(int fd);

    UniqueFd(UniqueFd && other);

    UniqueFd(const UniqueFd&) = delete;
    
    UniqueFd& operator=(const UniqueFd&) = delete;

    UniqueFd& operator=(UniqueFd&& other);

    //获取fd
    int get() const;

    ~UniqueFd();
};