#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    int idCliente; // auto incremental
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[30];
    char genero;
    int rol;    // 1: es admin - 0: es com n
    int activo; // indica 1 activo y 0 inactivo
} stCliente;

typedef struct
{
    int idPedido;   // auto incremental
    int idCliente;  // este valor corresponde al id del cliente que realiz  el pedido
    char fecha[12]; // dd/MM/aaaa
    char descripcion[300];
    float costo;
    int pedidoAnulado; // indica 1 activo y 0 anulado
} stPedido;

int idClienteNuevo();
void menuAdmin();
void menuABMCLclientes();
void bajaDeCliente();
void altaDeCliente();
int verificarClienteYaExiste();
void mostrarArchivo();
void menuBienvenida();
void modificarCliente();

int main()
{




    char clientes[] = {"clientes.bin"};
    char pedidos[] = {"pedidos.bin"};
    int aux, eleccion;

    // mostrarArchivo(clientes);
    // aux = login(clientes);
    mostrarArchivo(clientes);
    modificarCliente(clientes);
    mostrarArchivo(clientes);
    return 0;
}
int idClienteNuevo(char archivo[])
{
    FILE *archi;
    archi = fopen(archivo, "rb");
    stCliente a;
    int i = 0;
    if (archi != NULL)
    {
        while (fread(&a, sizeof(stCliente), 1, archi) > 0)
        {
            i = a.idCliente + 1;
        }
    }
    return i;
}
void menuAdmin()
{
    printf("\n\tMenu de administrador\n");
    printf("\n\t[ 1 ] - Alta de clientes");
    printf("\n\t[ 2 ] - Baja de clientes");
    printf("\n\t[ 3 ] - Modificar clientes");
    printf("\n\t[ 4 ] - Consultar clientes");
    printf("\n\t[ 5 ] - Consultar pedidos");
    printf("\n\t[ 6 ] - Eliminar clientes");
    printf("\n\t[ 7 ] - Eliminar pedidos");
    printf("\n\t[ 8 ] - Alta de nuevo admin");
}

void menuABMCLclientes()
{
    printf("\n\tMenu de ABMCL de Clientes\n");
    printf("\n\t[ 1 ] - Alta de clientes");
    // Carga de datos verificar no cargar un mismo cliente
    // guardar en archivo
    printf("\n\t[ 2 ] - Baja de clientes");
    // Buscar cliente
    // Dar de baja cliente
    // Guardar los cambios en archivo
    printf("\n\t[ 3 ] - Modificar clientes");
    // Buscar cliente
    // Modificar cliente
    // Guardar los datos en archivo
    printf("\n\t[ 4 ] - Listar clientes");
    // Mostrar todos los clientes
    // Buscar un cliente en particular
}

