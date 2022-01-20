#include <string>
#include <vector>
#include <stack>
#include "question3.cpp"

void parcours_de_graphe_iteratif_list_ad(Graph graphe){
    // parcourt de manière itérative un graphe avec des listes d'adjacence
    std::vector <Sommet> list_sommet = graphe.getlist_sommet();
    std::vector<Listadjacence> list_listadjacence = graphe.getlist_listadjacence();
    Sommet sommet_visite = list_sommet.at(0);
    std::stack <Sommet> list_sommet_en_cours_de_visite; // pile des sommets en cours de visite
    list_sommet_en_cours_de_visite.push(sommet_visite);
    while (list_sommet_en_cours_de_visite.empty()== false){ // tant qu'il reste des sommets dans notre pile
        sommet_visite = list_sommet_en_cours_de_visite.top();
        list_sommet_en_cours_de_visite.pop();
        if (list_sommet.at(sommet_visite.get_num()).get_visited()==false){ // On arrive sur un nouveau sommet
            std::cout <<std::endl << "Nouveau sommet : " ;
            sommet_visite.print();
            list_sommet.at(sommet_visite.get_num()).mark_visited(); // On le note comme visité
            Listadjacence list_adjacence_sommet_visite = list_listadjacence.at(sommet_visite.get_num());
            for (int i=0 ; i<list_adjacence_sommet_visite.getlist_arete().size() ; i++){// Pour chaque sommet de la liste d'adjacence
                std::cout << "Nouvelle arête : " ; // On affiche l'arête
                list_adjacence_sommet_visite.getlist_arete().at(i).print();
                Sommet new_sommet = list_adjacence_sommet_visite.getlist_sommet().at(i);
                list_sommet_en_cours_de_visite.push(new_sommet); // Il faudra repartir de ce sommet pour continuer
            }
        }
    }
    std::cout << "Tout le graphe a été parcouru" << std::endl;
}

void parcours_de_graphe_iteratif_mat_ad(GraphWithMatrice graphe){
    // parcourt de manière récursive un graphe avec des listes d'adjacence
    std::vector <Sommet> list_sommet = graphe.get_list_sommet();
    std::vector<std::vector<double>> mat_ad = graphe.get_mat_ad();
    Sommet sommet_visite = list_sommet.at(0);
    std::stack <Sommet> list_sommet_en_cours_de_visite; // pile des sommets en cours de visite
    list_sommet_en_cours_de_visite.push(sommet_visite);

    while (list_sommet_en_cours_de_visite.empty()== false){ // tant qu'il reste des sommets dans notre pile
        sommet_visite = list_sommet_en_cours_de_visite.top();
        list_sommet_en_cours_de_visite.pop();
        if (list_sommet.at(sommet_visite.get_num()).get_visited()==false){ // On arrive sur un nouveau sommet
            std::cout <<std::endl << "Nouveau sommet : " ;
            sommet_visite.print();
            list_sommet.at(sommet_visite.get_num()).mark_visited(); // On le note comme visité
            for (int i=0 ; i<mat_ad.size() ; i++){ // Pour chaque élément de la ligne du sommet
                double n = mat_ad.at(sommet_visite.get_num()).at(i);
                if (std::isnan(n)== false){ // Il y a une arête entre ces deux sommets
                    Sommet new_sommet = list_sommet.at(i);
                    Arete new_arete (n, sommet_visite, new_sommet);
                    std::cout << "Nouvelle arête : " ;
                    new_arete.print(); // On affiche l'arête correspondante
                    list_sommet_en_cours_de_visite.push(new_sommet); // Il faudra repartir de ce sommet pour continuer
                }
            }
        }
    }
    std::cout << "Tout le graphe a été parcouru" << std::endl;
}


void question4(){
    std::cout << std::endl << std::endl << std::endl << "Question 4 : " << std::endl;

    // Test de la fonction itérative avec la représentation par liste d'adjacence
    std::cout << "Parcours itératif de graphe avec liste d'adjacence : " << std::endl;
    Graph graphe1 = try_representation_with_list_ad();
    parcours_de_graphe_iteratif_list_ad(graphe1);

    std::cout << std::endl << std::endl << std::endl << std::endl;
    std::cout << "Parcours itératif de graphe avec matrice d'adjacence : " << std::endl;
    //Test de la fonction itérative avec la représentation par matrice d'adjacence
    GraphWithMatrice graphe2 = try_representation_with_mad_ad();
    parcours_de_graphe_iteratif_mat_ad(graphe2);
}