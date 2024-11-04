#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <queue>
#include <stack>
#include <utility>  // To use pair

using namespace std;


class Cenario {
 public:
    Cenario(string& texto, size_t indice_inicial) {
        size_t pos = indice_inicial;
        nome = proxima_tag_conteudo(texto, pos, "nome");
        altura = static_cast<size_t>(stoi(proxima_tag_conteudo(texto, pos, "altura")));
        largura = static_cast<size_t>(stoi(proxima_tag_conteudo(texto, pos, "largura")));
        x = static_cast<size_t>(stoi(proxima_tag_conteudo(texto, pos, "x")));
        y = static_cast<size_t>(stoi(proxima_tag_conteudo(texto, pos, "y")));
        matriz = matriz_remove_espacos(proxima_tag_conteudo(texto, pos, "matriz"));
        indice_final = pos;
    }
    ~Cenario() {};
    string nome;
    size_t altura;
    size_t largura;
    size_t x;
    size_t y;
    string matriz;
    size_t indice_final;

 private:
    string proxima_tag(string& texto, size_t& pos) {
        string tag = "";
        for ( ; pos < texto.length(); pos++) {
            if (texto[pos] == '<') {
                pos++;
                while (texto[pos] != '>') {
                    tag += texto[pos];
                    pos++;
                }
                pos++;
                return tag;
            }
        }
        return tag;
    }

    string proximo_conteudo(string& texto, size_t& pos) {
        string txt = "";
        while (texto[pos] != '<') {
            txt += texto[pos];
            pos++;
        }

        while(texto[pos] != '>') {
            pos++;
        }

        pos++;
        return txt;
    }

    string proxima_tag_conteudo(string& texto, size_t& pos, string nome_tag) {
        string tag = "";
        while (tag != nome_tag) {
            tag = proxima_tag(texto, pos);
        }
        return proximo_conteudo(texto, pos);
    }

    string matriz_remove_espacos(string texto) {
        string saida;
        for (int i = 0; i < texto.length(); i++) {
            if (texto[i] == '0' || texto[i] == '1') {
                saida += texto[i];
            }
        }
        return saida;
    }
};

typedef struct {
    std::size_t x;
    std::size_t y;
} Coord;


int main() {
    string filename;
    int cases = 1;

    while (std::cin >> filename) {
        // Abertura do arquivo
        ifstream filexml(filename);
        if (!filexml.is_open()) {
            cerr << "Erro ao abrir o arquivo " << filename << endl;
            throw runtime_error("Erro no arquivo XML");
        }
    
        // Leitura do XML
        string texto;
        char character;
        while (filexml.get(character)) {
            texto += character;
        }
    
        // Tags verification:
        std::stack<std::string> tags; 
        bool tag_verify = true;
        for (std::size_t i = 0; i < texto.size(); i++) {
            bool open = true;
            if (texto[i] == '<') {
                std::string tag = "";
                i++;  // To catch only the tag
        
                if (texto[i] == '/') {
                    open = false;
                    i++;  // To surpass the slash
                }
    
                while (texto[i] != '>') {
                    tag += texto[i];  // Catch the tag
                    i++;
                }
    
                if (open) {  // If its a start tag
                    tags.push(tag);
                } else {  // If its a tag closer
                    if (tags.empty() || tags.top() != tag) {
                        tag_verify = false;  // Its failed
                        break;
                    } else {  // Its ok. Closing the tag.
                        tags.pop();
                    }
                }
            }
        }
    
        if (!tags.empty())  // If there are some tag in the stack yet
            tag_verify = false;
    
        
        // std::cout << "TAMANHO DO TEXTO: " << texto.size() << '\n';        
        // Print
        std::cout << "case=" << cases << '\n';
        std::cout << "input=" << filename << '\n';
        std::cout << "output=";
    
    
        // Scenarios read
        if (tag_verify) {
            std::queue<Cenario> scenarios;
    
            Cenario first_scenario(texto, 0);
            scenarios.push(first_scenario);  // First scenario

            int positions;
            std::size_t pos = 0;  // To handle the file
            
            while (true) {
                Cenario current_scenario = scenarios.front();
                scenarios.pop();

                std::size_t altura = current_scenario.altura;
                std::size_t largura = current_scenario.largura;
    
    
                // The input matrix int version
                std::vector<std::vector<int>> area(altura, std::vector<int>(largura, 0));
                size_t aux = 0;
                for (std::size_t row = 0; row < altura; row++) {
                    for (std::size_t column = 0; column < largura; column++) {
                        area[row][column] = current_scenario.matriz[aux] - '0';
                        aux++;
                    }
                }
    
                // The R auxiliar matrix
                std::vector<std::vector<int>> R(altura, std::vector<int>(largura, 0));
                for (size_t row = 0; row < altura; row++) {
                    for (size_t column = 0; column < largura; column++) {
                        R[row][column] = 0;
                    }
                }
    
                // Analysing
                std::queue<Coord> clean_coords;

                Coord robot_pos = {current_scenario.x, current_scenario.y};
                clean_coords.push(robot_pos);

                positions = 0;  // The answer to the second problem of the project

                // Subs: up -> right -> down -> left
                int row_offsets[] = {-1, 0, 1, 0};
                int column_offsets[] = {0, 1, 0, -1};
    
                Coord current_pos;
                while (!clean_coords.empty()) {
                    current_pos = clean_coords.front();
                    clean_coords.pop();
                    for (size_t i = 0; i < 4; i++) {
                        size_t x = current_pos.x + row_offsets[i];
                        size_t y = current_pos.y + column_offsets[i];
                        if (x >= 0 && y >= 0 && x < altura && y < largura) {
                            if (area[x][y] == 1 && R[x][y] == 0) {
                                R[x][y] = 1;
                                area[x][y] = 0;
                                clean_coords.push({x, y});
                                positions++;
                            }
                        }
                    }
                }

                std::cout << current_scenario.nome << " " << positions << '\n';

                // std::cout << "FINAL POSITION: " << current_scenario.indice_final << '\n';
                // if (texto[current_scenario.indice_final+3] == '\n')
                //     break;
                if (texto.size() - current_scenario.indice_final < 128) {
                    break;
                } else {
                    Cenario new_scenario(texto, current_scenario.indice_final);
                    scenarios.push(new_scenario);
                }

            }
        } else {
            std::cout << "erro" << '\n';
        }
        cases++;  // To the possible next file
        std::cout << '\n';  // Break line thru cases
    }
    return 0;
}