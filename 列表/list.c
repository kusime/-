#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_COUNT 100
//this code will show the list
//TODO:1,这个叫做顺序储存结构

struct Student
{
    char name[10]; //10byte
    char sex[10];
    int age;
    struct //匿名//the bit filed cannot use the scanf @fuck!
    {
        unsigned int status : 1; //this will creat a bit filed and the progran will check here
        //if the arrary is useful;//this will occur 1 byte
    };
};
typedef struct Student S_List;
typedef S_List(*S_pointer);

//TODO:我这里要定义一个结构体为数据元素，然后这些构成一个线性表，
//TODO:然后查找的时候可以更具结构体里面的属性来进行查找，返回的值是这个结构体里面的所有信息
//TODO:然后结构体里面有数据标识符，1就代表着这个数据有效，然后0就说明这个数数据无效
//TODO:对于插入的解决办法就是检查对应位的元素是否有1，如果有一的话输出
void Show_Mode(int show_mode);
void Get_Data(S_pointer List, int input_mode); //cannot take address of bit-field 'status'
S_pointer InitList(void);                      //初始化一个空的表
int ListEmpty(S_pointer List);                 //检查表是不是空
void ClearList(S_pointer List);                //turncate the list
void GetElement(S_pointer List);               //这个直接查找并且输出算了
void LocateElement_C(S_pointer List);
void LocateElement(S_pointer List); //find a struct which have a sign value
//mode = find name //or mode = find ages //if more than one struct have the value
//this will return the double pointer ainway
void ListInsert(S_pointer List); //at count insert a strcut
void ListDel(S_pointer List);
int ListLents(S_pointer List); //this will return the
void ShowList(S_pointer List, int show_mode);

//void *__cdecl realloc(void *_Memory,size_t _NewSize);
int main(int argc, char const *argv[])
{
    S_pointer List = NULL; //this is a pointer for the struct;//all of the function is center with this

    //!!!!!woc this is just the pointer of the struct so you do not need to unpack again!!!@_@fuck!!
    enum mde
    {
        I_T = 1, //init list this will not call the get data !!
        L_C,     //2clear list
        G_E,     //3get element
        L_E,     //4locate element
        L_I,     //5list insert
        L_D,     //6list del
        L_L,     //7list length
        L_S,     //8LIST SHOW
        G_D,     //9 GET DATA
        Q_U
    };
    int exe_status = 0; //0 is first
    int mode;
    int runner = 1;
    int init_status = 0; //not yet is 0 initted is 1
    int win_status = 0;  //0 is mode not enter yet 1 is enter win
    while (runner)
    {
        if (win_status)
        {
            /* code */;
        }
        else
        { //this means out of input
            if (!exe_status)
            {
                Show_Mode(exe_status);
                exe_status = 1;
            }
            else
            {
                Show_Mode(exe_status);
            }
        }

        while (!(scanf("%d", &mode)))
        {
            printf("\nSorry please Input Inter ");
            printf("[Element Count] >>");
            scanf("%d", &mode);
            fflush(stdin);
        }

        switch (mode)
        {
        case I_T:

            if (init_status)
            {
                printf("\nYou Have Init The List Please Do NO Init Again\n");
            }
            else
            {
                List = InitList();

                init_status = 1;
            }

            break;
        case L_C:
            if (!init_status)
            {
                puts("\n");
                puts("Please Init First");
            }
            else
            {
                puts("\n");
                ClearList(List);

                printf("DONE \n");
            }

            break;

        case G_E:

            if (!init_status)
            {
                puts("\n");
                puts("Please Init First");
            }
            else
            {
                GetElement(List);
                printf("DONE \n");
            }

            break;

        case L_E:

            if (!init_status)
            {
                puts("\n");
                puts("Please Init First");
            }
            else
            {
                LocateElement_C(List);
                printf("DONE \n");
            }

            break;

        case L_I:

            if (!init_status)
            {
                puts("\n");
                puts("Please Init First");
            }
            else
            {
                ListInsert(List);
            }

            break;

        case L_D:

            if (!init_status)
            {
                puts("\n");
                puts("Please Init First");
            }
            else
            {
                ListDel(List);
            }

            break;

        case L_L:

            if (!init_status)
            {
                puts("\n");
                puts("Please Init First");
            }
            else
            {
                printf("\nTHIS LIST HAVE [%d] ELEMENT\n", ListLents(List));
            }

            break;

        case L_S:

            if (!init_status)
            {
                puts("\n");
                puts("Please Init First");
            }
            else
            {
                ShowList(List, 0);
            }

            break;

        case G_D:

            if (List == NULL)
            {
                puts("\n");
                puts("Please Init First");
            }
            else
            {
                if (!init_status) //this only sing with if of not the list is init
                //cannot use this value to jude the element empty or not
                {
                    puts("NOT DISTRIBUT THE MEMORY SPACE PLEASE INIT THE LIST FIRST");
                }
                else
                {
                    if (((List)->status) != 0)
                    {
                        printf("\n[Detect Data in list] \n[Please Do Use the Clear List To OVERWRITE THE DATA] \n");
                    }
                    else
                    {
                        printf("\nDetect Memory Space AND NO DATA IN THE MEMORY");

                        Get_Data(List, 0);
                    }
                }
            }

            break;

        case Q_U:

            //exit(EXIT_SUCCESS);
            //break; 这个switch里面的break是无法结束循环的
            runner = 0; //use signal to break the while
            break;
        }
    }
    fflush(stdin); //this will clear the break buffer
    getchar();
    free(List);
    return 0;
}

