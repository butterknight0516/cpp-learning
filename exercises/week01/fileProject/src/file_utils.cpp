#include "file_utils.h"
#include <fstream>
#include <iostream>
using namespace std;

int getFileLineCount(const char* file_path){
    ifstream in(file_path, ios::binary);
    if (!in){
        cerr << file_path << "文件打开失败，请检查文件是否存在\n";
        return -1;           
    }

    string line;
    int line_cnt = 0;
    while(getline(in, line))  line_cnt++;
    return line_cnt;
}

std::streampos getFileByteCount(const char* file_path){
    ifstream in(file_path, ios::binary);
    if (!in){
        cerr << file_path << "文件打开失败，请检查文件是否存在\n";
        return streampos(-1);           
    }

    //in.tellg()统计文件字节数,     in.seekg(-3, ios::end)表示将指针移动到结束位置前3字节
    in.seekg(0, ios::end);
    streampos sz = in.tellg();
    return sz;
}