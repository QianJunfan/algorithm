/* 0017 - letter combinations of a phone number (dfs)
 *      - from https://github.com/qianjunfan
 */

const char *map[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

void backtrack(const char *digits, int index, char *path, char ***result, int *size)
{
        if (digits[index] == '\0') {
                (*size)++;

                *result = realloc(*result, (*size) * sizeof(char *));

                (*result)[(*size) - 1] = strdup(path);

                return;
        }

        const char *letters = map[digits[index] - '0'];

        for (int i = 0; letters[i] != '\0'; i++) {
                path[index] = letters[i];
                backtrack(digits, index + 1, path, result, size);
        }
}

char **letterCombinations(char *digits, int *size)
{
        *size = 0;
        int len = strlen(digits);
        if (len == 0)
                return NULL;
       
        char **result = NULL;

        char path[len + 1];

        path[len] = '\0';

        backtrack(digits, 0, path, &result, size);

        return result;
}

