#include <hash.h>

void hash(uint8 *algorithm, uint8 *data, size_t len)
{
    const EVP_MD *md = EVP_get_digestbyname(algorithm);
    EVP_MD_CTX *mdctx;
    uint8 md_value[EVP_MAX_MD_SIZE];
    uint32 md_len, i;

    if (md == NULL)
    {
        printf("Unknown message digest %s\n");
        return;
    }

    mdctx = EVP_MD_CTX_new();
    if (!EVP_DigestInit_ex2(mdctx, md, NULL))
    {
        printf("Message digest initialization failed.\n");
        EVP_MD_CTX_free(mdctx);
        return;
    }
    if (!EVP_DigestUpdate(mdctx, data, len))
    {
        printf("Message digest update failed.\n");
        EVP_MD_CTX_free(mdctx);
        return;
    }
    if (!EVP_DigestFinal_ex(mdctx, md_value, &md_len))
    {
        printf("Message digest finalization failed.\n");
        EVP_MD_CTX_free(mdctx);
        return;
    }
    EVP_MD_CTX_free(mdctx);

    printf("Digest is: ");
    for (i = 0; i < md_len; i++)
    {
        printf("%02x", md_value[i]);
    }
    printf("\n");
}

void fileHash(uint8 *algorithm, uint8 *file)
{
    int n = 18 + strlen(algorithm) + strlen(file);
    uint8 command[n];
    sprintf(command, "%s%s%s%s", "./openssl dgst -", algorithm, " ", file);
    system(command);
}

void hashHandler(char *argv[])
{
    uint8 *algorithm = argv[2];
    uint8 *mode = argv[3];
    uint8 *in = argv[4];
    if (strcmp(mode, "data") == 0)
    {
        int textLen = strlen(in);
        uint8 data[textLen/2];
        int re = hexStr2byte(in, data);
        if (re == 0)
        {
            hash(algorithm, data, textLen / 2);
        }
    }
    else if (strcmp(mode, "file") == 0)
    {
        fileHash(algorithm, in);
    }
    else
    {
        printf("Choose data or file\n");
    }
}