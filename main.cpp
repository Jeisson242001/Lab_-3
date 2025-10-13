#include "Menu.h"

using namespace std;

int main(){
    string prueba; cout<<"Ingrese la cadena a codificar: "; getline(cin, prueba);

    int longitud= prueba.length();
    string lineaBin= "";
    string final = "";
    int semilla; cout<<"Ingrese la semilla de codificacion: "; cin >>semilla;

    for (int i = 0; i < longitud; i++) {
        char aux[9];
        convIntBin(aux, prueba[i]);
        lineaBin+= aux;
    }
    cout<<"Linea ingresada en bytes: "<< lineaBin<<endl;
    lineaBin = ponerCeros(lineaBin, semilla);
    cout<<"Linea ingresada en bytes segun la semilla: "<< lineaBin<<endl;
    codificarM1(lineaBin, semilla);
    cout<<"Linea codificada con el metodo 1: "<<lineaBin<<endl;
    decodificarM1(lineaBin, semilla);
    cout<<"Decodificada con ceros: " <<lineaBin<<endl;
    lineaBin= quitarCeros(lineaBin, longitud);
    cout<<"Decodificada sin los ceros: "<<lineaBin<<endl;
    final = convBinInt(lineaBin); cout<<"Linea original en bytes: "<< lineaBin<<endl;
    cout<<"Linea original: "<< final<<endl;
    cout<<"\n\n"<<endl;
    lineaBin = ponerCeros(lineaBin, semilla);
    cout<<"Linea ingresada en bytes segun la semilla: "<< lineaBin<<endl;
    lineaBin= codificarM2(lineaBin, semilla);
    cout<<"Linea codificada con el metodo 2: "<<lineaBin<<endl;
    lineaBin= decodificarM2(lineaBin, semilla);
    cout<<"Decodificada con ceros: " <<lineaBin<<endl;
    lineaBin= quitarCeros(lineaBin, longitud);
    cout<<"Decodificada sin los ceros: "<<lineaBin<<endl;
    final = convBinInt(lineaBin); cout<<"Linea original en bytes: "<< lineaBin<<endl;
    cout<<"Linea original: "<< final<<endl;
}