S_pointer InitList(void)
{
    printf("\n[NOW INIT LIST]\n[Maxcount  %d]\n[DONE]\n", MAX_COUNT);
    S_pointer List = (S_pointer)malloc(sizeof(S_List) * MAX_COUNT);
    for (size_t i = 0; i < MAX_COUNT; i++)
    {
        (List + i)->status = 0; //this will init the struct
    }

    return List;
}
void Get_Data(S_pointer List, int input_mode) //mode 0 is init  mode 1 is insert
{
    int counter;
    int camp;

    if (!input_mode)
    {
        puts("\n[DATA INPUT MODE]\n");
        printf("[Element Count] >>");
        //static S_pointer    >>block-scope 函数只能包含外部存储类

        while (!(scanf("%d", &counter)))
        {
            printf("\nSorry please Input Inter ");
            printf("[Element Count] >>");
            scanf("%d", &counter);
            fflush(stdin);
        }
        fflush(stdin);

        for (size_t i = 0; i < counter; i++)
        {
            (List + i)->status = 1;

            puts("\n");
            printf("[ %d in %d ] \n[Names]>> ", i + 1, counter);
            scanf("%s", (List + i)->name);
            fflush(stdin);

            printf("\n[Ages ]>> ", i + 1, counter);
            while (!(scanf("%d", &((List + i)->age))))
            {
                printf("\nSorry please Input Inter>>");
                fflush(stdin);
            }
            fflush(stdin);

            printf("\n[Sex ] (boy or girl)>> ", i + 1, counter);
            scanf("%s", (List + i)->sex);
            fflush(stdin);
            while (((strcmp((List + i)->sex, "boy")) && (strcmp((List + i)->sex, "girl"))))
            { //我去，这里是离散的德摩根定律？？
                printf("\nSorry please Input [boy or girl]>>");
                scanf("%s", (List + i)->sex);
                fflush(stdin);
            }
            fflush(stdin);
        }
    }
    else
    {
        (List)->status = 1;

        puts("\n");
        printf("[Names]>> ");
        scanf("%s", (List)->name);
        fflush(stdin);

        printf("\n[Ages ]>> ");
        while (!(scanf("%d", &((List)->age))))
        {
            printf("\nSorry please Input Inter>>");
            fflush(stdin);
        }
        fflush(stdin);

        printf("\n[Sex ] (boy or girl)>> ");
        scanf("%s", (List)->sex);
        fflush(stdin);
        while (((strcmp((List)->sex, "boy")) && (strcmp((List)->sex, "girl"))))
        { //我去，这里是离散的德摩根定律？？
            printf("\nSorry please Input [boy or girl]>>");
            scanf("%s", (List)->sex);
            fflush(stdin);
        }
        fflush(stdin);
    }
}

int ListEmpty(S_pointer List) //printf("%d\n", (*(list+i)).status);会输出随机的1是因为，，，你他妈没初始化啊傻逼,海油list本来就是一级
//指针了，你还解包？？
{

    for (size_t i = 0; i < MAX_COUNT; i++)
    {
        if (((List + i)->status) == 1)
        {
            printf("Detect data\n Break Element at %d", i + 1); //this is arrary index not squens
            return 1;
        }
    }
    printf("NoData in the List \n");
    return 0;
}

void ClearList(S_pointer List)
{
    puts("[DEL DONE]");
    for (size_t i = 0; i < MAX_COUNT; i++)
    {
        (List + i)->status = 0; //this will set the struct status to empty
    }
}

