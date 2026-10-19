#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

  if (argv[1] == NULL || argc == 0) {
      printf("not valid!");
      return 0;
    }
  char *file_name = argv[1];
  FILE *file = fopen(file_name, "rb");

  char P_numero[3];
  int largura;
  int altura;
  int max_val;
  //le o header e move o cursor do fscanf
  fscanf(file, "%s", P_numero);
  fscanf(file, "%d", &largura);
  fscanf(file, "%d", &altura);
  fscanf(file, "%d", &max_val);
  
  // printa o header (nao necessario)
  printf("%s\n", P_numero);
  printf("%d\n", largura);
  printf("%d\n", altura);
  printf("%d\n", max_val);
  
  int caracteres_absoluto = largura * altura * 3; 
  unsigned char *img = malloc(sizeof(char) * (caracteres_absoluto));
 
  if (P_numero[1] == '3') {
    for (int i = 0; i < caracteres_absoluto; i++) {
      fscanf(file, "%hhu ", &img[i]);
    }
  }
  if (P_numero[1] == '6') {
    fgetc(file);
    fread(img, sizeof(unsigned char), caracteres_absoluto, file);
  }

  unsigned char *img_convertida = malloc(sizeof(unsigned char) * (largura*altura));
  unsigned char formatado = 0;
  int n = 0;
  for (int i = 0; i < caracteres_absoluto; i += 3) {
    formatado = 0.299 * img[i] + 0.587 * img[i+1] + 0.114 * img[i+2];
    img_convertida[n] = formatado;
    n++;
  }
  
  for (int i = 0; i < (largura * altura); i++) {
    printf("%d ", img_convertida[i]);
  }

  /*
  printa todos os caracteres_absoluto
  for (int i = 0; i < caracteres_absoluto; i++) {
    printf("%d ", img[i]);
  //se quiser printar cada pixel como linha pra conferir:
    if ((i + 1) % 3 == 0) {
      printf("\n");
    }
  } 
  */
  free(img_convertida);
  free(img);
  fclose(file);
   

}
