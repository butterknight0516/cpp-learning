#include "file_utils.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    if (argc < 2){
        cout << "请至少输入一个文件路径\n";
        return 0;
    }
    for (int i = 1;i < argc;i++){
        cout << argv[i] << "文件字节数 " << getFileByteCount(argv[i]) << endl;
        cout << argv[i] << "文件行数 " << getFileLineCount(argv[i]) << endl << endl;
    }

    return 0;
}