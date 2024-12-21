#include <iostream>
#include <limits>

#include "./../include/grafo.hpp"

Grafo carregar_entrada()
{
    size_t n_vertices, n_arestas;
    std::cin >> n_vertices >> n_arestas;

    Grafo grafo = Grafo(n_vertices + 2);

    size_t max = std::numeric_limits<size_t>::max();

    for (size_t i = 0; i != n_vertices; i++)
    {
        size_t v, demanda;
        std::cin >> v >> demanda;

        if (demanda == 0)
        {
            grafo.add_aresta(0, v, max, 's');
            
            grafo.add_aresta(v, 0, max, max, 'r');
        }
        else
        {
            grafo.add_aresta(v, n_vertices + 1, demanda, 't');
            grafo.add_aresta(n_vertices + 1, v, demanda, demanda, 'r');
        }
    }

    for (size_t i = 0; i != n_arestas; i++)
    {
        size_t v1, v2, cap;
        std::cin >> v1 >> v2 >> cap;
        grafo.add_aresta(v1, v2, cap, 'o');
        grafo.add_aresta(v2, v1, cap, cap, 'r');
    }

    return grafo;
}

int main()
{
    auto grafo = carregar_entrada();
    return 0;
}