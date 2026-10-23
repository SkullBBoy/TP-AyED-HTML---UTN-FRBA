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
            system("pause");

        break;

        case 2:
            system("cls");
            mostrarAtaqueCargado(memoriaDron);
            system("pause");


        break;

        case 3:
            system("cls");
            crearArchivoAtaqueNuevo();
            system("pause");

        break;

        case 4:
            system("cls");
            corregirRegistroArchivo();
            system("pause");

        break;

        case 5:
            system("cls");
            corregirRegistroMemoria(memoriaDron);
            system("pause");


        break;

        case 6:
            system("cls");
            guardarMemoriaArchivoNuevo(memoriaDron);
            system("pause");


        break;

        case 7:
            system("cls");
            visualizarArchivoAtaqueHTML(memoriaDron);
            system("pause");


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

            if(registroTemp.x < 0 || registroTemp.x > 199 || registroTemp.y < 0 || registroTemp.y > 199){
               archivoInvalido = true;
               cout << "Error: Coordenadas principales fuera del mapa 200x200." << endl;
               break;
             }



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

              Xanterior=registroTemp.siguientex;
              YAnterior=registroTemp.siguientey;
            }


      }

      if (!registroTemp.aterrizaje && !registroTemp.ataqueKamikaze) {
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
      }

      }//------------- FIN WHILE VALIDACIONES-----------------------------------------------------------------

      if(archivoInvalido == false){
          if(despegueCont == 0){
              archivoInvalido = true;
              cout << "error: el archivo no tiene instruccion de despegue" << endl;
          }
          if(aterrizajeOKamikazeHecho == false){
              archivoInvalido=true;
              cout << "error: la mision termina sin aterrizaje ni ataque kamikaze" << endl;
          }
      }


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

        cout<<"Ataque cargado: "<<nombre<<endl<<endl<<"correctamente en la memoria"<<endl<<endl;



      }





        fclose(f1);
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

    //calculo columna
    columna = ((pagina-1)*datos_por_pagina)/200;

    //calculo fila

    fila = (pagina-1)*datos_por_pagina - (columna*200);

    do{

        pagina = fila + columna * datos_por_pagina;

        for(int i = 0;i < datos_por_pagina;i++){
            if((fila + i) >= 200){
                columna++;
                fila -= 200;
            }
            if(columna >199){
                continue;
            }
            auxAtaque = &memoria[fila + i ][columna];


            if(auxAtaque == NULL){
                cout<<"Coordenadas: "<<endl;
                cout << "X: "<< fila+i<<endl;

                cout << "Y: "<< columna<<endl;

                cout<<"Sin datos"<<endl;
                cout << "-------------------"<<endl;
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
                cout<<"Aterrizaje: " << auxAtaque->aterrizaje<<endl;
                cout<<"Despegue: " << auxAtaque->despegue<<endl;


                cout<<endl<<"Siguientes coordenadas:"<<endl;
                cout << "X: " << auxAtaque->siguientex<<endl;
                cout << "Y: " << auxAtaque->siguientey<<endl;
                 cout << "-------------------"<<endl;
            }

        }
        cout<<"Pagina " << pagina<<endl;
        cout<<"Si quiere terminar ingrese 201"<<endl;
        cout<<"Ingrese posicion x"<<endl;

        cin>>fila;
        cout<<"Ingrese posicion y"<<endl;
        cin>>columna;

        system("cls");
        if(fila == 201 || columna == 201){
            cout<<"Volviendo a menu"<<endl;
            system("pause");
            return;
        }
        if (fila < 0 || fila > 200 || columna < 0 || columna > 200){
            cout<<"Limite exedido, volviendo a menu"<<endl;
            system("pause");
            return;
        }
    }while(true );



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
            cout<<"Aterrizaje: ";cin>>registroAtaque.aterrizaje;
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
    char corregirOtro='s';

    OrdenArchivo registro;

    int x, y;
    bool encontrado=false;

    cout<<"ingrese ruta en la que esta el archivo a corregir"<<endl;
    cin>>ruta;

    cout<<"ingrese nombre del archivo"<<endl;
    cin>> nombre;
    system("cls");

    strcat(ruta, nombre);

    f1=fopen(ruta,"r+b");

    if(f1==NULL){
        cout<<"error con el archivo"<<endl;
        system("pause");
        return;
    }


    while(corregirOtro=='s' || corregirOtro=='S'){

            cout<<"indique coordenadas del registro a corregir"<<endl;

            cout<<"x: ";
            cin>>x;
            cout<<"y: ";
            cin>>y;

            system("cls");

            while(!encontrado && fread(&registro, sizeof(OrdenArchivo), 1, f1)){
                if(registro.x==x && registro.y==y){
                    encontrado=true;
                }
            }

            if(!encontrado){
                cout<<"no existe un registro en las coordenadas x: "<<x<<" y: "<<y<<endl;
            }else{
                cout<<"registro actual:"<<endl<<endl;
                cout<<"coordenadas: "<<endl;
                cout<<"x: "<<registro.x<<endl;
                cout<<"y: "<<registro.y<<endl;

                cout<<endl;
                cout<<"espera: "<<registro.espera<<endl;

                cout<<endl<<"granadas:"<<endl;
                cout<<"granada 1: "<<registro.soltarGranada1<<endl;
                cout<<"granada 2: "<<registro.soltarGranada2<<endl;

                cout<<endl;
                cout<<"ataque kamikaze: "<<registro.ataqueKamikaze<<endl;
                cout<<"aterrizaje: "<<registro.aterrizaje<<endl;
                cout<<"despegue: "<<registro.despegue<<endl;

                cout<<endl<<"siguientes coordenadas:"<<endl;
                cout<<"x: "<<registro.siguientex<<endl;
                cout<<"y: "<<registro.siguientey<<endl;

                cout<<endl<<"quiere corregir este registro? s/S n/N"<<endl;
                cin>>opcion;

                if(opcion=='s' || opcion=='S'){
                    system("cls");
                    cout<<"ingrese los nuevos datos (X: "<<x<<" Y: "<<y<<")"<<endl<<endl;

                    cout<<"espera: ";
                    cin>>registro.espera;

                    cout<<endl;
                    cout<<"(0= no, 1= si)"<<endl<<endl;
                    cout<<"granadas: "<<endl;
                    cout<<"granada 1: ";
                    cin>>registro.soltarGranada1;
                    cout<<"granada 2: ";
                    cin>>registro.soltarGranada2;

                    cout<<endl;
                    cout<<"ataque kamikaze: ";
                    cin>>registro.ataqueKamikaze;
                    cout<<"aterrizaje: ";
                    cin>>registro.aterrizaje;
                    cout<<"despegue: ";
                    cin>>registro.despegue;

                    cout<<endl<<"siguientes coordenadas:"<<endl;
                    cout<<"x: ";
                    cin>>registro.siguientex;
                    cout<<"y: ";
                    cin>>registro.siguientey;

                    system("cls");
                }if (opcion=='n' || opcion=='N'){

                    cout<<"no se va a modificar el archivo"<<endl;
                }
                cout <<"quiere corregir otro registro? s/S n/N"<<endl;
                cin >> corregirOtro;
            }
    }

    fclose(f1);
    system("pause");
    return;
}

