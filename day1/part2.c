#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Open file
    FILE *file = fopen("input.txt", "r");
    if (file)
    {
        // Check the size of the whole file
        fseek(file, 0, SEEK_END);
        int end = ftell(file);
        fseek(file, 0, SEEK_SET);

        // Allocate space for the file plus a string terminator
        char *content = malloc(end + 1);

        // Read the whole file into content and null-terminate the string
        fread((void *)content, 1, end, file);
        content[end] = '\0';

        const char *numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        const int lengths[9] = {3, 3, 5, 4, 4, 3, 5, 5, 4};

        for (int i = 0; i < end; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (strncmp(content + i, numbers[j], lengths[j]) == 0)
                {
                    content[i] = j + 1 + '0';
                    break;
                }
            }
        }

        int result = 0;
        int start = 0;

        while (content[start] != '\0')
        {
            int curr = start;
            while (content[curr] < '0' || content[curr] > '9')
            {
                curr++;
            }
            int first = content[curr] - '0';

            int last;
            while (content[start] != '\n' && content[start] != '\0')
            {
                if (content[start] >= '0' && content[start] <= '9')
                {
                    last = content[start] - '0';
                }
                start++;
            }
            if (content[start] != '\0')
            {
                start++;
            }

            result += first * 10 + last;
        }

        // Print the whole string
        printf("%d\n", result);

        // Clean up
        free(content);
        fclose(file);
    }
    return 0;
}