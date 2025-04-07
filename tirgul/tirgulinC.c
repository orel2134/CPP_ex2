#include <math.h>
#include <stdio.h>
#define PI 3.14
int int_pow(int base, int exp) {
    int result = 1;
    while (exp != 0) {
        result *= base;
        --exp;
    }
    return result;
}


int* getAddressOfMaxElem(int arr[],int size){
    int i;
    int* maxElemant = &arr[0];
    for(i=0;i<size;i++){
        if(*maxElemant<arr[i]){
            *maxElemant=arr[i];
        }
    }
    return maxElemant;
}



void swap_memcpy(void*p1,void*p2,size_t size){
void*tmp;
tmp=malloc(size);
memcpy(tmp,p1,size);
memcpy(p1,p2,size);
memcpy(p2,tmp,size);
free(tmp);
return;

}
/** 
typedef struct_Student{
    char name[100];
    int id;
    in grade;
}student;
*/




int main(){

    int arr[]={3,7,2};
    int size=sizeof(arr)/sizeof(arr[0]);
    int* pMax=getAddressOfMaxElem(arr,size);
    printf("the number is:",pMax,*pMax);
}


  int extractMsbBits(int num, int bits) {
     int size = 8 * sizeof(num); 
     int mask = (1 << bits) - 1; 
     mask = mask << (size - bits); 
        int extract = (num & mask) >> (size - bits);
        
        return extract; 
      }
       int main() { 
        int num = 0b101101100; 
         int bits = 3; 
      // מספר הביטים להוצאה מה-MSB 
      int result = extractMsbBits(num, bits);
       printf("The result is: %d\n", result); // מדפיס את התוצאה בפורמט עשרוני  
       }
