#!/bin/bash

echo "Compilação do arquivo"
make

echo "Executando código para o primeiro arquivo"
./trabalho1 TPI_F_0.txt model0.lp > TPI_F_0_saida.txt

echo "Executando código para o segundo arquivo"
./trabalho1 TPI_F_1.txt model1.lp > TPI_F_1_saida.txt

echo "Executando código para o terceiro arquivo"
./trabalho1 TPI_F_2.txt model2.lp > TPI_F_2_saida.txt