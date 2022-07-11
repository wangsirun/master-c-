#include "log.h"

int main(int argc, char const *argv[])
{
    /* code */
    for (size_t i = 0; i < 100; i++)
    {
        LOG_DEBUG("test");
    }
    return 0;
}
