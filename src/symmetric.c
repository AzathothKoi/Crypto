#include <symmetric.h>

void encrypt(uint8 *algorithm, uint8 *data, int dataLen, uint8 *key, uint8 *iv)
{
    EVP_CIPHER_CTX *ctx;

    int i, len;
    int cipher_len = ((dataLen + 15) / 16) * 16;
    uint8 ciphertext[cipher_len];
    EVP_CIPHER *cipher = EVP_get_cipherbyname(algorithm);

    ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    if (1 != EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv))
    {
        printf("Message encrypt initialization failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, data, dataLen))
    {
        printf("Message encrypt update failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    {
        printf("Message encrypt final failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    EVP_CIPHER_CTX_free(ctx);
    printf("CipherText is: ");
    for (i = 0; i < cipher_len; i++)
    {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
}

void decrypt(uint8 *algorithm, uint8 *data, int dataLen, uint8 *key, uint8 *iv)
{
    EVP_CIPHER_CTX *ctx;

    int i, len;
    int cipher_len = ((dataLen + 15) / 16) * 16;
    uint8 ciphertext[cipher_len];
    EVP_CIPHER *cipher = EVP_get_cipherbyname(algorithm);

    ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    if (1 != EVP_DecryptInit_ex(ctx, cipher, NULL, key, iv))
    {
        printf("Message encrypt initialization failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    if (1 != EVP_DecryptUpdate(ctx, ciphertext, &len, data, dataLen))
    {
        printf("Message encrypt update failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    if (1 != EVP_DecryptFinal_ex(ctx, ciphertext + len, &len))
    {
        printf("Message encrypt final failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return;
    }
    EVP_CIPHER_CTX_free(ctx);
    printf("CipherText is: ");
    for (i = 0; i < cipher_len; i++)
    {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
}

void encryptFile(uint8 *algorithm, uint8 *key, uint8 *iv, uint8 *inFile, uint8 *outFile)
{
    int n = 46 + strlen(algorithm) + strlen(key) + strlen(iv) + strlen(inFile) + strlen(outFile);
    uint8 command[n];
    sprintf(command, "%s%s%s%s%s%s%s%s%s%s", "./openssl enc -e -nopad -", algorithm, " -K ", key, " -iv ", iv, " -in ", inFile, " -out ", outFile);
    system(command);
}

void decryptFile(uint8 *algorithm, uint8 *key, uint8 *iv, uint8 *inFile, uint8 *outFile)
{
    int n = 46 + strlen(algorithm) + strlen(key) + strlen(iv) + strlen(inFile) + strlen(outFile);
    uint8 command[n];
    sprintf(command, "%s%s%s%s%s%s%s%s%s%s", "./openssl enc -d -nopad -", algorithm, " -K ", key, " -iv ", iv, " -in ", inFile, " -out ", outFile);
    system(command);
}

void symmetricHandler(char *argv[], int enc)
{
    uint8 *algorithm = argv[2];
    uint8 *mode = argv[3];
    uint8 *key = argv[4];
    uint8 *iv = argv[5];
    uint8 *in = argv[6];

    if (strcmp(mode, "data") == 0)
    {
        int textLen = strlen(in);
        int keyLen = strlen(key);
        int ivLen = strlen(iv);
        uint8 data[16];
        uint8 keyBytes[16];
        uint8 ivBytes[16];

        int re1 = hexStr2byte(in, data);
        int re2 = hexStr2byte(key, keyBytes);
        int re3 = hexStr2byte(iv, ivBytes);
        if ((re1 == 0) && (re2 == 0) && (re3 == 0))
        {
            if (enc == 1)
            {
                encrypt(algorithm, data, textLen / 2, keyBytes, ivBytes);
            }
            else
            {
                decrypt(algorithm, data, textLen / 2, keyBytes, ivBytes);
            }
        }
    }
    else if (strcmp(mode, "file") == 0)
    {
        uint8 *out = argv[7];
        if (enc == 1)
        {
            encryptFile(algorithm, key, iv, in, out);
        }
        else
        {
            decryptFile(algorithm, key, iv, in, out);
        }
    }
    else
    {
        printf("Choose data or file\n");
    }
}