#include "constants/load_constants.h"
#include "files/file_IO.h"

#include <stdio.h>

int LoadConstantFile(const char *file_name, HashTable *result)
{
    char line_buffer[KEY_LENGTH + 1 + 32];
    int constant_count = 0;

    file_t *fp = F_OPEN(file_name, READ);

    char* res = fgets(line_buffer, sizeof(char) * 10, fp);
    constant_count = atoi(line_buffer);

    char key_buffer[KEY_LENGTH];
    int32_t data_buffer;

    for (int i = 0; i < constant_count; i++)
    {
        res = fgets(line_buffer, sizeof(char) * (KEY_LENGTH + 1 + 32), fp);
        char *token = strtok(line_buffer, ":");
        if (token)
        {
            strncpy(key_buffer, token, KEY_LENGTH);
        }
        token = strtok(NULL, ":");
        if (token)
        {
            data_buffer = atoi(token);
        }

        Hash_AddEntry(result, key_buffer, data_buffer);
    }
    F_CLOSE(fp);
}
