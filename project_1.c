#include <stdio.h>

    int array[32];
    int *aptr_1;
    int *aptr_2;
    int *aptr_3;

void project_1_report(){
 
    aptr_1 = &array[0];
    aptr_2 = &array[8];
    aptr_3 = &array[16];
    
    //move 8 bytes from aptr_1 to aptr_3
    memmove(aptr_1, aptr_3, 8);
    
    //move 16 bytes from aptr_2 to aptr_1
    memmove(aptr_2, aptr_1, 16);
    
    //reverse on aptr_1 to reverse the entire 32 bytes
    my_reverse(aptr_1);

    //a pointer to memory and prints the hex output
    dump_memory();

    //convert int to char using my_atoi
    my_atoi(aptr_1);
    
    return;
}

void project_1_call_by_main(){

    //print out the entire 32 byte array in a nicely formatted way
    printf("entire array is %s : \n",array);

}
