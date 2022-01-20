#include "question6.cpp"

class ResultFloydWarshall{ // On crée une classe pour renvoyer les deux matrices de résultat de l'algorithme
    std::vector<std::vector<double>> D;
    std::vector<std::vector<double>> P;
    public:
    ResultFloydWarshall(std::vector<std::vector<double>> D, std::vector<std::vector<double>> P):
    D(D), P(P){}
    std::vector<std::vector<double>> get_D(){
        return D;
    }
    std::vector<std::vector<double>> get_P(){
        return P;
    }
};

void print(std::vector<std::vector<double>> mat){
    // affiche une matrice
    for (int i=0 ; i<mat.size(); i++){
        for (int j=0 ; j<mat.size();j++){
            std::cout << mat.at(i).at(j) << "  ";
        }
        std::cout << std::endl;
    }  
}

std::vector<std::vector<double>> initD (GraphWithMatrice graphe){
    // initialise le matrice D, qui à terme doit contenir, pour chaque terme (i,j), la distance de i à j.
    std::vector<std::vector<double>> mat_ad = graphe.get_mat_ad();
    int n = mat_ad.size();
    std::vector<double> column (n,INFINITY);
    std::vector<std::vector<double>> D(n,column);
    for (int i=0 ; i<n ; i++){
        for (int j=0 ; j<n ; j++){
            double val=mat_ad.at(i).at(j);
            if (std::isnan(val)== false){ // Si les deux sommets sont reliés
                D.at(i).at(j) = val;
            }
            if (i==j){ // la distance entre un sommet et lui même est 0
                D.at(i).at(j)=0;
            }
        }
    }
    return D;
}

std::vector<std::vector<double>> initP (GraphWithMatrice graphe){
    // initialise le matrice P, qui à terme doit contenir, pour chaque terme (i,j), le prédécesseur de j dans le plus court chemin entre i et j
    std::vector<std::vector<double>> mat_ad = graphe.get_mat_ad();
    int n = mat_ad.size();
    std::vector<double> column (n,NAN);
    std::vector<std::vector<double>> P(n,column);
    for (int i=0 ; i<n ; i++){
        for (int j=0 ; j<n ; j++){
            double val=mat_ad.at(i).at(j);
            if (std::isnan(val)== false){ // il y a une arête entre les deux sommets
                P.at(i).at(j) = i; // Le predecesseur est donc i
            }
        }
    }
    return P;
}

ResultFloydWarshall algo_FloydWarshall (GraphWithMatrice graphe){
    // renvoie les résultats de l'algorithme de Floyd et Warshall
    std::vector <Sommet> list_sommet = graphe.get_list_sommet();
    std::vector<std::vector<double>> mat_ad = graphe.get_mat_ad();
    std::vector<std::vector<double>> D = initD(graphe);
    std::vector<std::vector<double>> P = initP(graphe);
    int n = mat_ad.size();
    for (int k=0 ; k<n ; k++){
        for (int i=0 ; i<n ; i++){
            for (int j=0 ; j<n ; j++){
                if (D.at(i).at(j) > D.at(i).at(k) + D.at(k).at(j)){
                    D.at(i).at(j)= D.at(i).at(k)+D.at(k).at(j);
                    P.at(i).at(j)=P.at(k).at(j);
                }
            }
        }
    }
    ResultFloydWarshall result (D,P);
    return result;
}

void print_all_pathways(GraphWithMatrice graphe, ResultFloydWarshall results ){
    std::vector<std::vector<double>> D = results.get_D();
    std::vector<std::vector<double>> P = results.get_P();
    // affiche tous les chemins trouvés pour un graphe
    std::vector <Sommet> list_sommet = graphe.get_list_sommet();
    for (int i=0 ; i<P.size() ; i++){
        for (int j=0 ; j< P.size() ; j++){ //pour tous les chemins entre i et j
            std::cout << std::endl << std::endl << "On cherche le plus court chemin entre les sommets " << std::endl;
            list_sommet.at(i).print();
            list_sommet.at(j).print();
            std::cout << "La distance du plus court chemin est " << D.at(i).at(j) << std::endl;
            std::cout <<"On passe par les sommets suivants : " << std::endl;
            int k=j;
            std::stack <int> to_print; // pile des sommets qui restent à imprimer
            while (k != i){
                to_print.push(k);
                k=P.at(i).at(k);
            }
            while(to_print.empty()== false){
                k = to_print.top();
                list_sommet.at(k).print(); // On affiche chaque sommet du chemin
                to_print.pop();
            }
        }
    }
}

void question7(){
    std::cout << std::endl << std::endl << std::endl << "Question 7 : " << std::endl;

    std::cout << "On implémente l'algorithme de Floyd et Warshall pour la représentation par matrice d'adjacence" << std::endl << std::endl;
    GraphWithMatrice graphe = try_representation_with_mad_ad();
    ResultFloydWarshall result = algo_FloydWarshall(graphe);
    std::vector<std::vector<double>> D = result.get_D();
    std::vector<std::vector<double>> P = result.get_P();
    std::cout << "La matrice D des distances entre i et j : " << std::endl << std::endl;
    print(D);
    std::cout << std::endl << std::endl;
    std::cout << "La matrice P des prédecesseurs de j dans le plus court chemin entre i et j: " << std::endl << std::endl;
    print(P);
    std::cout << std::endl << std::endl;
    std::cout << "Tous les chemins trouvés pour un graphe : " << std::endl << std::endl;
    print_all_pathways(graphe,result);
}