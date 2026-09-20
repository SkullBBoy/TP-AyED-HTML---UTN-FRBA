#include <iostream>
#include <windows.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct Orden {

  unsigned int espera  = 0;
  bool soltarGranada1 = false;
  bool soltarGranada2 = false;
  bool ataqueKamikaze = false;
  bool aterrizaje = false;
  bool despegue = false;
  int siguientex= 0;
  int siguientey= 0;

};

struct OrdenArchivo{

  int x = 0;
  int y = 0;
  unsigned int espera  = 0;
  bool soltarGranada1 = false;
  bool soltarGranada2 = false;
  bool ataqueKamikaze = false;
  bool aterrizaje = false;
  bool despegue = false;
  int siguientex = 0;
  int siguientey = 0;

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
            system("cls");
            cargarArchivoAtaqueMemoria(memoriaDron);


        break;

        case 2:
            system("cls");
            mostrarAtaqueCargado(memoriaDron);


        break;

        case 3:
            system("cls");
            crearArchivoAtaqueNuevo();


        break;

        case 4:
            system("cls");
            corregirRegistroArchivo();


        break;

        case 5:
            system("cls");
            corregirRegistroMemoria(memoriaDron);


        break;

        case 6:
            system("cls");
            guardarMemoriaArchivoNuevo(memoriaDron);


        break;

        case 7:
            system("cls");
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

    Orden *auxAtaque;
    int pagina = 1;
    int columna, fila;
    int datos_por_pagina = 10;
    char opcion;

    do{
        //calculo columna

        columna = ((pagina-1)*datos_por_pagina)/200;

        //calculo fila

        fila = (pagina-1)*datos_por_pagina - (columna*200);

        //mostrar datos

        for(int i = 0;i < datos_por_pagina;i++){
            if((fila + i) >= 200){
                columna++;
                fila -= 200;
            }
            auxAtaque = &memoria[fila + i ][columna];


            if(auxAtaque == NULL){
                cout<<"Coordenadas: "<<endl;
                cout << "X: "<< fila+i<<endl;

                cout << "Y: "<< columna<<endl;

                cout<<"Sin datos"<<endl;
                continue;
            }
            else{
                cout<<"Coordenadas: "<<endl;
                cout << "X: "<< fila+i<<endl;

                cout << "Y: "<< columna<<endl;

                cout<<endl;
                cout << "Espera (segundos): " << auxAtaque->espera<<endl;

                cout<<"Explosivos:"<<endl;
                cout<<"Granada 1: "<< auxAtaque->soltarGranada1<<endl;
                cout<<"Granada 2: "<< auxAtaque->soltarGranada2<<endl;

                cout<<"Ataque kamikaze: "<< auxAtaque->ataqueKamikaze<<endl;
                cout<<"Aterrizaje: " << auxAtaque->despegue<<endl;
                cout<<"Despegue: " << auxAtaque->despegue<<endl;


                cout<<endl<<"Siguientes coordenadas:"<<endl;
                cout << "X: " << auxAtaque->siguientex<<endl;
                cout << "Y: " << auxAtaque->siguientey<<endl;

            }

        }
        cout<<"Pagina " << pagina<<endl;
        cout<<"Siguiente pagina con s/S, anterior con a/A "<<endl;
        cout<<"Si quiere terminar ingrese n/N"<<endl;
        cin>>opcion;
        if(opcion == 's' || opcion == 'S'){
            pagina++;
        }
        else if(opcion == 'a' || opcion == 'A'){
            pagina--;
        }
        system("cls");
        if (pagina <= 0 || pagina*datos_por_pagina >=40000){
            cout<<"Limite exedido, volviendo a menu"<<endl;
            // sacado de ia chatgpt xd, simplemnete elimina buffer y espera enter
            system("pause");
            return;
        }
    }while(opcion!='n' && opcion!='N' );
}

void crearArchivoAtaqueNuevo(){

    OrdenArchivo registroAtaque;
    char ruta[150];
    char nombre[150];
    FILE *f1;
    char opcion;


    cout<<"Ingrese ruta"<<endl;
    cin>>ruta;


    cout<<"Ingrese nombre del archivo"<<endl;
    cin>>nombre;
    system("cls");


    strcat(ruta, nombre);

    f1=fopen(ruta,"wb");

    if(f1!=NULL){


        do{

            cout<<"Coordenadas: "<<endl;
            cout << "X: ";cin >> registroAtaque.x;

            cout << "Y: ";cin >> registroAtaque.y;

            cout<<endl;
            cout << "Espera (segundos): "; cin >> registroAtaque.espera;

            cout<<endl;
            cout<<"(0= no, 1= si)"<<endl<<endl;
            cout<<"Explosivos: "<<endl;
            cout<<"Granada 1: "; cin>>registroAtaque.soltarGranada1;
            cout<<"Granada 2: ";cin >> registroAtaque.soltarGranada2;

            cout<<endl;
            cout<<"Ataque kamikaze: "; cin>>registroAtaque.ataqueKamikaze;
            cout<<"Aterrizaje: ";cin>>registroAtaque.despegue;
            cout<<"Despegue: ";cin>>registroAtaque.despegue;


            cout<<endl<<"Siguientes coordenadas:"<<endl;
            cout << "X: ";cin >> registroAtaque.siguientex;
            cout << "Y: ";cin >> registroAtaque.siguientey;



            fwrite(&registroAtaque, sizeof(OrdenArchivo), 1, f1);

            cout<<endl<<"Desea cargar otro registro? y/Y n/N"<<endl;
            cin>>opcion;

        }while(opcion!='n' && opcion!='N' );




    }else{

        cout<<"Error con el archivo"<<endl;

    }


    fclose(f1);
}

void corregirRegistroArchivo(){

}

void corregirRegistroMemoria(Orden memoria[200][200]){

}

void guardarMemoriaArchivoNuevo(Orden memoria[200][200]){

}

void visualizarArchivoAtaqueHTML(Orden memoria[200][200]){

}

