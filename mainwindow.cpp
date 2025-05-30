#[code](https://github.com/Ekani237/PROJET-SN-ALGO-CPP-SPRINT-2025/blob/80c6131135462305b2a8636271dd90134086e0f6/projets/groupe16/algo/code)
    btnCharger = new QPushButton("Charger les favoris", this);
    btnCharger->setStyleSheet("background-color: #ba68c8; color: black;");

    btnQuitter = new QPushButton("Quitter", this);
    btnQuitter->setStyleSheet("background-color: #616161; color: black;");

    listeFavoris = new QListWidget(this);
    listeFavoris->setStyleSheet("background-color: #424242; color: white; border: 1px solid #616161; selection-background-color: #616161;");

    QVBoxLayout* layout = new QVBoxLayout;

    //Centrer chaque bouton
    QPushButton* boutons[] = {btnAjouter, btnSupprimer, btnModifier, btnSauvegarder, btnCharger, btnQuitter};
    for(QPushButton* bouton : boutons)
    {
        bouton->setFixedSize(300, 35);
        bouton->setCursor(Qt::PointingHandCursor);
        QHBoxLayout* ligne = new QHBoxLayout;
        ligne->addStretch();
        ligne->addWidget(bouton);
        ligne->addStretch();
        layout->addLayout(ligne);
    }

    //Barre de recherche
    barreRecherche = new QLineEdit(this);
    barreRecherche->setPlaceholderText("Rechercher un favori...");
    layout->addWidget(barreRecherche);
    connect(barreRecherche, &QLineEdit::textChanged, this, &MainWindow::rechercherFavori);


    layout->addWidget(listeFavoris);
    central->setLayout(layout);

    //Connexion des boutons de la fenetre principale
    connect(btnAjouter, &QPushButton::clicked, this, &MainWindow::ajouterFavori);
    connect(btnSupprimer, &QPushButton::clicked, this, &MainWindow::supprimerFavori);
    connect(btnModifier, &QPushButton::clicked, this, &MainWindow::modifierFavori);
    connect(btnSauvegarder, &QPushButton::clicked, this, &MainWindow::sauvegarderFavoris);
    connect(btnCharger, &QPushButton::clicked, this, &MainWindow::ChargerFavoris);
    connect(btnQuitter, &QPushButton::clicked, this, &MainWindow::confirmerQuitter);
}

//Ajouter un favori
void MainWindow::ajouterFavori()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Ajouter un favori");

    QLineEdit* titreEdit = new QLineEdit(&dialog);
    QLineEdit* urlEdit = new QLineEdit(&dialog);

    QPushButton* okBtn = new QPushButton("OK", &dialog);
    QPushButton* cancelBtn = new QPushButton("Annuler", &dialog);

    QVBoxLayout* layout = new QVBoxLayout;

    QHBoxLayout* titreLayout = new QHBoxLayout;
    titreLayout->addWidget(new QLabel("Titre:", &dialog));
    titreLayout->addWidget(titreEdit);
    layout->addLayout(titreLayout);

    QHBoxLayout* urlLayout = new QHBoxLayout;
    urlLayout->addWidget(new QLabel("URL:", &dialog));
    urlLayout->addWidget(urlEdit);
    layout->addLayout(urlLayout);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);

    dialog.setFixedSize(400, 200);
    dialog.setLayout(layout);

    connect(okBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        QString titre = titreEdit->text();
        QString url = urlEdit->text();
        if (!titre.isEmpty() && !url.isEmpty())
        {
            gestionnaire.ajouter(titre.toStdString(), url.toStdString());
        }
    }
    afficherFavoris();
}


//Supprimer un favori
void MainWindow::supprimerFavori()
{
    bool ok;
    QString titre = QInputDialog::getText(this, "Supprimer un favori", "Titre: ", QLineEdit::Normal, "", &ok);
    if (ok && !titre.isEmpty())
    {
        if (gestionnaire.supprimer(titre.toStdString()))
        {
            QMessageBox::information(this, "Succès", "Favori supprimé.");
        }
        else
        {
            QMessageBox::warning(this, "Erreur", "Favori non trouvé.");
        }
    }
    afficherFavoris();
}

