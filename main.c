#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>


// Função para ordenar um vetor de strings usando o Bubble Sort
void bubbleSort(char **arr, int n) {
	int i,j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                // Troca as strings se estiverem na ordem errada
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Função para ordenar um vetor de strings usando o Selection Sort
void selectionSort(char **arr, int n) {
    int i, j, min_index;
    char *temp;

    for (i = 0; i < n - 1; i++) {
        min_index = i;
        for (j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[min_index]) < 0) {
                min_index = j;
            }
        }

        // Troca as strings se estiverem na ordem errada
        if (min_index != i) {
            temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

// Função para ordenar um vetor de strings usando o Shell Sort
void shellSort(char **arr, int n) {
    int gap, i, j;
    char *temp;

    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = arr[i];
            for (j = i; j >= gap && (strcmp(arr[j - gap], temp) > 0);j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Função de partição usada no Quick Sort
int partition(char **arr, int low, int high) {
    char *pivot = arr[high];
    int i = low - 1,j;

    for (j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            char *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    char *temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Função principal do Quick Sort
void quickSort(char **arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//Duplica o Array Original
char** duplicaArray(char** original, int size)
{
  char** copia = (char**)malloc(size * sizeof(char*));
  int i;
  for (i = 0; i < size; i++) {
    copia[i] = (char*)malloc(strlen(original[i]) + 1);
    strcpy(copia[i], original[i]);
  }
  return copia;
}


//Função Imprime Arquivo
void imprimeArquivo(char **imgCopia,int img_size)
{
  int opt2,i;
  printf("\nDeseja imprimir a lista de imagens ordenadas em um arquivo de texto?\n1 - Sim\n2 - Não\n");
  scanf("%d", &opt2);

  if (opt2 == 1) {
    FILE *arquivo_saida = fopen("imgs_ord.txt", "w");
    if (arquivo_saida == NULL) {
      perror("Erro ao criar o arquivo de saída");
      exit(EXIT_FAILURE);
    }

    for (i = 0; i < img_size; i++) {         
      fprintf(arquivo_saida, "%s\n", imgCopia[i]);
    }

    fclose(arquivo_saida);
    printf("As imagens ordenadas foram salvas em 'imgs_ord.txt'.\n");

    // Libera a memória alocada para imgCopia
    for (i = 0; i < img_size; i++) {
      free(imgCopia[i]);
    }
    free(imgCopia);
  }
}

void main() {
  setlocale(LC_ALL,"Portuguese");
  FILE *fp;
  char line[BUFSIZ];  // Buffer para armazenar uma linha
  char **img = NULL;  // Vetor para armazenar as linhas
  int img_size = 0,i;

  fp = fopen("wildfire.txt", "r");
  if (fp == NULL) {
    perror("Erro ao abrir o arquivo!");
    exit(EXIT_FAILURE);
  }

  while (fgets(line, sizeof(line), fp) != NULL) {
    // Remove o caractere de nova linha do final da linha, se presente
    char *newline = strchr(line, '\n');
    if (newline != NULL) {
      *newline = '\0';
    }

    // Aloca memória para uma nova string no vetor img
    img = (char **)realloc(img, (img_size + 1) * sizeof(char *));
    img[img_size] = (char *)malloc(strlen(line) + 1);

    // Copia a linha atual para o vetor img
    strcpy(img[img_size], line);
    img_size++;
  }

  int opt, opt2, numRuns,run;
  clock_t inicio, fim;
  double tempo, soma_t;
  do{
    printf("\n#### Algoritmos de Ordenação Disponíveis ####\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Selection Sort\n");
    printf("3 - Shell Sort\n");
    printf("4 - Quick Sort\n");
    printf("Escolha a opção desejada: ");
    scanf("%d", &opt);

    switch (opt) {
      case 1:
        //Bubble Sort
        printf("Quantas vezes deseja rodar o algoritmo? ");
        scanf("%d", &numRuns);
        printf("\nExecutando...");
        if(numRuns > 10){
          printf("\nNúmero de execuções excede 10, iremos mostrar somente os resultados");
        }

        for (run = 0; run < numRuns; run++) {
          char** imgCopia = duplicaArray(img, img_size);

          inicio = clock();
          bubbleSort(imgCopia, img_size);
          fim = clock();

          tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
          soma_t += tempo;
          if(numRuns <= 10){
            printf("\nTempo para ordenar com Bubble Sort (Execução %d): %f segundos\n", run + 1, tempo);
          }

          if(run + 1 == numRuns){
            printf("\nTempo total: %f",soma_t);
            printf("\nTempo médio: %f",soma_t/numRuns);
            imprimeArquivo(imgCopia, img_size);
          }
          else{
          // Libera a memória alocada para imgCopia
            for (i = 0; i < img_size; i++) {
              free(imgCopia[i]);
            }
            free(imgCopia);
          }
        }
      break;

      case 2:
        //Selection Sort
        printf("Quantas vezes deseja rodar o algoritmo? ");
        scanf("%d", &numRuns);
        printf("\nExecutando...");
        if(numRuns > 10){
          printf("\nNúmero de execuções excede 10, iremos mostrar somente os resultados");
        }

        for (run = 0; run < numRuns; run++) {
          char** imgCopia = duplicaArray(img, img_size);

          inicio = clock();
          selectionSort(imgCopia, img_size);
          fim = clock();

          tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
          soma_t += tempo;
          if(numRuns <= 10){
            printf("\nTempo para ordenar com Selection Sort (Execução %d): %f segundos\n", run + 1, tempo);
          }

          if(run + 1 == numRuns){
            printf("\nTempo total: %f",soma_t);
            printf("\nTempo médio: %f",soma_t/numRuns);
            imprimeArquivo(imgCopia, img_size);
          }
          else{
            // Libera a memória alocada para imgCopia
            for (i = 0; i < img_size; i++) {
              free(imgCopia[i]);
            }
            free(imgCopia);
          }
        }
      break;

      case 3:
        // Shell Sort
        printf("Quantas vezes deseja rodar o algoritmo? ");
        scanf("%d", &numRuns);
        printf("\nExecutando...");
        if(numRuns > 10){
          printf("\nNúmero de execuções excede 10, iremos mostrar somente os resultados");
        }

        for (run = 0; run < numRuns; run++) {
          char** imgCopia = duplicaArray(img, img_size);

          inicio = clock();
          shellSort(imgCopia, img_size);
          fim = clock();

          tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
          soma_t += tempo;
          if(numRuns <= 10){
            printf("\nTempo para ordenar com Shell Sort (Execução %d): %f segundos\n", run + 1, tempo);
          }

          if(run + 1 == numRuns){
            printf("\nTempo total: %f",soma_t);
            printf("\nTempo médio: %f",soma_t/numRuns);
            imprimeArquivo(imgCopia, img_size);
          }
          else{
            // Libera a memória alocada para imgCopia
            for (i = 0; i < img_size; i++) {
                free(imgCopia[i]);
            }
            free(imgCopia);
          }
        }
      break;

      case 4:
        // Quick Sort
        printf("Quantas vezes deseja rodar o algoritmo? ");
        scanf("%d", &numRuns);
        printf("\nExecutando...");
        if(numRuns > 10){
          printf("\nNúmero de execuções excede 10, iremos mostrar somente os resultados");
        }

        for (run = 0; run < numRuns; run++) {
          char** imgCopia = duplicaArray(img, img_size);

          inicio = clock();
          quickSort(imgCopia, 0, img_size - 1);
          fim = clock();

          tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
          soma_t += tempo;
          if(numRuns <= 10){
            printf("\nTempo para ordenar com Quick Sort (Execução %d): %f segundos\n", run + 1, tempo);
          }

          if(run + 1 == numRuns){
            printf("\nTempo total: %f",soma_t);
            printf("\nTempo médio: %f",soma_t/numRuns);
            imprimeArquivo(imgCopia, img_size);
          }
          else{
            // Libera a memória alocada para imgCopia
            for (i = 0; i < img_size; i++) {
              free(imgCopia[i]);
            }
            free(imgCopia);
          }
        }
      break;

      default:
        printf("Escolha inválida.\n");
    }
  } while(opt > 4 || opt < 0);


  // Libera a memória alocada para as strings no vetor img
  for (i = 0; i < img_size; i++) {
    free(img[i]);
  }

  // Libera o vetor img
  free(img);
  fclose(fp);
  exit(EXIT_SUCCESS);
}
