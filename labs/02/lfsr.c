#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

unsigned bit_get(uint16_t x, unsigned n){
	return x>>16-n & 1;
}

unsigned nor(unsigned a , unsigned b){
	return ~(a & b) & (a | b);
}
void lfsr_calculate(uint16_t *reg) {
	unsigned output = nor(nor(bit_get(*reg, 11), bit_get(*reg, 13)),
						  nor(bit_get(*reg, 14), bit_get(*reg, 16)));
	*reg = output<<15 | *reg>>1;
}

int main() {
  int8_t *numbers = (int8_t*) malloc(sizeof(int8_t) * 65535);
  if (numbers == NULL) {
    printf("Memory allocation failed!");
    exit(1);
  }

  memset(numbers, 0, sizeof(int8_t) * 65535);
  uint16_t reg = 0x1;
  uint32_t count = 0;
  int i;

  do {
    count++;
    numbers[reg] = 1;
    if (count < 24) {
      printf("My number is: %u\n", reg);
    } else if (count == 24) {
      printf(" ... etc etc ... \n");
    }
    for (i = 0; i < 32; i++)
      lfsr_calculate(&reg);
  } while (numbers[reg] != 1);

  printf("Got %u numbers before cycling!\n", count);

  if (count == 65535) {
    printf("Congratulations! It works!\n");
  } else {
    printf("Did I miss something?\n");
  }

  free(numbers);

  return 0;
}
