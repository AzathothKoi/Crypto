#ifndef SYMMETRIC_H
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <type.h>
#include <tools.h>
void encrypt(uint8 *algorithm, uint8 *data, int dataLen, uint8 *key, uint8 *iv);
void decrypt(uint8 *algorithm, uint8 *data, int dataLen, uint8 *key, uint8 *iv);
void encryptFile(uint8 *algorithm, uint8 *key, uint8 *iv, uint8 *inFile, uint8 *outFile);
void decryptFile(uint8 *algorithm, uint8 *key, uint8 *iv, uint8 *inFile, uint8 *outFile);
extern void symmetricHandler(char *argv[], int enc);
#define SYMMETRIC_H
#endif