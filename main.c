#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Função para calcular o n-ésimo termo de Fibonacci (1, 1, 2, 3, 5, 8, 13...)
int fibonacci(int n) {
    if (n <= 1) return 1;
    int a = 1, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return a;
}

// Função para calcular o n-ésimo termo de uma PA (a1=1, r=2 por exemplo)
int pa(int n) {
    int a1 = 1, r = 2;
    return a1 + n * r;
}

// Função para calcular o n-ésimo termo de uma PG (a1=1, q=2 por exemplo)
int pg(int n) {
    int a1 = 1, q = 2;
    int termo = a1;
    for (int i = 0; i < n; i++) {
        termo *= q;
    }
    return termo;
}

// Função para obter o n-ésimo número primo
int primo(int n) {
    int primos[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    if (n >= 0 && n < 15) return primos[n];
    return 2;
}

int main() {
    char palavra[16];
    char palavra_cripto[16];
    int shift, opcao_seq;

    printf("=== SISTEMA DE CRIPTOGRAFIA SIMPLES ===\n");
    
    // 1. Leitura da palavra secreta
    printf("Digite a palavra secreta (ate 15 letras, sem acentos): ");
    scanf("%15s", palavra);

    // 2. Leitura do SHIFT
    printf("Digite o valor do SHIFT (deslocamento fixo): ");
    scanf("%d", &shift);

    // 3. Escolha da sequência matemática
    printf("\nEscolha a Sequencia Matematica:\n");
    printf("1 - PA (Progressao Aritmetica)\n");
    printf("2 - PG (Progressao Geometrica)\n");
    printf("3 - Fibonacci\n");
    printf("4 - Numeros Primos\n");
    printf("Opcao: ");
    scanf("%d", &opcao_seq);

    int tam = strlen(palavra);

    // Processamento da criptografia por caractere
    for (int i = 0; i < tam; i++) {
        char c = tolower(palavra[i]);

        if (c >= 'a' && c <= 'z') {
            int seq_val = 0;
            switch (opcao_seq) {
                case 1: seq_val = pa(i); break;
                case 2: seq_val = pg(i); break;
                case 3: seq_val = fibonacci(i); break;
                case 4: seq_val = primo(i); break;
                default: seq_val = fibonacci(i); break;
            }

            // Deslocamento total = SHIFT + sequencia[i]
            int deslocamento_total = shift + seq_val;

            // Aplicação da cifra mantendo dentro do intervalo 'a'-'z' (26 letras)
            palavra_cripto[i] = 'a' + ((c - 'a' + deslocamento_total) % 26);
        } else {
            palavra_cripto[i] = c; // Mantém caracteres que não sejam letras
        }
    }
    palavra_cripto[tam] = '\0';

    // Exibição do resultado no console
    printf("\n--- RESULTADO ---\n");
    printf("Palavra Original: %s\n", palavra);
    printf("Palavra Criptografada: %s\n", palavra_cripto);

    // 4. Salvar log/resultado no arquivo resultado_criptografia.txt
    FILE *arquivo = fopen("resultado_criptografia.txt", "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "Palavra codificada: %s | SHIFT: %d | Tipo: %d | Letras: %d\n",
                palavra_cripto, shift, opcao_seq, tam);
        fclose(arquivo);
        printf("\nResultado gravado com sucesso em 'resultado_criptografia.txt'.\n");
    } else {
        printf("\nErro ao criar o arquivo de resultado.\n");
    }

    return 0;
}