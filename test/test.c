#include "..\include\xxlog.h"

int main(){
    for (size_t i = 0; i < 0xFF; i++)
    {
        xxlog_print(XXLOG_INFO, XXLOG_UART, "testlong  %d \n", i);
    }
    xxlog_print(XXLOG_INFO, XXLOG_UART, "\n");
}