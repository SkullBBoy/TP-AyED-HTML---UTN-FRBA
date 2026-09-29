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

    char ruta[150];
    char nombre[150];
    FILE *f1;
    char opcion;
    OrdenArchivo registroTemp;

    int Xleidos[40000];
    int Yleidos[40000];
    int cantLeidos=0;

    bool primerRegistro=true;
    int Xanterior;
    int YAnterior;


    bool archivoInvalido=false;

    int despegueCont=0;
    bool aterrizajeOKamikazeHecho=false;


    cout<<"Ingrese ruta en la que esta el ataque que quiere cargar"<<endl;
    cin>>ruta;

    cout<<endl;

    cout<<"Ingrese nombre del archivo del ataque"<<endl;
    cin>>nombre;
    system("cls");


    strcat(ruta, nombre);

    f1=fopen(ruta,"rb");

    if(f1!=NULL){

      while(fread(&registroTemp, sizeof(OrdenArchivo), 1, f1)){



             if (aterrizajeOKamikazeHecho){

                cout << "error, se escribio el aterrizaje o el kamikaze mas a de una vez"<<endl;
                archivoInvalido=true;
                break;

             }

            if(registroTemp.despegue==true){

                if(registroTemp.soltarGranada1 || registroTemp.soltarGranada2 || registroTemp.ataqueKamikaze){

                    archivoInvalido=true;
                    cout <<"hubo error al escribir el despegue con otra accion" << endl;
                    break;

                }else{
                    despegueCont++;

                    if(despegueCont>1){

                        archivoInvalido=true;
                        cout << "error, se escribio dos veces el despegue" << endl;
                        break;
                    }


                }

            }



            if(registroTemp.aterrizaje || registroTemp.ataqueKamikaze){

                    aterrizajeOKamikazeHecho=true;
            }


            for(int i=0; i<cantLeidos; i++){

                if(registroTemp.x== Xleidos[i] && registroTemp.y== Yleidos[i]){

                    archivoInvalido=true;
                    cout<<"Error. Colicion de coordenadas"<<endl;
                    break;
                    }

            }

            if(archivoInvalido){

                break;
            }

            Xleidos[cantLeidos]=registroTemp.x;
            Yleidos[cantLeidos]=registroTemp.y;
            cantLeidos++;


            if (primerRegistro==true){

            Xanterior=registroTemp.siguientex;
            YAnterior=registroTemp.siguientey;

            primerRegistro=false;

            }else if(primerRegistro==false){

            if(Xanterior!=registroTemp.x || YAnterior!=registroTemp.y){

            cout<<"Error, coordenadas no contiguas"<<endl;
            archivoInvalido=true;
            break;

            }else{

              Xanterior=registroTemp.x;
              YAnterior=registroTemp.y;
            }


      }

      if (registroTemp.siguientex<registroTemp.x-1 ||  registroTemp.siguientex>registroTemp.x+1){
            archivoInvalido=true;
            cout << "error, hubo un hueco al escribir las posiciones x" << endl;
            break;
      }

      if (registroTemp.siguientey<registroTemp.y-1 || registroTemp.siguientey>registroTemp.y+1){
            archivoInvalido=true;
            cout << "error, hubo un hueco al escribir las posiciones y" << endl;
            break;
      }

      }//------------- FIN WHILE VALIDACIONES-----------------------------------------------------------------


      if(archivoInvalido==true){
        cout<<endl<<"El Archivo invalido"<<endl;

      }else{

        for(int i=0; i<200; i++){

            for(int j=0; j<200; j++){
                memoria[i][j].espera=0;
                memoria[i][j].soltarGranada1=false;
                memoria[i][j].soltarGranada2=false;
                memoria[i][j].ataqueKamikaze=false;
                memoria[i][j].aterrizaje=false;
                memoria[i][j].despegue=false;
                memoria[i][j].siguientex=0;
                memoria[i][j].siguientey=0;
            }

        }

        fseek(f1, 0, SEEK_SET);

        while(fread(&registroTemp, sizeof(OrdenArchivo), 1, f1)){

            memoria[registroTemp.x][registroTemp.y].espera=registroTemp.espera;
            memoria[registroTemp.x][registroTemp.y].soltarGranada1=registroTemp.soltarGranada1;
            memoria[registroTemp.x][registroTemp.y].soltarGranada2=registroTemp.soltarGranada2;
            memoria[registroTemp.x][registroTemp.y].ataqueKamikaze=registroTemp.ataqueKamikaze;
            memoria[registroTemp.x][registroTemp.y].aterrizaje=registroTemp.aterrizaje;
            memoria[registroTemp.x][registroTemp.y].despegue=registroTemp.despegue;
            memoria[registroTemp.x][registroTemp.y].siguientex=registroTemp.siguientex;
            memoria[registroTemp.x][registroTemp.y].siguientey=registroTemp.siguientey;


        }



      }






    }else{
        cout<<"Error con el archivo"<<endl;
    }
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
            // Use IA chatgpt, simplemnete elimina buffer y espera enter
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

    cout<<endl;

    cout<<"Ingrese nombre del archivo"<<endl;
    cin>>nombre;
    system("cls");


    strcat(ruta, nombre);

    f1=fopen(ruta,"wb");

    if(f1!=NULL){


        do{
            system("cls");

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

    char ruta[150];
    char nombre[150];
    FILE *f1;
    char opcion;

    OrdenArchivo registroActual;
    OrdenArchivo registroNuevo;

    int x, y;
    bool encontrado=false;
    bool registroValido=true;

    // Limpiamos el salto de línea residual dejado por cin >> opcion en el menu principal
    cin.ignore();

    cout<<"Ingrese ruta en la que esta el archivo a corregir"<<endl;
    cin.getline(ruta, 150);

    cout<<"Ingrese nombre del archivo"<<endl;
    cin.getline(nombre, 150);
    system("cls");

    strcat(ruta, nombre);

    // "r+b": lectura y escritura sobre un archivo binario que ya existe
    f1=fopen(ruta,"r+b");

    if(f1==NULL){
        cout<<"Error con el archivo"<<endl;
        system("pause");
        return;
    }

    cout<<"Coordenadas del registro a corregir"<<endl;
    cout<<"X: ";cin>>x;
    cout<<"Y: ";cin>>y;
    system("cls");

    // busqueda secuencial: al salir con encontrado==true, la posicion del archivo
    // queda justo despues del registro buscado
    while(!encontrado && fread(&registroActual, sizeof(OrdenArchivo), 1, f1)){
        if(registroActual.x==x && registroActual.y==y){
            encontrado=true;
        }
    }

    if(!encontrado){
        cout<<"No existe un registro en las coordenadas X: "<<x<<" Y: "<<y<<endl;
    }else{
        cout<<"Registro actual:"<<endl<<endl;
        cout<<"Coordenadas: "<<endl;
        cout<<"X: "<<registroActual.x<<endl;
        cout<<"Y: "<<registroActual.y<<endl;

        cout<<endl;
        cout<<"Espera (segundos): "<<registroActual.espera<<endl;

        cout<<endl<<"Explosivos:"<<endl;
        cout<<"Granada 1: "<<registroActual.soltarGranada1<<endl;
        cout<<"Granada 2: "<<registroActual.soltarGranada2<<endl;

        cout<<endl;
        cout<<"Ataque kamikaze: "<<registroActual.ataqueKamikaze<<endl;
        cout<<"Aterrizaje: "<<registroActual.aterrizaje<<endl;
        cout<<"Despegue: "<<registroActual.despegue<<endl;

        cout<<endl<<"Siguientes coordenadas:"<<endl;
        cout<<"X: "<<registroActual.siguientex<<endl;
        cout<<"Y: "<<registroActual.siguientey<<endl;

        cout<<endl<<"Desea corregir este registro? s/S n/N"<<endl;
        cin>>opcion;

        if(opcion=='s' || opcion=='S'){
            system("cls");
            cout<<"Ingrese los nuevos datos (X: "<<x<<" Y: "<<y<<")"<<endl<<endl;

            // x e y son la "clave" del registro original en la matriz, se mantienen
            registroNuevo.x=x;
            registroNuevo.y=y;

            cout<<"Espera (segundos): ";cin>>registroNuevo.espera;

            cout<<endl;
            cout<<"(0= no, 1= si)"<<endl<<endl;
            cout<<"Explosivos: "<<endl;
            cout<<"Granada 1: ";cin>>registroNuevo.soltarGranada1;
            cout<<"Granada 2: ";cin>>registroNuevo.soltarGranada2;

            cout<<endl;
            cout<<"Ataque kamikaze: ";cin>>registroNuevo.ataqueKamikaze;
            cout<<"Aterrizaje: ";cin>>registroNuevo.aterrizaje;
            cout<<"Despegue: ";cin>>registroNuevo.despegue;

            cout<<endl<<"Siguientes coordenadas:"<<endl;
            cout<<"X: ";cin>>registroNuevo.siguientex;
            cout<<"Y: ";cin>>registroNuevo.siguientey;

            system("cls");

            // validaciones que se pueden hacer sobre un solo registro
            if(registroNuevo.despegue && (registroNuevo.soltarGranada1 || registroNuevo.soltarGranada2 || registroNuevo.ataqueKamikaze)){
                cout<<"Error, el despegue no puede estar acompanado de un ataque"<<endl;
                registroValido=false;
            }

            if(registroNuevo.siguientex<0 || registroNuevo.siguientex>199 || registroNuevo.siguientey<0 || registroNuevo.siguientey>199){
                cout<<"Error, las siguientes coordenadas estan fuera de la tabla (0 a 199)"<<endl;
                registroValido=false;
            }

            if(registroNuevo.siguientex<x-1 || registroNuevo.siguientex>x+1 || registroNuevo.siguientey<y-1 || registroNuevo.siguientey>y+1){
                cout<<"Error, la siguiente celda no es aledana (hueco en la ruta)"<<endl;
                registroValido=false;
            }

            if(registroValido){
                // se vuelve un registro atras (el fread lo dejo adelante) y se pisa de forma segura
                fseek(f1, -1L * sizeof(OrdenArchivo), SEEK_CUR);
                fwrite(&registroNuevo, sizeof(OrdenArchivo), 1, f1);

                cout<<"Registro corregido correctamente"<<endl;
            }else{
                cout<<"No se modifico el archivo debido a los errores de validacion"<<endl;
            }
        }else{
            cout<<"No se modifico el archivo"<<endl;
        }
    }

    fclose(f1);
    system("pause");
}

void corregirRegistroMemoria(Orden memoria[200][200]){

}

void guardarMemoriaArchivoNuevo(Orden memoria[200][200]){

}

void visualizarArchivoAtaqueHTML(Orden memoria[200][200]){

}

