#ifndef MENU_H
#define MENU_H
#include <vector>
#include "codificaciones.h"
#include <string>

int NumeroLineasArchivo(string nombreArchivo){
    string linea;
    int numero_linea_actual=0;
    ifstream archivo;
    archivo.open(nombreArchivo);
    while(getline(archivo, linea)){
        numero_linea_actual++;
    }
    archivo.close();
    return numero_linea_actual;
}

bool comprobarLectura( string nombredelarchivo){
    ifstream archivo;
    archivo.open(nombredelarchivo);
    if(!archivo){
        cerr << "No se puede abrir el archivo. No se encuentra." << endl;
        return false;
    }else{
        archivo.close();
        cout << "Verificacion exitosa" <<endl;
        return true;
    }
}

string leerUnaLinea(int numero_linea_deseada, string nombreArchivo){
    string linea;
    int numero_linea_actual=0;
    ifstream archivo;
    archivo.open(nombreArchivo);
    while(getline(archivo, linea)){
        if(numero_linea_actual==numero_linea_deseada){
            archivo.close();
            return linea;
        }
        numero_linea_actual++;
    }
}
string ponerCeros(string lineaBinString, int n){
    if(lineaBinString.length() < n){
        for(int x = lineaBinString.length(); x < n ; x++)
            lineaBinString += "0";
    }

    if((lineaBinString.length() % n) != 0){
        for(int x = (lineaBinString.length()%n); x < n ; x++)
            lineaBinString += "0";
    }
    return lineaBinString;
}


bool verificacionAdministrador(string nombreArchivo, int semilla_de_codificacion, int longitud){
    string contraseña_ingresada = " ";
    string contraseña_guardada= leerUnaLinea(0, nombreArchivo);
    cin >> contraseña_ingresada;
    contraseña_guardada= decodificarM2(contraseña_guardada, semilla_de_codificacion);
    contraseña_guardada= quitarCeros(contraseña_guardada, longitud);
    contraseña_guardada= convBinInt(contraseña_guardada);
    if(contraseña_guardada==contraseña_ingresada){
        return true;
    }else{
        return false;
    }
}

void EscribirContraseñasobreArchivo(string line, string nombreArchivo){
    ofstream archivo;
    archivo.open(nombreArchivo);
    archivo<<line<<endl;
    archivo.close();
}


bool esNumero(string str){
    for(char c : str){
        if((c < '0') || (c > '9')){
            return false;
        }
    }
    return true;
}

int numeroLegal(){
    string entrada;
    bool entradaValida = false;
    int numero = 0;

    while(!entradaValida){
        cout << "Ingrese la semilla de codificacion: ";
        cin >> entrada;

        entradaValida = esNumero(entrada);

        if(entradaValida){
            numero = 0;
            for (char c : entrada){
                numero = numero * 10 + (c - '0');
            }

            if(numero < 1){

                entradaValida = false;
            }
        }

        if(!entradaValida){
            cout << "Entrada invalida. Por favor, ingrese un numero entero mayor o igual a 1." << endl;
        }
    }

    return numero;
}

string CrearArhcivo(int& n, int &longitud, vector<int>& longitud_cedula, vector<int>& longitd_clave, vector<int>& longitud_saldo){
    //Primera parte: Pedir una contraseña para el administrados y encriptarla
    string nombre_nuevo_archivo= "Nuevo archivo.txt";
    string lecturaConsola = "";
    cout << "Ingrese la clave del administrador: " << endl;
    cin >> lecturaConsola;
    longitud = lecturaConsola.length();

    string lineaBin= "";

    for (int i = 0; i < longitud; i++) {
        char aux[9];
        convIntBin(aux, lecturaConsola[i]);
        lineaBin+= aux;
    }

    //cout << "La contraseña en binario es: " << lineaBin << endl;


    n = numeroLegal();

    int tamaño= lineaBin.length();
    if(tamaño < n){
        for(int x = tamaño; x < n ; x++)
            lineaBin += "0";
    }

    if((tamaño % n) != 0){
        for(int x = (tamaño % n); x < n ; x++)
            lineaBin += "0";
    }

    string contraseña_encriptada;

    contraseña_encriptada= codificarM2(lineaBin, n);

    EscribirContraseñasobreArchivo(contraseña_encriptada, nombre_nuevo_archivo);

    longitud_cedula.clear();
    longitud_cedula.shrink_to_fit();
    longitd_clave.clear();
    longitd_clave.shrink_to_fit();
    longitud_saldo.clear();
    longitud_saldo.shrink_to_fit();

    return nombre_nuevo_archivo;
}

void ComprobacionDeArchivo(string& nombre_del_archivo, bool& bandera, int &semilla, int& longitud, vector<int>& longitud_cedula, vector<int>& longitd_clave, vector<int>& longitud_saldo){
    bool inicio= true;
    char respuesta= ' ';
    string verificar_tamaño= "";
    char respuesta_creacion_archivo= ' ';

    while(inicio){
        cout <<"\nVerficacion de los archivos del sistema...\n"<<endl;
        bandera= comprobarLectura(nombre_del_archivo);
        if(bandera){
            inicio= false;
        }else{
            cout << "Desea crear un archivo? (Ingrese s(si) o n(no)): "; cin >>verificar_tamaño;
            if(verificar_tamaño.length() > 1){
                cout << "Solo puedes ingresar una letra" <<endl;
            }else if (verificar_tamaño.length() ==1 && verificar_tamaño != "\n"){
                respuesta= verificar_tamaño[0];
                switch(respuesta){
                case 's':
                    nombre_del_archivo = CrearArhcivo(semilla, longitud, longitud_cedula, longitd_clave, longitud_saldo);
                    break;
                case 'n':
                {
                    bool bandera_interna= true;
                    while(bandera_interna){
                        cout<< "Desea salir del programa? (Ingrese s(si) o n(no)):  "; cin >> respuesta_creacion_archivo;
                        switch(respuesta_creacion_archivo){
                        case 's':{
                            inicio=false;
                            bandera_interna=false;}
                        break;
                        case 'n':
                            bandera_interna= false;
                            break;
                        default:
                            cout << "\nIngresaste una opcion invalida" <<endl;
                            break;
                        }
                        cin.clear();
                        cin.ignore(255, '\n');
                    }
                }
                break;
                default:
                    cout << "\nIngresaste una opcion invalida" <<endl;
                    cin.clear();
                    cin.ignore(255, '\n');
                    break;
                }
            }
        }
    }

}


#endif // MENU_H
