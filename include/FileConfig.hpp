#pragma once
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <string>

class FileConfig {

public:
    FileConfig(const char * file);
    ~FileConfig();
    int writeStruct(char * in, size_t size);
    int readStruct(char * out, size_t size);
private:
    FILE *  fp;
    char fname[100];
};