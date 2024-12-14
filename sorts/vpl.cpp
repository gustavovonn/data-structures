// Copyright [2024] <Gustavo Rodrigues Alves D'Angelo>

#include <iostream>
#include <time.h>
#include <chrono>
#include <vector>

void heapify(int* array, int n, int i) {
    int maior_index = i;
    int esquerda_index = (2 * i) + 1;
    int direita_index = (2 * i) + 2;

    if (esquerda_index < n && array[esquerda_index] > array[maior_index])
        maior_index = esquerda_index;

    if (direita_index < n && array[direita_index] > array[maior_index])
        maior_index = direita_index;
    
    if (maior_index != i) {
        int temp = array[i];
        array[i] = array[maior_index];
        array[maior_index] = temp;
    
        heapify(array, n, maior_index);
    }
}

void heapsort(int* array, int size) {

    // Construindo a heap (prioridade de maior valor)
    for (int i = size / (2 - 1); i >= 0; i--) {
        heapify(array, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        // Colocando a raiz para a esquerda
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
    
        heapify(array, i, 0);
    }
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

    // Execucoes do Heapsort:

    auto start = std::chrono::high_resolution_clock::now();
    heapsort(mil, 1000);
    auto end = std::chrono::high_resolution_clock::now();

    // Teste de corretude:
    std::cout << "Array depois: \n";
    for (int i = 0; i < 1000; i++) {
        std::cout << mil[i] << ' ';
    }
    std::cout << '\n';

    // Timing do primeiro (que foi desmontrado teste)
    std::chrono::duration<double, std::milli> float_ms = end - start;
    std::cout << "Tempo de execucao Heapsort (Array c/ 1.000 ints): " << float_ms.count() << " ms\n";

    // Continuacao do Heapsort

    start = std::chrono::high_resolution_clock::now();
    heapsort(cinco_mil, 5000);
    end = std::chrono::high_resolution_clock::now();
    float_ms = end - start;
    std::cout << "Tempo de execucao Heapsort (Array c/ 5.000 ints): " << float_ms.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    heapsort(dez_mil, 10000);
    end = std::chrono::high_resolution_clock::now();
    float_ms = end - start;
    std::cout << "Tempo de execucao Heapsort (Array c/ 10.000 ints): " << float_ms.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    heapsort(cinq_mil, 50000);
    end = std::chrono::high_resolution_clock::now();
    float_ms = end - start;
    std::cout << "Tempo de execucao Heapsort (Array c/ 50.000 ints): " << float_ms.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    heapsort(cem_mil, 100000);
    end = std::chrono::high_resolution_clock::now();
    float_ms = end - start;
    std::cout << "Tempo de execucao Heapsort (Array c/ 100.000 ints): " << float_ms.count() << " ms\n";

    return 0;
}