void corregirRegistroMemoria(Orden memoria[200][200]){
    char opcion;
    char corregirOtro='s';
    int x, y;
    while(corregirOtro=='s' || corregirOtro=='S'){
        cout <<"indique las coordenadas del registro que quiere modificar"<< endl;
        cout << "x:";
        cin >> x;
        cout << "y:";
        cin >> y;

        if (memoria[x][y].siguientex==0 && memoria[x][y].siguientey==0 && memoria[x][y].ataqueKamikaze==0 && memoria[x][y].aterrizaje==0 && memoria[x][y].despegue==0 && memoria[x][y].soltarGranada1==0 && memoria[x][y].soltarGranada2==0 && memoria[x][y].espera==0){
            cout <<"las cordenadas que se eligieron no tienen nada registrado para corregir"<< endl;
        }else if (x<0 || x>199 || y<0 || y>199){
            cout <<"las coordenadas ingresadas no son validas"<< endl;
        }else {
            cout<<"registro actual:"<<endl<<endl;

            cout<<endl;
            cout<<"espera: "<<memoria[x][y].espera<<endl;

            cout<<endl<<"granadas:"<<endl;
            cout<<"granada 1: "<<memoria[x][y].soltarGranada1<<endl;
            cout<<"granada 2: "<<memoria[x][y].soltarGranada2<<endl;

            cout<<endl;
            cout<<"ataque kamikaze: "<<memoria[x][y].ataqueKamikaze<<endl;
            cout<<"aterrizaje: "<<memoria[x][y].aterrizaje<<endl;
            cout<<"despegue: "<<memoria[x][y].despegue<<endl;

            cout<<endl<<"siguientes coordenadas:"<<endl;
            cout<<"x: "<<memoria[x][y].siguientex<<endl;
            cout<<"y: "<<memoria[x][y].siguientey<<endl;

            cout<<endl<<"quiere corregir este registro? s/S n/N"<<endl;
            cin>>opcion;

            if(opcion=='s' || opcion=='S'){
                system("cls");
                cout<<"ingrese los nuevos datos (X: "<<x<<" Y: "<<y<<")"<<endl<<endl;

                cout<<"espera: ";
                cin>>memoria[x][y].espera;

                cout<<endl;
                cout<<"(0= no, 1= si)"<<endl<<endl;
                cout<<"granadas: "<<endl;
                cout<<"granada 1: ";
                cin>>memoria[x][y].soltarGranada1;
                cout<<"granada 2: ";
                cin>>memoria[x][y].soltarGranada2;

                cout<<endl;
                cout<<"ataque kamikaze: ";
                cin>>memoria[x][y].ataqueKamikaze;
                cout<<"aterrizaje: ";
                cin>>memoria[x][y].aterrizaje;
                cout<<"despegue: ";
                cin>>memoria[x][y].despegue;

                cout<<endl<<"siguientes coordenadas:"<<endl;
                cout<<"x: ";
                cin>>memoria[x][y].siguientex;
                cout<<"y: ";
                cin>>memoria[x][y].siguientey;

                system("cls");
            }if (opcion=='n' || opcion=='N'){

                cout<<"no se va a modificar el archivo"<<endl;
            }

        cout <<"quiere corregir otro registro? s/S n/N"<<endl;
        cin >> corregirOtro;
        }
    }
system("pause");
}

