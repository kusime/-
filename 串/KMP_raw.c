#include <stdio.h>
#include <stdlib.h>
#define MAX_COUNT 100
typedef char(*POINTER);
typedef int(*NEXT);
void init_string(POINTER main_string, POINTER small_string);
int get_int_input(void);

int get_string_length(POINTER string);

void get_next_arrary(POINTER small_string, NEXT next_arrary);
void kmp(POINTER main_string, POINTER samll_string, NEXT next);

int main(int argc, char const *argv[])
{

    char main_string[MAX_COUNT] = {'\0'};
    char small_string[MAX_COUNT] = {'\0'};
    int i = 0;
    while (i++ < 4)
    {
        init_string(main_string, small_string);

        int len_small = get_string_length(small_string);
        int len_main = get_string_length(main_string);
        int next[len_small];

        get_next_arrary(small_string, next);

        kmp(main_string, small_string, next);
    }

    getchar();
    //AA=get_next_arrary();//这里的写法是错误的，因为，在函数内部的都是自动变量，
    //在函数运行结束之后的话，这些变量就被释放了，及时通过指针继续访问，那也只是访问已经被释放的空间的位置，
    //这就是迷途指针，所以最好的方法就是传入data

    return 0;
}
void get_next_arrary(POINTER raw, NEXT next_arrary)
{

    int length = get_string_length(raw); //  长度问题再初始化的时候解决

    int head = 0;
    int end = 1;
    next_arrary[0] = 0;

    while (end < length)
    {
        if (raw[head] != raw[end])
        {
            if (head)
            {
                while (raw[head] != raw[end])
                {
                    head = next_arrary[head - 1];
                    if (raw[head] != raw[end])
                    {
                        next_arrary[end] = head;
                    }
                    else
                    {
                        next_arrary[end] = head + 1;
                        break;
                    }
                    if (head == 0)
                    {
                        break;
                    }
                }
            }
            else
            {
                next_arrary[end] = head;
                end++;
            }
        }
        else
        {
            head++;
            next_arrary[end] = head;
            end++;
        }
    }
    printf("\nnext_arrary is [");
    for (size_t i = 0; i < length; i++)
    {
        if (i == length - 1)
        {
            printf(" %d ]", next_arrary[i]);
        }
        else
        {
            printf(" %d ,", next_arrary[i]);
        }
    }
}

int get_string_length(POINTER string)
{
    int len = 0;

    while (string[len] != '\0')
    {
        len++;
    }
    return len;
}
void init_string(POINTER main_string, POINTER small_string)
{

    printf("\n[please input string for main_string >>]\n");

    printf("\n[THE STRING SHOULD LENGTH >0  >>]");
    scanf("%s", main_string);
    fflush(stdin);

    printf("\n[please input small string >]\n");

    printf("\n[THE STRING SHOULD LENGTH >0  >>]");
    scanf("%s", small_string);
    fflush(stdin);
    if (get_string_length(main_string) < get_string_length(small_string))
    {
        printf("\n\n length check fail please input again\n");
        init_string(main_string, small_string);
    }
}
int get_int_input(void)
{
    int temp;
    while (!(scanf("%d", &temp)))
    {
        printf("\n[Sorry please Input Inter]>>>>");
        fflush(stdin);
    }
    fflush(stdin);
    return temp;
}
void kmp(POINTER main_string, POINTER small_string, NEXT next)
{
    int len_main = get_string_length(main_string);
    int len_sma = get_string_length(small_string);

    int in = 0;
    int counter = 0;
    int finder;
    for (size_t out = 0; out < len_main;)
    {
        /* code */

        if (main_string[out] != small_string[in])
        { //这个是不相等的情况，而且内层没有做偏移或者，偏移之后到 0 了
            //这个是最基本的情况 ，也 不需要 next数组来指明下一步偏移
            if (in == 0)
            {
                out++;       //外部加一，内部不变
                counter = 0; //reset the counter
            }
            else
            {                      //首先，内部index不为0 的时候就说明这个时候已经发生了偏移，这个时候就需要next数组来
                                   //说明下一步的偏移，注意一下，所有的next数组啊，都是针对于小字符穿的呃
                in = next[in - 1]; //这个时候的话就取到内部前面的
                counter = in;
                //这里注意一下，真的比较都是再外部继续的
            }
        }
        else
        { //这里是开始出现了相等的情况
            in++;
            out++;
            counter++;
        }
        if (counter == len_sma)
        {
            finder = out;
            break;
        }
    }
    if (counter == len_sma)
    {
        if (len_sma==1)
        {
            printf(" \ndata find!!\n in index >> %d\n", finder);
        }
        
        printf(" \ndata find!!\n in index >> %d\n", finder-counter);
    }
    else
    {
        printf("\n\n NO DATA MATCH");
    }
}