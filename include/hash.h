#ifndef HASH_H
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <type.h>
#include <tools.h>

void hash(uint8* algorithm, uint8* data, size_t len);
void fileHash(uint8* algorithm, uint8* file);

extern void hashHandler(char *argv[]);

#define HASH_H
#endif