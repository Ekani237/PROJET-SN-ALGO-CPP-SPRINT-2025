#ifndef FAVORI_HPP
#define FAVORI_HPP

#include <string>

struct FavoriNode
{
    std::string m_titre;
    std::string m_url;
    FavoriNode* suivant;

    FavoriNode(std::string titre, std::string url) : m_titre(titre), m_url(url), suivant(nullptr)
    {

    }
};

#endif