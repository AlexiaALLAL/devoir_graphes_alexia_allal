#include "question5.cpp"

class SommetWithDistance{ // On définit une classe où l'on rajoute la distance du sommet (à un sommet que l'on choisira plus tard)
    Sommet s;
    double distance;
    public:
    SommetWithDistance (Sommet s, double distance):
    s(s), distance(distance) {}
    Sommet get_sommet(){
        return s;
    }
    double get_distance(){
        return distance;
    }
    void change_distance(double d){ // Pour mettre à jour la distance d'un sommet
        distance = d;
    }
};

class SommetAndPredecesseur{ // On définit un classe où on peut associer à un sommet son prédécesseur. Ca nous sera utile pour retrouver le chemin qui donne la plus courte distance
    SommetWithDistance s;
    SommetWithDistance predecesseur;
    public:
    SommetAndPredecesseur (SommetWithDistance s,SommetWithDistance predecesseur):
    s(s), predecesseur(predecesseur){}
    SommetWithDistance get_sommet(){
        return s;
    }
    SommetWithDistance get_predecesseur(){
        return predecesseur;
    }
};

std::vector <SommetWithDistance> initialisation (std::vector<Sommet> list_sommet){ //met la valeur infinie à tous les sommets
    // transforme la liste des sommets en SommetWithDistance, en leur mettant à tous une distance infinie (pour le moment)
    std::vector <SommetWithDistance> new_list_sommet ;
    for (int i=0; i<list_sommet.size(); i++){
        SommetWithDistance new_sommet (list_sommet.at(i), INFINITY);
        new_list_sommet.push_back(new_sommet);
    }
    return new_list_sommet;
}

SommetWithDistance find_min(std::vector<SommetWithDistance> list){
    // renvoie le sommet dont la distance est minimale dans une liste de SommetWithDistance
    double min=INFINITY;
    int idmin = -1;
    for (int i=0 ; i<list.size() ; i++){ // On parcourt toute la liste
        if (list.at(i).get_distance() < min){ // Si l'un des éléments a une distance plus faible
            min=list.at(i).get_distance(); // Il devient le min
            idmin=i;
        }
    }
    return list.at(idmin);
}

void upload_distances (SommetWithDistance& new_s, SommetWithDistance s, std::vector<std::vector<double>> mat_ad, std::vector<SommetAndPredecesseur>& predecesseurs){
    // teste si le nouveau sommet new_s peut être atteint plus rapidement en passant par s
    // Si c'est le cas, la fonction met à jour la distance de new_s et retient que le prédécesseur de new_s est s
    double possible_distance =  s.get_distance() + mat_ad.at(s.get_sommet().get_num()).at(new_s.get_sommet().get_num()); // distance en passant par s
    if (new_s.get_distance()>possible_distance){ // Si cette distance est plus faible
        new_s.change_distance(possible_distance); // On remplace la distance de new_s
        SommetAndPredecesseur new_pathway (new_s, s);
        predecesseurs.push_back(new_pathway); // On mémorise le chemin
    }
}

int find_index(SommetWithDistance S, std::vector<SommetWithDistance> list){
    // trouve la position d'un SommetWithDistance dans une liste de SommetWithDistance
    for (int i=0 ; i<list.size() ; i++){
        Sommet S2 = list.at(i).get_sommet();
        if (S.get_sommet().get_name() == S2.get_name()){
            return i;
        }
    }
    throw "Le sommet est pas dans la liste !";
}

SommetWithDistance find_sommet_distance_from_number (int num, std::vector<SommetWithDistance> list_sommet){
    // renvoie le SommetWithDistance correspondant à un numéro donné, en le cherchant dans une liste de SommetWithDistance
    for (int i = 0 ; i<list_sommet.size() ; i++){
        SommetWithDistance sommet = list_sommet.at(i);
        if (sommet.get_sommet().get_num()== num){
            return sommet;
        }
    }
    throw "Le sommet est pas dans la liste !";
}

bool test_appartenance (SommetWithDistance S, std::vector<SommetWithDistance> list_sommet){
    // teste si un SommetWithDistance est dans la liste donnée
    int n = list_sommet.size();
    for (int i=0 ; i<n ; i++){
        SommetWithDistance S2 = list_sommet.at(i);
        if (S.get_sommet().get_name() == S2.get_sommet().get_name()){
            return true;
        }
    }
    return false;
}

