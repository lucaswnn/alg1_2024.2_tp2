#include <stdexcept>

#include "./../include/grafo.hpp"

Aresta::Aresta(size_t vertice,
               size_t capacidade,
               char categoria) : v(vertice),
                                 cap(capacidade),
                                 fluxo(0),
                                 cat(categoria) {}

Aresta::Aresta(size_t vertice,
               size_t capacidade,
               char categoria,
               std::vector<Aresta>::iterator rev) : v(vertice),
                                                    cap(capacidade),
                                                    fluxo(capacidade),
                                                    cat(categoria),
                                                    aresta_rev(rev) {}

void Aresta::add_fluxo(size_t qtd)
{
    if (qtd + fluxo > cap)
    {
        throw std::invalid_argument("Fluxo maior do que a capacidade");
    }

    fluxo += qtd;
}

void Aresta::sub_fluxo(size_t qtd)
{
    if (qtd > fluxo)
    {
        throw std::invalid_argument("Fluxo maior do que o já existente");
    }

    fluxo -= qtd;
}

// -------

std::vector<Aresta>::iterator Vertice::add_aresta(size_t vertice,
                         size_t capacidade,
                         char categoria)
{
    arestas.push_back(Aresta(vertice, capacidade, categoria));
}

void Vertice::add_aresta(size_t vertice,
                         size_t capacidade,
                         char categoria,
                         std::vector<Aresta>::iterator rev)
{
    arestas.push_back(Aresta(vertice, capacidade, categoria, rev));
}

Aresta &Vertice::operator[](size_t i)
{
    return arestas[i];
}

std::vector<Aresta>::iterator Vertice::begin()
{
    return arestas.begin();
}

std::vector<Aresta>::iterator Vertice::end()
{
    return arestas.end();
}

// -------

Grafo::Grafo(size_t n_v) : n_vertices(n_v)
{
    vertices.assign(n_v, Vertice());
}

void Grafo::add_aresta(size_t v1,
                       size_t v2,
                       size_t capacidade,
                       char categoria)
{
    vertices[v1].add_aresta(v2, capacidade, categoria);
}

void Grafo::add_aresta(size_t v1,
                       size_t v2,
                       size_t capacidade,
                       char categoria,
                       std::vector<Aresta>::iterator rev)
{
    vertices[v1].add_aresta(v2, capacidade, categoria, rev);
}

Vertice &Grafo::operator[](size_t i)
{
    return vertices[i];
}

std::vector<Vertice>::iterator Grafo::begin()
{
    return vertices.begin();
}

std::vector<Vertice>::iterator Grafo::end()
{
    return vertices.end();
}