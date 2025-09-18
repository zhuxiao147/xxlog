#include "../include/xxlog.h"

int main(){
    for (size_t i = 0x10; i < 0xFF; i++)
    {
        xxlog_print(XXLOG_INFO, XXLOG_UART, "abcdefghi%d %d %d %d \n", i, i+1, i+2, i+3);
        xxlog_print(XXLOG_INFO, XXLOG_UART, "abcdefghi%dabcdefghiabcdefghiabcdefghi%dbcdefghiabcdefghiabcdefghi%dabcdefghiabcdefghiabcdefghi%d \n", i, i+1, i+2, i+3);
        xxlog_print(XXLOG_INFO, XXLOG_UART, "%d%d%d%d \n", i, i+1, i+2, i+3);
        xxlog_print(XXLOG_INFO, XXLOG_UART, "%04d %04d %08d %05d \n", i, i+1, i+2, i+3);
    }
    xxlog_print(XXLOG_INFO, XXLOG_UART, "\n");
}