void GetElement(S_pointer List)
{
    int getter;
    int avaliable;
    avaliable = ListLents(List);
    if (avaliable)
    {
        printf("Please Input the Suq Number >>");
        while (!(scanf("%d", &getter)))
        {
            printf("\n[Sorry please Input Inter]\n");
            printf("Please Use Arrary Index Support Range Is [0,%d] (use index type)>>", avaliable - 1);
            fflush(stdin);
        }
        fflush(stdin); //clear buffer
        if (((List + getter)->status) == 0)
        {
            printf("[Sorry No Data Here]\n", getter);
            printf("[NOW QUIT THE GetElememt]\n");
        }
        else
        {
            puts("[FIND DATA]\n[NOW SHOW THE OBJECT]\n");
            printf("[SQUENC]        [  NAME  ]        [  AGE  ]        [ SEX ]\n");
            printf("[  %d   ]        ", getter);
            ShowList((List + getter), 1); //this use mode 1 sig output
        }
    }
    else
    {

        puts("\nDetect Memory But No Data In List");
    }
}
//TODO:339
void LocateElement_C(S_pointer List)
{
    int avaliable;
    avaliable = ListLents(List);
    if (avaliable)
    {
        LocateElement(List);
    }
    else
    {
        puts("\n");
        puts("NO DATA IN LIST");
    }
}
void LocateElement(S_pointer List)
{
    printf("\nplease input the types data you want to find\n");
    enum mode
    {
        name = 1,
        ages,
        sex
    };

    int mode_input;
    puts("Please Input The Mode Of Finder\n");
    printf("[NAMES] ==1 [AGE]==2 [SEX]==3 \n[[MODE]]>>>");

    while (!(scanf("%d", &mode_input))) //init the finder mode
    {
        printf("Please Input Inter >>");
        fflush(stdin);
    }
    fflush(stdin);

    int avaliable_length = ListLents(List);

    printf("\ndetect a %d element in the list \n", avaliable_length);
    S_pointer finder[MAX_COUNT] = {NULL};
    int line[MAX_COUNT]={0};
    

    if (mode_input == ages)
    {
        printf("Please Input The AGES YOU WANT TO FIND]>> ");
        int age_finder;

        while (!(scanf("%d", &age_finder))) //init the finder mode
        {
            printf("Please Input Inter");
            fflush(stdin);
        }
        fflush(stdin);

        for (size_t i = 0; i < avaliable_length; i++) //this just in range useful data
        {
            if (((List + i)->age) == age_finder)
            {
                for (size_t j = 0; j < avaliable_length; j++)
                {
                    if (finder[j] == NULL)
                    {
                        finder[j] = (List + i); //attion the list +i is the struct pointer
                        line[j]=i;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        if (mode_input == name)
        {
            char name_finder[10];

            printf("Please Input The NAME YOU WANT TO FIND]>> ");
            scanf("%s", name_finder);
            fflush(stdin);

            for (size_t i = 0; i < avaliable_length; i++) //this just in range useful data
            {
                if ((strcmp(((List + i)->name), name_finder)) == 0)
                {
                    for (size_t j = 0; j < avaliable_length; j++)
                    {
                        if (finder[j] == NULL)
                        {
                            finder[j] = (List + i); //attion the list +i is the struct pointer
                            line[j]=i;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            if (mode_input == sex)
            {
                char sex_finder[10];

                printf("Please Input The SEX YOU WANT TO FIND]>> ");
                scanf("%s", sex_finder);
                fflush(stdin);

                for (size_t i = 0; i < avaliable_length; i++) //this just in range useful data
                {
                    if ((strcmp(((List + i)->sex), sex_finder)) == 0)
                    {
                        for (size_t j = 0; j < avaliable_length; j++)
                        {
                            if (finder[j] == NULL)
                            {
                                finder[j] = (List + i); //attion the list +i is the struct pointer
                                line[j]=i;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    int j = 0;
    //attion finder [j] is struct pointer
    //and finder j js point to sigil what the data the logic find
    //so we jst need to look all the element
    //and the finder[j] ,if no data find the finder will store the NULL pointer
    //so we just need to check the first element
    if (finder[0] == NULL)
    {
        printf("\n[NO DATA MATCHED !!]\n");
    }
    else
    {
        while (finder[j])
        { //if finder not empty we need to out put
            //and we need to pay attion to the shower
            if (j == 0) //means this is the first out put so we need to print the
            //header
            {
                printf("[SQUENC]        [  NAME  ]        [  AGE  ]        [ SEX ]\n");
                printf("[  %d   ]        ", line[j]);
                ShowList(finder[j], 1); //this use mode 1 sig output
            }
            else
            {
                printf("[  %d   ]        ", line[j]);
                ShowList(finder[j], 1);
            }

            j++;
        }
    }

    //this will show the answer it gets
}
int ListLents(S_pointer List)
{
    int counter = 0;
    for (size_t i = 0; i < MAX_COUNT; i++)
    {
        if (((List + i)->status) == 1) //we just pick up the useful data
        {
            counter++;
        }
    }
    return counter; //this funcion will return the number of the useful counter
}
//TODO:MODE
void ShowList(S_pointer List, int show_mode) //TODO://show mode =1 is show one line for
//the getelement or the finder or get
{
    int avaliable_size = ListLents(List);
    if (show_mode)
    { //one line mode //just print the point element
        printf("[  %-6s ]        [  %-3d  ]        [ %-3s ]\n",
               (List)->name, (List)->age, (List)->sex);
    }
    else
    { //show all available
        if (avaliable_size)
        { //16
            printf("\n[SQUENC]        [  NAME   ]        [  AGE  ]        [ SEX ]\n");
            for (size_t i = 0; i < avaliable_size; i++)
            {
                printf("[  %-4d]        [  %-5s ]        [  %-3d  ]        [ %-3s  ]\n",
                       i, (List + i)->name, (List + i)->age, (List + i)->sex);
            }
        }
        else
        {
            printf("\n[NO DATA IN LIST]\n");
        }
    }
}
void ListInsert(S_pointer List)
{
    int avaliable = ListLents(List);

    int index;
    int distance;
    if (!avaliable)
    {
        printf("\n[NO DATA IN THE LIST !!]\n");
        puts("[NOW QUIT THE INSERT MODE]");
    }
    else
    {
        puts("\n[NOW INSERT MODE] [INTPUT [Quit] To End INSERT MODE] \n");
        printf("Please Use Arrary Index Support Range Is [0,%d] (use index type)>>", avaliable - 1);

        while (!(scanf("%d", &index)))
        {
            printf("\n[Sorry please Input Inter]\n");
            printf("Please Use Arrary Index Support Range Is [0,%d] (use index type)>>", avaliable - 1);
            fflush(stdin);
        }
        fflush(stdin);

        do
        {

            if (index+1 > avaliable)//this will make prifore again
            {
                printf("[INDEX OUT OF RANGE]\n");
                printf("Please Use Arrary Index Support Range Is [0,%d] (use index type)>>", avaliable - 1);
            }
            else
            { //the length will return the block useful not index
                distance = avaliable - index;
                if (((List + index)->status) == 1)
                {
                    printf("\n[NOW MOVE THE ELEMENT FOR INSERT]");
                    memmove((List + index + 1), (List + index), sizeof(S_List) * distance); //这个把多余块给向后移动块
                    Get_Data((List + index), 1);
                    break;
                }
            }
            fflush(stdin); //这个超级重要
        } while (!(scanf("%d", &index)));
    }
    fflush(stdin);
}
void ListDel(S_pointer List)
{
    int avaliable = ListLents(List);

    int index;
    int distance;
    if (!avaliable)
    {
        puts("\n");
        printf("[NO DATA IN THE LIST !!]\n");
    }
    else
    {
        puts("\n[NOW DEL MODE] [INTPUT [Quit] To End DEL MODE] \n");
        printf("Please Use Arrary Index Support Range Is [0,%d] (use index type)>>", avaliable - 1);

        while (!(scanf("%d", &index)))
        {
            printf("\n[Sorry please Input Inter]\n");
            printf("Please Use Arrary Index Support Range Is [0,%d] (use index type)>>", avaliable - 1);
            fflush(stdin);
        }
        fflush(stdin);

        do
        {
            distance = avaliable - index + 1;
            if (((List + index)->status) == 0)
            {
                puts("[NO DATA HERE !!]");
                break;
            }
            else if (((List + index)->status) == 1)
            {
                printf("[NOW FREE THE BLOCK]\n");

                memmove((List + index), (List + index + 1), sizeof(S_List) * distance); //这个把多余块给向后移动块
                (List + (avaliable - 1))->status = 0;
                puts("[DONE]");
                break;
            }
            fflush(stdin); //这个超级重要
        } while (!(scanf("%d", &index)));
    }
    fflush(stdin);
}
void Show_Mode(int show_mode)
{
    enum
    {
        I_T = 1, //init list
        L_C,     //2clear list
        G_E,     //3get element
        L_E,     //4locate element
        L_I,     //5list insert
        L_D,     //6list del
        L_L,     //7list length
        L_S,     //8LIST SHOW
        G_D,     //9 GET DATA
        Q_U
    };
    if (!show_mode)
    {
        puts("###########WELCOME TO THE ADT - LIST########################WELCOME TO THE ADT - LIST#######################WELCOME TO THE ADT - LIST###################################");
        puts("\n");
    }
    else
    {
        puts("\n");
    }

    printf("[INIT LIST] == %d  [CLEAR LIST] == %d  [GET ELEMENT BY INDEX] == %d", I_T, L_C, G_E);
    printf("[FIND MODE] == %d  [INSERT MODE] == %d  [DEL MODE] == %d  [LIST LENGTH] == %d", L_E, L_I, L_D, L_L);
    printf("  [SHOW LIST ]==%d", L_S);
    printf("  [GET DATA]==%d", G_D);
    printf("  [QUIT]==%d\n", Q_U);

    printf("\nPlease Input  [[MODE]] >>");
}
