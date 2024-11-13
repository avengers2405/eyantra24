
/*
* EcoMender Bot (EB): Task 2B Path Planner
*
* This program computes the valid path from the start point to the end point.
* Make sure you don't change anything outside the "Add your code here" section.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#define V 32

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

    #endif

    // array to store the planned path
    uint8_t path_planned[10];
    // index to keep track of the path_planned array
    uint8_t idx = 0;

    /* Functions Usage

    instead of using printf() function for debugging,
    use the below function calls to print a number, string or a newline

    for newline: _put_byte('\n');
    for string:  _put_str("your string here");
    for number:  _put_value(your_number_here);

    Examples:
            _put_value(START_POINT);
            _put_value(END_POINT);
            _put_str("Hello World!");
            _put_byte('\n');
    */

    // ############# Add your code here #############
    // if (START_POINT==END_POINT) path_planned[idx++]=START_POINT;
    path_planned[idx++]=START_POINT;
    int C_POINT = START_POINT;
    while (path_planned[idx-1]!=END_POINT){
        if (C_POINT==0){
            if (END_POINT>=6 && END_POINT<=9){ // component 1
                if (END_POINT==6){
                    path_planned[idx++]=6;
                } else {
                    path_planned[idx++]=6;
                    path_planned[idx++]=END_POINT;
                }
            } else if (END_POINT==10 || (END_POINT>=21 && END_POINT<=31)){
                path_planned[idx++]=10;
                C_POINT=10;
            } else {
                path_planned[idx++]=1;
                C_POINT=1;
            }
        } else if (C_POINT==1){
            if (END_POINT>=2 && END_POINT<=5){
                if (END_POINT==2){
                    path_planned[idx++]=2;
                } else {
                    path_planned[idx++]=2;
                    path_planned[idx++]=END_POINT;
                }
            } else if (END_POINT>=11 && END_POINT<=22){
                path_planned[idx++]=11;
                C_POINT=11;
            } else {
                path_planned[idx++]=0;
                C_POINT=0;
            }
        } else if (C_POINT==2){ // done
            if (END_POINT>=3 && END_POINT<=5){
                path_planned[idx++]=END_POINT;
            } else {
                path_planned[idx++]=1;
                C_POINT=1;
            }
        } else if (C_POINT==3){ // done
            path_planned[idx++]=2;
            C_POINT=2;
        } else if (C_POINT==4){ // done
            path_planned[idx++]=2;
            C_POINT=2;
        } else if (C_POINT==5){ // done
            path_planned[idx++]=2;
            C_POINT=2;
        } else if (C_POINT==6){ // done
            if (END_POINT>=7 && END_POINT<=9){
                path_planned[idx++]=END_POINT;
            } else {
                path_planned[idx++]=0;
                C_POINT=0;
            }
        } else if (C_POINT==7){ // done
            path_planned[idx++]=6;
            C_POINT=6;
        } else if (C_POINT==8){ // done
            path_planned[idx++]=6;
            C_POINT=6;
        } else if (C_POINT==9){ // done
            path_planned[idx++]=6;
            C_POINT=6;
        } else if (C_POINT==10){ // done
            if (END_POINT>=26 && END_POINT<=31){
                path_planned[idx++]=26;
                C_POINT=26;
            } else if ((END_POINT>=21 && END_POINT<=25) || (END_POINT>=16 && END_POINT<=18)){
                path_planned[idx++]=24;
                C_POINT=24;
            } else {
                path_planned[idx++]=0;
                C_POINT=0;
            }
        } else if(C_POINT==11){
            if (END_POINT>=12 && END_POINT<=17){
                path_planned[idx++]=12;
                C_POINT=12;
            } else if ((END_POINT>=18 && END_POINT<=23) || (END_POINT>=30 && END_POINT>=31)){
                path_planned[idx++]=19;
                C_POINT=19;
            } else {
                path_planned[idx++]=1;
                C_POINT=1;
            }
        } else if (C_POINT==12){
            if (END_POINT==13){
                path_planned[idx++]=END_POINT;
            } else if (END_POINT>=14 && END_POINT<=17){
                path_planned[idx++]=14;
                C_POINT=14;
            } else {
                path_planned[idx++]=11;
                C_POINT=11;
            }
        } else if (C_POINT==13){
            path_planned[idx++]=12;
            C_POINT=12;
        } else if (C_POINT==14){
            if (END_POINT==15){
                path_planned[idx++]=END_POINT;
            } else if ((END_POINT>=16 && END_POINT<=25) || (END_POINT>=28 && END_POINT<=31)){
                path_planned[idx++]=16;
                C_POINT=16;
            } else {
                path_planned[idx++]=12;
                C_POINT=12;
            }
        } else if (C_POINT==15){
            path_planned[idx++]=14;
            C_POINT=14;
        } else if (C_POINT==16){
            if (END_POINT==17){
                path_planned[idx++]=END_POINT;
            } else if ((END_POINT>=18 && END_POINT<=31) || (END_POINT==10)){
                path_planned[idx++]=18;
                C_POINT=18;
            } else {
                path_planned[idx++]=14;
                C_POINT=14;
            }
        } else if (C_POINT==17){
            path_planned[idx++]=16;
            C_POINT=16;
        }else if (C_POINT==18){
            if (END_POINT>=14 && END_POINT<=17){
                path_planned[idx++]=16;
                C_POINT=16;
            } else if ((END_POINT>=21 && END_POINT<=31) || END_POINT==10){
                path_planned[idx++]=21;
                C_POINT=21;
            } else {
                path_planned[idx++]=19;
                C_POINT=19;
            }
        } else if (C_POINT==19){
            if (END_POINT==20){
                path_planned[idx++]=END_POINT;
            } else if ((END_POINT>=14 && END_POINT<=18) || (END_POINT>=21 && END_POINT<=25) || (END_POINT>=28 && END_POINT<=31)){
                path_planned[idx++]=18;
                C_POINT=18;
            } else {
                path_planned[idx++]=11;
                C_POINT=11;
            }
        } else if (C_POINT==20){
            path_planned[idx++]=19;
            C_POINT=19;
        } else if (C_POINT==21){
            if (END_POINT==22){
                path_planned[idx++]=END_POINT;
            } else if ((END_POINT>=1 && END_POINT<=5) && (END_POINT>=11 && END_POINT<=20)){
                path_planned[idx++]=18;
                C_POINT=18;
            } else {
                path_planned[idx++]=23;
                C_POINT=23;
            }
        } else if (C_POINT==22){
            path_planned[idx++]=21;
            C_POINT=21;
        } else if (C_POINT==23){
            if (END_POINT>=28 && END_POINT<=31){
                path_planned[idx++]=30;
                C_POINT=30;
            } else if (END_POINT>=11 && END_POINT<=22){
                path_planned[idx++]=21;
                C_POINT=21;
            } else {
                path_planned[idx++]=24;
                C_POINT=24;
            }
        } else if (C_POINT==24){
            if (END_POINT==25){
                path_planned[idx++]=END_POINT;
            } else if ((END_POINT>=28 && END_POINT<=31) || (END_POINT>=14 && END_POINT<=23)){
                path_planned[idx++]=23;
                C_POINT=23;
            } else {
                path_planned[idx++]=10;
                C_POINT=10;
            }
        } else if (C_POINT==25){
            path_planned[idx++]=24;
            C_POINT=24;
        } else if (C_POINT==26) {
            if (END_POINT==27){
                path_planned[idx++]=END_POINT;
            } else if (END_POINT>=28 && END_POINT<=31){
                path_planned[idx++]=28;
                C_POINT=28;
            } else {
                path_planned[idx++]=10;
                C_POINT=10;
            }
        } else if (C_POINT==27){
            path_planned[idx++]=26;
            C_POINT=26;
        } else if (C_POINT==28){
            if (END_POINT==29){
                path_planned[idx++]=END_POINT;
            } else if ((END_POINT>=30 && END_POINT<=31) || (END_POINT>=14 && END_POINT<=25)){
                path_planned[idx++]=30;
                C_POINT=30;
            } else {
                path_planned[idx++]=26;
                C_POINT=26;
            }
        } else if (C_POINT==29){
            path_planned[idx++]=END_POINT;
        } else if (C_POINT==30){
            if (END_POINT==31){
                path_planned[idx++]=END_POINT;
            } else if (END_POINT>=26 && END_POINT<=29){
                path_planned[idx++]=28;
                C_POINT=28;
            } else {
                path_planned[idx++]=23;
                C_POINT=23;
            }
        } else if (C_POINT==31){
            path_planned[idx++]=30;
            C_POINT=30;
        }
    }
    
    // prefer declaring variable like this
    // #ifdef __linux__
    //     // uint8_t graph[30];
    //     // uint8_t arr[]={0, 17, 35, 97, 35, 0, 1, 1, 1, 0, 16, 16, 1, 1, 1, 1};
    // #else
    //     // uint32_t *graph = (uint32_t *) 0x02000010;
    // #endif

    // ##############################################

    // the node values are written into data memory sequentially.
    for (int i = 0; i < idx; ++i) {
        NODE_POINT = path_planned[i];
    }
    // Path Planning Computation Done Flag
    CPU_DONE = 1;

    #ifdef __linux__    // for host pc

        _put_str("######### Planned Path #########\n");
        for (int i = 0; i < idx; ++i) {
            _put_value(path_planned[i]);
        }
        _put_str("################################\n");

    #endif

    return 0;
}

