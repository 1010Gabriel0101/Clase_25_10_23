#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
void crear();
void continuar();
void cargar();
void listar();
void consulta();
void modificar();
void eliminar();

typedef struct{
 int codigo;
char descripcion[40];
float precio;
}tproduct;
int main(){
int opcion;
  do{
   printf("1. Crear Archivo binario llamado \"productos.dat\"\n");
    printf("2. Cargar los registros de tipo producto\n");
    printf("3. Listado completo de productos\n");
    printf("4. Consulta de un producto por su codigo\n");
    printf("5. Modificacion del precio de un producto\n");
    printf("6. Eliminar Producto\n");
    printf("7. Salir\n\n");
    printf("Ingresa una opcion: ");
    scanf("%d",&opcion);
    switch(opcion){
      case 1:
      crear();
      break;
      case 2:
      cargar();
      break;
      case 3:
      listar();
      break;
      case 4:
      consulta();
      break;
      case 5:
      modificar();
      break;
      case 6:
      eliminar();
      break;
      default:
      break;
    }
  } while(opcion != 7);
}
/*Funcion que permite crear un archivo de tipo binario*/
void crear()
{
  FILE *arch;
  arch = fopen("productos.dat","wb");
  if(arch == NULL)
     exit(1);
    fclose(arch);
    continuar(); 
}

void continuar()
{
  printf("Presione cualquier tecla para continuar:\n\n");
  getch();
}

void cargar()
{
  FILE *arch;
  arch = fopen("productos.dat","ab");
  if(arch == NULL)
     exit(1);
  tproduct producto;
  printf("Introduce el codigo del producto: ");
  scanf("%d",&producto.codigo);
  fflush(stdin);
  printf("Ingrese el nombre del producto: ");
  scanf("%s",&producto.descripcion);
  printf("Ingrese el precio: ");
  scanf("%.f",&producto.precio);
  fflush(stdin);
  fwrite(&producto, sizeof(tproduct), 1, arch);
  fclose(arch);
  continuar();
}
void listar()
{
  FILE *arch;
  arch = fopen("productos.dat","rb");
  if(arch == NULL)
    exit(1);
  tproduct producto;
  fread(&producto, sizeof(tproduct), 1, arch);
  while(!feof(arch))
  {
    printf("%d\n%s\n%.2f\n",producto.codigo, producto.descripcion, producto.precio);
    fread(&producto, sizeof(tproduct), 1, arch);
  }
  fclose(arch);
  continuar();
}
void consulta()
{
  FILE *arch;
  int cod;
  tproduct producto;
  bool existe = false;
  arch = fopen("productos.dat","rb");
  if(arch == NULL)
    exit(1);
  printf("Ingresa el codigo del producto a consultar: ");
  scanf("%d",&cod);
  fread(&producto, sizeof(tproduct), 1, arch);
  while(!feof(arch))
  {
    if(cod == producto.codigo)
    {
      printf("%d %s %.2f \n",producto.codigo, producto.descripcion, producto.precio);
    }
    existe = true;
    break;
  }
  fread(&producto, sizeof(tproduct), 1, arch);
if(!existe)
   printf("No existe el producto del codigo insertado");
  fclose(arch);
  continuar();
}


void modificar()
{
  FILE *arch;
  int cod;
  tproduct producto;
  bool existe = false;
  arch = fopen("productos.dat","r+b");
  if(arch == NULL)
    exit(1);
  printf("Ingresa el codigo del producto a modificar: ");
  scanf("%d",&cod);
  fread(&producto, sizeof(tproduct), 1, arch);
  while(!feof(arch))
  {
    if(cod == producto.codigo)
    {
      printf("%d %s %.2f\n",producto.codigo, producto.descripcion, producto.precio);
      printf("Ingresa el nuevo precio: ");
       scanf("%f",&producto.precio);
      int posicion = ftell(arch) - sizeof(tproduct);
      fseek(arch, posicion, SEEK_SET);
      fwrite(&producto, sizeof(tproduct), 1, arch);
      printf("Se modifico el precio del producto");
      existe = true;
      break;
  }
  fread(&producto, sizeof(tproduct), 1, arch);
}
if(!existe)
   printf("No existe el producto del codigo insertado");
  fclose(arch);
  continuar();
}

void eliminar()
{
	FILE *arch;
    int cod;
    tproduct producto;
    bool existe = false;
    FILE *temp;

    arch = fopen("productos.dat", "rb");
    if (arch == NULL)
        exit(1);

    temp = fopen("temp.dat", "wb");
    if (temp == NULL)
        exit(1);

    printf("Ingresa el codigo del producto a eliminar: ");
    scanf("%d", &cod);

    fread(&producto, sizeof(tproduct), 1, arch);
    while (!feof(arch))
    {
        if (cod == producto.codigo)
        {
            printf("%d %s %.2f\n", producto.codigo, producto.descripcion, producto.precio);
            printf("Se eliminó el producto\n");
            existe = true;
        }
        else
        {
            fwrite(&producto, sizeof(tproduct), 1, temp);
        }
        fread(&producto, sizeof(tproduct), 1, arch);
    }

    fclose(arch);
    fclose(temp);

    remove("productos.dat");
    rename("temp.dat", "productos.dat");

    if (!existe)
        printf("No existe el producto del codigo insertado");

    continuar();
}
	
