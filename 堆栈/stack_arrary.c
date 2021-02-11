#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 4
#define EMPTY -1

struct stack_s
{
    int data[MAX_SIZE];
    int top;
};
typedef struct stack_s STACK;
typedef STACK *POINTER;
POINTER init_stack(void);
void destory_stack(POINTER stack_p);
void clear_stack(POINTER stack_p);
void stack_empty(POINTER stack_p);
void show_stack(POINTER stack_p);
void push(POINTER stack_p);
void pop(POINTER stack_p);

int stack_length(POINTER stack_p);
int get_int_input(void);//我就不设计那种初始化数据的函数了//这里的话，数据的加和减法就通过 pop 和 push 这两个函数了
int get_top(POINTER stack_p);

int main(int argc, char const *argv[])
{
    POINTER header = NULL;
    header = init_stack();
    push(header);
    push(header);
    push(header);
    push(header);
    show_stack(header);
    push(header);

    pop(header);
    show_stack(header);
    getchar();
    return 0;
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

POINTER init_stack(void)
{
    POINTER temp;
    temp = (POINTER)malloc(sizeof(STACK)); //这里就是一个单独的结构体罢了，对于stack的具体操作是针对
    //这个结构体里面的数组的，我这个程序用arrary来实现
    for (size_t i = 0; i < MAX_SIZE; i++)
    {
        temp->data[i] = 0; //this will set the stack with init value 0
    }
    temp->top = EMPTY; //this will set the top pointer to -1
    return temp;       //init done
}

int stack_length(POINTER stack_p) //this will return the block length
{                                 //对于这里的长度的话，不就是直接读取top指针就好了？？
                                  //length=top+1   this could let the func to the get_top()

    if (stack_p != NULL)
    {
        return get_top(stack_p) + 1; //他这里的index和正常的长度差了1位,这里用的是那个top和长度的关系
    }
    else
    {
        printf("\n [PLEASE INIT THE STACK]\n");
    }
}
int get_top(POINTER stack_p) //this will return the top , unless the stack not init
{
    if (stack_p != NULL)
    {
        return stack_p->top;
    }
    else
    {
        printf("\n [PLEASE INIT THE STACK]\n");
    }
}
void stack_empty(POINTER stack_p)
{
    int length = stack_length(stack_p);
    if (stack_p != NULL)
    {
        if (!length)
        {
            printf("\n(THIS STACK NOT EMPTY DETECK [%d] DATA SEGMENT)");
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
void destory_stack(POINTER stack_p)
{
    if (stack_p != NULL)
    {
        free(stack_p);
        printf("\n[STACK DESTORY DONE]\n");
        stack_p = NULL; //set the pointer to NULL
    }
    else
    {
        printf("\n [PLEASE INIT THE STACK]\n");
    }
}
void clear_stack(POINTER stack_p)
{
    if (stack_p != NULL)
    {
        printf("\n[THIS FUNCTION WILL NOT DESTORY THE STACK]\n");
        for (size_t i = 0; i < MAX_SIZE; i++)
        {
            stack_p->data[i] = 0;
        }
        stack_p->top = EMPTY; //set he top pointer to 0
    }
    else
    {
        printf("\n [PLEASE INIT THE STACK]\n");
    }
}
void push(POINTER stack_p)
{ //对于这个函数的话，栈的话，不支持什么插入操作，（emm我也懒的写
    //但是逻辑很简单的，就是先把指定的输出去和top进行判度胺，。。。。啊啊啊算了，写了算了，但是呢
    //总之，就是push和pop的方法一定要完善，pop可以做一个弹出数据的返回）
    //int length = stack_length(stack_p);//这里的话不需要得到长度，

    if (stack_p != NULL)
    {

        
        
        int top_v=stack_p->top;
        top_v++;//这里的变量就只做局部的改变，不会影响栈的top 
        //这里有个坑，你这里改top知识改了内部变量啊？
        //这里的话就先加着，然后有问题再复位？
        if (top_v==MAX_SIZE)//这里要不就干脆就用到局部变量的特点，有点类似于，遇见未来的赶脚？
        {//这里不会出现top+1>MAX_SIZE 的情况
            printf("\n[THIS STACK IS FULL SO TRY POP]\n");
            //
        }
        else
        {
            printf("\n[PLEASE INPUT THE DATA OF THE PUSH DATA]>>");
            stack_p->top++;//this need the control the stack not the narrow values
            stack_p->data[stack_p->top] = get_int_input();
        }
        
        
        
    }
    else
    {
        printf("\n [PLEASE INIT THE STACK]\n");
    }
}
void show_stack(POINTER stack_p)
{
    int length = stack_length(stack_p);
    int top = get_top(stack_p);
    if (stack_p != NULL)
    {
        if (length)
        {
            printf("\n(DETECK [%d] DATA SEGMENT)", length);
            printf("\n[TOP POINTER IS >(%d)<]\n\n", top);
            printf("   [STACK TOP    ][STACK TOP  ]\n");
            
            printf("   [  STACK DATA  ]  [ INDEX ]\n");
            for (size_t i = 0; i < MAX_SIZE; i++)//这里展现完所有栈长度就好
            {
                printf("   [     %-9d]  [   %-4d]\n", stack_p->data[MAX_SIZE - i - 1], MAX_SIZE - i - 1);
                printf("   ---------------------------\n");
            }
            printf("   [STACK BOTTOM ][STACK BOTTOM ]\n");

            
            
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
void pop(POINTER stack_p)//这个是弹栈，这个要求数据不为0//这里默认弹出栈首
{

    if (stack_p != NULL)
    {
        int top=get_top(stack_p);
        if (get_top(stack_p)==EMPTY)
        {
            printf("\n[NO DATA TO POP  !! TRY PUSH FIRST]\n");
            
        }
        else
        {
            stack_p->data[top]=EMPTY;//this 0 means the data is NULL
            stack_p->top--;//this pointer will down one times 
            
        }
        
        
    }
    else
    {
        printf("\n [PLEASE INIT THE STACK]\n");
    }
}