//Modifier un favori
void MainWindow::modifierFavori()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Modifier un favori");

    QLineEdit* oldTitreEdit = new QLineEdit(&dialog);
    QLineEdit* newTitreEdit = new QLineEdit(&dialog);
    QLineEdit* newUrlEdit = new QLineEdit(&dialog);
    QPushButton* okBtn = new QPushButton("OK", &dialog);
    QPushButton* cancelBtn = new QPushButton("Annuler", &dialog);

    QVBoxLayout* layout = new QVBoxLayout;

    QHBoxLayout* titreLayout = new QHBoxLayout;
    titreLayout->addWidget(new QLabel("Titre existant:", &dialog));
    titreLayout->addWidget(oldTitreEdit);
    layout->addLayout(titreLayout);

    QHBoxLayout* newTitreLayout = new QHBoxLayout;
    newTitreLayout->addWidget(new QLabel("Nouveau titre:", &dialog));
    newTitreLayout->addWidget(newTitreEdit);
    layout->addLayout(newTitreLayout);

    QHBoxLayout* newUrlLayout = new QHBoxLayout;
    newUrlLayout->addWidget(new QLabel("Nouvelle URL:", &dialog));
    newUrlLayout->addWidget(newUrlEdit);
    layout->addLayout(newUrlLayout);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);

    dialog.setFixedSize(400, 200);
    dialog.setLayout(layout);

    connect(okBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        std::string ancienTitre = oldTitreEdit->text().toStdString();
        std::string nouveauTitre = newTitreEdit->text().toStdString();
        std::string nouvelleUrl = newUrlEdit->text().toStdString();

        if (gestionnaire.modifier(ancienTitre, nouveauTitre, nouvelleUrl))
        {
            QMessageBox::information(this, "Succès", "Favori modifié.");
        }
        else
        {
            QMessageBox::warning(this, "Erreur", "Favori introuvable.");
        }
    }
    afficherFavoris();
}


//Afficher un favori
void MainWindow::afficherFavoris()
{
    listeFavoris->clear();
    listeFavoris->addItems(gestionnaire.afficher());
}

//Sauvegarder les favoris
void MainWindow::sauvegarderFavoris()
{
    QString nomFichier = QFileDialog::getSaveFileName(this, "Sauvegarder les favoris", "", "Fichiers texte (*.txt)");
    if (!nomFichier.isEmpty())
    {
        if (gestionnaire.sauvegarder(nomFichier.toStdString()))
        {
            QMessageBox::information(this, "Succès", "Favoris sauvegardes !");
        }
        else
        {
            QMessageBox::warning(this, "Erreur", "Echec de la sauvegarde.");
        }
    }
}

//Charger les favoris
void MainWindow::ChargerFavoris()
{
    QString nomFichier = QFileDialog::getOpenFileName(this, "charger", "", "Fichiers texte (*.txt)");
    if (!nomFichier.isEmpty())
    {
        if (gestionnaire.charger(nomFichier.toStdString()))
        {
            QMessageBox::information(this, "Succes", "Favoris charges !");
        }
        else
        {
            QMessageBox::warning(this, "Erreur", "Fichier introuvable.");
        }
    }
    afficherFavoris();
}

//Rechercher un favori
void MainWindow::rechercherFavori()
{
    QString recherche = barreRecherche->text().toLower();
    for (int i = 0; i < listeFavoris->count(); i++)
    {
        QListWidgetItem* item = listeFavoris->item(i);
        item->setHidden(!item->text().toLower().contains(recherche));
    }
}

//Quitter l'application
void MainWindow::confirmerQuitter()
{
    QMessageBox::StandardButton reponse = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment quitter ?", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        close();
    }
}
