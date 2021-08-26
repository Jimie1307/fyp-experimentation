// this file is me trying to understand File Source to use it in FYP...maybe
// Crypto++ library is used here

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <psapi.h>
#include <chrono>

#include "argnames.h"
#include "algparam.h"
#include "osrng.h"
#include "default.h"
#include "cryptlib.h"
#include "filters.h"
#include "lea.h"
#include "files.h"
#include "twofish.h"
#include "hex.h"
#include "tea.h"

//using CryptoPP::AutoSeededRandomPool;

using namespace CryptoPP;
using namespace std;

void DecryptFile(const char* fin, const char* fout, SecByteBlock key, SecByteBlock iv) {


    try
    {
        CBC_Mode< Twofish >::Decryption Decrypt;
        Decrypt.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter removes
        //  padding as required.
        FileSource s(fin, true,
            new StreamTransformationFilter(Decrypt,
                new FileSink(fout)
            ) // StreamTransformationFilter
        ); // FileSource

    }
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

}

void EncryptFile(const char* fin, const char* fout, SecByteBlock key, SecByteBlock iv) {

//
//Encryption with CBC
//
try
{

    CBC_Mode< Twofish >::Encryption Encrypt;
    Encrypt.SetKeyWithIV(key, key.size(), iv);

    // The StreamTransformationFilter adds padding
    //  as required. ECB and CBC Mode must be padded
    //  to the block size of the cipher.
    FileSource s(fin, true,
        new StreamTransformationFilter(Encrypt,
            new FileSink(fout)
        ) // StreamTransformationFilter
    ); // FileSource
}
catch (const CryptoPP::Exception& e)
{
    std::cerr << e.what() << std::endl;
    exit(1);
}

}

// fucntion to write the time on txt file
void writeTime(double cpu_clock, chrono::duration <double> wall_time, const char* filename) {
    fstream my_file;
    my_file.open(filename, fstream::app);
    if (!my_file) {
        cout << "File not created";
    }
    else {
            my_file << "-----------------------------" << endl;
            my_file << "\n\nIt took " << cpu_clock << " seconds to do 100 trials [CPU clock]" << endl;
            my_file << "\n\nIt took " << wall_time.count() << " seconds to do 100 trials [Wall clock]" << endl;
    }

    my_file.close();
}

int main(int argc, char* argv[])
{
    
    //declare variables
    string str;
    string input_key;
    float x, y;
    clock_t requiredTime;


    // initialise variables
    const char* fileTitle = "Time-trials-TWOFISH256-ODS-encrypt.txt";
    
    const char* fileSource = "Dicionrio_Microdados_Enem_2016.ods";
    
    const char* fileSink = "encrypted-ODS-TWOFISH256.enc";


    /*
    FYI, Wan:
    128 key= 16
    192 key= 24 
    256 key= 32 

    AutoSeededRandomPool prng;
    prng.GenerateBlock(iv, iv.size());
    */  


    // initialise key and iv
    // it is fixed for experimentation purposes only
    string password = "pArkj!m!n_13";
    string fixed_iv = "B151356C2E75690825DFE4ED29A1C495";
    SecByteBlock key((const unsigned char*)(password.data()), 32);
    SecByteBlock iv((const unsigned char*)(fixed_iv.data()), Twofish::BLOCKSIZE);


    // starting clock cpu time
    clock_t startcputime = clock();
    auto wcts = chrono::system_clock::now();
    for (int i = 1; i < 101; i++){

        try {
            EncryptFile(fileSource, fileSink, key, iv);
            //DecryptFile(fileSource, fileSink, key, iv);
        }
        catch (const Exception& ex) {
            cout << "\n\n Something went wrong";
            cerr << ex.what() << endl;

        }
    }
   

    // calcaulting the real time required time 
    double cpu_duration = (clock() - startcputime) / (double)CLOCKS_PER_SEC;
    chrono::duration <double> wctduration = (chrono::system_clock::now() - wcts);
    writeTime(cpu_duration, wctduration, fileTitle);

    cout << "\n\nIt took " << cpu_duration << " seconds to do 100 trials [CPU clock]" << endl;
    cout << "\n\nIt took " << wctduration.count() << " seconds to do 100 trials [Wall clock]" << endl;
    

 
    return 0;
}