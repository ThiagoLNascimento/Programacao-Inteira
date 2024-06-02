#include <iostream>
#include <fstream>
#include <string>
#include <ilcplex/ilocplex.h>
ILOSTLBEGIN
using namespace std;

int main(int argc, char *argv[]){

    IloEnv             env;   // declara Variável de ambiente do CPLEX
    IloModel     model(env);  // declara Variavel do modelo do CPLEX (que existe dentro do ambiente criado)
    IloBoolVarArray  w(env);  // criação do array para as variáveis binárias w_i caso a cor i em V seja utilizada
    IloCplex   cplex(model);

    ifstream file;
    // Nome do arquivo com o nome dado como argumento
    string input_file = argv[1];
    string output = argv[2];
    const char*output_file = output.c_str();

    file.open(input_file); 
    string line;
    if ( file.is_open() ) {
        // Leitura da primeira linha do arquivo
        getline(file, line); 
        char * cstr = new char [line.length()+1];
        std::strcpy (cstr, line.c_str());

        // Varíaveis referente às informações básicas do problema contidas na primeira linha

        string p = strtok(cstr, " ");
        string edges = strtok(NULL, " ");
        int vertex = atoi(strtok(NULL, " ")); // Quantidade de vértices do modelo
        int edge = atoi(strtok(NULL, " "));   // Quantidade de arestas do modelo
        int graph [vertex][vertex];

    
        // Variável binária x_i_j referente ao vértice i em V ter a cor j em V
        IloArray<IloBoolVarArray> x(env, vertex); 
        char var_name[100000];

        for(int i = 0; i < vertex ; i++){
            sprintf (var_name, "w_%d", (int)i);

            // Adição da variável w binária ao modelo
            w.add(IloBoolVar(env, var_name));
                
        }
            
        for(int i = 0; i < vertex ; i++){
        sprintf (var_name, "y_%d", (int)i);

            // Adição da variável w binária ao modelo
            w.add(IloBoolVar(env, var_name));    

            // Criação da variável x binária e com dimensão vertex
            x[i] = IloBoolVarArray(env, vertex); 

            for(int j = 0; j < vertex; j++){
                sprintf (var_name, "x_%d_%d", (int)i,(int)j);
                x[i][j] = IloBoolVar(env, var_name); 
                graph [i][j] = 0;
            }
        }

        // Preenchimento das arestas do grafo
        for (int i = 0; i < edge; i ++){ 
            getline (file, line);
            cstr = new char [line.length()+1];
            std::strcpy (cstr, line.c_str());

            string p = strtok(cstr, " ");
            int x1 = atoi(strtok(NULL, " ")) - 1;
            int x2 = atoi(strtok(NULL, " ")) - 1;

            // Adição da variável x_i_j ao modelo
            model.add(x[x1][x2]);
            graph[x1][x2] = 1;

        }

        // funcao objetivo, equação (1)
        IloExpr fo(env);

        for(int i=0; i < vertex; i++) {        
                fo += w[i];                                 
            }                           

        model.add(IloMinimize(env,fo,"f"));

        // Adição da restrição (2) na qual para todo i em V o somatório de x_i_j deve ser igual a 1
        IloConstraintArray color_for_vertice(env);
        
        for(int i=0; i < vertex; i++) {
            IloExpr constraint(env);                    
            for(int j=0; j < vertex; j++) {
                    constraint += x[i][j];                             
            }
            color_for_vertice.add(constraint == 1);
            constraint.end();     

        }

        model.add(color_for_vertice);

        
    
        // Adição da restrição (3) na qual para todo par ik em E e j entre 1 e N, a soma de xij + xkj deve ser menor ou igual a wj
        IloConstraintArray neighbor_different_colors(env);
        
        for(int i=0; i < vertex; i++) {
            for(int k=0; k < vertex; k++) {
                if(graph[i][k] != 0){
                    for(int j=0; j < vertex; j++) {
                        IloExpr constraint(env);
                        constraint += x[i][j] + x[k][j];
                        neighbor_different_colors.add(constraint <= w[j]); 
                        constraint.end();  
                    }
                }                                 
            }                 
        }

        model.add(neighbor_different_colors);

        // Adição da restrição (4) na qual para todo j entre 1 e n-1, wj deve ser maior ou igual que wj+1
        // Restrição para quebra de simetria

        IloConstraintArray symmetry(env);
        for (int j=0; j < vertex - 1; j++){
            IloExpr constraint(env);
            constraint += w[j];
            symmetry.add(constraint >= w[j+1]);
            constraint.end();
        }

        model.add(symmetry);

        cplex.exportModel(output_file);

        // Adição da restrição (5) na qual para todo j entre 1 e n, wj deve ser menor ou igual que o somátorio de xij
        // Restrição que aumenta a velocidade de execução

        IloConstraintArray restriction_to_strengthen(env);
        for (int j=0; j < vertex; j++){
            IloExpr constraint(env);
            for (int i=0; i < vertex; i++) {
                constraint += x[i][j];
            }
            restriction_to_strengthen.add(constraint >= w[j]);
            constraint.end();
        }

        model.add(restriction_to_strengthen);

        // Exportação do modelo para o Arquivo model%d, na qual %d é o número do modelo lido
        cplex.exportModel(output_file);
        cplex.solve();         // chama o "solver"
  
        cout << "Min=" << cplex.getObjValue() << endl; //  imprime solução do problema
        env.end(); 
    }
    else {
        cout << "Problema com a abertura do arquivo, verificar pasta e nome\n";
    }
 
    return 0;      
}