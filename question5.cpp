#include <queue>
#include "question4.cpp"

class SommetWithLevel{ // On définit une classe où l'on rajoute le niveau d'un sommet (sa génération par rapport à un autre)
    Sommet s; // Le sommet
    int level; // son niveau
    public:
    SommetWithLevel (Sommet s, int level):
    s(s), level(level) {}
    //On crée des fonctions pour récupérer les valeurs dans la classe
    Sommet get_sommet(){
        return s;
    }
    int get_level(){
        return level;
    }
};

void parcours_de_graphe_en_largeur_list_ad(Graph graphe, int level_stop){
    // parcourt en largeur un graphe avec des listes d'adjacence, s'arrête à la génération level_stop
    std::vector <Sommet> list_sommet = graphe.getlist_sommet();
    std::vector<Listadjacence> list_listadjacence = graphe.getlist_listadjacence();
    Sommet sommet_visite =list_sommet.at(0);
    int level = 1;
    SommetWithLevel sommet_visite_with_level  (list_sommet.at(0),level); //level=0
    std::queue <SommetWithLevel> list_sommet_en_cours_de_visite; // file des sommets en cours de visite
    list_sommet_en_cours_de_visite.push(sommet_visite_with_level);
    while (list_sommet_en_cours_de_visite.empty()== false){ // tant qu'il reste des sommets dans notre file
        sommet_visite = list_sommet_en_cours_de_visite.front().get_sommet();
        int level = list_sommet_en_cours_de_visite.front().get_level();
        list_sommet_en_cours_de_visite.pop();
        if ((list_sommet.at(sommet_visite.get_num()).get_visited()==false) && (level<level_stop+1 || level_stop==0)){ // On arrive sur un nouveau sommet et sa génération est suffisament petite
            std::cout << std::endl << std::endl << "Niveau : " << level << std::endl ;
            std::cout << "Nouveau sommet : " ;
            sommet_visite.print();
            list_sommet.at(sommet_visite.get_num()).mark_visited(); // On le note comme visité
            Listadjacence list_adjacence_sommet_visite = list_listadjacence.at(sommet_visite.get_num());
            for (int i=0 ; i<list_adjacence_sommet_visite.getlist_arete().size() ; i++){ // Pour chaque sommet de la liste d'adjacence
                std::cout << "Nouvelle arête : " ; // On affiche l'arête
                list_adjacence_sommet_visite.getlist_arete().at(i).print();
                Sommet new_sommet = list_adjacence_sommet_visite.getlist_sommet().at(i);
                SommetWithLevel new_sommet_with_level (new_sommet,level+1);
                list_sommet_en_cours_de_visite.push(new_sommet_with_level); // Il faudra repartir de ce sommet pour continuer
            }
        }
    }
    std::cout << "Tout le graphe a été parcouru" << std::endl;
}



void parcours_de_graphe_en_largeur_mat_ad(GraphWithMatrice graphe, int level_stop){
    // parcourt en largeur un graphe avec des listes d'adjacence, s'arrête à la génération level_stop
    std::vector <Sommet> list_sommet = graphe.get_list_sommet();
    std::vector<std::vector<double>> mat_ad = graphe.get_mat_ad();
    Sommet sommet_visite =list_sommet.at(0);
    int level = 1;
    SommetWithLevel sommet_visite_with_level  (list_sommet.at(0),level); //level=0
    std::queue <SommetWithLevel> list_sommet_en_cours_de_visite; // file des sommets en cours de visite
    list_sommet_en_cours_de_visite.push(sommet_visite_with_level);
    while (list_sommet_en_cours_de_visite.empty()== false){ // tant qu'il reste des sommets dans notre file
        sommet_visite = list_sommet_en_cours_de_visite.front().get_sommet();
        int level = list_sommet_en_cours_de_visite.front().get_level();
        list_sommet_en_cours_de_visite.pop();
        if ((list_sommet.at(sommet_visite.get_num()).get_visited()==false) && (level<level_stop+1 || level_stop==0)){ // On arrive sur un nouveau sommet et sa génération est suffisament petite
            std::cout << std::endl<< std::endl << "Niveau : " << level << std::endl;
            std::cout << "Nouveau sommet : " ;
            sommet_visite.print();
            list_sommet.at(sommet_visite.get_num()).mark_visited(); // On le note comme visité
            for (int i=0 ; i<mat_ad.size() ; i++){ // Pour chaque élément de la ligne du sommet
                double n = mat_ad.at(sommet_visite.get_num()).at(i);
                if (std::isnan(n)== false){ // Il y a une arête entre ces deux sommets
                    Sommet new_sommet = list_sommet.at(i);
                    SommetWithLevel new_sommet_with_level (new_sommet, level+1);
                    Arete new_arete (n, sommet_visite, new_sommet);
                    std::cout << "Nouvelle arête : " ;
                    new_arete.print(); // On affiche l'arête correspondante
                    list_sommet_en_cours_de_visite.push(new_sommet_with_level);  // Il faudra repartir de ce sommet pour continuer
                }
            }
        }
    }
    std::cout << "Tout le graphe a été parcouru" << std::endl;
}

void question5(){
    std::cout << std::endl << std::endl << std::endl << "Question 5 : " << std::endl;


    // Test du parcours en largeur avec la représentation par liste d'adjacence
    std::cout << "Parcours en largeur de graphe avec liste d'adjacence : " << std::endl;
    Graph graphe1 = try_representation_with_list_ad();
    std::cout << "Avec n=0 (on veut tout le graphe) : " << std::endl;
    parcours_de_graphe_en_largeur_list_ad(graphe1,0);
    std::cout << std::endl << std::endl;
    std::cout << "Avec n=1 (on veut uniquement la première génération) : " << std::endl;
    parcours_de_graphe_en_largeur_list_ad(graphe1,1);
    std::cout << std::endl << std::endl;

    // Test du parcours en largeur avec la représentation par matrice d'adjacence
    std::cout << "Parcours en largeur de graphe avec matrice d'adjacence : " << std::endl;
    GraphWithMatrice graphe2 = try_representation_with_mad_ad();
    std::cout << "Avec n=0 (on veut tout le graphe) : " << std::endl;
    parcours_de_graphe_en_largeur_mat_ad(graphe2,0);
    std::cout << std::endl << std::endl;
    std::cout << "Avec n=1 (on veut uniquement la première génération) : " << std::endl;
    parcours_de_graphe_en_largeur_mat_ad(graphe2,1);
}