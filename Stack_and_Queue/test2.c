#include <stdio.h>

typedef struct _person
{
    char name[20];
    char phoneNum[20];
    int age;

} person;

int main(void)
{
    person arr = {"한지수", "010-1717-0003", 19};
    person temp;
    person temp2;
    
    
    printf("%s %s %d\n", arr.name, arr.phoneNum, arr.age);
    temp = arr;
    
    arr.age = 20;
    printf("%s %s %d\n", temp.name, temp.phoneNum, temp.age);
    strcpy(temp2.name, arr.name);
    strcpy(temp2.phoneNum, arr.phoneNum);
    temp2.age = arr.age;


    printf("%s %s %d\n", temp2.name, temp2.phoneNum, temp2.age);
    printf("arr의 크기는 ? : %d byte", sizeof(arr));
    return 0;
}