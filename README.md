### Programacao-Inteira
 
Código referente aos trabalhos para a Matéria de Programção Inteira 2024.1 na UFF feito pelo aluno Thiago Lopes Nascimento.

Para os trabalhos foi pedido a execução de problemas de programção inteira, para isso foi utilizado o cplex como base para resolver o problema, portanto é necessário que ele já esteja baixado anteiormente no computador.


## Solução

Cada problema está contido em uma pasta diferente, na qual inicialmente possuem o código c++ contendo todo o código necessário para solucionar o problema, o arquivo make para compilação do programa além de um script sh que facilita a execução de todo o programa.
O código em c++ necessita de argumentos, o primeiro dele sendo o arquivo de entrada e o segundo o nome de um arquivo de saída para verificação do modelo resultante.

Além desses 3 arquivos, também está presente os arquivos de entrada utilizados como instâncias do problema em questão.

## Execução

Foi criado um arquivo Makefile que permite a compilação do código, vale destacar que nas linhas 5 e 6 dele deve-se **MUDAR** o diretório para aquele em que a pasta CPLEXDIR e CONCERTDIR se encontram no computador que deseja rodar o programa.

Além disso também foi feito um arquivo script.sh para facilitar a execução do programa.

Ao executar o comando `$ sh script.sh ` dentro da pasta designada para cada trabalho, o comando make também será realizado, sendo assim compilando o código e além disso será criado para cada arquivo de instância 2 novos arquivos, um sendo o módelo criado pelo código e o outro sendo a saída do programa contendo a solução para aquela instância.
