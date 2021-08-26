#pragma once

#ifndef learning-FileSource-cryptopp
#define learning-FileSource-cryptopp

#include <iostream>
#include "lea.h"
#include "files.h"
#include "twofish.h"
#include "osrng.h"
#include "files.h"
#include "hex.h"
#include "default.h"
#include "cryptlib.h"
#include "default.h"

using namespace std;
using namespace CryptoPP;

class Crypt
{
	public:
		Crypt() {};
		~Crypt() {};

		int init() {};
		void EncryptFile(const char* fin, const char* fout, SecByteBlock key, SecByteBlock iv) {};
		void DecryptFile(const char* fin, const char* fout, string password) {};
};
#endif 
