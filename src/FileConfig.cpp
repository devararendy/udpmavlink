#include "FileConfig.hpp"
using namespace std;

FileConfig::FileConfig(const char * file) {
    // fp=fopen(file,"rw");
    strcpy(fname, file);
}

FileConfig::~FileConfig() {
    fclose(fp);
}
int FileConfig::writeStruct(char * in, size_t size)
{
    fp = fopen(fname, "wb");
    if(fp==NULL)
        return -1;
    if(fwrite(in, 1, size, fp)!=size)
    {
        printf("Unable to write data..!\r\n");
    }
    fclose(fp);
    return size;
}
int FileConfig::readStruct(char * out, size_t size)
{
    fp = fopen (fname , "rb" );
    if (fp==NULL)
    {
        fputs ("File error ",stderr);
        exit (1);
        return-1;
    }

    // obtain file size:
    fseek (fp , 0 , SEEK_END);
    size_t lSize = ftell (fp);
    rewind (fp);
    if(lSize > size)
    {
        printf("Unable to load config, not enough space on struct");
        printf("Struct Size : %d, file Size : %d\r\n", size, lSize);
        return -2;
    }
        
    // copy the file into the buffer:
    int result = fread (out,1,lSize,fp);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
    /* the whole file is now loaded in the memory buffer. */
    
    // terminate
    fclose (fp);
    // free (buffer);
    return 0;
}