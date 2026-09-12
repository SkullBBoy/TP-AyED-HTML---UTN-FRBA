#include <iostream>
#include <windows.h>
#include <locale.h>
#include <stdlib.h>

using namespace std;

struct Orden {

  unsigned int espera  = 0;
  bool soltarGranada1 = false;
  bool soltarGranada2 = false;
  bool ataqueKamikaze = false;
  bool aterrizaje = false;
  bool despegue = false;
  int siguientex =0;
  int siguientey= 0;

};

struct OrdenArchivo{

  int x =0;
  int y =0;
  unsigned int espera  = 0;
  bool soltarGranada1 = false;
  bool soltarGranada2 = false;
  bool ataqueKamikaze = false;
  bool aterrizaje = false;
  bool despegue = false;
  int siguientex =0;
  int siguientey= 0;

};

void cargarArchivoAtaqueMemoria(Orden memoria[200][200]);
void mostrarAtaqueCargado(Orden memoria[200][200]);
void crearArchivoAtaqueNuevo();
void corregirRegistroArchivo();
void corregirRegistroMemoria(Orden memoria[200][200]);
void guardarMemoriaArchivoNuevo(Orden memoria[200][200]);
void visualizarArchivoAtaqueHTML(Orden memoria[200][200]);

int main(){

    int opcion;
    Orden memoriaDron[200][200];


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
            cargarArchivoAtaqueMemoria(memoriaDron);


        break;

        case 2:
            mostrarAtaqueCargado(memoriaDron);


        break;

        case 3:
            crearArchivoAtaqueNuevo();


        break;

        case 4:
            corregirRegistroArchivo();


        break;

        case 5:
            corregirRegistroMemoria(memoriaDron);


        break;

        case 6:
            guardarMemoriaArchivoNuevo(memoriaDron);


        break;

        case 7:
            visualizarArchivoAtaqueHTML(memoriaDron);


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

void cargarArchivoAtaqueMemoria(Orden memoria[200][200]){


}

void mostrarAtaqueCargado(Orden memoria[200][200]){

}

void crearArchivoAtaqueNuevo(){

}

void corregirRegistroArchivo(){

}

void corregirRegistroMemoria(Orden memoria[200][200]){

}

void guardarMemoriaArchivoNuevo(Orden memoria[200][200]){

}

void visualizarArchivoAtaqueHTML(Orden memoria[200][200]){

}

