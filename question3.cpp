#include "question2.cpp"

void fonction_recursive_listad (Sommet& sommet, std::vector<Sommet>& list_sommet, std::vector<Listadjacence>& list_listadjacence ){
    // fonction récursive qui parcourt un graphe avec des listes d'adjacence
    std::cout <<std::endl << "Nouveau sommet : " ;
    sommet.print(); // On arrive sur un nouveau sommet
    list_sommet.at(sommet.get_num()).mark_visited(); // On le note comme visité
    Listadjacence list_ad_sommet = list_listadjacence.at(sommet.get_num());
    int n = list_ad_sommet.getlist_sommet().size();
    for (int i=0 ; i< n ; i++){ // Pour chaque sommet de la liste d'adjacence
        Sommet new_sommet = list_ad_sommet.getlist_sommet().at(i);
        std::cout << "Nouvelle arête : " ; // On affiche l'arête
        list_ad_sommet.getlist_arete().at(i).print();
        if (list_sommet.at(new_sommet.get_num()).get_visited()== false){
            // Si le sommet n'est pas visité, on recommence l'algorithme en partant de ce sommet
            fonction_recursive_listad(new_sommet,list_sommet, list_listadjacence);
        }
    }
}

void parcours_de_graphe_recursif_list_ad (Graph graphe){
    // parcourt de manière récursive un graphe avec des listes d'adjacence
    std::vector <Sommet> list_sommet = graphe.getlist_sommet();
    std::vector<Listadjacence> list_listadjacence = graphe.getlist_listadjacence();
    fonction_recursive_listad(list_sommet.at(0),list_sommet, list_listadjacence); // On démarre du premier sommet
    std::cout << "Tout le graphe a été parcouru" << std::endl;
}

void fonction_recursive_matad(Sommet& sommet, std::vector <Sommet>& list_sommet, std::vector<std::vector<double>> mat_ad){
    // fonction récursive qui parcourt un graphe avec une matrice d'adjacence
    std::cout << std::endl << "Nouveau sommet : " ;
    sommet.print(); // On arrive sur un nouveau sommet
    list_sommet.at(sommet.get_num()).mark_visited(); // On le note comme visité
    for (int i=0 ; i<mat_ad.size() ; i++){ // Pour chaque élément de la ligne du sommet
        double n = mat_ad.at(sommet.get_num()).at(i);
        if (std::isnan(n)== false){ // Il y a une arête entre ces deux sommets
            Sommet new_sommet = list_sommet.at(i);
            Arete new_arete (n, sommet, new_sommet);
            std::cout << "Nouvelle arête : " ;
            new_arete.print(); // On affiche l'arête correspondante
            // Si le sommet n'est pas visité, on recommence l'algorithme en partant de ce sommet
            if (list_sommet.at(new_sommet.get_num()).get_visited()== false){
                fonction_recursive_matad(new_sommet, list_sommet, mat_ad);
            }
        }
    }
}

void parcours_de_graphe_recursif_matad(GraphWithMatrice graphe){
    // parcourt de manière récursive un graphe avec une matrice d'adjacence
    std::vector <Sommet> list_sommet = graphe.get_list_sommet();
    std::vector<std::vector<double>> mat_ad = graphe.get_mat_ad();
    fonction_recursive_matad(list_sommet.at(0), list_sommet, mat_ad);
    std::cout << "Tout le graphe a été parcouru" << std::endl;
}

void question3(){
    std::cout << std::endl << std::endl << std::endl << "Question 3 : " << std::endl;

    // Test de la fonction récursive avec la représentation par liste d'adjacence
    std::cout << "Parcours récursif de graphe avec liste d'adjacence : " << std::endl;
    Graph graphe1 = try_representation_with_list_ad();
    parcours_de_graphe_recursif_list_ad(graphe1);

    std::cout << std::endl << std::endl << std::endl << std::endl;
    std::cout << "Parcours récursif de graphe avec matrice d'adjacence : " << std::endl;
    //Test de la fonction récursive avec la représentation par matrice d'adjacence
    GraphWithMatrice graphe2 = try_representation_with_mad_ad();
    parcours_de_graphe_recursif_matad(graphe2);
}