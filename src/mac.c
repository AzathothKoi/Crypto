#include <mac.h>
void mac(uint8 *mac, uint8 *algorithm, uint8 *key, uint8 *data, int keyLen, int dataLen)
{
    EVP_MAC *_evp_mac = NULL;
    EVP_MAC_CTX *_evp_mac_ctx = NULL;
    EVP_MD_CTX *_evp_md_ctx = NULL;
    size_t out_len = 0;
    OSSL_PARAM params[3];
    size_t params_n = 0;
    uint8 out[128];

    _evp_mac = EVP_MAC_fetch(NULL, mac, NULL);
    if (_evp_mac == NULL)
    {
        fprintf(stderr, "EVP_MAC_fetch() returned NULL\n");
        goto free_mem;
    }
    /* Create a context for the HMAC operation */
    _evp_mac_ctx = EVP_MAC_CTX_new(_evp_mac);
    if (_evp_mac_ctx == NULL)
    {
        fprintf(stderr, "EVP_MAC_CTX_new() returned NULL\n");
        goto free_mem;
    }
    if ((strcmp(mac, "HMAC") == 0) || (strcmp(mac, "hmac") == 0))
    {
        params[params_n++] = OSSL_PARAM_construct_utf8_string("digest", (char *)algorithm, 0);
    }
    else if ((strcmp(mac, "CMAC") == 0) || (strcmp(mac, "cmac") == 0))
    {
        params[params_n++] = OSSL_PARAM_construct_utf8_string("cipher", (char *)algorithm, 0);
    }
    else
    {
        goto free_mem;
    }

    params[params_n] = OSSL_PARAM_construct_end();
    if (!EVP_MAC_init(_evp_mac_ctx, key, keyLen, params))
    {
        fprintf(stderr, "EVP_MAC_init() failed\n");
        goto free_mem;
    }

    /* Make one or more calls to process the data to be authenticated */
    if (!EVP_MAC_update(_evp_mac_ctx, data, dataLen))
    {
        fprintf(stderr, "EVP_MAC_update() failed\n");
        goto free_mem;
    }

    /* Make a call to the final with a NULL buffer to get the length of the MAC */
    if (!EVP_MAC_final(_evp_mac_ctx, NULL, &out_len, 0))
    {
        fprintf(stderr, "EVP_MAC_final() failed\n");
        goto free_mem;
    }
    if (!EVP_MAC_final(_evp_mac_ctx, out, &out_len, out_len))
    {
        fprintf(stderr, "EVP_MAC_final() failed\n");
        goto free_mem;
    }

    for (int i = 0; i < out_len; i++)
    {
        printf("%02x", out[i]);
    }

    printf("\n");

free_mem:
    EVP_MD_CTX_free(_evp_md_ctx);
    EVP_MAC_CTX_free(_evp_mac_ctx);
    EVP_MAC_free(_evp_mac);
}

void fileMac(uint8 *mac, uint8 *algorithm, uint8 *key, uint8 *file)
{
    int commandLen = 49 + strlen(algorithm) + strlen(key) + strlen(file);
    uint8 command[commandLen];
    if ((strcmp(mac, "HMAC") == 0) || (strcmp(mac, "hmac") == 0))
    {
        sprintf(command, "%s%s%s%s%s%s%s", "./openssl mac -digest ", algorithm, " -macopt hexkey:", key, " -in ", file, " hmac");
    }
    else if ((strcmp(mac, "CMAC") == 0) || (strcmp(mac, "cmac") == 0))
    {
        sprintf(command, "%s%s%s%s%s%s%s", "./openssl mac -cipher ", algorithm, " -macopt hexkey:", key, " -in ", file, " cmac");
    }
    else
    {
        return;
    }
    system(command);
}

void macHandler(char *argv[])
{
    uint8 *algorithm = argv[2];
    uint8 *mode = argv[3];
    uint8 *key = argv[4];
    uint8 *in = argv[5];
    if (strcmp(mode, "data") == 0)
    {
        int textLen = strlen(in);
        int keyLen = strlen(key);
        uint8 data[textLen / 2];
        uint8 keyBytes[keyLen / 2];
        int re1 = hexStr2byte(in, data);
        int re2 = hexStr2byte(key, keyBytes);
        printf("%d %d\n", re1, re2);
        if ((re1 == 0) && (re2 == 0))
        {
            mac(argv[1], algorithm, keyBytes, data, keyLen / 2, textLen / 2);
        }
    }
    else if (strcmp(mode, "file") == 0)
    {
        fileMac(argv[1], algorithm, key, in);
    }
    else
    {
        printf("Choose data or file\n");
    }
}