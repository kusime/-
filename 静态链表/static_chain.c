#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
struct node
{
    int data;
    int cur;
};
static int global_length = 0; //这里声明全局变量，在之后就不要再次输入这个语句了，这个变量的作用域为整个文件，直接再下面的所有函数使用
static int global_const_for_show = 0;
typedef struct node NODE; //这里所
typedef NODE(*POINTER);
//这个数据结构叫静态链表，然后末尾元素储存数据块第一个index
//首段就是储存空闲数据块的index （这个一般较大）
//这里通过index进行真实偏移。然后cur实现模拟指针偏移
int get_int_input(void);
POINTER init_static_chain(void);
void init_data(POINTER list);
void insert_data(POINTER list);
void del_data(POINTER list);
int length(POINTER list);
void show_data(POINTER list);
void clear_list(POINTER list); //这里直接设置HD 和 ED 为零就好，然后具体检查做在插入 删除的函数内部

POINTER jump(POINTER list, int index); //this index is the data block
int next(POINTER to_be_next);
int find_avaliable(POINTER list);

int main(int argc, char const *argv[])
{
    puts("#################WELCOME TO  ADT-STATIC-CHAIN########################################WELCOME TO  ADT-STATIC-CHAIN#######################");

    POINTER header = NULL;
    //header = init_header_node();
    //0
    enum mode
    {
        init_static_chain_1 = 1, //1
        init_data_2,             //2
        insert_data_3,
        del_data_4,
        show_data_5,
        length_6,
        clear_list_7,
        quit_8
    };
    int mode_1;
    int init_status = 0;
    //int free_status=0;
    int runner = 1;
    while (runner)
    {
        printf("\n[INIT STATIC HEADER ]==1 [INIT NODE DATA]==2 [INSERT NODE]==3  ");
        printf("[DEL MODE ]==4 [SHOW ALL CHAIN]==5 [GET LENGTH]==6  [CLEAR CHAIN DEL HEADER ALSO !!]==7 [QUIT]==8\n\n");
        printf("\n PLEASE INPUT THE MODE >>");
        mode_1 = get_int_input();
        switch (mode_1)
        {

        case init_static_chain_1:
        {
            if (!init_status)
            {
                printf("\n[NO HEADER DETECT CREAT NEW NODE] ");
                header = init_static_chain();
                init_status = 1;
            }
            else
            {
                puts("\n[YOU HAVE INIT A HEADER DO NOT INIT HEADER AGAIN!!]");
            }
        }
        break;
        case init_data_2:
        {
            if (init_status)
            {
                init_data(header);
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;

        case clear_list_7:
        {
            if (init_status)
            {
                clear_list(header);
                init_status = 0;
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;
        case insert_data_3:
        {
            if (init_status)
            {
                insert_data(header);
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;

        case del_data_4:
        {
            if (init_status)
            {
                del_data(header);
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;
        case show_data_5:
        {
            if (init_status)
            {
                show_data(header);
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;

        case length_6:
        {
            if (init_status)
            {
                printf("\nDETECT [%d] NODE IN CHAIN\n", length(header));
            }
            else
            {
                printf("\n[PLEASE INIT CHAIN HEADER  FIRST]\n");
            }
        }
        break;

        case quit_8:
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
    clear_list(header); //turn cate the memory anyway
    getchar();
    return 0;
}

POINTER init_static_chain(void)
{
    printf("\n[NOW CREAT MEMORY FOR THE STATIC CHAIN]\n");
    POINTER temp;
    temp = (NODE(*))malloc(sizeof(NODE) * MAX_SIZE);
    for (size_t i = 0; i < MAX_SIZE; i++)
    {
        (temp + i)->data = 0;
        (temp + i)->cur = i + 1; //the cur should be init 这里就是说，cur这里地方再初始化的时候就要有一个index
        //来表达cur的顺序，至于插入和删除的操作只不过就是打乱cur的顺序罢了
    }
    (temp)->cur = 0;                //this means the no data in the list
    (temp + MAX_SIZE - 1)->cur = 0; //这个就是说可用数据的index
    return temp;
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

int length(POINTER list)
{

    if (list != NULL)
    {

        return global_length;
    }
    else
    {
        printf("\n[NOT INIT THE STATIC CHAIN!! \nPLEASE INIT THE CHAIN FIRST !!]\n");
    }
}
void init_data(POINTER list)
{

    if (list != NULL)
    {
        if (!global_length)
        {
            printf("\n[NO DATA DETECT !] [NOW ENTER THE INIT DATA MODE]\n");
            int block;
            printf("\n[PLEASE INPUT THE BLOCK COUNT YOU WANT TO INIT WITH ]>>>");
            block = get_int_input();
            if (block)
            {

                (list)->cur = block + 1;            //this mean the block of the ED should store the first empty block index
                ((list + (MAX_SIZE - 1))->cur) = 1; //the HEAD OF THE STATIC SHOULD STORE THE DATA BLOCK START INDEX
                for (size_t i = 0; i < block; i++)
                {
                    printf("\n[PLEASE INPUT THE DATA OF (%d IN %d)] >>>> ", i + 1, block);
                    jump(list, i + 1)->data = get_int_input(); //since the i ==0 so we need to make a offset
                    global_length++;
                    global_const_for_show++;
                }
                (list + block)->cur = 0; //the end element should be the 0 means the next data is empty
            }
            else
            {
                printf("\n[PLEASE INPUT TEH BLOCK SHOULD LANGER THAN 1 ]");
            }
        }
        else
        {
            printf("\n[DETECT DATA IN THE CHAIN DO NOT INIT THE CHAIN AGAIN !!!]\n");
        }
    }
    else
    {
        printf("\n[NOT INIT THE STATIC CHAIN!! \nPLEASE INIT THE CHAIN FIRST !!]\n");
    }
}
void show_data(POINTER list)
{
    int data_length = length(list);
    if (list != NULL)
    {
        if (data_length)
        {
            printf("\n[ DATA DETECT !] [NOW SHOW THE STATIC CHAIN]\n\n");
            printf("||||||||||||||||||||||||||HEAD||||SPACE||||||||||||||||||||||||||");
            printf("\n[ RAW INDEX ]   [ DATA IN RAW ]   [ CUR    ]  [ CUR ARRARY DATA ]\n");
            printf("[    %-7d]   [    %-9s]   [  %-6d]  [    %-13s]  \n\n", 0, "NULL", list->cur, " END ");
            printf("||||||||||||||||||||||||||HEAD||||SPACE||||||||||||||||||||||||||\n\n\n\n");

            printf("||||||||||||||||||||||||||DATA||||SPACE||||||||||||||||||||||||||\n");

            printf("[ RAW INDEX ]   [ DATA IN RAW ]   [ CUR    ]  [ CUR ARRARY DATA ]\n");
            for (size_t i = 0; i < global_const_for_show; i++) //TODO:这里展现固定位数？？这里的展示不因为长度的变化而改变输出
            //目的是为了方便看清链表里面的操作
            {
                printf("[    %-7d]   [    %-9d]   [  %-6d]  [      %-11d]  \n",
                       i + 1, (list + i + 1)->data, (list + i + 1)->cur, jump(list, i + 1)->data, jump(list, i + 1));
            }
            printf("||||||||||||||||||||||||||DATA||||SPACE||||||||||||||||||||||||||\n\n");
            printf("\n||||||||||||||||||||||||||END ||||SPACE||||||||||||||||||||||||||");
            printf("\n[ RAW INDEX ]   [ DATA IN RAW ]   [ CUR    ]  [ CUR ARRARY DATA ]");

            printf("\n[    %-7d]   [    %-9s]   [  %-6d]  [   %-14s]  \n", MAX_SIZE - 1, "NULL", (list + MAX_SIZE - 1)->cur, " HEADER ");
            printf("||||||||||||||||||||||||||END ||||SPACE||||||||||||||||||||||||||\n");
        }
        else
        {
            printf("\n[NO DATA IN THE LIST PLEASE INIT THE DATA FIRST ]\n\n");
        }
    }
    else
    {
        printf("\n[NOT INIT THE STATIC CHAIN!! \nPLEASE INIT THE CHAIN FIRST !!]\n");
    }
}

POINTER jump(POINTER list, int count) //这个jump 我仔细看了，这个是指定到数据块的第n位，所有，这个不应该作为内存空位
//的指定依据们需要另一套来确定，比如说，内存在第4块位【这个基于index】，但是我们jump是说访问 data数据链条的第4块
//jump是跳数据链条的！！！是访问数据链条的，在index上面可能是乱的啊~！
{
    int index = next(list + MAX_SIZE - 1);
    POINTER temp = list;

    for (size_t i = 0; i < count; i++)
    {
        temp = (list + index);
        index = temp->cur;
    }

    return temp;
}
int next(POINTER to_be_next)
{
    return (to_be_next)->cur;
}
void insert_data(POINTER list)
{
    int data_length = length(list);
    if (list != NULL)
    {
        if (data_length)
        {
            int index;
            int cur1;
            int cur2;
            printf("\n[PLEASE INPUT THE INDEX  YOU WANT TO INSERT WITH ]>>>");
            index = get_int_input();
            if (index > data_length)
            {
                printf("\n[INDEX OUT OF RANGE 1-%d]\n\n", data_length);
            }
            else
            {
                int avaliable = find_avaliable(list); //注意avaliability 只返回到这个空位的偏移量
                //这里的ava 应该是基于index的
                if (index == 1)
                {
                    printf("\nPLEASE DO NOT INSERT DATA AT DATA HEADER\n");
                }
                else
                {
                    //jump(list,avaliable)->cur;//这里注意，jump是不是基于index，这个是基于curl，是相当于访问数据链条的第几个的意思
                    list->cur = (list + avaliable)->cur; //这里更新储存块
                    cur1 = jump(list, index - 1)->cur;   //这里储存修改之前 指定index之前的下一个位置
                    jump(list, index - 1)->cur = avaliable;
                    (list + avaliable)->cur = cur1; //这里的话是吧插入内存块的下一个位置，指向到原来index的位置
                    printf("\n[PLEASE INPUT THE DATA FOR THE INSERT DATA ]>>>");
                    (list + avaliable)->data = get_int_input();
                    global_length++; //这里插入，长度加1
                    global_const_for_show++;//这里的话就获取最大长度，只多不少
                }
            }
        }
        else
        {
            printf("\n[NO DATA IN THE STATIC CHAIN !!]\n");
        }
    }
    else
    {
        printf("\n[NOT INIT THE STATIC CHAIN!! \nPLEASE INIT THE CHAIN FIRST !!]\n");
    }
}
int find_avaliable(POINTER list)
{
    return list->cur; //这个数组的第一个元素储存空闲空间的块//这个是空闲的，真的影响
    //偏移的是里面的数字
}
void del_data(POINTER list)
{
    int data_length = length(list);
    if (list != NULL)
    {
        if (data_length)
        {
            int index;
            printf("\n[PLEASE INPUT THE INDEX  YOU WANT TO DEL  ]>>>");
            index = get_int_input();
            int cur1_raw;
            if (index > data_length)
            {
                printf("\n[INDEX OUT OF RANGE 1-%d\n]", data_length);
            }
            else
            {
                int avaliable = find_avaliable(list); //注意avaliability 只返回到这个空位的偏移量
                //这里的ava 应该是基于index的
                if (index == 1)
                {
                    printf("\nPLEASE DO NOT FREE DATA AT DATA HEADER\n");
                }
                else
                {
                    cur1_raw = jump(list, index)->cur;     //这里的话是读取index的下一个元素的位置
                    jump(list, index)->cur = avaliable;    //这里的curl是指向原来的空闲空间
                    jump(list, index - 1)->cur = cur1_raw; //这里直接强行把指针剪短
                    list->cur = index;                     //这里设施空闲位置指针为释放的优先

                    global_length--; //这里插入，长度加1
                }
            }
        }
        else
        {
            printf("\n[NO DATA IN THE STATIC CHAIN !!]\n");
        }
    }
    else
    {
        printf("\n[NOT INIT THE STATIC CHAIN!! \nPLEASE INIT THE CHAIN FIRST !!]\n");
    }
}
void clear_list(POINTER list)
{
    free(list); //因为这里和chain不一样，这个直接释放就好好
}