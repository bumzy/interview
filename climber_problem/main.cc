#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

enum { INPUT_ERROR = -1, INT_PARSE_ERROR = -1, INT_PARSE_OK = 0 };

int resolve(const char* input);
int nextInt(const char*& str, int& number);

int main(int argc, char* argv[])
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
        //TODO please add more test case here
        "0\n", //expect 0
        "1\n0,0,0\n", //expect 0
        "1\n0,0,1\n", //expect 2
        "1\n0,1,0\n", //expect 1
        "1\n1,2,0\n", //expect 2
        "2\n0,0,0\n0,0,0\n", //expect 0
        "3\n0,0,0\n0,0,0\n0,0,1\n", //expect 2
        "", //expect INPUT_ERROR
        "1\nasdf", //expect INPUT_ERROR
        "-1", //expect INPUT_ERROR
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20, 0, 0, 2, 1, 2, 0, 2, INPUT_ERROR, INPUT_ERROR, INPUT_ERROR};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        int result = resolve(input[i]);
        printf("resolve: %d %d\n", result, expectedSteps[i]);
        assert(result == expectedSteps[i]);
    }
    return 0;
}

int resolve(const char* input)
{
    if(input == NULL)
        return INPUT_ERROR;

    int totalNumber = -1, distance = 0, maxEnd = 0, vertical = 0;
    int start = -1, end = -1, height = -1, /*preStart = -1,*/ preEnd = -1, preHeight = -1;

    if(nextInt(input, totalNumber) == -1)
        return INPUT_ERROR;

    for(int i = 0; i < totalNumber; ++i)
    {
        if(nextInt(input, start) == -1)
            return INPUT_ERROR;
        if(nextInt(input, end) == -1)
            return INPUT_ERROR;
        if(nextInt(input, height) == -1)
            return INPUT_ERROR;

        if(maxEnd < end)
            maxEnd = end;

        if(i == 0)
            vertical += height;
        else
        {
            if(preEnd < start)
                vertical += height + preHeight;
            else
                vertical += abs(height - preHeight);
        }

        if(i == totalNumber - 1)
            vertical += height;

        //preStart = start;
        preEnd = end;
        preHeight = height;
    }

    if(*input != '\0')
        return INPUT_ERROR;

    distance = maxEnd + vertical;
    return distance;
}


int nextInt(const char*& str, int& number)
{
    char* end = NULL;
    long temp = strtol(str, &end, 10);
    if(str == end)
    {
        fprintf(stderr, "str is empty or does not have the expected form\n");
        return INT_PARSE_ERROR;
    }
    else if(errno ==  ERANGE || temp < INT_MIN || temp > INT_MAX)
    {
        fprintf(stderr, "%.*s is out of range\n", static_cast<int>(end - str), str);
        errno = 0;
        return INT_PARSE_ERROR;
    }
    else if(temp < 0)
    {
        fprintf(stderr, "%.*s is negative\n", static_cast<int>(end - str), str);
        return INT_PARSE_ERROR;
    }
    number = static_cast<int>(temp);
    while(*end == '\n' || *end == ',')
        end++;
    str = end;
    return INT_PARSE_OK;
}
