#include "question1.cpp"
#include <fstream>

bool test_existence (std::string s, std::vector<Sommet> list_sommet){
    // teste si il existe un sommet de nom "s" dans une liste de sommets
    for (int i=0 ; i<list_sommet.size() ; i++){ // Pour chaque sommet de la liste
        Sommet S2 = list_sommet.at(i);
        if (s == S2.get_name()){ // Si le sommet a le même nom
            return true ; // Alors le sommet de nom "s" existe déjà
        }
    }
    return false;
}

Sommet find_sommet(std::string s,  std::vector<Sommet> list_sommet){
    // renvoie le sommet de nom "s" dans la liste des sommets (sous réserve d'existence)
    for (int i=0 ; i<list_sommet.size() ; i++){ // Pour chaque sommet de la liste
        Sommet S2 = list_sommet.at(i);
        if (s == S2.get_name()){ // Si le sommet a le même nom
            return S2; // Alors on le renvoie
        }
    }
    throw "Le sommet est pas dans la liste !";
}

Graph read_list_ad(std::ifstream& fichier){
    // prend en argument un fichier texte, le lit et retourne un graphe avec des listes d'adjacence correspondant
    std::vector<Sommet> list_sommet;
    std::vector<Arete> list_arete_tot;
    if(fichier){
        std::string ligne;
        while(getline(fichier, ligne)){  // tant que l'on peut encore trouver une ligne
            int d;
            std::string s_1, s_2;
            fichier >> s_1 >> s_2 >>d; // On extrait du fichier les caractéristiques de l'arête : son étiquette d, son sommet source s_1 et son sommet d'arrivée s_2
            if (test_existence(s_1,list_sommet)==false){ // Si le premier sommet n'existe pas encore
                Sommet S1 = create_sommet(list_sommet.size(), s_1, list_sommet); // On le rajoute            
            }
            if (test_existence(s_2,list_sommet)==false){ // Idem avec le deuxième sommet
                Sommet S2 = create_sommet(list_sommet.size(), s_2, list_sommet);               
            }
            Sommet S1=find_sommet(s_1,list_sommet); // On cherche donc les sommets correspondants (maintenant ils existent forcément)
            Sommet S2=find_sommet(s_2,list_sommet);
            create_arete(d, S1,S2, list_arete_tot); // On crée l'arête
        }

        fichier.close(); // La lecture du fichier est terminée
        Graph graphe = create_graph(list_sommet, list_arete_tot); // On crée le graphe
        return graphe;
    }
    else{
        throw "ERREUR: Impossible d'ouvrir le fichier en lecture.";
    }
}

std::vector<Sommet> create_list_sommets_mat_ad(std::ifstream& fichier){
    // Dans un premier temps, on crée la liste des sommets, pour pouvoir correctement dimentioner mat_ad
    // Prend en argument un fichier texte, le lit et retourne la liste des sommets correspondante
    std::vector<Sommet> list_sommet;
    if(fichier){
        std::string ligne;
        while(getline(fichier, ligne)){  // tant que l'on peut encore trouver une ligne
            int d;
            std::string s_1, s_2;
            fichier >> s_1 >> s_2 >>d; // On extrait du fichier les caractéristiques de l'arête
            if (test_existence(s_1,list_sommet)==false){ // Si les sommets n'existent pas, on les crée
                Sommet S1 = create_sommet(list_sommet.size(), s_1, list_sommet);              
            }
            if (test_existence(s_2,list_sommet)==false){
                Sommet S2 = create_sommet(list_sommet.size(), s_2, list_sommet);               
            }
        }
        fichier.close(); // On a lu tout le fichier
        return list_sommet; // On a à présent tous les sommets
    }
    else{
        throw "ERREUR: Impossible d'ouvrir le fichier en lecture.";
    }
}

GraphWithMatrice read_mat_ad(std::ifstream& fichier, std::vector<Sommet> list_sommet){
    // prend en argument un fichier texte, et la liste des sommets, et retourne un graphe avec une matrice d'adjacence correspondant
    std::vector<double> column (list_sommet.size(),NAN);
    std::vector <std::vector <double>> mat_ad (list_sommet.size() , column); // La matrice vide
    if(fichier){
        std::string ligne;
        while(getline(fichier, ligne)){  // tant que l'on peut encore trouver une ligne
            int d;
            std::string s_1, s_2;
            fichier >> s_1 >> s_2 >>d; // On extrait du fichier les caractéristiques de l'arête
            Sommet S1=find_sommet(s_1,list_sommet); // Les sommets existent
            Sommet S2=find_sommet(s_2,list_sommet);
            create_arete2(d, S1,S2, mat_ad); // on crée l'arête correspondante
        }
        fichier.close(); // On a tout lu
        GraphWithMatrice graphe (list_sommet, mat_ad); // On crée le graphe
        return graphe;
    }
    else{
        throw "ERREUR: Impossible d'ouvrir le fichier en lecture.";
    }
}

void question2(){
    std::cout << std::endl << std::endl << std::endl << "Question 2 : " << std::endl;

    // On teste la lecture pour un graphe avec des listes d'adjacence
    std::cout << "Graphe créé avec des listes d'adjacence à partir du fichier texte : " << std::endl;
    std::ifstream fichier1("graphe.graph");
    Graph graphe1=read_list_ad(fichier1);
    graphe1.print(); 

    // On teste la lecture pour un graphe avec une matrice d'adjacence
    std::cout << "Graphe créé avec une matrice d'adjacence à partir du fichier texte : " << std::endl;
    std::ifstream fichier2("graphe.graph"); // Le fichier est modfié à chaque fois, il faut le réimporter
    std::vector <Sommet> list_sommets=create_list_sommets_mat_ad(fichier2);
    std::ifstream fichier3("graphe.graph");
    GraphWithMatrice graphe2=read_mat_ad(fichier3, list_sommets);
    graphe2.print();    
}