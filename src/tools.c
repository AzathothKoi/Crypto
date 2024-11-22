#include <tools.h>

int hexStr2byte(uint8 *hexStr, uint8 *data)
{
    int strLen = strlen(hexStr);
    if (strLen < 1 || strLen % 2 != 0)
    {
        printf("HexStr length incorrect\n");
        return -1;
    }
    for (int i = 0; i < strLen; i += 2)
    {
        uint8 high = hex2int(hexStr[i]);
        uint8 low = hex2int(hexStr[i + 1]);
        data[i / 2] = (high * 16 + low) & 0xFF;
    }
    return 0;
}

uint8 hex2int(uint8 c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 10;
    }
    else if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }
    else
    {
        return 0;
    }
}