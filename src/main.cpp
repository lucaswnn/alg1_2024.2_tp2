#include <iostream>
#include <limits>

#include "./../include/grafo.hpp"
#include "./../include/algoritmos.hpp"

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
        }
        else
        {
            grafo.add_aresta(v, n_vertices + 1, demanda, 't');
        }
    }

    for (size_t i = 0; i != n_arestas; i++)
    {
        size_t v1, v2, cap;
        std::cin >> v1 >> v2 >> cap;
        grafo.add_aresta(v1, v2, cap, 'o');
    }

    return grafo;
}

int main()
{
    // carrega a entrada do problema
    auto grafo = carregar_entrada();

    // atualiza o grafo com o fluxo a partir do algoritmo de Ford-Fulkerson
    alg::ford_fulkerson(grafo);
    return 0;
}