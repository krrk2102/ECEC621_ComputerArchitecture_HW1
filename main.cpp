#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BaseCache.h"
using namespace std;

int main(int argc, char **argv) {
    string inp_line, parsed_line;
    string command;
    unsigned int address, data;
    uint32_t cacheSize, associativity, blockSize;
    argv[1] = "131072";
    cacheSize = atoi(argv[1]);
    argv[2] = "4";
    associativity = atoi(argv[2]);
    argv[3] = "128";
    blockSize = atoi(argv[3]);
    argv[4] = "/Users/wushangqi/assignment/input2.txt";
    ifstream fp_inp(argv[4]);

    BaseCache BaseCache(cacheSize, associativity, blockSize);
    
    if(fp_inp.is_open()) {
        while(getline(fp_inp, inp_line)) {
            stringstream inp_string(inp_line);
            if(getline(inp_string,parsed_line, ' '))
            command = parsed_line;
            if(getline(inp_string,parsed_line, ' '))
            address = stoul(parsed_line, NULL, 16);
            if (!(command.compare("w"))) {
                if(getline(inp_string,parsed_line, ' ')) {
                    data = stoul(parsed_line, NULL, 16);
                }
            }
            //Issue read/write command
            if (!(command.compare("w"))) {
                if(BaseCache.write(address, data)) {
                    cout <<"Write Hit : addr:0x"<<hex<<address;
                    cout <<"     data:0x"<<hex<<data<<"\n";
                } else {
                    cout <<"Write miss: addr:0x"<<hex<<address;
                    cout <<"     data:0x"<<hex<<data<<"\n";
                }
            }
            if (!(command.compare("r"))) {
                if(BaseCache.read(address, &data)) {
                    cout <<"Read Hit  : addr:0x"<<hex<<address;
                    cout <<"     data:0x"<<hex<<data<<endl;
                } else {
                    cout <<"Read miss : addr:0x"<<hex<<address;
                    cout <<"     data:Unavailable"<<endl;
                }
            }
        }
        fp_inp.close();
    }
    cout <<endl;
    cout << "Read Hits (HitRate): "<<hex<<BaseCache.getReadHits()<<" ("<<dec<<(int)BaseCache.getReadHitRate()<<"%)"<<endl;
    cout << "Read Misses (MissRate): "<<hex<<BaseCache.getReadMisses() <<" ("<<dec<<(int)BaseCache.getReadMissRate()<<"%)"<<endl;
    cout << "Write Hits (HitRate): "<<hex<<BaseCache.getWriteHits()<<" ("<<dec<<(int)BaseCache.getWriteHitRate()<<"%)"<<endl;
    cout << "Write Misses (MissRate): "<<hex<<BaseCache.getWriteMisses() <<" ("<<dec<<(int)BaseCache.getWriteMissRate()<<"%)"<<endl;
    cout << "Overall Hit Rate: "<<dec<<(int)BaseCache.getOverallHitRate() <<"%" << endl;
    cout << "Overall Miss Rate: "<<dec<<(int)BaseCache.getOverallMissRate()<<"%"<<endl;
    return 1;
}