SommetAndPredecesseur find_som_in_list (SommetWithDistance s, std::vector<SommetAndPredecesseur> predecesseurs){
    // Renvoie le SommetAnndPredecesseur en le cherchant dans une liste
    int n = predecesseurs.size();
    for (int i=0 ; i<n ; i++){
        if (predecesseurs.at(i).get_sommet().get_sommet().get_num()== s.get_sommet().get_num()){
            return predecesseurs.at(i);
        }
    }
    throw "Le sommet est pas dans la liste !";
}

void print_result(SommetWithDistance s_end_with_distance, std::vector<SommetAndPredecesseur> predecesseurs, Sommet s_start, std::vector<SommetWithDistance> new_list_sommet){
    // affiche le chemin en remontant les prédécesseurs
    std::stack<SommetAndPredecesseur> chemin; // on remplit le chemin à l'envers, une structure LIFO est plus adaptée
    SommetAndPredecesseur s_with_predecesseur = find_som_in_list(s_end_with_distance,predecesseurs);
    while (s_with_predecesseur.get_predecesseur().get_sommet().get_num() != s_start.get_num()){ // tant qu'on est pas retourné au sommet de départ
        chemin.push(s_with_predecesseur);
        SommetWithDistance pred= s_with_predecesseur.get_predecesseur();
        s_with_predecesseur = find_som_in_list(pred,predecesseurs); //on cherche le predecesseur de ce sommet
    }
    std::cout << "On va de : ";
    s_start.print();
    std::cout << "A : ";
    chemin.top().get_predecesseur().get_sommet().print(); // on affiche le premier
    while (chemin.empty()==false){ // tant qu'on a pas affiché tous les sommets
        std::cout <<std::endl << "On va de : ";
        chemin.top().get_predecesseur().get_sommet().print();
        std::cout << "A : ";
        chemin.top().get_sommet().get_sommet().print();
        chemin.pop();
    }
    std::cout << std::endl << std::endl ;
}

float algo_dijkstra(GraphWithMatrice graphe, Sommet s_start, Sommet s_end){
    // implémente l'algorithme de Dijkstra
    std::vector <Sommet> list_sommet = graphe.get_list_sommet();
    std::vector<std::vector<double>> mat_ad = graphe.get_mat_ad();
    // Initialisation :
    std::vector <SommetWithDistance> new_list_sommet = initialisation(list_sommet);
    new_list_sommet.at(s_start.get_num()).change_distance(0); // Le sommet de départ est à une distance 0
    std::vector <SommetWithDistance> list_sommet_restants= new_list_sommet;
    std::vector <SommetAndPredecesseur> predecesseurs; // liste des sommets avec leur prédecesseur

    while (list_sommet_restants.empty()== false){ // tant qu'il reste des sommets à considérer
        SommetWithDistance sommet_visite = find_min(list_sommet_restants); // on sélectionne le plus proche
        int position = find_index(sommet_visite, list_sommet_restants);
        list_sommet_restants.erase(list_sommet_restants.begin()+position); // on l'efface de la liste des sommets restants
        for (int i=0 ; i<mat_ad.size() ; i++){ // pour chaque sommet
            double n = mat_ad.at(sommet_visite.get_sommet().get_num()).at(i);
            if (std::isnan(n)== false){ // Il y a une arête entre ces deux sommets
                SommetWithDistance new_sommet = find_sommet_distance_from_number(i, new_list_sommet);
                if (test_appartenance(new_sommet, list_sommet_restants)==true){ // s'il n'a pas déjà été considéré
                    int k=find_index(new_sommet,list_sommet_restants);
                    upload_distances(list_sommet_restants.at(k), sommet_visite, mat_ad, predecesseurs); // on met sa distance à jour
                    upload_distances(new_list_sommet.at(i), sommet_visite, mat_ad, predecesseurs);
                }
            }
        }
    }
    SommetWithDistance s_end_with_distance = new_list_sommet.at(s_end.get_num());
    print_result(s_end_with_distance, predecesseurs, s_start, new_list_sommet);
    return s_end_with_distance.get_distance();
}

void question6(){
    std::cout << std::endl << std::endl << std::endl << "Question 6 : " << std::endl;

    std::cout << "On implémente l'algorithme de Dijkstra pour la représentation par matrice d'adjacence" << std::endl << std::endl;
    GraphWithMatrice graphe = try_representation_with_mad_ad();
    Sommet s_start = graphe.get_list_sommet().at(0);
    Sommet s_end = graphe.get_list_sommet().at(3);
    std::cout<<"On cherche la distance entre le point de départ : " << std::endl;
    s_start.print();
    std::cout << "Et le point d'arrivée : " << std::endl;
    s_end.print();
    float d=algo_dijkstra(graphe,s_start,s_end);
    std::cout << "La distance vaut : "<< d << std::endl;
}