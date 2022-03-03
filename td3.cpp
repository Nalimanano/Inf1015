#pragma once
// Structures mémoires pour une collection de films.

#include <string>
#include <cassert>
#include "gsl/span"
#include <memory>
using gsl::span;
using namespace std;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.

class ListeFilms {
public:
	ListeFilms() = default;
	ListeFilms(const std::string& nomFichier);
	ListeFilms(const ListeFilms& l) { assert(l.elements == nullptr); } // Pas demandé dans l'énoncé, mais on veut s'assurer qu'on ne fait jamais de copie de liste, car la copie par défaut ne fait pas ce qu'on veut.  Donc on ne permet pas de copier une liste non vide (la copie de liste vide est utilisée dans la création d'un acteur).
	~ListeFilms();
	void ajouterFilm(Film* film);
	void enleverFilm(const Film* film);
	shared_ptr<Acteur> trouverActeur(const std::string& nomActeur) const;
	span<Film*> enSpan() const;
	int size() const { return nElements; }

private:
	void changeDimension(int nouvelleCapacite);

	int capacite = 0, nElements = 0;
	Film** elements = nullptr; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.
	bool possedeLesFilms_ = false; // Les films seront détruits avec la liste si elle les possède.
};

class ListeActeurs {
public:
	ListeActeurs() {};
	ListeActeurs(int capacite, int nElements)
		: capacite_(capacite), nElements_(nElements)
	{
		elements_ = make_unique<shared_ptr<Acteur> []>(capacite);
	}

	ListeActeurs operator = (ListeActeurs const& liste2)
	{
		ListeActeurs liste1;
		liste1.capacite_ = capacite_ + liste2.capacite_;
		liste1.nElements_ = nElements_ + liste2.nElements_;
		return liste1;

	}
	ListeActeurs(const ListeActeurs& liste1) { capacite_ = liste1.capacite_; nElements_ = liste1.nElements_; }

	int getCapacite() { return capacite_; }
	int getNElements() { return nElements_; }

	shared_ptr<Acteur>* getElement() { return elements_.get(); }

	span<shared_ptr<Acteur>> spanListeActeurs() const { return span(elements_.get(), nElements_); }

	void ajouterActeurListe(shared_ptr<Acteur> nom) { elements_[nElements_] = nom; }
	void supprimerFilmListe(Acteur* nom) { elements_[nElements_] = nullptr; }
	// Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
private:
	int capacite_ = 0;
	int nElements_ = 0;
	unique_ptr<shared_ptr<Acteur>[]> elements_ = make_unique<shared_ptr<Acteur>[]>(1);
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
