#ifndef GESTIONNAIRE_DE_FICHIERS_HPP
#define GESTIONNAIRE_DE_FICHIERS_HPP

#include <QStringList>
#include <string>
#include "Favori_node.hpp"

class GestionnaireFavoris
{
    public:
        GestionnaireFavoris();
        ~GestionnaireFavoris();
    
        void ajouter(const std::string titre, const std::string url);
        bool supprimer(const std::string titre);
        QStringList afficher() const;
        bool modifier (const std::string ancienTitre, const std::string nouveauTitre, const std::string nouvelleUrl);
        bool sauvegarder(const std::string &nomFichier) const;
        bool charger(const std::string &nomFichier);

    private:
        FavoriNode* tete;
};

#endif
