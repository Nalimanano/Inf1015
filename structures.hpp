#pragma once
// Structures mémoires pour une collection de films.

#include <string>

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.


class ListeFilms
{
public:
	// constructeur
	ListeFilms() 
	{
		int capacite = 0;
		int nElements = 0;
		Film** elements = nullptr;
	}


	void ajoutfilm(Film* film);
	void enleverfilm(Film* film);
	
	Acteur* trouverActeur(const string& nom);
	Acteur* lireActeur(istream& fichier);
	void suprimerListFilm();
	void afficherListeFilms();
private:
	int capacite;
	int nElements;
	Film** elements;

};

struct ListeActeurs {
	int capacite, nElements;
	Acteur** elements; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
};

struct Film
{
	std::string titre, realisateur; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie, recette; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs;
};

struct Acteur
{
	std::string nom; int anneeNaissance; char sexe;
	ListeFilms joueDans;
};
