### Programacao-Inteira
 
Código referente ao primeiro trabalho para a Matéria de Programção Inteira 2024.1 na UFF.

Para o trabalho foi pedido a execução de 3 instâncias de um problema de programção inteira, para isso foi utilizado o cplex como base para resolver o problema, portanto é necessário que ele já esteja baixado anteiormente no computador.
O problema tem como uma função de minimização como objetivo além de necessitar de 3 restrições diferentes.

## Solução

Para resolver o problema foi criado um código c++ cujo nome é trabalho1.cpp, nele está presente todo o código que permite a solução e para a sua execução é necessário dois argumentos, o primeiro dele sendo o arquivo de entrada e o segundo o nome de um arquivo de saída para verificação do modelo resultante.

## Execução

Foi criado um arquivo Makefile que permite a compilação do código, vale destacar que nas linhas 5 e 6 dele deve-se **MUDAR** o diretório para aquele em que a pasta CPLEXDIR e CONCERTDIR se encontram no computador que deseja rodar o programa.

Além disso também foi feito um arquivo script.sh para facilitar a execução do programa.

Ao executar o comando `$ sh script.sh ` o comando make também será realizado, sendo assim compilando o código e além disso será criado 6 arquivos diferentes, 3 deles sendo os modelos criados pelo código com o nome *modelx.lp* e os outros 3 a saída do programa com a solução do problema, com os nomes *TPI_F_x_saida.txt*, onde x é o número do arquivo de entrada, podendo ser 0, 1 ou 2.