void bajaDeCliente(char archivo[])
{
    stCliente cliente;
    FILE *archivito;
    archivito = fopen(archivo, "r+b");
    int aux = 0;
    char ok = 's';
    char myUserName[20];
    printf("Estas seguro que queres darte de baja? (s/n) \n");
    fflush(stdin);
    scanf("%c", &ok);
    printf("Ingrese su usuario para validar la baja\n");
    fflush(stdin);
    scanf("%s", myUserName);

    if (archivito != NULL && ok == 's')
    {
        while (aux == 0 && (fread(&cliente, sizeof(stCliente), 1, archivito) > 0))
        {

            if (strcmp(cliente.userName, myUserName) == 0)
            {
                cliente.activo = 0;
                fseek(archivito, (-1) * sizeof(stCliente), SEEK_CUR);
                fwrite(&cliente, sizeof(stCliente), 1, archivito);
                aux = 1;
            }
        }
    }
    fclose(archivito);
}
void altaDeCliente(char archivo[])
{
    stCliente cliente;
    FILE *archivito;
    archivito = fopen(archivo, "ab");
    int var;

    if (archivito != NULL)
    {
        cliente.idCliente = idClienteNuevo(archivo);

        printf("Ingrese nombre max.30 char\n");
        fflush(stdin);
        scanf("%s", cliente.nombre);

        printf("Ingrese apellido max.30 char\n");
        fflush(stdin);
        scanf("%s", cliente.apellido);
        do
        {
            printf("Ingrese username max.20 char\n");
            fflush(stdin);
            scanf("%s", cliente.userName);
            var = verificarClienteYaExiste(archivo, cliente);
        } while (var == 0);
        printf("Ingrese password max.20 char\n");
        fflush(stdin);
        scanf("%s", cliente.password);

        printf("Ingrese email max.30 char\n");
        fflush(stdin);
        scanf("%s", cliente.mail);

        printf("Ingrese genero m o f \n");
        fflush(stdin);
        scanf("%c", &cliente.genero);

        cliente.rol = 0;
        cliente.activo = 1;

        fwrite(&cliente, sizeof(stCliente), 1, archivito);
        fclose(archivito);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
}

int verificarClienteYaExiste(char archivo[], stCliente clienteIngreso)
{
    FILE *archivito;
    stCliente cliente;
    archivito = fopen(archivo, "rb");
    int resultado;

    if (archivito != NULL)
    {
        while (fread(&cliente, sizeof(stCliente), 1, archivito) > 0)
        {
            resultado = strcmp(cliente.userName, clienteIngreso.userName);

            if (resultado == 0)
            {
                printf("YA EXISTE EL USERNAME\n");
            }
        }
        if (resultado != 0)
        {
            printf("EL USERNAME NO EXISTE, PODES USARLO\n");
        }
    }
    return resultado;
}

int login(char archivo[])
{
    FILE *archivito;
    stCliente cliente;
    stCliente clienteIngreso;
    archivito = fopen(archivo, "rb");
    int resultado;

    if (archivito != NULL)
    {
        printf("Ingrese username\n");
        fflush(stdin);
        scanf("%s", clienteIngreso.userName);
        printf("Ingrese password\n");
        fflush(stdin);
        scanf("%s", clienteIngreso.password);

        while (fread(&cliente, sizeof(stCliente), 1, archivito) > 0 && resultado != 0)
        {
            resultado = strcmp(cliente.userName, clienteIngreso.userName);
            printf("%d", resultado);
            system("pause");
        }
    }

    if (resultado != 0)
    {
        printf("\tEL USUARIO INGRESADO NO EXISTE\n");
        printf("\tPOR FAVOR, REGISTRE UN NUEVO USUARIO\n");
        altaDeCliente(archivo);
    }
    else
    {
        printf("\tINGRESASTE CON EXITO\n");
    }

    fclose(archivito);
    return resultado;
}

void mostrarArchivo(char archivo[])
{
    FILE *archivito;
    stCliente cliente;
    archivito = fopen(archivo, "rb");
    int i = 0;

    if (archivito != NULL)
    {
        while (fread(&cliente, sizeof(stCliente), 1, archivito) > 0)
        {
            printf("\n Registro numero %d", i++);
            puts("\n-------------------------------------");
            printf("\n IdCliente: %d", cliente.idCliente);
            printf("\n Nombre: %s", cliente.nombre);
            printf("\n Apellido: %s", cliente.apellido);
            printf("\n Username: %s", cliente.userName);
            printf("\n Password: %s", cliente.password);
            printf("\n Mail: %s", cliente.mail);
            printf("\n Genero: %c", cliente.genero);
            printf("\n Rol: %d", cliente.rol);
            printf("\n Activo: %d", cliente.activo);
            puts("\n-------------------------------------");
        }
        fclose(archivito);
    }
}

void menuBienvenida(char archivo[])
{
    puts("\tBienvenido a HaCPedidos\n");
    login(archivo);
}
void modificarCliente(char archivo[])
{
    stCliente cliente;
    FILE *archivito;
    archivito = fopen(archivo, "r+b");
    int resultado = 0;
    char usuario[20], datoModificar, control;
    printf("Ingrese el usuario que quiere modificar?\n");
    fflush(stdin);
    scanf("%s", usuario);

    if (archivito != NULL)
    {
        while (fread(&cliente, sizeof(stCliente), 1, archivito) > 0)
        {
            if (strcmp(cliente.userName, usuario) == 0)
            {
                printf("Ingrese dato a modificar: \n");
                fflush(stdin);
                scanf("%c", &datoModificar);
                switch (datoModificar)
                {
                case 'n':
                    printf("\nIngrese nuevo nombre:");
                    fflush(stdin);
                    scanf("%s", cliente.nombre);
                    fseek(archivito, (-1) * sizeof(stCliente), SEEK_CUR);
                    fwrite(&cliente, sizeof(stCliente), 1, archivito);
                    break;
                case 'a':
                    printf("\nIngrese nuevo apellido:");
                    fflush(stdin);
                    scanf("%s", cliente.apellido);
                    fseek(archivito, (-1) * sizeof(stCliente), SEEK_CUR);
                    fwrite(&cliente, sizeof(stCliente), 1, archivito);
                    break;
                case 'u':
                    do
                    {
                        printf("\nIngrese nuevo usuario: ");
                        fflush(stdin);
                        scanf("%s", cliente.userName);
                        resultado = verificarClienteYaExiste(archivo, cliente);
                    } while (resultado == 0);
                    fwrite(&cliente, sizeof(stCliente), 1, archivito);
                    break;
                case 'p':
                    printf("\nIngrese nueva password: ");
                    fflush(stdin);
                    scanf("%s", cliente.password);
                    fseek(archivito, (-1) * sizeof(stCliente), SEEK_CUR);
                    fwrite(&cliente, sizeof(stCliente), 1, archivito);
                    break;
                case 'm':
                    printf("\nIngrese nuevo mail: ");
                    fflush(stdin);
                    scanf("%s", cliente.mail);
                    fseek(archivito, (-1) * sizeof(stCliente), SEEK_CUR);
                    fwrite(&cliente, sizeof(stCliente), 1, archivito);
                    break;
                default:
                    puts("----------------");
                    printf("\n El dato que quiere modificar no existe\n");
                    printf("Ingrese n/nombre , a/apellido , u/usuario, p/password, m/mail\n");
                    puts("----------------");
                    break;
                }
                printf("\nQuiere modificar otro dato del mismo usuario? s/n \n");
                fflush(stdin);
                scanf("%c", &control);
                if (control == 's')
                {
                    fseek(archivito, (-1) * sizeof(stCliente), SEEK_CUR);
                }
                else
                {
                    fseek(archivito, sizeof(stCliente), SEEK_END);
                }
            }
        }
    }
    fclose(archivito);
}
