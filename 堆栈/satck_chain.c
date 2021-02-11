#include <stdio.h>
#include <stdlib.h>

#define EMPTY -1

struct stack_s
{
    struct stack_s *top;
    int length;
    struct stack_s *next;
    int data;
}; //我这里是把功能集成了，可以用两个结构体去控制整个
typedef struct stack_s STACK;
typedef STACK *POINTER;
POINTER init_header(void);
POINTER new_node(void); //因为链表本身就是单向的，所以不需要初始化也可以的,但是这里方便检查参数还是有个初始化也好些
void destory_stack(POINTER stack_p);
void clear_stack(POINTER stack_p);
void stack_empty(POINTER stack_p);
void show_stack(POINTER stack_p);
void push(POINTER stack_p);
void pop(POINTER stack_p);
POINTER next(POINTER to_be_next);
//int stack_length(POINTER stack_p);//这个也是鸡肋。。。长度和top，你直接去读取就好了
int get_int_input(void); //我就不设计那种初始化数据的函数了//这里的话，数据的加和减法就通过 pop 和 push 这两个函数了
//int get_top(POINTER stack_p);//这是个鸡肋
POINTER jump(POINTER header, int index);
int main(int argc, char const *argv[])
{
    POINTER header = NULL;
    header = init_header();
    push(header);
    push(header);
    push(header);
    show_stack(header);
    pop(header);
    show_stack(header);
    getchar();
    return 0;
}
POINTER init_header(void)
{
    POINTER temp;
    temp = (POINTER)malloc(sizeof(STACK)); //这里一次也只创建一个节点，这个就是头节点了
    printf("\n[PLEASE INPUT THE DATA OF HEADER !!]>>");
    temp->data = get_int_input();

    temp->next = NULL;
    temp->top = temp;  //自己就是顶，因为自己也可以储存数据啊
    temp->next = NULL; //这里做一个环路
    temp->length = 1;  //这里直接描述数组的长度
    return temp;       //init done
}
POINTER new_node(void)
{
    POINTER temp;
    temp = (POINTER)malloc(sizeof(STACK)); //这里一次也只创建一个节点，这个就是头节点了
    temp->data = EMPTY;
    temp->next = NULL;
    temp->top = NULL; //这份new——node再创建的时候不需要去对长度来初始，我这里
    //要单独写一个函数来创建节点的原因就是我要把控件和数据本身分离开
    //说白了就是创建新节点的时候不应该对头产生影响
    return temp; //init done
}

void push(POINTER stack_p) //atttaintion this stack is the header but we should use the indx to make offset
{                          //这个是要检查头就好了，但是要注意，进行添加的时候是依赖top
    if (stack_p != NULL)
    {

        POINTER temp = stack_p;
        printf("\n[PLEASE INPUT THE DATA OF THE PUSH DATA]>>");
        int offset;
        offset = stack_p->length;
        temp = jump(stack_p, offset-1);
        temp->next = new_node();

        stack_p->length++;
        
        temp->next->data = get_int_input();
        stack_p->top = temp->next;
    }
    else
    {
        printf("\n [PLEASE INIT THE STACK]\n");
    }
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
    return to_be_next->next;
}

void show_stack(POINTER stack_p)
{
    if (stack_p != NULL)
    {
        if (stack_p->top != NULL)
        {
            printf("    \n(DETECK [%d] DATA SEGMENT)\n", stack_p->length);
            printf("    \n[TOP POINTER IS >(%d)<]\n\n", stack_p->top);
            printf("   [ STACK TOP    ]   [  STACK TOP  ]    [ STACK TOP    ]    [   STACK TOP    ]\n\n");
            printf("   [  STACK DATA  ]  [  MY POINTER  ]    [ NEXT POINTER ]  [    INDEX    ]\n");
            POINTER temp = stack_p; //你要注意一下，我传进来的只是头指针啊
            int i = 0;
            for (size_t i = 0; i < stack_p->length; i++)
            {
                temp = jump(stack_p, stack_p->length - i -1);//单向链表推荐从头开始
                printf("   [     %-9d]  [   %-11d]    [   %-11d]  [     %-8d]\n", temp->data, temp, temp->next, stack_p->length - i -1);
                printf("   ----------------------------------------------------------------------\n");
            }
            

            printf("\n   [ STACK BOTTOM ]  [ STACKBOTTOM ]    [ STACK BOTTOM ]    [ STACK BOTTOM ]\n");
        }
        else
        {
            printf("\n [NO DATA IN THE STACK TRY PUSH] \n");
        }
    }
    else
    {
        printf("\n [PLEASE INIT THE STACK]\n");
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
void pop(POINTER stack_p){

    if (stack_p != NULL)
    {
        if (stack_p->length)
        {
            POINTER to_be_free;
            int offset;
            offset = stack_p->length-1;
            to_be_free = stack_p->top;
            stack_p->top=jump(stack_p,offset-1);
            stack_p->top->next=NULL;
            stack_p->length--;
            free(to_be_free);
            //this will move to the
        }
        else
        {
            printf("\n[NO DATA  OT POP]\n");
        }
        
        

    }
    else
    {
        printf("\n [PLEASE INIT THE STACK]\n");
    }




}