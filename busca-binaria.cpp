#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype> // transformar texto em uppercase
#include <algorithm> // pra ordenar o resultado

using namespace std;

vector<string> buscaBinaria(vector<string> nomes, int qtdNomes, string letras){

    int s = 0, e = qtdNomes - 1;
    vector<string> resultado;
    int aux = 0;

    for(char &caractere : letras){ // transformando as letras do valor informado para uppercase
        caractere = toupper(caractere);
    }
    while (s <= e) {

        int m = (s + e) / 2;
        string nome;
        for(char c : nomes[m]) nome += toupper(c); // transformando o nome em uppercase
        // tambem poderia usar nome.substr(...) == letras
        if (nome.substr(0, letras.size()).compare(letras) == 0){ // verificando se o nome começa com o valor informado
            resultado.push_back(nomes[m]);
            nomes.erase(nomes.begin() + m); // apagando o valor que foi inserido
        }
        else if(nome.substr(0, letras.size()).compare(letras) > 0){ // se o nome for maior que o valor informado, diminui o fim
            e = m - 1;
        }
        else if(nome.substr(0, letras.size()).compare(letras) < 0){ // se o nome for menor que o valor informado, aumenta o inicio
            s = m + 1;
        }
    }

    return resultado;
}

bool funcaoOrdenar(const string& a, const string& b){
    return a.compare(b) < 0;
}
void ordenar(vector<string>& resultado){
    sort(resultado.begin(), resultado.end(), funcaoOrdenar);
}

int main() {

    fstream arquivo("nomes.txt", fstream::in);

    if(!arquivo.is_open()){
        cout << "Erro ao ler arquivo! Verifique se ele está no diretório correto." << endl;
    }

    vector<string> nomes;
    while(!arquivo.eof()){
        string linha;
        getline(arquivo, linha);
        if(linha.empty()) break;
        nomes.push_back(linha);
    }

    arquivo.close();

    int opcao = 1;
    do{
        string letras;
        cout << "Digite o valor:" << endl;
        cin >> letras;

        vector<string> resultado = buscaBinaria(nomes, nomes.size(), letras);
        ordenar(resultado);
        for(string nome : resultado){
            cout << nome << endl;
        }

        cout << endl << "Digite 1 para pesquisar outro valor. Qualquer outro valor ira sair do programa." << endl;
        cin >> opcao;
    }while(opcao == 1);

    return 0;
}
