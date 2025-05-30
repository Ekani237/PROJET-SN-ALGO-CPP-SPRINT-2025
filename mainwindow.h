#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include "Gestionnaire_de_fichiers.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void ajouterFavori();
    void supprimerFavori();
    void modifierFavori();
    void confirmerQuitter();
    void afficherFavoris();
    void sauvegarderFavoris();
    void ChargerFavoris();
    void rechercherFavori();

private:
    QPushButton* btnAjouter;
    QPushButton* btnSupprimer;
    QPushButton* btnModifier;
    QPushButton* btnAfficher;
    QPushButton* btnSauvegarder;
    QPushButton* btnCharger;
    QPushButton* btnQuitter;
    QListWidget* listeFavoris;
    QLineEdit* barreRecherche;
    GestionnaireFavoris gestionnaire;
};
#endif // MAINWINDOW_H
