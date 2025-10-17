#include "Menu.h"


using namespace std;

int main()
{
    bool bandera= false;
    string nombre_del_archivo= "sudo.txt";
    int semilla_De_codificacion=4; int longitud=4;
    vector <int> longitudes_cedula_usuarios={10,7};
    vector <int> longitudes_claves_usuarios={8, 8};
    vector <int> longitudes_saldos_usuarios={5, 4};
    int posicion_archivo_usuario=0;

    ComprobacionDeArchivo(nombre_del_archivo, bandera, semilla_De_codificacion, longitud, longitudes_cedula_usuarios, longitudes_claves_usuarios, longitudes_saldos_usuarios);

    while(bandera){
        int eleccion_menu_ingreso=0;
        cout << "\nBIENVENIDO A NUESTRO SISTEMA! \n" << endl;
        cout << "Seleccione un modo de ingreso: " <<endl;
        cout << "1. Administrador" <<endl;
        cout << "2. Usuario" <<endl;
        cout << "3. Salir del sistema" <<endl;

        try{

            if(!(cin >> eleccion_menu_ingreso)){
                throw 1;

            }else if(eleccion_menu_ingreso!=1 && eleccion_menu_ingreso!=2 && eleccion_menu_ingreso!=3){
                throw 2;

            }else if(eleccion_menu_ingreso==1){
                bool bandera_menu_admin= true;
                while(bandera_menu_admin){
                    bool verificacion_administrador= verificacionAdministrador(nombre_del_archivo, semilla_De_codificacion, longitud);
                    if(verificacion_administrador){
                        bool menu_interno_admin=true;
                        char respuesta_menu_admin = ' ';
                        while(menu_interno_admin){
                            cout << "\nSeleccione una opción: " <<endl;
                            cout << "1. Crear usuarios"<<endl;
                            cout << "2. Salir de la cuenta" <<endl;

                            string verificar_tamaño= "";
                            cin >> verificar_tamaño;
                            if(verificar_tamaño.length() > 1){
                                cout << "Solo puedes ingresar una letra" <<endl;
                            }else if (verificar_tamaño.length() ==1 && verificar_tamaño != "\n"){
                                respuesta_menu_admin= verificar_tamaño[0];
                                switch(respuesta_menu_admin){
                                case '1':{
                                    cout<<"\nCreando usuario..."<<endl;
                                    CrearUsuario(nombre_del_archivo, semilla_De_codificacion, longitudes_cedula_usuarios, longitudes_claves_usuarios, longitudes_saldos_usuarios);
                                }
                                break;
                                case '2':
                                    bandera_menu_admin=false;
                                    menu_interno_admin= false;
                                    break;
                                default:
                                    cout << "\nIngresaste una opcion invalida" <<endl;
                                    cin.clear();
                                    cin.ignore(255, '\n');
                                    break;
                                }
                            }
                        }
                    }else{
                        cout <<"Contraseña incorrecta"<<endl;
                    }
                }

            }else if(eleccion_menu_ingreso==2){
                char salir_usuario=' ';
                bool bandera_validacion_usuario= true;
                int numero_de_linea_principal;
                bool bandera_repetir_menu_usuario= false;

                while(bandera_validacion_usuario){

                    if(ValidacionUsuario(nombre_del_archivo, semilla_De_codificacion, numero_de_linea_principal, longitudes_cedula_usuarios, posicion_archivo_usuario)){
                        bool validacion_clave_usuario=true;

                        while(validacion_clave_usuario){
                            string clave;
                            cout<<"Ingrese la clave: ";cin >> clave;
                            string clave_guardada= leerUnaLinea(numero_de_linea_principal+1, nombre_del_archivo);
                            clave_guardada= decodificarM2(clave_guardada, semilla_De_codificacion);
                            clave_guardada= quitarCeros(clave_guardada, longitudes_claves_usuarios[posicion_archivo_usuario]);
                            clave_guardada= convBinInt(clave_guardada);
                            if(clave==clave_guardada){
                                bandera_repetir_menu_usuario= true;;
                                validacion_clave_usuario=false;
                                bandera_validacion_usuario=false;

                            }else{
                                cout<<"Clave incorrecta"<<endl;
                            }
                        }

                    }else{
                        cout<< "La cedula ingresada no se encuentra registrada. "<<endl;
                        bool miban=true;
                        while(miban){
                            cout <<"Quiere volver a intentarlo? (s/n): ";
                            salir_usuario= VerificarTamaño();
                                switch(salir_usuario){
                            case 's':{
                                miban=false;
                            }
                            break;
                            case 'n':
                                bandera_validacion_usuario=false;
                                miban=false;
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


                while(bandera_repetir_menu_usuario){
                    cout << "\nSeleccione una opción: " <<endl;
                    cout << "1. Consultar saldo"<<endl;
                    cout << "2. Retirar dinero" <<endl;
                    cout << "3. Salir de la cuenta"<<endl;
                    char respuesta_menu_usuario= ' ';

                    string verificar_tamaño= "";
                    cin >> verificar_tamaño;
                    if(verificar_tamaño.length() > 1){
                        cout << "Solo puedes ingresar una letra" <<endl;
                    }else if (verificar_tamaño.length() ==1 && verificar_tamaño != "\n"){
                        respuesta_menu_usuario= verificar_tamaño[0];
                        switch(respuesta_menu_usuario){
                        case '1':{
                            int valorsaldo=0;
                            bool verificacion_saldo= VerificarSaldo(valorsaldo, numero_de_linea_principal+2, nombre_del_archivo, semilla_De_codificacion, longitudes_saldos_usuarios[posicion_archivo_usuario]);
                            if(verificacion_saldo){
                                cout << "\nSu saldo es de: " << valorsaldo << " pesos\n" <<endl;
                                cout <<"Se le cobraran 1000 pesos por consultar su saldo\n"<<endl;
                                valorsaldo-= 1000;
                                ActualizarSaldo(valorsaldo, nombre_del_archivo, numero_de_linea_principal+2, semilla_De_codificacion, longitudes_saldos_usuarios, posicion_archivo_usuario);
                            }else{
                                cout<<"Tiene menos de mil pesos, por lo tanto no puede consultar su saldo"<<endl;
                            }

                        }
                            break;
                        case '2':{
                            long long int cantidad_a_retirar= stoi(ValidarCedula_o_Saldo("la cantidad a retirar"));
                            int valorsaldo=0;

                            bool verificacion_saldo= VerificarSaldoRetirar(valorsaldo, numero_de_linea_principal+2, nombre_del_archivo, semilla_De_codificacion, longitudes_saldos_usuarios[posicion_archivo_usuario], cantidad_a_retirar);
                            if(verificacion_saldo){
                                valorsaldo-= cantidad_a_retirar;
                                cout << "\nSu saldo es de: " << valorsaldo << " pesos\n" <<endl;
                                cout <<"Se le cobraran 1000 pesos por retirar\n"<<endl;
                                valorsaldo-=1000;
                                ActualizarSaldo(valorsaldo, nombre_del_archivo, numero_de_linea_principal+2, semilla_De_codificacion, longitudes_saldos_usuarios, posicion_archivo_usuario);
                            }else{
                                if(valorsaldo<1000){
                                    cout<<"Tiene menos de mil pesos, por lo tanto no puedes retirar"<<endl;
                                }else if(cantidad_a_retirar>valorsaldo){
                                    cout<<"No tiene suficiente saldo"<<endl;
                                }else{
                                    cout<<"No puede retirar esta cantidad, tenga en cuenta los 1000 pesos que se le cobraran despues de retirar"<<endl;
                                }
                            }
                        }

                            break;

                        case '3':
                            bandera_repetir_menu_usuario=false;
                            break;
                        default:
                            cout << "\nIngresaste una opcion invalida" <<endl;
                            cin.clear();
                            cin.ignore(255, '\n');
                            break;

                        }
                    }
                }


            }else if(eleccion_menu_ingreso==3){
                bandera=false;
            }

        } catch(int n){
            if(n==1){
                cout<<"\n Ingresate una opcion invalida. Solo puede ingresar numeros\n"<<endl;
            }if(n==2){
                cout<<"\nSeleccione 1 o 2 para ingresar\n"<<endl;
            }
        }
        cin.clear();
        cin.ignore(255, '\n');
    }

    cout<<"\nGracias por usar nuestros servicios!"<<endl;
    cout <<"Vuelva pronto!"<<endl;

    return 0;
}


/*

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

*/
