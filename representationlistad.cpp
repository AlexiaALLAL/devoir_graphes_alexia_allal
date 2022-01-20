#include <iostream>
#include <string>
#include <vector>

// Dans ce fichier, on crée tout ce dont on a besoin pour manipuler un graphe avec des listes d'adjacence

class Sommet{ // On définit une classe pour les sommets
    int num ; // le numéro du sommet (sa place dans la liste complète des sommets)
    std::string name ; // le nom du sommet
    bool visited; // ça nous sera utile dans la suite pour savoir si le sommet a déjà été visité dans les parcours de graphe
    
    public :
    Sommet (int num, std::string name): // Quand on définit un sommet, il est automatiquement marqué comme non-visité
    num(num), name(name), visited(false) {}
    void print (){ // Une fonction pour écrire le sommet :
    std::cout << "Numéro du sommet : " << num << ", Nom du sommet : " <<name<< std::endl;
    }
    //On crée des fonctions pour récupérer les valeurs dans la classe
    std::string get_name() { 
        return name;
    }
    int get_num() {
        return num;
    }
    bool get_visited(){
        return visited;
    }
    void mark_visited(){ //Pour noter que le sommet a été visité
        visited=true;
    }
};

class Arete{ // On définit une classe pour les arêtes
    int nbarete; // L'étiquette de l'arête
    Sommet sommet1; //L'arête va du sommet1 au sommet2
    Sommet sommet2;
    public :
    Arete (int nbarete, Sommet sommet1, Sommet sommet2):
    nbarete(nbarete), sommet1(sommet1), sommet2(sommet2) {}

    void print (){ // Pour décrire l'arête
    std::cout << "Numéro arête : " <<nbarete<< " Va du sommet " << sommet1.get_name() << " au sommet " << sommet2.get_name() << std::endl;
    }
    //On crée des fonctions pour récupérer les valeurs dans la classe
    int getnb (){
        return nbarete;
    }
    Sommet getsommet1 (){
        return sommet1;
    }
    Sommet getsommet2 (){
        return sommet2;
    }
};

class Listadjacence{ // On définit une classe pour la liste d'adjacence d'un sommet
    Sommet sommet ; // Le sommet source de la liste
    std::vector<Arete> list_arete ; // La liste des arêtes qui partent de ce sommet
    std::vector<Sommet> list_sommet; // La liste des sommets reliés par des arêtes (dans le même ordre que pour list_arete)
    public :
    Listadjacence (Sommet sommet, std::vector<Arete> list_arete, std::vector<Sommet> list_sommet):
    sommet(sommet), list_arete(list_arete), list_sommet(list_sommet) {}
    //On crée des fonctions pour récupérer les valeurs dans la classe
    Sommet getsommet(){
        return sommet;
    }
    std::vector<Arete> getlist_arete(){
        return list_arete;
    }
    std::vector<Sommet> getlist_sommet(){
        return list_sommet;
    }
    void print(){ // Pour décrire la liste d'adjacence
        std::cout << "Sommet source : " << sommet.get_name()<< std::endl ;
        for (int i=0 ; i<list_sommet.size() ; i++){
            std::cout << "Arête : " ;
            list_arete.at(i).print();
        }
    }
};