void guardarMemoriaArchivoNuevo(Orden memoria[200][200]){
    OrdenArchivo registroAtaque;
    char ruta[150];
    char nombre[150];
    FILE *f1;


    cout<<"Ingrese ruta"<<endl;
    cin>>ruta;

    cout<<endl;

    cout<<"Ingrese nombre del archivo"<<endl;
    cin>>nombre;
    system("cls");


    strcat(ruta, nombre);

    f1=fopen(ruta,"wb");

    for(int y=0; y<200;y++){

        for(int x=0; x<200; x++){
            if((memoria[x][y].siguientex!=0 && memoria[x][y].siguientey!=0) ||
            (memoria[x][y].ataqueKamikaze==false || memoria[x][y].aterrizaje==false)){
                registroAtaque.x = x;
                registroAtaque.y = y;
                registroAtaque.siguientex = memoria[x][y].siguientex;
                registroAtaque.siguientey = memoria[x][y].siguientey;
                registroAtaque.ataqueKamikaze = memoria[x][y].ataqueKamikaze;
                registroAtaque.aterrizaje = memoria[x][y].aterrizaje;
                registroAtaque.despegue = memoria[x][y].despegue;
                registroAtaque.espera = memoria[x][y].espera;
                registroAtaque.soltarGranada1 = memoria[x][y].soltarGranada1;
                registroAtaque.soltarGranada2 = memoria[x][y].soltarGranada2;

                fwrite(&registroAtaque, sizeof(OrdenArchivo), 1, f1);
            }
        }

    }
    fclose(f1);
    return;
}

