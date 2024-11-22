#ifndef MAC_H
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/params.h>
#include <openssl/core_names.h>
#include <type.h>
#include <tools.h>

void mac(uint8 *mac, uint8 *algorithm, uint8 *key, uint8 *data, int keyLen, int dataLen);
void fileMac(uint8 *mac, uint8 *algorithm, uint8 *key, uint8 *file);
extern void macHandler(char *argv[]);

#define MAC_H
#endif