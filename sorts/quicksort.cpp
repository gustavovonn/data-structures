// Copyright [2024] <Gustavo Rodrigues Alves D'Angelo>

#include <iostream>
#include <time.h>
#include <chrono>

int quicksort_particao(int* array, int start, int end) {
    /* Funcao que de fato vai reorganizar as particoes do vetor.
    Ao final, retorna o indice do pivo*/

    int pivo = array[end];  // Por convencao o pivo base eh o ultimo elemento
    int i = start - 1;  // Index auxiliar

    for(int j = start; j <= end - 1; j++) {
        /* Permutacoes do quicksort; Troca os valores de posicao
        comparando o valor do pivo base*/
        if(array[j] < pivo) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    /* Substituicoes finais para relocalizar o pivo base para o real pivo*/
    i++;
    int temp = array[i];
    array[i] = array[end];
    array[end] = temp;

    return i;
}

void quicksort(int* array, int start, int end) {
    if (end <= start)  // Final das iteracoes entre as particoes recursivas. Start encontra end
        return;

    int pivo = quicksort_particao(array, start, end);  // Coordena as particoes e permutacoes

    quicksort(array, start, pivo - 1);  // Ordenando recursivamente o lado esquerdo
    quicksort(array, pivo + 1, end); // Ordenando recursivamente o lado direito
}


int main() {
    srand(time(NULL));  // Semente para geracao de numeros aleatorios

    // Arrays com 1000, 5000, 10000, 50000 e 100000 inteiros
    int mil[1000];
    int cinco_mil[5000];
    int dez_mil[10000];
    int cinq_mil[50000];
    int cem_mil[100000];


    // Preenchendo os vetores com numeros aleatorios:

    for (int i = 0; i < 1000; i++) {
        mil[i] = rand() % 1000;  // Seta numero aleatorio de 0 a 999
    }

    for (int i = 0; i < 5000; i++) {
        cinco_mil[i] = rand() % 5000;  // Seta numero aleatorio de 0 a 4999
    }

    for (int i = 0; i < 10000; i++) {
        dez_mil[i] = rand() % 10000;  // Seta numero aleatorio de 0 a 9999
    }

    for (int i = 0; i < 50000; i++) {
        cinq_mil[i] = rand() % 50000;  // Seta numero aleatorio de 0 a 49999
    }

    for (int i = 0; i < 100000; i++) {
        cem_mil[i] = rand() % 100000;  // Seta numero aleatorio de 0 a 99999
    }

    // Teste de corretude:
    std::cout << "Array antes: \n";
    for (int i = 0; i < 1000; i++) {
        std::cout << mil[i] << ' ';
    }
    std::cout << '\n';

    // Execucoes do Quicksort:

    auto start = std::chrono::high_resolution_clock::now();
    quicksort(mil, 0, 999);
    auto end = std::chrono::high_resolution_clock::now();

    // Teste de corretude:
    std::cout << "Array depois: \n";
    for (int i = 0; i < 1000; i++) {
        std::cout << mil[i] << ' ';
    }
    std::cout << '\n';

    // Timing do primeiro (que foi desmontrado teste)
    std::chrono::duration<double, std::milli> float_ms = end - start;
    std::cout << "Tempo de execucao Quicksort (Array c/ 1.000 ints): " << float_ms.count() << " ms\n";

    // Continuacao do quicksort

    start = std::chrono::high_resolution_clock::now();
    quicksort(cinco_mil, 0, 4999);
    end = std::chrono::high_resolution_clock::now();
    float_ms = end - start;
    std::cout << "Tempo de execucao Quicksort (Array c/ 5.000 ints): " << float_ms.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    quicksort(dez_mil, 0, 9999);
    end = std::chrono::high_resolution_clock::now();
    float_ms = end - start;
    std::cout << "Tempo de execucao Quicksort (Array c/ 10.000 ints): " << float_ms.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    quicksort(cinq_mil, 0, 49999);
    end = std::chrono::high_resolution_clock::now();
    float_ms = end - start;
    std::cout << "Tempo de execucao Quicksort (Array c/ 50.000 ints): " << float_ms.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    quicksort(cem_mil, 0, 99999);
    end = std::chrono::high_resolution_clock::now();
    float_ms = end - start;
    std::cout << "Tempo de execucao Quicksort (Array c/ 100.000 ints): " << float_ms.count() << " ms\n";

    return 0;
}