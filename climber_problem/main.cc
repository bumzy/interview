#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <vector>
#include <algorithm>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

enum {
    INPUT_ERROR = -1,
    INT_PARSE_ERROR = -1,
    INT_PARSE_OK = 0
};

struct VerticalEdge
{
    int x, height;
    int flag; //left edge = -1, right edge = 1
    VerticalEdge(int _x, int _h, int _f) : x(_x), height(_h), flag(_f) {}
    bool operator<(const VerticalEdge& ve) const
    {
        if(x != ve.x)
            return x < ve.x;
        else if(flag != ve.flag)
            return flag > ve.flag;
        else
            return height > ve.height;
    }
};

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
        "1\n0,0,1\n", //expect 0
        "1\n0,1,0\n", //expect 1
        "1\n1,2,0\n", //expect 2
        "2\n0,0,0\n0,0,0\n", //expect 0
        "3\n0,0,0\n0,0,0\n0,0,1\n", //expect 0
        "2\n1,4,2\n2,3,1\n", //test one rectangle in another rectangle expect 8
        "3\n1,6,3\n2,5,2\n3,4,1\n", //expect 12
        "3\n6,7,5\n1,3,2\n2,4,4\n", //test uordered input expect 25
        //"", //expect INPUT_ERROR
        //"1\nasdf", //expect INPUT_ERROR
        //"-1", //expect INPUT_ERROR
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20, 0, 0, 0, 1, 2, 0, 0, 8, 12, 25, /*INPUT_ERROR, INPUT_ERROR, INPUT_ERROR*/};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}

int resolve( const char* input)
{
    if(input == NULL)
        return INPUT_ERROR;

    std::vector<VerticalEdge> edge;
    std::vector<int> bar;
    int total = -1, distance = 0, maxEnd = 0;

    if(nextInt(input, total) == -1)
        return INPUT_ERROR;

    for(int i = 0; i < total; ++i)
    {
        int start = -1, end = -1, height = -1;
        if(nextInt(input, start) == -1)
            return INPUT_ERROR;
        if(nextInt(input, end) == -1)
            return INPUT_ERROR;
        if(nextInt(input, height) == -1)
            return INPUT_ERROR;

        if(start > end)
            std::swap(start, end);

        edge.push_back(VerticalEdge(start, height, -1));
        edge.push_back(VerticalEdge(end, height, 1));
        if(maxEnd < end)
            maxEnd = end;
    }

    sort(edge.begin(), edge.end());
    distance += maxEnd;

    int preX = 0, preHeight = 0, preFlag = 1;
    for(size_t i = 0; i < edge.size(); ++i)
    {
        int x = edge[i].x, height = edge[i].height, flag = edge[i].flag;
        if(preX == x)
        {
            if(preFlag == 1 && flag == -1)
            {
                preHeight = height;
                preFlag = flag;
            }
            else if(height > preHeight)
            {
                preHeight = height;
                preFlag = flag;
            }
        }
        else
        {
            if(preFlag == -1 && flag == 1)
            {
                bar.push_back(preHeight);
                if(preHeight == height)
                    preFlag = flag;
            }
            else if(preFlag == -1 && flag == -1)
            {
                bar.push_back(preHeight);
                if(preHeight < height)
                    preHeight = height;
            }
            else if(preFlag == 1 && flag == 1)
            {
                bar.push_back(height);
                if(preHeight > height)
                    preHeight = height;
            }
            else if(preFlag == 1 && flag == -1)
            {
                bar.push_back(0);
                preHeight = height;
                preFlag = flag;
            }
            preX = x;
        }
    }

    if(!bar.empty())
    {
        for(size_t i = 0; i < bar.size() - 1; ++i)
        {
            distance += abs(bar[i] - bar[i+1]);
        }
        distance += bar[0];
        distance += bar[bar.size() - 1];
    }

    if(*input != '\0')
        return INPUT_ERROR;

    return distance;
}

int nextInt(const char*& str, int& number)
{
    char* end = NULL;
    long temp = strtol(str, &end, 10);
    if(str == end)
    {
        fprintf(stderr, "INT_PARSE_ERROR ： str is empty or does not have the expected form\n");
        return INT_PARSE_ERROR;
    }
    else if(errno ==  ERANGE || temp < INT_MIN || temp > INT_MAX)
    {
        fprintf(stderr, "INT_PARSE_ERROR ： %.*s is out of range\n", static_cast<int>(end - str), str);
        errno = 0;
        return INT_PARSE_ERROR;
    }
    else if(temp < 0)
    {
        fprintf(stderr, "INT_PARSE_ERROR ： %.*s is negative\n", static_cast<int>(end - str), str);
        return INT_PARSE_ERROR;
    }
    number = static_cast<int>(temp);
    while(*end == '\n' || *end == ',')
        end++;
    str = end;
    return INT_PARSE_OK;
}
