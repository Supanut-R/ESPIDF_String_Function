#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

char *TAG = "STRING";

// c-string ในรูปแบบนี้ (called array)
char A[6] = "hello";
char B[6] = "world";
char C[9] = "helloNay"; // Increase size of C to 7 to avoid Guru Meditation Error

// c-string ในรูปแบบนี้ (called string literal - read-only memory) ถ้าต้องการใช้งาน string ใน C จะต้องมี memory allocation ให้กับ string นั้นๆ
// ถ้าใช้งาน string ใน C จริงๆ จะต้องมีการ free memory ที่ได้ถูก allocate ก่อนหน้านี้
char *c = "HELLO";
char *d = "world";
char *e = "baller";
char *f;

uint8_t D[6] = {0x48, 0x45, 0x4C, 0x4C, 0x4F, 0x45};


void app_main()
{
    // string copy


    // *****************************************************
    strcpy(A, B);
    printf("A: %s\n", A); // (output: A: world)
    // strcpy(A, C); // it's not a good thing to copy a string to a smaller string (it can cause buffer overflows, but the program may crash in the future)
    // printf("A: %s\n", A); // (output: A: helloNay)
    // printf("strlen(A): %d\n", strlen(A)); // (output: strlen(A): 8)
    // You should always ensure that the destination buffer is large enough to hold the source string, including the null-terminator (\0). If the destination buffer is smaller, use strncpy or dynamically allocate memory.
    strncpy(A, C, sizeof(A) - 1); //  Copy only up to the size of A - 1
    A[sizeof(A) - 1] = '\0';      // Null-terminate the string
    printf("A: %s\n", A);
    // A = "WORLD"; (expression must be a modifiable lvalue)
    // *****************************************************

    // *****************************************************
    // strcpy(C, D);
    // printf("C: %s\n", C);
    // ---> Solution: Allocate memory for C
    // c = malloc(6);
    // if (!c)
    // {
    //     ESP_LOGE(TAG, "Failed to allocate memory for c");
    //     return; // Handle memory allocation failure
    // }
    // d = malloc(6);
    // if (!d)
    // {
    //     ESP_LOGE(TAG, "Failed to allocate memory fordc");
    //     return; // Handle memory allocation failure
    // }
  
    // strcpy(c, d);
    // printf("c: %s\n", c);
    // free(c);              
    // printf("c: %s\n", c); // C is now a dangling pointer, it points to freed memory (output: c: ���?���?���?)
    // *****************************************************

    // copied characters from char* c (string literal) to array A  (✓)
    // strcpy(A, c);
    // printf("A copied from char* c: %s\n", A); // (output: A from char* c: HELLO)
    
    /*
    <Guru Meditation Error: Core  0 panic'ed (LoadStoreError). Exception was unhandled.>
    strcpy(c, A);
    printf("c copied from Array A: %s\n", c); // (output: A from char* c: HELLO)
    */

   /*
   // copied characters from array uint8_t D to array char A  (✓)
   strcpy(A, (char*)D);
   printf("A copied from array uint8_t D: %s\n", A); // (output: A from char* D: HELLO)
   printf("A copied from array uint8_t D: %02X:%02X:%02X:%02X:%02X:%02X\n", A[0], A[1], A[2], A[3], A[4], A[5]); // (output: A from char* D: HELLO)
   */

    /*
    // let pointer f point to array uint8_t D
    f = (char*)D;
    printf("f copied from array uint8_t D: %s\n", f); // (output: f from array uint8_t D: HELLO)
    */
}