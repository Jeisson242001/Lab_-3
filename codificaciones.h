#ifndef CODIFICACIONES_H
#define CODIFICACIONES_H
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

using namespace std;

//Esta función aplica las reglas de la decodificación uno
void aplicarReglasInv(string &grupo, string &grupoAnterior){

    int unosAnterior = 0, cerosAnterior = 0;

    for(char bit : grupoAnterior){
        if (bit == '1'){
            unosAnterior++;
        } else{
            cerosAnterior++;
        }
    }

    if(unosAnterior == cerosAnterior){

        for (char &bit : grupo){
            bit = (bit == '1') ? '0' : '1';
        }

    } else if(unosAnterior > cerosAnterior){
        int tamaño= grupo.length();
        for (int i = 2; i < tamaño; i += 3){
            grupo[i] = (grupo[i] == '1') ? '0' : '1';
        }
    } else{
        int tamaño= grupo.length();
        for (int i = 1; i < tamaño; i += 2){
            grupo[i] = (grupo[i] == '1') ? '0' : '1';
        }
    }
}


//Esta función decodifica bajo el método uno
void decodificarM1(string &cadena, int n){

    int longitud = cadena.length();
    string resultado = "";

    string primerBloque = cadena.substr(0, n);

    for(char &bit : primerBloque){
        bit = (bit == '1') ? '0' : '1';
    }

    resultado += primerBloque;

    string grupoAnterior = primerBloque;

    for(int i = n; i < longitud; i += n){
        string grupo = cadena.substr(i, n);
        aplicarReglasInv(grupo, grupoAnterior);
        resultado += grupo;
        grupoAnterior = grupo;
    }
    cadena = resultado;
}

//Esta función decodifica bajo el método dos
string decodificarM2(string cadena, int n){
    int longitud = cadena.length();
    string resultado = "";

    for (int i = 0; i < longitud; i += n){
        string grupo = cadena.substr(i, n);

        char primerBit = grupo[0];

        for (int j = 1; j < n; j++){
            grupo[j - 1] = grupo[j];
        }
        grupo[n - 1] = primerBit;

        resultado += grupo;
    }

    return resultado;
}

#endif // CODIFICACIONES_H
