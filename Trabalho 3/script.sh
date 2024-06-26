#!/bin/bash

echo "Compilação do arquivo"
make

echo "Executando código para o primeiro arquivo"
./trabalho3 TPI_BC_COL_0.txt model0.lp > TPI_BC_COL_0_saida.txt

echo "Executando código para o segundo arquivo"
./trabalho3 TPI_BC_COL_1.txt model1.lp > TPI_BC_COL_1_saida.txt

echo "Executando código para o terceiro arquivo"
./trabalho3 TPI_BC_COL_2.txt model2.lp > TPI_BC_COL_2_saida.txt