#ifndef MENU_H
#define MENU_H
#include <vector>
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

#endif // MENU_H
