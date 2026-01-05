#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#define N 50

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
// se defiene la estructura de los datos a ingresar
typedef struct
{
    char nombre[50];
    int cantidadNotas;
    int *notas;
} Alumno;

//PROTOTIPOS DE LAS FUNCIONES
void dibujarCuadro(int x1,int y1,int x2,int y2);
void gotoxy(int x,int y);
void CursorOn(bool visible, DWORD size);
void CursorOff();
void limpia();
void cambio(char a[]);
void login();
void leerPasw(char frase[]);
void menu();
void calcularEstadisticas(Alumno *alumnos, int cantidadAlumnos);
void freespacio(Alumno *alumnos, int cantidadAlumnos);
void listaAlumnos(Alumno *alumnos, int cantidadAlumnos);

//FUNCION PRINCIPAL MAIN: Aqu? dentro de main llamamos a las dem?s funciones.
int main(){
	system("COLOR C0");
	dibujarCuadro(0,0,78,24);//Cuadro grande
	dibujarCuadro(1,1,77,3);//Cuadro del titulo
	CursorOff();
	gotoxy(16,2); printf("        C L A S S R O O M 98");  //Cambiar t?tulo del programa
	menu();

    //login();
	
	getch();
	return 0;
}

void menu() {
    CursorOn(1, 10);

    int cantidadAlumnos;
    gotoxy(4, 6); printf("¿Cuántos alumnos desea ingresar? ");
    scanf("%d", &cantidadAlumnos);

    Alumno *alumnos = (Alumno *)malloc(cantidadAlumnos * sizeof(Alumno));
    CursorOn(0, 10);
    limpia();

    for (int i = 0; i < cantidadAlumnos; i++) {
        CursorOn(0, 10);

        getchar(); // Consumir el carácter de nueva línea en el buffer.
        gotoxy(5, 7); printf("Ingrese el nombre del alumno %d: ", i + 1);
        fgets(alumnos[i].nombre, sizeof(alumnos[i].nombre), stdin);

        alumnos[i].nombre[strcspn(alumnos[i].nombre, "\n")] = '\0';
        
        limpia();

        gotoxy(5, 8); printf("¿Cuántas notas desea ingresar para %s? ", alumnos[i].nombre);
        scanf("%d", &alumnos[i].cantidadNotas);

        // Asignar memoria para las notas
        alumnos[i].notas = (int *)malloc(alumnos[i].cantidadNotas * sizeof(int));

        getchar(); // Consumir el carácter de nueva línea en el buffer.
        limpia();

        for (int j = 0; j < alumnos[i].cantidadNotas; j++) {
            CursorOn(1, 10);
            gotoxy(4, 7); printf("Ingrese la nota número %d: ", j + 1);
            scanf("%d", &alumnos[i].notas[j]);
            

            // La nota debe estar en el rango de 0 - 10
            if (alumnos[i].notas[j] < 0 || alumnos[i].notas[j] > 10) {
                gotoxy(4, 20); printf("Nota no válida. Debe estar en el rango de 0-10. Inténtelo de nuevo.\n");
                j--;
            }
            CursorOn(0, 10);
            limpia();
        }
    }

   
        listaAlumnos(alumnos, cantidadAlumnos);
    
    
    
    
}

// Definición de la función para calcular estadísticas
void calcularEstadisticas(Alumno *alumnos, int cantidadAlumnos)
{
    // Declaración de variables locales para las estadísticas
    float promedioGeneral = 0;
    int cantidadEstudiantesAprobados = 0;
    int cantidadEstudiantesReprobados = 0;
    float promedioMasAlto = 0;
    float promedioMasBajo = 1000;

    // Calcular estadísticas para cada alumno
    for (int i = 0; i < cantidadAlumnos; i++)
    {
        // Calcular el promedio del alumno
        float suma = 0;
        for (int j = 0; j < alumnos[i].cantidadNotas; j++)
        {
            suma += alumnos[i].notas[j];
        }
        float promedioEstudiante = suma / alumnos[i].cantidadNotas;

        // Actualizar las estadísticas generales
        promedioGeneral += promedioEstudiante;

        if (promedioEstudiante <= 7)
        {
            cantidadEstudiantesAprobados++;
        }
        else
        {
            cantidadEstudiantesReprobados++;
        }

        if (promedioEstudiante > promedioMasAlto)
        {
            promedioMasAlto = promedioEstudiante;
        }

        if (promedioEstudiante < promedioMasBajo)
        {
            promedioMasBajo = promedioEstudiante;
        }
    }

    // Mostrar estadísticas generales
    gotoxy(4, 10);printf("Promedio general de todos los estudiantes: %.2f", promedioGeneral / cantidadAlumnos);
    gotoxy(4, 11);printf("Cantidad de estudiantes aprobados: %d", cantidadEstudiantesAprobados);
    gotoxy(4, 12);printf("Cantidad de estudiantes reprobados: %d", cantidadEstudiantesReprobados);
    gotoxy(4, 13);printf("CanPromedio mas alto: %.2f", promedioMasAlto);
    gotoxy(4, 14);printf("CanPromedio mas bajo: %.2f", promedioMasBajo);
}

