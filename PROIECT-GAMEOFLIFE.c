#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("%s", argv[0]);
    return 1;
  }

  FILE *input = fopen(argv[1], "r");
  if (!input) {
    printf("Eroare\n");
    return 1;
  }

  FILE *output = fopen(argv[2], "w");
  if (!output) {
    printf("Eroare\n");
    fclose(input);
    return 1;
  }

  fclose(input);
  fclose(output);
  return 0;
}