class Graph{ // On définit une classe pour la totalité du graphe
    std::vector<Sommet> list_sommet ; //La liste des sommets du graphe
    std::vector<Listadjacence> list_listadjacence ; //La liste des listes d'adjacence, dans le même ordre que les sommets
    public :
    Graph (std::vector<Sommet> list_sommet, std::vector<Listadjacence> list_listadjacence):
    list_sommet(list_sommet), list_listadjacence(list_listadjacence) {}
    //On crée des fonctions pour récupérer les valeurs dans la classe
    std::vector<Sommet> getlist_sommet(){
        return list_sommet;
    }
    std::vector<Listadjacence> getlist_listadjacence(){
        return list_listadjacence;
    }
    void print(){ // Pour décrire le graphe, et vérifier que ce qu'on a fait fonctionne
        std::cout << "Voici une description du graphe : " << std::endl;
        std::cout <<"Il contient " << list_sommet.size() << " sommets," << std::endl;
        std::cout<< "Voici la liste des noms des sommets, ainsi que leur liste d'adjacence : "<< std::endl;
        for (int i=0 ; i<list_sommet.size() ; i++){ // Pour chaque sommet
            std::cout <<i<< "  "; //On affiche son numéro
            std::cout << "Sommet : " <<list_sommet.at(i).get_name() << std::endl; // On affiche son nom
            std::cout << "Liste d'adjacence : ";
            list_listadjacence.at(i).print(); // On affiche sa liste d'ajacence
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

Sommet create_sommet (int num, std::string name, std::vector<Sommet>& list_sommet){
    // Renvoie un sommet, et le rajoute dans une liste de sommet totaux
    Sommet S (num, name);
    list_sommet.push_back(S);
    return S;
}

void create_arete (int nbarete, Sommet S1, Sommet S2, std::vector<Arete>& list_arete_tot){
    // Crée une arête, et la rajoute dans une liste d'arêtes totale
    Arete arete (nbarete, S1,S2);
    list_arete_tot.push_back(arete);
}

Listadjacence create_list_ad (Sommet S, std::vector<Arete> list_arete_tot){
    // Crée la liste d'adjacence du Sommet S en cherchant les arêtes utiles dans une liste d'arêtes totale
    std::vector<Arete> list_arete = {}; // La liste des arêtes partant du sommmet, à compléter
    std::vector<Sommet> list_sommet = {}; // La liste des sommets adjacents à S, à compléter
    int n= list_arete_tot.size();
    for (int i=0 ; i<n ; i++){ // Pour chaque arête existante
        Arete arete = list_arete_tot.at(i);
        Sommet sommet_source = arete.getsommet1();
        if (sommet_source.get_name() == S.get_name()){ // On regarde si l'arête part du sommet S
            list_arete.push_back(arete);
            list_sommet.push_back(arete.getsommet2());
        }
    }
    Listadjacence listad (S, list_arete, list_sommet);
    return listad;
}

Graph create_graph(std::vector<Sommet> list_sommet, std::vector<Arete> list_arete_tot){
    // Crée un graphe à partir d'une liste de sommets et d'une liste d'arêtes totale
    std::vector<Listadjacence> list_listadjacence = {};
    for (int i=0 ; i<list_sommet.size() ; i++){ // Pour chaque sommet,
        Sommet S = list_sommet.at(i);
        Listadjacence listadS = create_list_ad(S,list_arete_tot); // On crée sa liste d'adjacence
        list_listadjacence.push_back(listadS); // Et on la rajoute dans la liste totale
    }
    Graph graphe (list_sommet, list_listadjacence);
    return graphe;
}

void initialise_list_ad (std::vector<Sommet>& list_sommet, std::vector<Arete>& list_arete_tot){
    // Crée des sommets et des arêtes (un peu au hasard), et les rentre dans des listes list_sommet et list_arete_tot
    Sommet S1 = create_sommet(0, "Ville 1", list_sommet);
    Sommet S2 = create_sommet(1, "Ville 2", list_sommet);
    Sommet S3 = create_sommet(2, "Ville 3", list_sommet);
    Sommet S4 = create_sommet(3, "Ville 4", list_sommet);
    Sommet S5 = create_sommet(4, "Ville 5", list_sommet);
    create_arete(1, S1,S2, list_arete_tot);
    create_arete(1, S1,S3, list_arete_tot);
    create_arete(1, S1,S5, list_arete_tot);
    create_arete(1, S2,S3, list_arete_tot);
    create_arete(1, S3,S4, list_arete_tot);
    create_arete(1, S4,S2, list_arete_tot);
    create_arete(1, S4,S5, list_arete_tot);
    create_arete(1, S5,S3, list_arete_tot);
    create_arete(1, S5,S1, list_arete_tot);
}

Graph try_representation_with_list_ad (){
    // Renvoie un exemple de graphe représenté avec les listes d'adjacence
    std::vector<Sommet> list_sommet = {};
    std::vector<Arete> list_arete_tot = {};
    initialise_list_ad (list_sommet, list_arete_tot);
    Graph graphe = create_graph(list_sommet, list_arete_tot);
    return graphe;
}