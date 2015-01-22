#include<stdint.h>
#include<stdlib.h>

// 注意这里对大端和小端的判断方法,参考资料： http://stackoverflow.com/questions/2437283/c-c-packing-signed-char-into-int
uint32_t pack_uint32(char* data) {
    uint16_t num = 0x0102;
    char c2[2] = {0x01, 0x02};
    uint16_t num2 = *(uint16_t*)c2;
    if (num == num2) {
        return *(uint32_t*)data;
    }
    char c4[4] = {data[3], data[2], data[1], data[0]};

    return *(uint32_t*)c4;
}


