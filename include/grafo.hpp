#ifndef _GRAFO_
#define _GRAFO_

#include <vector>

// classe que simboliza aresta
class Aresta
{
public:
    size_t v;
    size_t cap;
    size_t fluxo;
    char cat;
    std::vector<Aresta>::iterator aresta_rev;

    Aresta() = default;

    Aresta(size_t vertice, size_t capacidade, char categoria);

    Aresta(size_t vertice, size_t capacidade, char categoria, std::vector<Aresta>::iterator rev);

    void add_fluxo(size_t qtd);

    void sub_fluxo(size_t qtd);
};

// classe que simboliza um vértice de um grafo
class Vertice
{
public:
    std::vector<Aresta> arestas;

    std::vector<Aresta>::iterator add_aresta(size_t vertice,
                    size_t capacidade,
                    char categoria);

    void add_aresta(size_t vertice,
                    size_t capacidade,
                    char categoria,
                    std::vector<Aresta>::iterator rev);

    Aresta &operator[](size_t i);

    std::vector<Aresta>::iterator begin();

    std::vector<Aresta>::iterator end();
};

// classe que simboliza um grafo por meio de lista de adjacências
class Grafo
{
public:
    size_t n_vertices;
    std::vector<Vertice> vertices;

    // construtor que reserva um número inicial de vértices
    Grafo(size_t n_vertices);

    // método que adiciona uma nova aresta de acordo com a categoria
    // 'o': original
    // 'r': reverso
    // 's': de origem
    // 't': de destino
    void add_aresta(size_t v1,
                    size_t v2,
                    size_t capacidade,
                    char categoria);

    void add_aresta(size_t v1,
                    size_t v2,
                    size_t capacidade,
                    char categoria,
                    std::vector<Aresta>::iterator rev);

    Vertice &operator[](size_t i);

    std::vector<Vertice>::iterator begin();

    std::vector<Vertice>::iterator end();
};

#endif