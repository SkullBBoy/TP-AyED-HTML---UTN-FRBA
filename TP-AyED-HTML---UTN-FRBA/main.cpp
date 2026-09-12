#include <iostream>
#include <windows.h>
#include <locale.h>
#include <stdlib.h>

using namespace std;

void cargarArchivoAtaqueMemoria();
void mostrarAtaqueCargado();
void crearArchivoAtaqueNuevo();
void corregirRegistroArchivo();
void corregirRegistroMemoria();
void guardarMemoriaArchivoNuevo();
void visualizarArchivoAtaqueHTML();

int main(){

    int opcion;


    do{
    system("cls");

    cout<<"1. Cargar archivo de ataque en memoria."<<endl;
    cout<<"2. Mostrar ataque cargado."<<endl;
    cout<<"3. Crear un archivo de ataque nuevo."<<endl;
    cout<<"4. Corregir un registro del archivo. "<<endl;
    cout<<"5. Corregir un registro en memoria."<<endl;
    cout<<"6. Guardar memoria en un archivo nuevo."<<endl;
    cout<<"7. Visualizar un archivo de ataque en html. "<<endl;
    cout<<"0/8 Salir"<<endl;

    cout<<endl<<"Opcion: "<<endl;
    cin>>opcion;


    switch(opcion){

        case 1:
            cargarArchivoAtaqueMemoria();


        break;

        case 2:
            mostrarAtaqueCargado();


        break;

        case 3:
            crearArchivoAtaqueNuevo();


        break;

        case 4:
            corregirRegistroArchivo();


        break;

        case 5:
            corregirRegistroMemoria();


        break;

        case 6:
            guardarMemoriaArchivoNuevo();


        break;

        case 7:
            visualizarArchivoAtaqueHTML();


        break;

        default:
            if(opcion==0 || opcion==8){
                system("cls");
                cout<<"Fin del programa"<<endl;

            }else{
                system("cls");
                cout<<"Opcion invalida"<<endl;
                system("pause");
            }

    }}while(opcion!=0 && opcion !=8);


    return 0;
}

void cargarArchivoAtaqueMemoria(){

}

void mostrarAtaqueCargado(){

}

void crearArchivoAtaqueNuevo(){

}

void corregirRegistroArchivo(){

}

void corregirRegistroMemoria(){

}

void guardarMemoriaArchivoNuevo(){

}

void visualizarArchivoAtaqueHTML(){

}

