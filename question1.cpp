#include <iostream>
#include <string>
#include <vector>
#include "representationmatrice.cpp" // L'autre représentation est incluse dans celle par matrice



GraphWithMatrice switch_listad_to_matad (Graph graphe){
    // passe de la représentation par liste d'adjacence à la représentation par matrice
    std::vector<Sommet> list_sommet = graphe.getlist_sommet();
    std::vector<Listadjacence> list_listadjacence = graphe.getlist_listadjacence();

    std::vector<double> column (list_sommet.size(),NAN);
    std::vector <std::vector <double>> mat_ad (list_sommet.size() , column); // La matrice d'adjacence vide
    for (int i=0; i<list_sommet.size();i++){ // Pour chaque sommet
        Listadjacence list_ad = list_listadjacence.at(i); // Liste d'adjacence du sommet
        std::vector<Arete> list_arete = list_ad.getlist_arete(); // Liste des arêtes qui partent de ce sommet
        std::vector<Sommet> list_sommetad = list_ad.getlist_sommet(); // Liste des sommets adjacents
        for (int j=0 ; j<list_sommetad.size() ; j++){
            create_arete2(list_arete.at(j).getnb(),list_sommet.at(i),list_sommetad.at(j), mat_ad); //On rajoute l'arête dans le graphe
        }
    }
    GraphWithMatrice new_graph (list_sommet, mat_ad); // On crée le graphe avec matrice
    return new_graph;    
}

Graph switch_matad_to_listad (GraphWithMatrice graphe){
    // passe de la représentation par matrice à la représentation par liste d'adjacence
    std::vector<Sommet> list_sommet = graphe.get_list_sommet();
    std::vector <std::vector <double>> mat_ad = graphe.get_mat_ad();

    std::vector<Arete> list_arete_tot = {}; // La liste des arêtes du graphe, vide
    for (int i = 0 ; i < mat_ad.size() ; i++){
        for (int j=0 ; j< mat_ad.size() ; j++){ // Pour chaque case de la matrice = pour chaque arête potentielle
            if (std::isnan(mat_ad.at(i).at(j)) == false) { // Il y a un nombre, donc il y a une arête entre les sommets
                create_arete (mat_ad.at(i).at(j),list_sommet.at(i),list_sommet.at(j), list_arete_tot); // On la rajoute donc dans la liste
            }
        }
    }
    Graph new_graph = create_graph(list_sommet,list_arete_tot); // On peut alors créer le graphe
    return new_graph;
}

void question1(){
    std::cout << "Question 1 : " << std::endl << std::endl << std::endl;
    
    // On vérifie que les représentations fonctionnent :
    std::cout << "Graphe créé avec des listes d'adjacence : " << std::endl;
    Graph graphe1 = try_representation_with_list_ad();
    graphe1.print();
    std::cout << std::endl << std::endl << "Graphe créé avec une matrice d'adjacence : " << std::endl;
    GraphWithMatrice graphe2 = try_representation_with_mad_ad();
    graphe2.print();    
    std::cout << std::endl << std::endl << std::endl << std::endl;

    // On vérifie que les fonctions pour passer de l'une à l'autre fonctionnent :
    std::cout << "Graphe avec matrice créé à partir d'un graphe avec des listes d'adjacence : " << std::endl;
    GraphWithMatrice new_graph1 = switch_listad_to_matad (graphe1);
    new_graph1.print();
    std::cout << std::endl << std::endl << "Graphe avec listes d'adjacence créé à partir d'un graphe avec matrice : " << std::endl;
    Graph new_graph2 = switch_matad_to_listad (graphe2);
    new_graph2.print();
}