void visualizarArchivoAtaqueHTML(Orden memoria[200][200]){

    //Escritura inicial
    FILE *archivo;
    char* nombreArchivo = "index.html";
    archivo = fopen(nombreArchivo, "w");
    const char* clase = "vacio";

    if (archivo == NULL)
    {
        printf("No se creo el archivo.\n");
        return;
    }


    fprintf(archivo, "<html>\n");

    fprintf(archivo, "<head>\n");

    fprintf(archivo, "<title>Ataque del dron</title>\n");

    fprintf(archivo, "<style>\n");

    fprintf(archivo, "table { border-collapse: collapse; }\n");
    fprintf(archivo, "td { width: 20px; height: 20px; border: 1px solid #ccc; }\n");
    fprintf(archivo, ".vacio { background-color: white; }\n");
    fprintf(archivo, ".despegue { background-color: green; }\n");
    fprintf(archivo, ".aterrizaje { background-color: blue; }\n");
    fprintf(archivo, ".granada { background-color: orange; }\n");
    fprintf(archivo, ".kamikaze { background-color: red; }\n");
    fprintf(archivo, ".moverse { background-color: cyan; }\n");
    fprintf(archivo, ".esperar { background-color: yellow; }\n");
    fprintf(archivo, ".caja-texto  { border: 2px solid #333; padding: 10px; border-radius: 8px; max-width: 150px;  }\n");

    fprintf(archivo, "</style>\n");

    fprintf(archivo, "</head>\n");

    fprintf(archivo, "<body>\n");

    fprintf(archivo, "<div class=\"caja-texto vacio\">\n");
    fprintf(archivo, "Color de vacio\n");
    fprintf(archivo, "</div>\n");

    fprintf(archivo, "<div class=\"caja-texto despegue\">\n");
    fprintf(archivo, "Color de despegue\n");
    fprintf(archivo, "</div>\n");

    fprintf(archivo, "<div class=\"caja-texto aterrizaje\">\n");
    fprintf(archivo, "Color de aterrizaje\n");
    fprintf(archivo, "</div>\n");

    fprintf(archivo, "<div class=\"caja-texto granada\">\n");
    fprintf(archivo, "Color de granada\n");
    fprintf(archivo, "</div>\n");

    fprintf(archivo, "<div class=\"caja-texto kamikaze\">\n");
    fprintf(archivo, "Color de kamikaze\n");
    fprintf(archivo, "</div>\n");

    fprintf(archivo, "<div class=\"caja-texto moverse\">\n");
    fprintf(archivo, "Color de moverse\n");
    fprintf(archivo, "</div>\n");

    fprintf(archivo, "<div class=\"caja-texto esperar\">\n");
    fprintf(archivo, "Color de esperar\n");
    fprintf(archivo, "</div>\n");

    fprintf(archivo, "<table border=\"1\">\n");

    for(int y = 0; y < 200; y++){
        fprintf(archivo, "<tr>\n");
        for(int x = 0 ; x < 200;x++){


            if (memoria[y][x].despegue)
                clase = "despegue";
            else if (memoria[y][x].aterrizaje)
                clase = "aterrizaje";
            else if (memoria[y][x].soltarGranada1 || memoria[y][x].soltarGranada2)
                clase = "granada";
            else if (memoria[y][x].ataqueKamikaze)
                clase = "kamikaze";
            else if (memoria[y][x].espera > 0)
                clase = "esperar";
            else if ((!memoria[y][x].ataqueKamikaze &&
                     !memoria[y][x].soltarGranada1 &&
                     !memoria[y][x].soltarGranada2 &&
                     !memoria[y][x].aterrizaje &&
                     !memoria[y][x].aterrizaje &&
                     !memoria[y][x].despegue) &&
                     (memoria[y][x].siguientex != 0   &&
                     memoria[y][x].siguientey != 0)
                     )
                clase = "moverse";
            else if (
                     (x == 0   &&
                     memoria[y][x].siguientey != 0) ||
                     (y == 0   &&
                     memoria[y][x].siguientex != 0)
                     )
                clase = "moverse";
            else
                clase = "vacio";

            fprintf(archivo, "<td class=\"%s\"></td>\n", clase);
        }
        fprintf(archivo, "</tr>\n");
    }


    fprintf(archivo, "</table>\n");
    fprintf(archivo, "</body>\n");
    fprintf(archivo, "</html>\n");
    fclose(archivo);

}

