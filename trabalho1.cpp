#include <iostream>
#include <fstream>
#include <string>
#include <ilcplex/ilocplex.h>
ILOSTLBEGIN
using namespace std;

int main(int argc, char *argv[]){

    IloEnv             env;   // declara Variável de ambiente do CPLEX
    IloModel     model(env);  // declara Variavel do modelo do CPLEX (que existe dentro do ambiente criado)
    IloBoolVarArray  y(env);  // criação do array para as variáveis binárias y_i caso a facilidade i em I seja criada
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

        // Varíaveis referente às informações básicas do problema contidas na primeira linha
        const char *const_line = line.c_str();
        char *end1, *end2, *end3, *end4;

        int facility = (int)strtof (const_line, &end1);
        int client = (int)strtof (end1, &end2);
        float cost_fixed = strtof (end2, &end3);
        int max_resource = (int)strtof (end3, &end4);
        int num_lines = (int)strtof (end4, NULL);

        float g [facility][client]; // gij do modelo
        int p [facility][client]; // pij do modelo

        // Inicialização do vetor com valor default 0, será utilizado para verificar se uma aresta pertence ou não ao modelo
        for (int i = 0; i < facility; i ++){
            for (int j = 0; j < client; j++){
                g[i][j] = 0;
                p[i][j] = 0;
            }
        }

        // Variável binária x_i_j referente à cliente j em J ser atendido pela facildiade i em I
        IloArray<IloBoolVarArray> x(env, facility); 
        char var_name[100000];

        for(int i = 0; i < facility ; i++){
            sprintf (var_name, "y_%d", (int)i);

            // Adição da variável y binária ao modelo
            y.add(IloBoolVar(env, var_name));
            
        }
        
        for(int i = 0; i < facility ; i++){
            sprintf (var_name, "y_%d", (int)i);

            // Adição da variável y binária ao modelo
            y.add(IloBoolVar(env, var_name));    

            // Criação da variável x binária e com dimensão client
            x[i] = IloBoolVarArray(env, client); 

            for(int j = 0; j < client; j++){
                	sprintf (var_name, "x_%d_%d", (int)i,(int)j);
                    x[i][j] = IloBoolVar(env, var_name); 
            }
        }

        // Preenchimento das matrizes de custo variavel, consumo e adição dos elementos ao modelo
        for (int i = 0; i < num_lines; i ++){ 
            getline (file, line);
            const_line = line.c_str();

            int origen = (int)strtof(const_line, &end1) - 1;
            int destiny = (int)strtof(end1, &end2) - 1;
            float variable_cost = strtof(end2, &end3);
            int resource = (int)strtof (end3, NULL);

            
            g[origen][destiny] = variable_cost;
            p[origen][destiny] = resource;

            // Adição da variável x_i_j ao modelo
            model.add(x[origen][destiny]);   

            // Adição da restrição (3) na qual para toda aresta x_i_j em E o seu valor deve ser menor ou igual a y_i
            model.add(x[origen][destiny] <= y[origen]);
        }

        // funcao objetivo, equação (1)
        IloExpr fo(env);

        for(int i=0; i < facility; i++) {        
            fo += cost_fixed * y[i];          
            for(int j=0; j < client; j++) {
                fo += g[i][j] * x[i][j];                                 
            }                           
        }

        model.add(IloMinimize(env,fo,"f"));

        // Adição da restrição (2) na qual para todo j em J o somatório de x_i_j deve ser igual a 1
        // ou seja, todo cliente deve ser atendido por somente uma facildiade
        IloConstraintArray client_answered(env);
        
        for(int i=0; i < client; i++) {
            IloExpr constraint(env);                         
            for(int j=0; j < facility; j++) {
                if(p[j][i] != 0){
                    constraint += x[j][i];
                }                                 
            }
            client_answered.add(constraint == 1);       
            constraint.end();                               
        }

        model.add(client_answered);   
        
        // Restrição (4) na qual para todo i em I o somatório de p_i_j vezes x_i_j deve ser menor ou igual a Q vezes y_i
        // ou seja, uma facilidade deve atender somente a quantidade disponível pelos seus recursos
        IloConstraintArray facility_resources_consumed(env);
        
        for(int i=0; i < facility; i++) {
            IloExpr constraint(env);                         
            for(int j=0; j < client; j++) {
                constraint += x[i][j] * p[i][j];                                 
            }
            facility_resources_consumed.add(constraint <= y[i] * max_resource);
            constraint.end();                               
        }

        model.add(facility_resources_consumed);  

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