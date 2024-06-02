#!/bin/bash

echo "Compilação do arquivo"
make

echo "Executando código para o primeiro arquivo"
./trabalho2 TPI_COL_1.txt model1.lp > TPI_COL_1_saida.txt

echo "Executando código para o segundo arquivo"
./trabalho2 TPI_COL_2.txt model2.lp > TPI_COL_2_saida.txt

echo "Executando código para o terceiro arquivo"
./trabalho2 TPI_COL_3.txt model3.lp > TPI_COL_3_saida.txt