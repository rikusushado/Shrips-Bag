#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {

   char cmd[10];
   strcpy(cmd,"df -h /");
   system(cmd);
   
   return 0;
}