#ifndef _ALGORITMOS_
#define _ALGORITMOS_

#include <tuple>

#include "./../include/grafo.hpp"

class CamadaBFS
{
public:
    std::vector<std::tuple<size_t, size_t, std::vector<Aresta>::iterator>> el_pos_it;

    CamadaBFS() = default;

    CamadaBFS(size_t el, size_t pos, std::vector<Aresta>::iterator it);

    void add_elemento(size_t el, size_t pos, std::vector<Aresta>::iterator it);

    std::tuple<size_t, size_t, std::vector<Aresta>::iterator> &operator[](size_t i);

    std::vector<std::tuple<size_t, size_t, std::vector<Aresta>::iterator>>::iterator begin();

    std::vector<std::tuple<size_t, size_t, std::vector<Aresta>::iterator>>::iterator end();
};

class CaminhoBFS
{
private:
    void _montar_caminho();

public:
    std::vector<CamadaBFS> camadas;
    std::vector<std::vector<Aresta>::iterator> caminho;
    size_t t_pos;

    void encontrar_caminho(Grafo &grafo);

    CamadaBFS &operator[](size_t i);

    std::vector<std::vector<Aresta>::iterator>::iterator begin();

    std::vector<std::vector<Aresta>::iterator>::iterator end();
};

namespace alg
{
    void aumentar_caminho(CaminhoBFS &caminho);
    void ford_fulkerson(Grafo &grafo);
}

#endif