#include <limits>

#include "./../include/algoritmos.hpp"

CamadaBFS::CamadaBFS(size_t el, size_t pos, std::vector<Aresta>::iterator it)
{
    el_pos_it.push_back({el, pos, it});
}

void CamadaBFS::add_elemento(size_t el, size_t pos, std::vector<Aresta>::iterator it)
{
    el_pos_it.push_back({el, pos, it});
}

std::tuple<size_t, size_t, std::vector<Aresta>::iterator> &CamadaBFS::operator[](size_t i)
{
    return el_pos_it[i];
}

std::vector<std::tuple<size_t, size_t, std::vector<Aresta>::iterator>>::iterator CamadaBFS::begin()
{
    return el_pos_it.begin();
}

std::vector<std::tuple<size_t, size_t, std::vector<Aresta>::iterator>>::iterator CamadaBFS::end()
{
    return el_pos_it.end();
}

// -------

CamadaBFS &CaminhoBFS::operator[](size_t i)
{
    return camadas[i];
}

std::vector<std::vector<Aresta>::iterator>::iterator CaminhoBFS::begin()
{
    return caminho.begin();
}

std::vector<std::vector<Aresta>::iterator>::iterator CaminhoBFS::end()
{
    return caminho.end();
}

void CaminhoBFS::encontrar_caminho(Grafo &grafo)
{
    size_t s = 0, t = grafo.n_vertices - 1;
    std::vector<char> descoberto(grafo.n_vertices, 0);
    descoberto[s] = 1;
    camadas.push_back(CamadaBFS({s, s, grafo[s].begin()}));
    size_t camada = 0;

    while (!descoberto[t])
    {
        camadas.push_back(CamadaBFS());

        size_t pos = 0;
        for (auto &u_tupla : camadas[camada])
        {
            size_t u = std::get<0>(u_tupla);
            for (auto u_v_it = grafo[u].begin(); u_v_it != grafo[u].end(); u_v_it++)
            {
                auto &u_v = *u_v_it;
                if (u_v.cap == u_v.fluxo)
                {
                    continue;
                }

                if (!descoberto[u_v.v])
                {
                    descoberto[u_v.v] = 1;
                    camadas[camada + 1].add_elemento(u_v.v, pos, u_v_it);
                    if (u_v.v == t)
                    {
                        t_pos = pos;
                        break;
                    }
                }
            }
            if (descoberto[t])
            {
                break;
            }
            pos++;
        }

        camada++;
    }

    _montar_caminho();
}

void CaminhoBFS::_montar_caminho()
{
    std::vector<std::vector<Aresta>::iterator> caminho_rev;
    auto camada_it = camadas.rbegin();
    auto camada_el = (*camada_it)[t_pos];
    caminho_rev.push_back(std::get<2>(camada_el));
    camada_it++;

    while (camada_it != camadas.rend())
    {
        size_t el_pos = std::get<1>(camada_el);
        camada_el = (*camada_it)[el_pos];
        caminho_rev.push_back(std::get<2>(camada_el));
        camada_it++;
    }

    caminho = std::vector<std::vector<Aresta>::iterator>(caminho_rev.rbegin(), caminho_rev.rend());
}

// -------

void alg::aumentar_caminho(CaminhoBFS &caminho)
{
    size_t gargalo = std::numeric_limits<size_t>::max();
    for (const auto &aresta_it : caminho)
    {
        auto &aresta = *aresta_it;
        size_t balanco = aresta.cap - aresta.fluxo;
        if (balanco < gargalo)
        {
            gargalo = balanco;
        }
    }

    for (const auto &aresta_it : caminho)
    {
        auto &aresta = *aresta_it;
        aresta.add_fluxo(gargalo);

        if (aresta.cat == 'o')
        {
            auto &aresta_rev = *(aresta_it + 1);
            aresta_rev.sub_fluxo(gargalo);
        }
        else
        {
            auto &aresta_rev = *(aresta_it - 1);
            aresta_rev.sub_fluxo(gargalo);
        }
    }
}

void alg::ford_fulkerson(Grafo &grafo)
{
    while (true)
    {
        CaminhoBFS caminho;
        caminho.encontrar_caminho(grafo);
        if (caminho.camadas.size() == 1)
        {
            break;
        }
        aumentar_caminho(caminho);
    }
}