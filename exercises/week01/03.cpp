#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    //注意：第一个参数是./03
    if (argc < 2){
        cout << "请至少输入一个文件路径\n";
        return 0;
    }
    for (int i = 1;i < argc;i++){
        ifstream istr(argv[i], ios::binary);
        if (!istr){
            cout << argv[i] << "文件打开失败，请检查文件是否存在\n";
            continue;           
        }

        //istr.tellg()统计文件字节数,     istr.seekg(-3, ios::end)表示将指针移动到结束位置前3字节
        istr.seekg(0, ios::end);
        streampos sz = istr.tellg();
        istr.seekg(0, ios::beg);


        string line;
        int line_cnt = 0;
        while(getline(istr, line))  line_cnt++;


        cout << argv[i] << "文件字节数 " << sz << endl;
        cout << argv[i] << "文件行数 " << line_cnt << endl << endl;
    }

    return 0;
}