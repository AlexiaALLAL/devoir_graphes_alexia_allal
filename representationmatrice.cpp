#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "representationlistad.cpp" // On l'inclut pour avoir accès à la classe Sommet qui est encore utile et à create_sommet

void draw (std::vector<std::vector<double>> matrice){
    // affiche la matrice ligne par ligne
    for (int i=0 ; i<matrice.size() ; i++){
        for (int j=0 ; j<matrice.size() ; j++){
            std::cout << matrice.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}

class GraphWithMatrice { // On définit une classe pour les graphes définis avec une matrice d'adjacence
    std::vector<Sommet> list_sommet; // La liste des sommets du graphe (correspondant à leurs numéros)
    std::vector <std::vector <double>> mat_ad; // La matrice d'adjacence
    public :
    GraphWithMatrice(std::vector<Sommet> list_sommet, std::vector <std::vector <double>> mat_ad):
    list_sommet(list_sommet), mat_ad(mat_ad) {}
    //On crée des fonctions pour récupérer les valeurs dans la classe
    std::vector<Sommet> get_list_sommet(){
        return list_sommet;
    }
    std::vector <std::vector <double>> get_mat_ad(){
        return mat_ad;
    }
    void print(){ // Pour décrire le graphe, et vérifier que ce qu'on a fait fonctionne
        std::cout << "Voici une description du graphe : " << std::endl;
        std::cout << "Il contient " << list_sommet.size() << " sommets," << std::endl;
        std::cout << "La liste des sommets est : " << std::endl;
        for (int i =0; i<list_sommet.size(); i++){
            list_sommet.at(i).print();
        }
        std::cout << std::endl << "Voici la matrice d'adjacence : " << std::endl;
        draw (mat_ad);
    }
};

void create_arete2(int nbarete, Sommet S1, Sommet S2, std::vector <std::vector <double>>& mat_ad){
    // Crée une arête, et la rajoute dans la matrice d'adjacence
    mat_ad.at(S1.get_num()).at(S2.get_num()) = nbarete;
}

std::vector <std::vector <double>> initialise_mat_ad (std::vector<Sommet>& list_sommet){
    // Crée des sommets et des arêtes (les mêmes que précédemment), et les rentre dans des listes list_sommet et list_arete_tot
    Sommet S1 = create_sommet(0, "Ville 1", list_sommet); // On utilise la même fonction create_sommet que pour les listes d'adjacence
    Sommet S2 = create_sommet(1, "Ville 2", list_sommet);
    Sommet S3 = create_sommet(2, "Ville 3", list_sommet);
    Sommet S4 = create_sommet(3, "Ville 4", list_sommet);
    Sommet S5 = create_sommet(4, "Ville 5", list_sommet);
    std::vector<double> column (list_sommet.size(),NAN);
    std::vector <std::vector <double>> mat_ad (list_sommet.size() , column); // La matrice vide
    create_arete2(1, S1,S2, mat_ad);
    create_arete2(2, S1,S3, mat_ad);
    create_arete2(2, S1,S5, mat_ad);
    create_arete2(2, S2,S3, mat_ad);
    create_arete2(1, S3,S4, mat_ad);
    create_arete2(1, S4,S2, mat_ad);
    create_arete2(1, S4,S5, mat_ad);
    create_arete2(1, S5,S3, mat_ad);
    create_arete2(1, S5,S1, mat_ad);
    return mat_ad;
}

GraphWithMatrice try_representation_with_mad_ad(){
    // Renvoie un exemple de graphe représenté avec une matrice d'adjacence
    std::vector<Sommet> list_sommet = {};
    std::vector<std::vector<double>> mat_ad = initialise_mat_ad(list_sommet);
    GraphWithMatrice graphe (list_sommet, mat_ad);
    return graphe ;
}