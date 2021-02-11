#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define EMPTY -1
struct queue
{
    int data[MAX_SIZE];
    int HEAD;
    int END;
};
typedef struct queue QUE;
typedef QUE *POINTER;

POINTER init_queue(void);
void destory_queue(POINTER queue);
void clear_queue(POINTER queue);
void empty_queue(POINTER queue);
void enter_queue(POINTER queue);
void out_queue(POINTER queue);
int length_queue(POINTER queue);
void show_queue(POINTER queue);

int get_int_input(void);
int get_reflect(int to_be_reflect);

int main(int argc, char const *argv[])
{

    POINTER header = NULL;
    //header = init_header_node();
    //0
    enum mode
    {
        initqueue = 1, //1
        destoryqueue,  //2
        clearqueue,
        emptyqueue,
        enterqueue,
        outqueue,
        lengthqueue,
        showqueue,
        quit
    };
    int mode_1;
    int init_status = 0;
    //int free_status=0;
    int runner = 1;
    while (runner)
    {
        printf("\n[init_queue]==1 [destory_queue]==2 [clear_queue]==3  ");
        printf("[empty_queue]==4 [enter_queue]==5 [out_queue]==6 [length_queue]==7 [show_queue]==8 [quit]==9\n\n");
        printf("\n PLEASE INPUT THE MODE >>");
        mode_1 = get_int_input();
        switch (mode_1)
        {

        case initqueue:
        {
            if (!init_status)
            {
                printf("\n[NOW HEADER DETECT CREAT NEW MEMORY]\n ");
                header = init_queue();
                init_status = 1;
            }
            else
            {
                puts("\n[YOU HAVE INIT A HEADER DO NOT INIT HEADER AGAIN!!]");
            }
        }
        break;
        case destoryqueue:
        {
            if (init_status)
            {
                printf("\n[this action will clear the memory]\n");
                destory_queue(header);
                init_status = 0;
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;

        case clearqueue:
        {
            if (init_status)
            {
                clear_queue(header);
                
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;
        case emptyqueue:
        {
            if (init_status)
            {
                empty_queue(header);
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;

        case enterqueue:
        {
            if (init_status)
            {
                enter_queue(header);
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;
        case outqueue:
        {
            if (init_status)
            {
                out_queue(header);
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;

        case lengthqueue:
        {
            if (init_status)
            {
                printf("\nDETECT [%d] NODE IN CHAIN\n", length_queue(header));
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;

        case showqueue:
        {
            if (init_status)
            {
                show_queue(header);
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;

        case quit:
        {
            runner = 0;
        }
        break;

        default:
        {
            printf("\n[ERROR]\n\n");
        }
        break;
        }
    }

    getchar();
    return 0;
}

POINTER init_queue(void)
{
    POINTER temp;
    temp = (POINTER)malloc(sizeof(QUE)); //这个不是链条，数据块内嵌再结构体里面
    for (size_t i = 0; i < MAX_SIZE; i++)
    {
        temp->data[i] = EMPTY;
    }
    temp->HEAD = 0;
    temp->END = 0;

    return temp;
    printf("\n[QUEUE CREAT DONE]\n");
}

int length_queue(POINTER queue)
{
    return (queue->END - queue->HEAD + MAX_SIZE) % MAX_SIZE;
    //这里的意思就是，再end - head 》0的时候就是直接减去的长度后面的max不对其产生影响
    //但是呢，如果前面的数据小于0 就说明这个时候已经进入了循环队列，。这个时候的话就是
    //要减去空白数据块的个数就好，这个时候，绝对会小于MAX所以这个时候就输出的就是
    //max - 空白数据块个数，那么这个时候的话就书数据块的个数撒你去画一个图就好
}

void clear_queue(POINTER queue)
{
    if (queue != NULL)
    {
        int length = length_queue(queue);

        if (!length)
        {
            printf("\n[THIS QUEUE IS EMPTY ! dont clear again]\n");
        }
        else
        {
            for (size_t i = 0; i < MAX_SIZE; i++)
            {
                queue->data[i] = EMPTY;
            }
            queue->HEAD = 0;
            queue->END = 0; //this will return to the init
        }
        printf("\n[THIS QUEUE CLEAR DONE (this action will not make infect to the header)]\n");
    }
    else
    {
        printf("\n [PLEASE INIT THE QUEUE]\n");
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

void empty_queue(POINTER queue)
{
    if (queue != NULL)
    {
        int length = length_queue(queue);

        if (!length)
        {
            printf("\n[THIS QUEUE IS EMPTY ! ]\n");
        }
        else
        {
            printf("\n[DETECT ( %d ) DATA SEGMENT]\n", length);
        }
    }
    else
    {
        printf("\n [PLEASE INIT THE QUEUE]\n");
    }
}

void destory_queue(POINTER queue)
{
    if (queue != NULL)
    {
        printf("\n[DESTORY DONE (this action will free the memory for the queue)]\n");
        free(queue);
    }
    else
    {
        printf("\n [THIS QUE NOT INIT YET PLEASE TYR INIT THE QUEUE]\n");
    }
}

void enter_queue(POINTER queue) //这个入队只会影响END
{
    if (queue != NULL)
    {
        int length = length_queue(queue); //length 这个数据描述的是有效数据块的个数哈
        //这里不推荐使用这个长度来定性的描述数组时候满了，//算了，也试一下
        if (length == MAX_SIZE - 1) //this que is FULL
        {
            printf("\n[THIS QUEUE IS FULL TRY OUT_QUEUE ! ]\n");
        }
        else
        { //对于这里的来说哈，应该是先加，然后再做循环队列的index的映射，
            //因为我们的目的就是要为了让END,
            //END 本身指向的就是空的数据块啊
            printf("\n[PLEASE INPUT THE  DATA YOU WANT TO ENTER QUE >>]");
            int END_1 = queue->END;
            queue->data[END_1] = get_int_input();
            //queue->END++;这里注意一下啊，他那个算是已经包含偏移了
            //仔细看，它返回的值是加一之后的那个值，如果小于maxsize的时候
            //这里注意局部变量的坑
            queue->END = get_reflect(queue->END); //这里可能会rewind 到那个0那里，但是，
            //再进入队列的时候。，这个数据绝对不是满的
            //TODO:这里可能有坑，注意一下
        }
    }
    else
    {
        printf("\n [PLEASE INIT THE QUEUE]\n");
    }
}

int get_reflect(int to_be_reflect)
{
    return (to_be_reflect + 1) % MAX_SIZE;
}
void show_queue(POINTER queue)
{

    if (queue != NULL)
    {
        int length = length_queue(queue); //length 这个数据描述的是有效数据块的个数哈
        //这里不推荐使用这个长度来定性的描述数组时候满了，//算了，也试一下
        //printf(">>[%d]\n", length);
        if (!length)
        {
            printf("\n[THIS QUEUE IS EMPTY no data to show]\n");
        }
        else
        {
            int head = queue->HEAD; //这个HEAD绝对是有数据的
            int end = queue->END;
            int counter=0;
            printf("HEADER ->> %d \n END ->> %d \n",head,end);
            printf("\n[  DATA IN QUEUE ]    [ DATA IN MEMORY ]\n");
            printf("[  HEAD    HEAD  ]    [  HEAD    HEAD  ]\n");
            while (counter<MAX_SIZE)//this will show all the queue number
            {//这里注意下 在while 里面写 counter ++ 是加了以后继续比较的
            //最好把变量加载里面

                printf("[        %-8d]    [        %-8d]\n", queue->data[head],queue->data[counter]);
                counter++;
                head = get_reflect(head); //这里展现的是从头开始，
                //如果这里偏移到end的时候就知道这个队列已经展现完了
            }
            printf("[   END    END   ]    [   END    END   ]\n");
        }
    }
    else
    {
        printf("\n [PLEASE INIT THE QUEUE]\n");
    }
}

void out_queue(POINTER queue)
{

    if (queue != NULL)
    {
        int length = length_queue(queue);
        //printf(">>[%d]\n", length);
        if (!length)
        {
            printf("\n[THIS QUEUE IS EMPTY (no data to out_queue)]\n");
        }
        else
        {
            printf("\n[HEAD DATA OUT QUEUE DONE !!]\n");
            int HEAD_1 = queue->HEAD; //出队才会影响
            queue->data[HEAD_1] = EMPTY;
            queue->HEAD = get_reflect(HEAD_1);
        }
    }
    else
    {
        printf("\n [PLEASE INIT THE QUEUE]\n");
    }
}