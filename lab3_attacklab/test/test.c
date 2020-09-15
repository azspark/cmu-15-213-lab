#include <stdio.h>

int test(char* b) { 
  b[0]++;
  b[1]--;
  return 0;
}

int main(){
  char a[5];
  a[0] = '1';
  a[2] = '2';
  test(a);
  return 0;

}