void listaAlumnos(Alumno *alumnos, int cantidadAlumnos/*, int cantidadNotas*/){
   gotoxy(2, 10); printf("-------LISTA DE ALUMNOS ------");
   
    for(int i;i <= cantidadAlumnos; i++){

     if(alumnos[i].nombre != alumnos[cantidadAlumnos].nombre){

       gotoxy(4, i+11); printf("%d.%s", i+1, alumnos[i].nombre);

       }
    }
   /* printf("dease ver las notas especificas de un alumon");
    scanf("%d", &opnion);
    if(opnion == 1){
    printf("ingrese el numeros del alumno");
    scanf("%d", &alumonNum);
    gotoxy(4, 20); printf("-------NOTAS DE %s ------", alumnos[alumonNum].nombre);      
    }*/
}


void freespacio(Alumno *alumnos, int cantidadAlumnos) {
    for (int i = 0; i < cantidadAlumnos; i++) {
        free(alumnos[i].notas);
    }
    free(alumnos);
}


//FUNCION LOGIN: Se crean 2 variables, de usuario y contrase?a y se comparan para mostrar sus respectivos mensajes
void login(){
	CursorOn(1,10);
	char user[] = "1"; //Modificar colocando el usuario que deseean
	char contra[] = "1"; //Modificar contrase?a que deseen
	char user2[20],contra2[20];
	int x=1000;
	int f=41;

	gotoxy(35,6); printf("LOGIN");
	dibujarCuadro(18,9,60,15);
	gotoxy(23,11); printf("Usuario: ");
	fgets(user2,20,stdin);
	cambio(user2);
	
	gotoxy(23,13); printf("Clave:   ");
	leerPasw(contra2);
	
	CursorOff();
	
	for(int i = 0; i < 3; i++ ){
		gotoxy(33,19); printf("Cargando");
		gotoxy(f,19); printf(".");
		f+=1;
		Sleep(x);
	}
	
	
	f=51;
	
	if ((strcmp(user2,user)) == 0 && (strcmp(contra2,contra)) == 0){
		gotoxy(30,19); printf("                                     ");
		for(int i = 0; i < 3; i++ ){
			gotoxy(30,19); printf("Accediendo al Sistema");
			gotoxy(f,19); printf(".");
			f+=1;
			Sleep(x);
		}
		limpia();	
		menu();
	} 
	
	
	else{
		gotoxy(35,19); printf("                                     ");
		gotoxy(30,19); printf("Datos incorrectos");
		gotoxy(18,20); printf("Presione una tecla para volver a ingresar..");
		getch();
		limpia();
		login();
	}
}


//FUNCION LEER CONTRASE?A: proceso que permite mostrar asteriscos en la contrase?a
void leerPasw(char frase[])
{
    int i=0;
    cout.flush();
	int aux=0;

	
    do
    {
        frase[i] = (unsigned char)getch();

		
        if(frase[i]!=8)  // no es retroceso
        {
            cout << '*';  // muestra por pantalla
            i++;
            
            if (frase[i-1]==13){
        		printf("\b \b");
                aux = 1;
			}
        }
        
        
        
        else if(i>0)    // es retroceso y hay caracteres
        {
            cout << (char)8 << (char)32 << (char)8;
            i--;  //el caracter a borrar en el backspace
            aux= 2;
        }
        
        
        cout.flush();

    }while(frase[i-1]!=13);  // si presiona ENTER

    frase[i-1] = 0;
    
}



//FUNCI0N CAMBIO: Cambia el caracter \n por \0
void cambio(char a[]){
	int aux;
	aux = strlen(a);
	a[aux-1] = '\0';
}




//************************************FUNCIONES ADICIONALES************************************************************


//FUNCION GOTOXY: Permite posicionar en pantalla mediante coordenadas X/Y
void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }
 
 
 
//FUNCION DIBUJAR CUADRO
void dibujarCuadro(int x1,int y1,int x2,int y2)
{

    int i;
    for (i=x1;i<x2;i++)
    {
	gotoxy(i,y1); putchar(205);//linea horizontal superior
	gotoxy(i,y2); putchar(205);//linea horizontal inferior
    }

    for (i=y1;i<y2;i++)
    {
	gotoxy(x1,i); putchar(186);//linea vertical izquierda
	gotoxy(x2,i); putchar(186);//linea vertical derecha
    }
    gotoxy(x1,y1); putchar(201);//Esquina izquierda superior
    gotoxy(x1,y2); putchar(200);//Esquina izquierda inferior
    gotoxy(x2,y1); putchar(187);//Esquina izquierda superior
    gotoxy(x2,y2); putchar(188);//Esquina derecha inferior
}

//FUNCION LIMPIAR PANTALLA
void limpia(){
	int i,j;
	for(i=5;i<=23;i++){
		for(j=3;j<=76;j++){
			gotoxy(j,i); printf(" ");}}
}

// FUNCION PARA OCULTAR EL CURSOR
void CursorOff(){
  CONSOLE_CURSOR_INFO cursor = {1, FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}



//FUNCION PARA APARECER EL CURSOR
void CursorOn(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if(size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}


