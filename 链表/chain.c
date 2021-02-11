#include <stdio.h>
#include <stdlib.h>
//int *next; 这里注意一下的是 链表的查找方式是通过结构体内部的结构体（节点）的指针的意思
//然后这里存的就应该是下一个节点的信息，而不是数据区域的
//然后还有就是这里的创建方式有点不一样的是，这里的所有元素都是动态的
//要=一个就申请多少个，然后再进行分配，我这里的赋值的话，就直接再创建的时候去赋值对应的序号就好了
struct node //since the header node do not need to store any data ,so i will let the node data space to
//store the list length .so that we do not need to use another function to count the node
{
    int data;
    struct node *next_node; //这里有顺序的问题，所以必须要这个地方暂时用自己来声明指着呢
    //这里和typedef的作用域有关系的
};

typedef struct node NODE; //这里所
typedef NODE(*POINTER);
int get_int_input(void);
POINTER init_header_node(void); //this function will creat the herder node
void init_node(POINTER header);
void clear_chain(POINTER header); //this will free all the node expect the header node
void insert_node(POINTER header); //this will support the insert mode
void del_node(POINTER header);
void show_all(POINTER header);
//void get_node(POINTER header);
//void find_data(POINTER header);
int get_length(POINTER header);
//TODO: update the creat mode use the new_mode union

//this func is buildin not open for user
POINTER jump(POINTER header, int times); //do not jump is header
POINTER next(POINTER header);
POINTER new_node(void); //this just creat a new space with init

