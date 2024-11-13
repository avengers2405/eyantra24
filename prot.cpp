/*
* EcoMender Bot (EB): Task 2B Path Planner
*
* This program computes the valid path from the start point to the end point.
* Make sure you don't change anything outside the "Add your code here" section.
*/

#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
// #define V 32

#ifdef __linux__ // for host pc

    #include <stdio.h>

    void _put_byte(char c) { putchar(c); }

    void _put_str(char *str) {
        while (*str) {
            _put_byte(*str++);
        }
    }

    void print_output(uint8_t num) {
        if (num == 0) {
            putchar('0'); // if the number is 0, directly print '0'
            _put_byte('\n');
            return;
        }

        if (num < 0) {
            putchar('-'); // print the negative sign for negative numbers
            num = -num;   // make the number positive for easier processing
        }

        // convert the integer to a string
        char buffer[20]; // assuming a 32-bit integer, the maximum number of digits is 10 (plus sign and null terminator)
        uint8_t index = 0;

        while (num > 0) {
            buffer[index++] = '0' + num % 10; // convert the last digit to its character representation
            num /= 10;                        // move to the next digit
        }
        // print the characters in reverse order (from right to left)
        while (index > 0) { putchar(buffer[--index]); }
        _put_byte('\n');
    }

    void _put_value(uint8_t val) { print_output(val); }

#else  // for the test device

    void _put_value(uint8_t val) { }
    void _put_str(char *str) { }

#endif



// main function
int main(int argc, char const *argv[]) {
    // printf("argc: %d done.", argc);
    
    // _put_str("here0");
    // printf("argc: %d done.", argc);
    #ifdef __linux__

        const uint8_t START_POINT   = atoi(argv[1]);
        const uint8_t END_POINT     = atoi(argv[2]);
        uint8_t NODE_POINT          = 0;
        uint8_t CPU_DONE            = 0;

    #else
        // Address value of variables for RISC-V Implementation
        #define START_POINT         (* (volatile uint8_t * ) 0x02000000)
        #define END_POINT           (* (volatile uint8_t * ) 0x02000004)
        #define NODE_POINT          (* (volatile uint8_t * ) 0x02000008)
        #define CPU_DONE            (* (volatile uint8_t * ) 0x0200000c)
        // const uint8_t START_POINT   = atoi(argv[1]);
        // const uint8_t END_POINT     = atoi(argv[2]);
        // uint8_t NODE_POINT          = 0;
        // uint8_t CPU_DONE            = 0;

    #endif
        // printf("argc: %d done.", argc);

    // array to store the planned path
    uint8_t path_planned[32];
    // index to keep track of the path_planned array
    uint8_t idx = 0;

    // ############# Add your code here #############
    // prefer declaring variable like this
    #ifdef __linux__
        uint32_t graph[32]={1090, 2053, 58, 4, 4, 4, 897, 64, 64, 64, 83888129, 529410, 26624, 4096, 102400, 16384, 409600, 65536, 2686976, 1312768, 524288, 12845056, 2097152, 1092616192, 41944064, 16777216, 402654208, 67108864, 1677721600, 268435456, 2424307712, 1073741824};
    #else
         uint32_t *graph = (uint32_t *) 0x02000010;
    
    #endif
       

    uint32_t stk1=(1<<START_POINT);
    uint32_t stk2=0, visited=0;
    uint8_t parent[32];
    uint32_t ONE=1;

    for (int i=0; i<32; i++) parent[i]=35;

    // printf("argc: %d done.", argc);

    while (stk1){
            for (uint8_t root=0; root<32; root++){
                if ((stk1&(1<<root)) && (!(visited&(1<<root)))){
                    for (uint8_t i=0; i<32; i++){
                        if ((graph[root]&(ONE<<i))) {
                            stk2|=(ONE<<i);
                            
                            if (parent[i]==35) {
                                parent[i]=root;
                            }
                        }
                    }
                    visited|=(1<<root);
                }
            }
        stk1=stk2;
        stk2=0;
    }
    

    if (END_POINT!=START_POINT){
        uint8_t EP=END_POINT;
        path_planned[idx++]=EP;
        while(parent[EP]!=START_POINT){
            path_planned[idx++]=parent[EP];
            EP=parent[EP];
        }
        path_planned[idx++]=START_POINT;
    }  
    // ##############################################

    // the node values are written into data memory sequentially.
    for (int i = idx-1; i >= 0; --i) {
        NODE_POINT = path_planned[i];
    }
        // printf("argc: %d done.", argc);

    // Path Planning Computation Done Flag
    CPU_DONE = 1;

    #ifdef __linux__    // for host pc
        // printf("argc: %d done.", argc);

        _put_str("######### Planned Path #########\n");
        for (int i = idx-1; i >= 0; --i) {
            // printf("%d ", path_planned[i]);
            _put_value(path_planned[i]);
        }
        _put_str("################################\n");

    #endif

    return 0;
}