int main(int argc, char const *argv[])
{
    puts("#################WELCOME TO  ADT-CHAIN########################################WELCOME TO  ADT-CHAIN#######################");

    POINTER header = NULL;
    //header = init_header_node();
    //0
    enum mode
    {
        initheader = 1, //1
        initnode,       //2
        clearchain,
        insertnode,
        delnode,
        showall,
        getlength,
        quit
    };
    int mode_1;
    int init_status = 0;
    //int free_status=0;
    int runner = 1;
    while (runner)
    {
        printf("\n[INIT HEADER]==1 [INIT NODE DATA]==2 [CLEAR CHAIN DEL HEADER ALSO !!]==3  ");
        printf("[INSERT NODE]==4 [DEL MODE ]==5 [SHOW ALL CHAIN]==6 [GET LENGTH]==7 [QUIT]==8\n\n");
        printf("\n PLEASE INPUT THE MODE >>");
        mode_1 = get_int_input();
        switch (mode_1)
        {

        case initheader:
        {
            if (!init_status)
            {
                printf("\n[NO HEADER DETECT CREAT NEW NODE] ");
                header = init_header_node();
                init_status = 1;
            }
            else
            {
                puts("\n[YOU HAVE INIT A HEADER DO NOT INIT HEADER AGAIN!!]");
            }
        }
        break;
        case initnode:
        {
            if (init_status)
            {
                init_node(header);
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;

        case clearchain:
        {
            if (init_status)
            {
                clear_chain(header);
                init_status = 0;
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;
        case insertnode:
        {
            if (init_status)
            {
                insert_node(header);
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;

        case delnode:
        {
            if (init_status)
            {
                del_node(header);
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;
        case showall:
        {
            if (init_status)
            {
                show_all(header);
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;

        case getlength:
        {
            if (init_status)
            {
                printf("\nDETECT [%d] NODE IN CHAIN\n", get_length(header));
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
    clear_chain(header);//turn cate the memory anyway
    getchar();
    return 0;
}

POINTER init_header_node(void)
{
    printf("\n[NOW CREAT THE HEADER NODE]\n[HEADER CREAT DONE]\n");
    POINTER header;
    header = new_node();
    //set the next node to NULL means no next data
    //set the length to 0 means no data here
    //this will replace by the new_node
    return header; //return the herder
}

int get_length(POINTER header) //this will only return the avaliable block count expect header
{
    return header->data;
}

void init_node(POINTER header) //require the header not NULL
{                              //this function will creat the first data in the chain
    if (header != NULL)
    {
        int length = get_length(header);
        if (!length)
        {

            printf("\nNOW INIT THE NODE");
            printf(" PLEASE INPUT THE NUMBER OF NODE YOU WANT TO INIT WITH\n >>>");
            int number = get_int_input();

            POINTER next_temp = header; //(POINTER)malloc(sizeof(NODE));
            for (size_t i = 0; i < number; i++)
            {

                jump(header, i)->next_node = new_node();
            }
            //jump(header, number)->next_node = NULL; //set end node to NULL
            //this will replace by the default value
            printf("\n[CREAT [%d] NODE DONE]\n", number);

            for (size_t i = 0; i < number; i++)
            {
                printf("\nPLEASE INPUT DATA [%d IN %d] >>", i + 1, number);
                jump(header, i + 1)->data = get_int_input(); //+1 is do not change the header node
                header->data++;                              //add length
            }
        }
        else
        {
            printf("\nDETECT DATA IN CHAIN PLEASE DO NOT INIT AGAIN\n");
        }
    }
    else
    {
        printf("\nPLEASE INIT THE HEADER FIREST !!! \n");
    }
}

//TODO:这里需要，1，指针的偏移 2，指针的相互赋值 有了jump就好搞了

void insert_node(POINTER header)
{
    //how many node you want to
    int length = get_length(header);

    POINTER temp;

    if (length)
    {

        printf("\nPLEASE INPUT THE INDEX YOU WANT TO INSERT >>");
        int index = get_int_input();
        if (!index)
        {
            printf("\nDO NOT INSERT AT HEADER TRY [1-%d]\n", length); //printf("\nINDEX OUT OF RANGE TRY [1-%d]", length);
        }
        else
        {
            if (index > length)
            {
                printf("\n INDEX OUT OF RANGE TRY [1-%d]\n", length);
            }
            else
            {
                printf("\n NOW INSERT CHAIN  \n");
                temp = jump(header, index);
                jump(header, index - 1)->next_node = new_node();
                printf("PLEASE INPUT DATA FOR [%d]>>>", index);
                jump(header, index)->data = get_int_input(); //这里再index == 0 的时候会有问题，因为jump的问题
                jump(header, index)->next_node = temp;
                header->data++; //add length
            }
        }
    }
    else
    {
        printf("\nNO DATA IN CHAINS!!\n");
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

POINTER jump(POINTER header, int index)
{                          //这里要用到自身迭代？？？
    POINTER temp = header; //times 1 的时候只跳一次 //这个函数不对用户开放
                           //这个jump的范围应该是0-length 0的话输出的是header的位置
                           //不然访问的内存就没分配
                           //this is the chain key this function will read the ->next (if the index !=0)[if index is 0 return the header pointer ]
                           //[this pointer is also malloed]
                           //and this pointer is the function malloc return , and if your input is 1 and this function will
                           //just read the block 0 [start with header]反正就是 应该jump就是应该链表的箭头，然后这个箭头返回它指向的位置
                           //这个位置当然是指针

    for (size_t i = 0; i < index; i++) //
    {
        temp = next(temp);
    }
    return temp;
}
POINTER next(POINTER to_be_next)
{
    return to_be_next->next_node;
}

void clear_chain(POINTER header)
{
    //this function will free the chain
    int length = get_length(header); //this will only return the avaliable block count expect header
    header->data = 0;
    printf("\n[THE CHAIN IS FREED [PLEASE INIT AGAIN]]\n");
    for (size_t i = 0; i <= length; i++)
    {
        free(jump(header, length - i)); //这里的释放方向为后从后到前
        //jump(header,length-i) return the struct but rember we need to free the pointer the malloc distribut
        //这里会释放头！！
    }
}
POINTER new_node(void)
{
    POINTER temp;
    temp = (POINTER)malloc(sizeof(NODE));
    temp->next_node = NULL;
    temp->data = 0; //this is defaut data
    return temp;
}
void show_all(POINTER header)
{
    int length = get_length(header);

    if (length)
    {
        printf("\n[ SQE ]   [  MY POINTER ]   [   DATA  ]    [  NEXT NODE POINTER ]\n");
        for (size_t i = 0; i < length; i++)
        {
            printf("[ %-4d]   [   %-10d]   [   %-6d]    [      %-14d]\n", i + 1, jump(header, i + 1), jump(header, i + 1)->data, jump(header, i + 1)->next_node);
        }
    }
    else
    {
        printf("\nNO DATA IN CHAINS!!\n");
    }
}
void del_node(POINTER header)
{
    //how many node you want to
    int length = get_length(header);

    POINTER temp;

    if (length)
    {

        printf("\nPLEASE INPUT THE INDEX YOU WANT TO DEL >>");
        int index = get_int_input();
        if (!index)
        {
            printf("\nDO NOT USE HEADER INDEX TRY [1-%d]", length); //printf("\nINDEX OUT OF RANGE TRY [1-%d]", length);
        }
        else
        {
            if (index > length)
            {
                printf("\n INDEX OUT OF RANGE TRY [1-%d]\n", length);
            }
            else
            {
                printf("\n NOW INSERT CHAIN  \n");
                temp = jump(header, index)->next_node;
                free(jump(header, index));
                jump(header, index - 1)->next_node = temp;
                header->data--; //add length
            }
        }
    }
    else
    {
        printf("\nNO DATA IN CHAINS!!\n");
    }
}