#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

//////////////////////////////////////////////////CONSTANTES//////////////////////////////////////////////////

#define archivoClientes "clientes.bin"//nombre archivo clientes
#define archivoPedidos "pedidos.bin"//nombre archivo pedidos
#define archivoProductos "productos.bin"//nombre archivo productos
#define dimStr 30//dimensión strings
#define dimArr 100//dimensión arreglos
#define RESALTADOR_T "\x1b[33m"//color menus
#define ROJO_T "\x1b[31m"//color menus
#define VERDE_T "\x1b[32m"//color menus
#define NEUTRA_T "\x1b[37m"//color menus

//////////////////////////////////////////////////ESTRUCTURAS//////////////////////////////////////////////////

typedef struct{
    char calle[dimStr];
    char altura[dimStr];
    char piso[dimStr];
    char departamento[dimStr];
    char localidad[dimStr];
}stDomicilio;

typedef struct{
    int idCliente;
    long int dni;
    char telefono[dimStr];
    char mail[dimStr];
    char apellido[dimStr];
    char nombre[dimStr];
    stDomicilio domicilio;
    int estado;//1 alta 0 baja
    int cantidadPedidos;
}stCliente;

typedef struct{
    int categoria;//1 bolsas 2 ladrillos 3 aridos 4 hierros 5 vigas 6 fletes 7 otros
    int idProducto;
    char nombre[dimStr];
    char marca[dimStr];
    char proveedor[dimStr];
    char descripcion[dimStr];
    float precioCosto;
    float porcentajeGanancia;
    float precioVenta;
}stProducto;

typedef struct{
    char nombre[100];
    float cantidad;
    float precioVenta;
    int estado;// 1 visible 0 invisible
}stProductoPedido;

typedef struct{
    int dia;
    int mes;
    int anio;
}stFecha;

typedef struct{
    int idPedido;
    int idCliente;//id del cliente que realiza el pedido
    int estadoEntrega;//1 entregado 0 pendiente
    int estadoPago;//1 pagado 0 pendiente
    int estadoPedido;//1 activo 2 cancelado
    stProductoPedido productosPedidos[dimArr];//no se pueden cargar más de 100 productos por pedido
    int validosProductosPedidos;
    float monto;
    stFecha fecha;
}stPedido;

//////////////////////////////////////////////////PROTOTIPADO DE FUNCIONES//////////////////////////////////////////////////
//COMUNES
void menuPrincipal(char *opcion);
int contarRegistrosArchivo(char nombreArchivo[], int tamanio);
void opcionGuardar(char *opcion);
void guardarNuevo(char archivo[], int tamanio, void *aux);
void guardarModificacion(char archivo[], int tamanio, void *aux);
void gotoxy(int x, int y);
//CLIENTES
void menuClientes(char *opcion);
int cargarCliente(stCliente *aux);
long int cargarDniCliente(int *flag);
void cargarTelefonoCliente(char telefono[]);
void cargarMailCliente(char mail[]);
void cargarApellidoCliente(char apellido[]);
void cargarNombreCliente(char nombre[]);
stDomicilio cargarDomicilioCliente();
int bajaCliente(int reg);
int buscarCliente(stCliente *aux);
void menuBuscarCliente(char *opcion);
int buscarClienteId(int id);
int buscarClienteDni(long int dni);
int buscarClienteApellido(char apellido[]);
void mostrarCliente(stCliente aux);
void modificarCliente(int reg);
void menuModificarCliente(stCliente *aux, char *opcion);
int cargarArregloClientes(stCliente arreglo[], int dimension);
void menuOrdenarClientes(char *opcion);
void ordenarClientesId(stCliente arreglo[], int validos);
int aux_OrdenarClientesId(stCliente arreglo[], int pos, int validos);
void ordenarClientesApellido(stCliente arreglo[], int validos);
void aux_OrdenarClientesApellido(stCliente arreglo[], int u, stCliente cliente);
void ordenarClientesCantidadPedidos(stCliente arreglo[], int validos);
int aux_OrdenarClientesCantidadPedidos(stCliente arreglo[], int pos, int validos);
void indiceClientesLista(int y);
void mostrarClientePorLista(stCliente aux, int y);
void top10clientes(stCliente arreglo[], int validos, int y);
void menuMostrarClientes(char *opcion);
void mostrarClientes(stCliente arreglo[], int validos, int y);
void mostrarClientesAlta(stCliente arreglo[], int validos, int y);
void mostrarClientesBaja(stCliente arreglo[], int validos, int y);
//PEDIDOS
void menuPedidos(char *opcion);
int cargarPedido(stPedido *aux);
int validarClientePedido(int *reg);
stFecha cargarFecha();
int cargarProductosPedidos(stProductoPedido arreglo[], int validos, int dimension);
stProductoPedido cargarProductoPedido();
int cargarEstadoPagoPedido();
float calcularMonto(stProductoPedido arreglo[], int validos);
void sumarPedidoCliente(int idCliente);
int bajaPedido(int reg);
void restarPedidoCliente(int idCliente);
int buscarPedido(stPedido *aux);
void menuBuscarPedido(char *opcion);
int buscarPedidoIdPedido(int idPedido);
int buscarPedidoIdCliente(int idCliente);
void mostrarPedido(stPedido aux);
void mostrarProductosPedidos(stProductoPedido arreglo[], int validos, int * y);
void modificarPedido(int reg);
void menuModificarPedido(stPedido *aux, char *opcion);
void quitarProductosPedidos(stProductoPedido arreglo[], int validos);
int cargarArregloPedidos(stPedido arreglo[], int dimension);
void ordenarPedidosIdPedido(stPedido arreglo[], int validos);
int aux_ordenarPedidosIdPedido(stPedido arreglo[], int pos, int validos);
void ordenarPedidosIdCliente(stPedido arreglo[], int validos);
int aux_ordenarPedidosIdCliente(stPedido arreglo[], int pos, int validos);
int aux_ordenarPedidosFecha(stPedido arreglo[], int pos, int validos);
void indicePedidosLista(int y);
void mostrarPedidoPorLista (stPedido aux, int y);
void mostrarPedidosXCliente(stPedido arreglo[], int validos, int idCliente, int y);
void mostrarPedidosActivos(stPedido arreglo[], int validos, int y);
void mostrarPedidosPagados(stPedido arreglo[], int validos, int y);
void mostrarPedidosPagoPendiente(stPedido arreglo[], int validos, int y);
void mostrarPedidosEntregados(stPedido arreglo[], int validos, int y);
void mostrarPedidosEntregaPendiente(stPedido arreglo[], int validos, int y);
void mostrarPedidosCancelados(stPedido arreglo[], int validos, int y);
//PRODUCTOS
void menuProductos(char *opcion);
stProducto cargarProducto();
void cargarCategoriaProducto(int *categoria);
int generarIdProducto(int categoria);
void cargarNombreProducto(char nombre[]);
void cargarMarcaProducto(char marca[]);
void cargarProveedorProducto(char proveedor[]);
void cargarDescripcionProducto(char descripcion[]);
void cargarPrecioCostoProducto(float *precioCosto);
void cargarPorcentajeGananciaProducto(float *porcentajeGanancia);
void calcularPrecioVentaProducto(float *precioVenta, float precioCosto, float porcentajeGanancia);
int buscarProducto(stProducto *aux);
void menuBuscarProducto(char *opcion);
int buscarProductoId(int id);
int buscarProductoNombre(char nombre[]);
void mostrarProducto(stProducto aux);
void modificarProducto(int reg);
void menuModificarProducto(stProducto *aux, char *opcion);
void aumentarCostoCategoria(int categoria, float aumento);
int cargarArregloProductos(stProducto arreglo[], int dimension);
void menuOrdenarProductos(char *opcion);
void ordenarProductosId(stProducto arreglo[], int validos);
int aux_OrdenarProductosId(stProducto arreglo[], int pos, int validos);
void ordenarProductosNombre(stProducto arreglo[], int validos);
void aux_OrdenarProductosNombre(stProducto arreglo[], int u, stProducto producto);
void ordenarProductosMarca(stProducto arreglo[], int validos);
void aux_OrdenarProductosMarca(stProducto arreglo[], int u, stProducto producto);
void menuMostrarProductos(char *opcion);
void indiceProductosLista (int y);
void mostrarProductoPorLista(stProducto aux, int y);
void mostrarProductos(stProducto arreglo[], int validos, int y);
void mostrarProductosCategoria(stProducto arreglo[], int validos, int categoria, int y);
//////////////////////////////////////////////////MAIN//////////////////////////////////////////////////

int main(){

    system("color 07");//fondo blanco (7) letras negro (0)

    char opcion;
    int flag;
    stCliente auxCliente;
    stProducto auxProducto;
    stPedido auxPedido;
    int reg;
    stCliente *clientes;
    stProducto *productos;
    stPedido *pedidos;
    int dimension;
    int validos;
    char filtro;
    int categoria;
    float aumento;

    do{
        system("cls");
        menuPrincipal(&opcion);
        switch(opcion){

            case 49://clientes
                do{
                    system("cls");
                    menuClientes(&opcion);
                    switch(opcion){

                        case 49://nuevo cliente
                            flag = cargarCliente(&auxCliente);//flag validación dni
                            if(flag == 1){//dni existe
                                printf(ROJO_T "Ya existe un cliente registrado con el DNI ingresado"NEUTRA_T);
                            }
                            else{//dni no existe
                                opcionGuardar(&opcion);
                                if(opcion == 's' || opcion == 'S'){
                                    guardarNuevo(archivoClientes, sizeof(stCliente), &auxCliente);
                                    printf(VERDE_T "\nCliente guardado"NEUTRA_T);
                                }
                                else{
                                    printf(ROJO_T "\nCliente descartado"NEUTRA_T);
                                }
                            }
                            printf("\n");
                            system("pause");
                            break;

                        case 50://baja/alta cliente
                            reg = buscarCliente(&auxCliente);//reg incializado en -1 en función
                            if(reg == -1){//no se encontró el cliente buscado
                                printf(ROJO_T "Cliente no encontrado\n"NEUTRA_T);
                            }
                            else{//se encontró el cliente buscado y se modifica estado
                                flag = bajaCliente(reg);
                                mostrarCliente(auxCliente);
                                if(flag == 0){
                                    printf(ROJO_T "El cliente fue dado de baja\n"NEUTRA_T);
                                }
                                else{
                                    printf(VERDE_T "El cliente fue dado de alta\n"NEUTRA_T);
                                }
                            }
                            system("pause");
                            break;

                        case 51://consulta cliente
                            reg = buscarCliente(&auxCliente);//reg iniciliazado en -1 en función
                            if(reg == -1){//no se encontró el cliente buscado
                                printf(ROJO_T "Cliente no encontrado\n" NEUTRA_T);
                            }
                            else{//se encontró el cliente buscado y se muestra
                                system("cls");
                                mostrarCliente(auxCliente);
                            }
                            system("pause");
                            break;

                        case 52://modificacion cliente
                            reg = buscarCliente(&auxCliente);//reg incializado en -1 en función
                            if(reg == -1){//no se encontró el cliente buscado
                                printf(ROJO_T "Cliente no encontrado\n" NEUTRA_T);
                            }
                            else{
                                system("cls");
                                modificarCliente(reg);//se encontró el cliente buscado y se modifica
                            }
                            system("pause");
                            break;

                        case 53://listados clientes
                            dimension = contarRegistrosArchivo(archivoClientes, sizeof(stCliente));
                            clientes = (stCliente*) malloc(dimension * sizeof(stCliente));
                            validos = cargarArregloClientes(clientes, dimension);
                            do{
                                system("cls");
                                menuOrdenarClientes(&opcion);
                                switch(opcion){

                                    case 49://por id
                                        ordenarClientesId(clientes, validos);
                                        break;

                                    case 50://por apellido y nombre
                                        ordenarClientesApellido(clientes, validos);
                                        break;

                                    case 51://por cantidad de pedidos
                                        ordenarClientesCantidadPedidos(clientes, validos);
                                        break;

                                    case 52://top 10 clientes
                                        ordenarClientesCantidadPedidos(clientes, validos);
                                        system("cls");
                                        indiceClientesLista (0);
                                        top10clientes(clientes, validos, 2);
                                        printf ("\n");
                                        break;

                                    case 53://peor cliente
                                        ordenarClientesCantidadPedidos(clientes, validos);
                                        system("cls");
                                        indiceClientesLista (0);
                                        mostrarClientePorLista(clientes[validos-1], 2);
                                        printf ("\n");
                                        break;

                                    default:
                                        printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                                        system("pause");
                                }
                            }while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 53);

                            if(opcion != 52 && opcion != 53){
                                do{
                                    system("cls");
                                    menuMostrarClientes(&opcion);
                                    switch(opcion){

                                        case 49://todos
                                            system("cls");
                                            indiceClientesLista (0);
                                            mostrarClientes(clientes, validos, 2);
                                            printf ("\n");
                                            break;

                                        case 50://alta
                                            system("cls");
                                            indiceClientesLista (0);
                                            mostrarClientesAlta(clientes, validos, 2);
                                            printf ("\n");
                                            break;

                                        case 51://baja
                                            system("cls");
                                            indiceClientesLista (0);
                                            mostrarClientesBaja(clientes, validos, 2);
                                            printf ("\n");
                                            break;

                                        default:
                                            printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                                            system("pause");
                                    }
                                }while(opcion != 49 && opcion != 50 && opcion != 51);
                            }
                            system("pause");
                            break;

                        case 27://menu principal
                            break;

                        default:
                            printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                            system("pause");
                    }
                }while(opcion != 27);
                break;

            case 50://pedidos
                do{
                    system("cls");
                    menuPedidos(&opcion);
                    switch(opcion){

                        case 49://nuevo pedido
                            reg = cargarPedido(&auxPedido);
                            if(reg == -1){//cliente no encontrado o no confirmado
                                printf(ROJO_T "Cliente no encontrado o no confirmado" NEUTRA_T);
                            }
                            else{//cliente encontrado, confirmado y pedido cargado
                                printf("\n");
                                opcionGuardar(&opcion);
                                if(opcion == 's' || opcion == 'S'){
                                    guardarNuevo(archivoPedidos, sizeof(stPedido), &auxPedido);
                                    sumarPedidoCliente(auxPedido.idCliente);//se suma 1 al campo cantidadPedidos del cliente
                                    printf(VERDE_T "\nPedido guardado" NEUTRA_T);
                                }
                                else{
                                    printf(ROJO_T "\nPedido descartado" NEUTRA_T);
                                }
                            }
                            printf("\n");
                            system("pause");
                            break;

                        case 50://baja/alta pedido
                            reg = buscarPedido(&auxPedido);//reg incializado en -1 en función
                            if(reg == -1){//no se encontró el pedido buscado
                                printf(ROJO_T "Pedido no encontrado\n" NEUTRA_T);
                            }
                            else{//se encontró el pedido buscado y se modifica estado
                                flag = bajaPedido(reg);
                                system("cls");
                                mostrarPedido(auxPedido);
                                if(flag == 0){
                                    printf(ROJO_T "El pedido fue dado de baja\n" NEUTRA_T);
                                    restarPedidoCliente(auxPedido.idCliente);//se resta 1 al campo cantidadPedidos del cliente
                                }
                                else{
                                    printf(VERDE_T "El pedido fue dado de alta\n" NEUTRA_T);
                                    sumarPedidoCliente(auxPedido.idCliente);//se suma 1 al campo cantidadPedidos del cliente
                                }
                            }
                            system("pause");
                            break;

                        case 51://consulta pedido
                            reg = buscarPedido(&auxPedido);//reg iniciliazado en -1 en función
                            if(reg == -1){//no se encontró el pedido buscado
                                printf(ROJO_T "Pedido no encontrado\n" NEUTRA_T);
                            }
                            else{//se encontró el pedido buscado y se muestra
                                system("cls");
                                mostrarPedido(auxPedido);
                            }
                            system("pause");
                            break;

                        case 52://modificacion pedido
                            reg = buscarPedido(&auxPedido);//reg incializado en -1 en función
                            if(reg == -1){//no se encontró el pedido buscado
                                printf(ROJO_T "Pedido no encontrado\n" NEUTRA_T);
                            }
                            else{
                                system("cls");
                                modificarPedido(reg);//se encontró el pedido buscado y se modifica
                            }
                            system("pause");
                            break;

                        case 53://listados pedidos
                            dimension = contarRegistrosArchivo(archivoPedidos, sizeof(stPedido));
                            pedidos = (stPedido*) malloc(dimension * sizeof(stPedido));
                            validos = cargarArregloPedidos(pedidos, dimension);
                            do{
                                system("cls");
                                menuOrdenarPedidos(&opcion);
                                switch(opcion){

                                    case 49://por id pedido
                                        ordenarPedidosIdPedido(pedidos, validos);
                                        break;

                                    case 50://por id cliente
                                        ordenarPedidosIdCliente(pedidos, validos);
                                        break;

                                    case 51://por fecha
                                        ordenarPedidosFecha(pedidos, validos);
                                        break;

                                    case 52://pedidos por cliente
                                        reg = buscarCliente(&auxCliente);//reg iniciliazado en -1 en función
                                        if(reg == -1){//no se encontró el cliente buscado
                                            printf(ROJO_T "Cliente no encontrado\n" NEUTRA_T);
                                        }
                                        else{//se encontró el cliente buscado y se muestran sus pedidos
                                            system("cls");
                                            indicePedidosLista (0);
                                            mostrarPedidosXCliente(pedidos, validos, auxCliente.idCliente, 2);
                                        }

                                        break;

                                    default:
                                        printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                                        system("pause");
                                }
                            }while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52);

                            if(opcion != 52){
                                do{
                                    system("cls");
                                    menuMostrarPedidos(&opcion);
                                    switch(opcion){

                                        case 49://activos
                                            system("cls");
                                            indicePedidosLista (0);
                                            mostrarPedidosActivos(pedidos, validos, 2);
                                            break;

                                        case 50://activos pagados
                                            system("cls");
                                            indicePedidosLista (0);
                                            mostrarPedidosPagados(pedidos, validos, 2);
                                            break;

                                        case 51://activos pendientes de pago
                                            system("cls");
                                            indicePedidosLista (0);
                                            mostrarPedidosPagoPendiente(pedidos, validos, 2);
                                            break;

                                        case 52://activos entregados
                                            system("cls");
                                            indicePedidosLista (0);
                                            mostrarPedidosEntregados(pedidos, validos, 2);
                                            break;

                                        case 53://activos pendientes de entrega
                                            system("cls");
                                            indicePedidosLista (0);
                                            mostrarPedidosEntregaPendiente(pedidos, validos, 2);
                                            break;

                                        case 54://cancelados
                                            system("cls");
                                            indicePedidosLista (0);
                                            mostrarPedidosCancelados(pedidos, validos, 2);
                                            break;

                                        default:
                                            printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                                            system("pause");
                                    }
                                }while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 53 && opcion != 54);
                            }
                            system("pause");
                            break;

                        case 27://menu principal
                            break;

                        default:
                            printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                            system("pause");
                    }
                }while(opcion != 27);
                break;

            case 51://productos
                do{
                    system("cls");
                    menuProductos(&opcion);
                    switch(opcion){

                        case 49://nuevo producto
                            auxProducto = cargarProducto();
                            opcionGuardar(&opcion);
                            if(opcion == 's' || opcion == 'S'){
                                guardarNuevo(archivoProductos, sizeof(stProducto), &auxProducto);
                                    printf(VERDE_T "\nProducto guardado" NEUTRA_T);
                            }
                            else{
                                printf(ROJO_T "\nProducto descartado" NEUTRA_T);
                            }
                            printf("\n");
                            system("pause");
                            break;

                        case 50://consulta producto
                            reg = buscarProducto(&auxProducto);//reg iniciliazado en -1 en función
                            if(reg == -1){//no se encontró el producto buscado
                                printf(ROJO_T "Producto no encontrado\n" NEUTRA_T);
                            }
                            else{//se encontró el producto buscado y se muestra
                                system("cls");
                                mostrarProducto(auxProducto);
                            }
                            system("pause");
                            break;

                        case 51://modificacion producto
                            reg = buscarProducto(&auxProducto);//reg incializado en -1 en función
                            if(reg == -1){//no se encontró el producto buscado
                                printf(ROJO_T "Producto no encontrado\n" NEUTRA_T);
                            }
                            else{
                                system("cls");
                                modificarProducto(reg);//se encontró el producto buscado y se modifica
                            }
                            system("pause");
                            break;

                        case 52://aumentos productos
                            cargarCategoriaProducto(&categoria);
                            printf("Ingrese el porcentaje de aumento: ");
                            scanf("%f", &aumento);
                            aumentarCostoCategoria(categoria, aumento);
                            printf(VERDE_T "Aumento guardado\n" NEUTRA_T, aumento);
                            dimension = contarRegistrosArchivo(archivoProductos, sizeof(stProducto));
                            productos = (stProducto*) malloc(dimension * sizeof(stProducto));
                            validos = cargarArregloProductos(productos, dimension);
                            indiceProductosLista (20);
                            mostrarProductosCategoria(productos, validos, categoria, 22);
                            printf ("\n");
                            system("pause");
                            break;

                        case 53://listados productos
                            dimension = contarRegistrosArchivo(archivoProductos, sizeof(stProducto));
                            productos = (stProducto*) malloc(dimension * sizeof(stProducto));
                            validos = cargarArregloProductos(productos, dimension);
                            do{
                                system("cls");
                                menuOrdenarProductos(&opcion);
                                switch(opcion){

                                    case 49://por id
                                        ordenarProductosId(productos, validos);
                                        break;

                                    case 50://por nombre
                                        ordenarProductosNombre(productos, validos);
                                        break;

                                    case 51://por marca
                                        ordenarProductosMarca(productos, validos);
                                        break;

                                    default:
                                        printf(ROJO_T"Opcion invalida\n" NEUTRA_T);
                                        system("pause");
                                }
                            }while(opcion != 49 && opcion != 50 && opcion != 51);

                            do{
                                system("cls");
                                menuMostrarProductos(&opcion);
                                switch(opcion){

                                    case 49://todos
                                        system("cls");
                                        indiceProductosLista (0);
                                        mostrarProductos(productos, validos, 2);
                                        printf ("\n");
                                        break;

                                    case 50://categoria
                                        cargarCategoriaProducto(&categoria);
                                        system("cls");
                                        indiceProductosLista (0);
                                        mostrarProductosCategoria(productos, validos, categoria, 2);
                                        printf ("\n");
                                        break;

                                    default:
                                        printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                                        system("pause");
                                }
                            }while(opcion != 49 && opcion != 50);
                            system("pause");
                            break;

                        case 27://menu principal
                            break;

                        default:
                            printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                            system("pause");
                    }
                }while(opcion != 27);
                break;

            case 48://salir
                printf(RESALTADOR_T "Gracias por usar Prolij%cn 1.1\n%c 2022 TiM ToC" NEUTRA_T, 161, 184);
                break;

            default:
                printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                system("pause");
        }
    }while(opcion != 48);

    return 0;
}

//////////////////////////////////////////////////FUNCIONES COMUNES//////////////////////////////////////////////////

void menuPrincipal(char *opcion){

    printf("\tMENU PRINCIPAL\n");
    printf("------------------------------\n");
    printf(RESALTADOR_T " 1\tClientes\n");
    printf(" 2\tPedidos\n");
    printf(" 3\tProductos\n");
    printf(" 0\tSalir\n");
    printf(NEUTRA_T "Ingrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

int contarRegistrosArchivo(char nombreArchivo[], int tamanio){

    int reg = 0;
    FILE * buf = fopen(nombreArchivo, "rb");

    if(buf){
        fseek(buf, 0, 2);
        reg = ftell(buf) / tamanio;//calcula la cantidad de registros del archivo
        fclose(buf);
    }

    return reg;
}

void opcionGuardar(char *opcion){

    printf("Guardar? s/n ");
    fflush(stdin);
    (*opcion) = getche();
}

void guardarNuevo(char archivo[], int tamanio, void *aux){

    FILE * buf = fopen(archivo, "ab");

    if(buf){
        fwrite(aux, tamanio, 1, buf);
        fclose(buf);
    }

}

void gotoxy(int x, int y){

    HANDLE manipulador;
    COORD coordenadas;
    manipulador = GetStdHandle(STD_OUTPUT_HANDLE);
    coordenadas.X = x;
    coordenadas.Y = y;
    SetConsoleCursorPosition(manipulador, coordenadas);
}

//////////////////////////////////////////////////FUNCIONES CLIENTES//////////////////////////////////////////////////

void menuClientes(char *opcion){

    printf("\tCLIENTES\n");
    printf("------------------------------\n");
    printf(RESALTADOR_T " 1\tNuevo\n");
    printf(" 2\t" VERDE_T "Alta " RESALTADOR_T "/" ROJO_T " Baja\n");
    printf(RESALTADOR_T " 3\tConsulta\n");
    printf(" 4\tModificacion\n");
    printf(" 5\tListados\n");
    printf(" ESC\tMenu principal\n");
    printf(NEUTRA_T "Ingrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

int cargarCliente(stCliente *aux){

    int flag;

    aux->idCliente = contarRegistrosArchivo(archivoClientes, sizeof(stCliente)) + 1;//suma 1 a la cantidad de registros del archivo
    aux->dni = cargarDniCliente(&flag);//flag validación dni
    if(flag == 0){//dni no existe
        cargarTelefonoCliente(aux->telefono);
        cargarMailCliente(aux->mail);
        cargarApellidoCliente(aux->apellido);
        cargarNombreCliente(aux->nombre);
        aux->domicilio = cargarDomicilioCliente();
        aux->estado = 1;//alta por defecto
        aux->cantidadPedidos = 0;//como es un cliente nuevo se inicializa en 0
    }

    return flag;
}

long int cargarDniCliente(int *flag){

    long int dni;
    stCliente aux;
    FILE * buf = fopen(archivoClientes, "rb");
    (*flag) = 0;

    do{
        printf("DNI: ");
        scanf("%li", &dni);
        if(dni <= 0){
            printf(ROJO_T "DNI invalido\n" NEUTRA_T);
        }
    }while(dni <= 0);

    if(buf){
        do{
            fread(&aux, sizeof(stCliente), 1, buf);
            if(aux.dni == dni){
                (*flag) = 1;//dni existe
            }
        }while(!feof(buf) && *flag == 0);
        fclose(buf);
    }

    return dni;
}

void cargarTelefonoCliente(char telefono[]){

    printf("Telefono: ");
    fflush(stdin);
    fgets(telefono, dimStr, stdin);
    strtok(telefono, "\n");
}

void cargarMailCliente(char mail[]){

    do{
        printf("Mail: ");
        fflush(stdin);
        fgets(mail, dimStr, stdin);
        strtok(mail, "\n");
        if(mail[0] != '\n' && (!strstr(mail, "@")  || !strstr(mail, "."))){
            printf(ROJO_T "Mail invalido\n" NEUTRA_T);
        }
    }while(mail[0] != '\n' && (!strstr(mail, "@")  || !strstr(mail, ".")));
}

void cargarApellidoCliente(char apellido[]){

    do{
        printf("Apellido: ");
        fflush(stdin);
        fgets(apellido, dimStr, stdin);
        strtok(apellido, "\n");
        if(apellido[0] == '\n'){//validación apellido
            printf(RESALTADOR_T "Campo obligatorio\n" NEUTRA_T);
        }
    }while(apellido[0] == '\n');

    for(int i = 0; apellido[i]; i++)
        apellido[i] = toupper(apellido[i]);
}

void cargarNombreCliente(char nombre[]){

    do{
        printf("Nombre: ");
        fflush(stdin);
        fgets(nombre, dimStr, stdin);
        strtok(nombre, "\n");
        if(nombre[0] == '\n'){
            printf(RESALTADOR_T "Campo obligatorio\n" NEUTRA_T);
        }
    }while(nombre[0] == '\n');

    for(int i = 0; nombre[i]; i++)
        nombre[i] = toupper(nombre[i]);
}

stDomicilio cargarDomicilioCliente(){

    stDomicilio domicilio;

    printf("Domicilio:\n");
    do{
        printf("Calle: ");
        fflush(stdin);
        fgets(domicilio.calle, dimStr, stdin);
        strtok(domicilio.calle, "\n");
        if(domicilio.calle[0] == '\n'){
            printf(RESALTADOR_T "Campo obligatorio\n" NEUTRA_T);
        }
    }while(domicilio.calle[0] == '\n');

    for(int i = 0; domicilio.calle[i]; i++)
        domicilio.calle[i] = toupper(domicilio.calle[i]);

    printf("Altura: ");
    fflush(stdin);
    fgets(domicilio.altura, dimStr, stdin);
    strtok(domicilio.altura, "\n");

    printf("Piso: ");
    fflush(stdin);
    fgets(domicilio.piso, dimStr, stdin);
    strtok(domicilio.piso, "\n");

    printf("Departamento: ");
    fflush(stdin);
    fgets(domicilio.departamento, dimStr, stdin);
    strtok(domicilio.departamento, "\n");

    do{
        printf("Localidad: ");
        fflush(stdin);
        fgets(domicilio.localidad, dimStr, stdin);
        strtok(domicilio.localidad, "\n");
        if(domicilio.localidad[0] == '\n'){
            printf(RESALTADOR_T "Campo obligatorio\n" NEUTRA_T);
        }
    }while(domicilio.localidad[0] == '\n');

    for(int i = 0; domicilio.localidad[i]; i++)
        domicilio.localidad[i] = toupper(domicilio.localidad[i]);

    return domicilio;
}

int bajaCliente(int reg){

    stCliente aux;
    int flag;
    FILE * buf = fopen(archivoClientes, "r+b");

    if(buf){
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fread(&aux, sizeof(stCliente), 1, buf);
        if(aux.estado == 1){
            aux.estado = 0;
            flag = 0;
        }
        else{
            aux.estado = 1;
            flag = 1;
        }
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fwrite(&aux, sizeof(stCliente), 1, buf);
        fclose(buf);
    }

    return flag;
}

int buscarCliente(stCliente *aux){

    char opcion;
    int id;
    long int dni;
    char apellido[dimStr];
    int reg = -1;

    do{
        system("cls");
        menuBuscarCliente(&opcion);
        switch(opcion){

            case 49://por id
                printf("ID: ");
                scanf("%i", &id);
                reg = buscarClienteId(id);
                break;

            case 50://por dni
                printf("DNI: ");
                scanf("%li", &dni);
                reg = buscarClienteDni(dni);
                break;

            case 51://por apellido
                printf("Apellido: ");
                fflush(stdin);
                fgets(apellido, dimStr, stdin);
                strtok(apellido, "\n");
                for(int i = 0; apellido[i]; i++)
                    apellido[i] = toupper(apellido[i]);
                reg = buscarClienteApellido(apellido);
                break;

            default:
                printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                system("pause");
        }
    }while(opcion != 49 && opcion != 50 && opcion != 51);

    if(reg != -1){//se encontró el cliente buscado y se guarda en aux para retornarlo y mostrarlo en el main
        FILE * buf = fopen(archivoClientes, "rb");
        if(buf){
            fseek(buf, sizeof(stCliente) * (reg - 1), 0);
            fread(aux, sizeof(stCliente), 1, buf);
            fclose(buf);
        }
    }

    return reg;
}

void menuBuscarCliente(char *opcion){

    printf("Buscar cliente por:");
    printf(RESALTADOR_T "\n 1\tID");
    printf("\n 2\tDNI");
    printf("\n 3\tApellido");
    printf(NEUTRA_T "\nIngrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

int buscarClienteId(int id){

    int reg = -1;
    stCliente aux;
    FILE * buf = fopen(archivoClientes, "rb");

    if(buf){
        while(fread(&aux, sizeof(stCliente), 1, buf) > 0 && reg == -1){
            if(aux.idCliente == id){
                reg = ftell(buf) / sizeof(stCliente);
            }
        }
        fclose(buf);
    }

    return reg;
}

int buscarClienteDni(long int dni){

    int reg = -1;
    stCliente aux;
    FILE * buf = fopen(archivoClientes, "rb");

    if(buf){
        while(fread(&aux, sizeof(stCliente), 1, buf) > 0 && reg == -1){
            if(aux.dni == dni){
                reg = ftell(buf) / sizeof(stCliente);
            }
        }
        fclose(buf);
    }

    return reg;
}

int buscarClienteApellido(char apellido[]){

    int reg = -1;
    char control;
    stCliente aux;
    FILE * buf = fopen(archivoClientes, "rb");

    if(buf){
        while(fread(&aux, sizeof(stCliente), 1, buf) > 0 && reg == -1){
            if(strstr(aux.apellido, apellido) != NULL){
                printf("\"" RESALTADOR_T "%s %s" NEUTRA_T "\"? s/n ", aux.apellido, aux.nombre);//verificación si hay más clientes con el mismo apellido
                fflush(stdin);
                control = getche();
                printf("\n");
                if(control == 's' || control == 'S'){
                    reg = ftell(buf) / sizeof(stCliente);
                }
            }
        }
        fclose(buf);
    }

    return reg;
}

void mostrarCliente(stCliente aux){

    gotoxy (1,1); printf(RESALTADOR_T "ID:" NEUTRA_T ".........................");
    gotoxy (30,1); printf(RESALTADOR_T "%i", aux.idCliente);

    gotoxy (1,2); printf("Apellido:" NEUTRA_T "....................." RESALTADOR_T);
    gotoxy (30,2); printf ("%s", aux.apellido);

    gotoxy (1,3); printf("Nombre:" NEUTRA_T "......................." RESALTADOR_T);
    gotoxy (30,3); printf ("%s", aux.nombre);

    gotoxy (1,4); printf("DNI:" NEUTRA_T "............................" RESALTADOR_T);
    gotoxy (30,4); printf("%li", aux.dni);

    gotoxy (1,5); printf("Telefono:" NEUTRA_T "......................." RESALTADOR_T);
    if(aux.telefono[0] == '\n'){//si no tiene teléfono
        gotoxy (30,5); printf("-----");
    }
    else{
        gotoxy (30,5); printf("%s", aux.telefono);
    }

    gotoxy (1,6); printf("Mail:" NEUTRA_T ".........................." RESALTADOR_T);
    if(aux.mail[0] == '\n'){//si no tiene mail
        gotoxy (30,6); printf("-----");
    }
    else{
        gotoxy (30,6); printf("%s", aux.mail);
    }

    gotoxy (1,7); printf("Domicilio:");
    gotoxy (3,8); printf ("- Calle:"NEUTRA_T "........................" RESALTADOR_T);
    gotoxy (30,8); printf ("%s", aux.domicilio.calle);

    gotoxy (3,9); printf ("- Altura:" NEUTRA_T "...................." RESALTADOR_T);
    if(aux.domicilio.altura[0] != '\n'){//si tiene altura
        gotoxy (30,9); printf("%s", aux.domicilio.altura);
    }
    else{
        gotoxy (30,9); printf("-----");
    }

    gotoxy (3,10); printf ("- Piso:" NEUTRA_T "....................." RESALTADOR_T);
    if(aux.domicilio.piso[0] != '\n'){//si tiene piso
        gotoxy (30,10); printf("%s", aux.domicilio.piso);
    }
    else{
        gotoxy (30,10); printf("-----");
    }

    gotoxy (3,11); printf ("- Departamento:" NEUTRA_T "............." RESALTADOR_T);
    if(aux.domicilio.departamento[0] != '\n'){//si tiene departamento
        gotoxy (30,11); printf("%s", aux.domicilio.departamento);
    }
    else{
        gotoxy (30,11); printf("-----");
    }

    gotoxy (1,12); printf ("Localidad:" NEUTRA_T "..................." RESALTADOR_T);
    gotoxy (30,12); printf("%s", aux.domicilio.localidad);

    gotoxy (1,13); printf("Estado:" NEUTRA_T "..................." RESALTADOR_T);
    if(aux.estado == 1){
        gotoxy (30,13); printf(VERDE_T "ALTA\n"NEUTRA_T);//alta si el estado es 1
    }
    else{
        gotoxy (30,13); printf(ROJO_T "BAJA\n"NEUTRA_T);//baja si el estado es 0
    }

    gotoxy (1,14); printf(RESALTADOR_T "Cantidad de pedidos:" NEUTRA_T ".........." RESALTADOR_T);
    gotoxy (30,14); printf ("%i\n" NEUTRA_T, aux.cantidadPedidos);
    printf ("\n");
}

void indiceClientesLista (int y){

    gotoxy (2,y); printf (RESALTADOR_T "| ID");
    gotoxy (6,y); printf ("|APELLIDO");
    gotoxy (20,y); printf ("|NOMBRE");
    gotoxy (32,y); printf ("| DNI");
    gotoxy (42,y); printf ("| TELEFONO");
    gotoxy (54,y); printf ("| CALLE");
    gotoxy (72,y); printf ("| ALTURA");
    gotoxy (93,y); printf ("| PISO");
    gotoxy (100,y); printf ("| DPTO");
    gotoxy (107,y); printf ("| LOCALIDAD");
    gotoxy (124,y); printf ("| ESTADO");
    gotoxy (134,y); printf ("| C.P"); //cantidad pedidos.
    gotoxy (140,y); printf ("|");

    printf ("\n  -------------------------------------------------------------------------------------------------------------------------------------------\n" NEUTRA_T);

}

void mostrarClientePorLista (stCliente aux, int y){

    gotoxy (2,y); printf ("|%i", aux.idCliente);
    gotoxy (6,y); printf ("|%s", aux.apellido);
    gotoxy (20,y); printf ("|%s", aux.nombre);
    gotoxy (32,y); printf ("|%li", aux.dni);
    gotoxy (42,y); printf ("|%s", aux.telefono);
    gotoxy (54,y); printf ("|%s", aux.domicilio.calle);
    gotoxy (72,y); printf ("|%s", aux.domicilio.altura);
    gotoxy (93,y); printf ("|%s", aux.domicilio.piso);
    gotoxy (100,y); printf ("|%s", aux.domicilio.departamento);
    gotoxy (107,y); printf ("|%s", aux.domicilio.localidad);

    if (aux.estado == 1){
        gotoxy (124,y); printf ("|" VERDE_T "ALTA");
    }
    else{
        gotoxy (124,y); printf ("|" ROJO_T "BAJA");
    }

    gotoxy (134,y); printf (NEUTRA_T "|%i", aux.cantidadPedidos);

    gotoxy (140,y); printf ("|");
}

void modificarCliente(int reg){

    stCliente aux;
    char opcion;
    long int dni;
    int flag;
    FILE * buf = fopen(archivoClientes, "r+b");

    if(buf){
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fread(&aux, sizeof(stCliente), 1, buf);
        do{
            system("cls");
            menuModificarCliente(&aux, &opcion);
            switch(opcion){

                case 49://dni
                    dni = aux.dni;//guarda dni por si el nuevo existe
                    aux.dni = cargarDniCliente(&flag);
                    if(flag == 1){//dni existe
                        printf(ROJO_T "Ya existe un cliente registrado con el DNI ingresado\n" NEUTRA_T);
                        aux.dni = dni;//no cambia dni porque el nuevo existe
                    }
                    system("pause");
                    break;

                case 50://telefono
                    cargarTelefonoCliente(aux.telefono);
                    system("pause");
                    break;

                case 51://mail
                    cargarMailCliente(aux.mail);
                    system("pause");
                    break;

                case 52://apellido
                    cargarApellidoCliente(aux.apellido);
                    system("pause");
                    break;

                case 53://nombre
                    cargarNombreCliente(aux.nombre);
                    system("pause");
                    break;

                case 54://domicilio
                    aux.domicilio = cargarDomicilioCliente();
                    system("pause");
                    break;


                case 48://finalizar
                    opcionGuardar(&opcion);
                    if(opcion == 's' || opcion == 'S'){
                        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
                        fwrite(&aux, sizeof(stCliente), 1, buf);
                        fclose(buf);
                        printf(VERDE_T "\nCambios guardados\n" NEUTRA_T);
                        opcion = '0';
                    }
                    else{
                        printf(ROJO_T "\nCambios descartados\n" NEUTRA_T);
                        opcion = '0';
                    }
                    break;

                default:
                    printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                    system("pause");
            }
        }while(opcion != 48);
    }
}

void menuModificarCliente(stCliente *aux, char *opcion){

    mostrarCliente(*aux);//muestra el cliente a modificar y los campos que van siendo modificados
    printf("\nModificar:");
    printf(RESALTADOR_T "\n 1\tDNI");
    printf("\n 2\tTelefono");
    printf("\n 3\tMail");
    printf("\n 4\tApellido");
    printf("\n 5\tNombre");
    printf("\n 6\tDomicilio");
    printf("\n 0\tFinalizar");
    printf(NEUTRA_T "\nIngrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

int cargarArregloClientes(stCliente arreglo[], int dimension){

    int i = 0;
    stCliente aux;
    FILE * buf = fopen(archivoClientes, "rb");

    while(fread(&aux, sizeof(stCliente), 1, buf) > 0 && i < dimension){
        arreglo[i] = aux;
        i++;
    }

    return i;
}

void menuOrdenarClientes(char *opcion){

    printf("Ordenar por:");
    printf(RESALTADOR_T "\n 1\tID");
    printf("\n 2\tApellido y Nombre");
    printf("\n 3\tCantidad de pedidos");
    printf(NEUTRA_T "\nMostrar:");
    printf(VERDE_T "\n 4\tTop 10");
    printf(ROJO_T "\n 5\tPeor cliente");
    printf(NEUTRA_T "\nIngrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void ordenarClientesId(stCliente arreglo[], int validos){

    int i = 0;
    int posMenor = 0;
    stCliente aux;

    while (i < validos - 1){
        posMenor = aux_OrdenarClientesId(arreglo, i, validos);
        aux = arreglo[posMenor];
        arreglo[posMenor] = arreglo[i];
        arreglo[i] = aux;
        i++;
    }
}

int aux_OrdenarClientesId(stCliente arreglo[], int pos, int validos){

    int posMenor = pos;
    int i = pos + 1;
    stCliente menor = arreglo[pos];

    while(i < validos){
        if(menor.idCliente > arreglo[i].idCliente){
            menor = arreglo[i];
            posMenor = i;
        }
        i++;
    }

    return posMenor;
}

void ordenarClientesApellido(stCliente arreglo[], int validos){

    int i = 0;

    while (i < validos - 1){
        aux_OrdenarClientesApellido(arreglo, i, arreglo[i+1]);
        i++;
    }
}

void aux_OrdenarClientesApellido(stCliente arreglo[], int u, stCliente cliente){

    while(u >= 0 && strcmpi(cliente.apellido, arreglo[u].apellido) < 0){
        arreglo[u+1] = arreglo[u];
        u--;
    }

    while(u >=0 && strcmpi(cliente.apellido, arreglo[u].apellido) == 0 && strcmpi(cliente.nombre, arreglo[u].nombre) < 0){//si tienen el mismo apellido
        arreglo[u+1] = arreglo[u];
        u--;
    }

    arreglo[u+1] = cliente;
}

void ordenarClientesCantidadPedidos(stCliente arreglo[], int validos){

    int i = 0;
    int posMenor = 0;
    stCliente aux;

    while (i < validos - 1){
        posMenor = aux_OrdenarClientesCantidadPedidos(arreglo, i, validos);
        aux = arreglo[posMenor];
        arreglo[posMenor] = arreglo[i];
        arreglo[i] = aux;
        i++;
    }
}

int aux_OrdenarClientesCantidadPedidos(stCliente arreglo[], int pos, int validos){

    int posMenor = pos;
    int i = pos + 1;
    stCliente menor = arreglo[pos];

    while(i < validos){
        if(menor.cantidadPedidos < arreglo[i].cantidadPedidos){
            menor = arreglo[i];
            posMenor = i;
        }
        i++;
    }

    return posMenor;
}

void top10clientes(stCliente arreglo[], int validos, int y){

    int i = 0;

    while(i < validos && i < 10){
        mostrarClientePorLista(arreglo[i], y);
        i++;
        y++;
    }

}

void menuMostrarClientes(char *opcion){

    printf("Mostrar:");
    printf(RESALTADOR_T "\n 1\tTodos");
    printf(VERDE_T "\n 2\tAlta");
    printf(ROJO_T "\n 3\tBaja");
    printf(NEUTRA_T "\nIngrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void mostrarClientes(stCliente arreglo[], int validos, int y){

    int i;

    for(i = 0; i < validos; i++){
        mostrarClientePorLista(arreglo[i], y);
        y ++;
    }
}

void mostrarClientesAlta(stCliente arreglo[], int validos, int y){

    int i;

    for(i = 0; i < validos; i++){
        if(arreglo[i].estado == 1){
            mostrarClientePorLista(arreglo[i],y);
            y ++;
        }
    }
}

void mostrarClientesBaja(stCliente arreglo[], int validos, int y){

    int i;

    for(i = 0; i < validos; i++){
        if(arreglo[i].estado == 0){
            mostrarClientePorLista(arreglo[i],y);
            y ++;
        }
    }
}

//////////////////////////////////////////////////FUNCIONES PEDIDOS//////////////////////////////////////////////////

void menuPedidos(char *opcion){

    printf("\tPEDIDOS\n");
    printf("------------------------------\n");
    printf(RESALTADOR_T " 1\tNuevo\n");
    printf(" 2\t" VERDE_T "Alta " RESALTADOR_T "/" ROJO_T " Baja\n");
    printf(RESALTADOR_T " 3\tConsulta\n");
    printf(" 4\tModificacion\n");
    printf(" 5\tListados\n");
    printf(" ESC\tMenu principal\n");
    printf(NEUTRA_T "Ingrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

int cargarPedido(stPedido *aux){

    int reg = -1;
    char opcion;

    aux->idPedido = contarRegistrosArchivo(archivoPedidos, sizeof(stPedido)) + 1;//suma 1 a la cantidad de registros del archivo

    aux->idCliente = validarClientePedido(&reg);

    if(reg != -1){//se carga el pedido solo si se encontró y confirmó el cliente
        system("cls");
        aux->fecha = cargarFecha();
        aux->validosProductosPedidos = 0;
        aux->validosProductosPedidos = cargarProductosPedidos(aux->productosPedidos, aux->validosProductosPedidos, dimArr);
        aux->estadoEntrega = 0;//pendiente por defecto
        aux->estadoPago = cargarEstadoPagoPedido();
        aux->estadoPedido = 1;//activo por defecto
        aux->monto = calcularMonto(aux->productosPedidos, aux->validosProductosPedidos);
    }

    return reg;
}

int validarClientePedido(int *reg){

    int idCliente;
    stCliente aux;
    char opcion;

    (*reg) = buscarCliente(&aux);//reg iniciliazado en -1 en función

    if(*reg != -1){//cliente encontrado
        system("cls");
        mostrarCliente(aux);
        printf("Confirmar cliente? s/n ");
        fflush(stdin);
        opcion = getche();
        printf("\n");
        if(opcion == 's' || opcion == 'S'){
            idCliente = aux.idCliente;
        }
        else{
            (*reg) = -1;
        }
    }

    return idCliente;
}

stFecha cargarFecha(){

    stFecha aux;
    time_t t = time(NULL);
    struct tm fechaActual = *localtime(&t);

    aux.dia = fechaActual.tm_mday;
    aux.mes = fechaActual.tm_mon + 1;
    aux.anio = fechaActual.tm_year + 1900;

    return aux;
}

int cargarProductosPedidos(stProductoPedido arreglo[], int validos, int dimension){

    char control = 's';

    while(validos < dimension && (control == 's' || control == 'S')){
        arreglo[validos] = cargarProductoPedido();
        validos ++;
        printf("Agregar mas productos? s/n ");
        fflush(stdin);
        control = getche();
    }

    return validos;
}

stProductoPedido cargarProductoPedido(){

    stProductoPedido aux;
    stProducto auxProducto;
    int reg = -1;

    while(reg == -1){
        reg = buscarProducto(&auxProducto);
        if(reg == -1){//no se encontró el producto buscado
            printf(ROJO_T "Producto no encontrado\n" NEUTRA_T);
            system("pause");
        }
        else{//se encontró el producto buscado y se muestra
            system("cls");
            mostrarProducto(auxProducto);

            strcpy(aux.nombre, auxProducto.nombre);//se concatenan nombre, marca y descripcion del producto como nombre del producto pedido
            strcat(aux.nombre, " ");
            strcat(aux.nombre, auxProducto.marca);
            strcat(aux.nombre, " ");
            strcat(aux.nombre, auxProducto.descripcion);

            do{
                printf("Cantidad: ");
                scanf("%f", &aux.cantidad);
                if(aux.cantidad <= 0){
                    printf(ROJO_T "Cantidad invalida\n" NEUTRA_T);
                }
            }while(aux.cantidad <= 0);

            aux.precioVenta = aux.cantidad * auxProducto.precioVenta;

            aux.estado = 1;//visible por defecto
        }
    }

    return aux;
}

int cargarEstadoPagoPedido(){

    int estadoPago;
    char control;

    printf("\nPedido pagado? s/n ");
    fflush(stdin);
    control = getche();
    if(control == 's' || control == 'S'){
        estadoPago = 1;
    }
    else{
        estadoPago = 0;
    }

    return estadoPago;
}

float calcularMonto(stProductoPedido arreglo[], int validos){

    int i;
    float monto = 0;

    for(i = 0; i < validos; i ++){
        if(arreglo[i].estado == 1)//solamente se consideran los productos pedidos visibles
        {
            monto = monto + arreglo[i].precioVenta;//recorre el arreglo y toma el valor total de cada producto (precio * cantidad), y lo suma al monto anterior
        }
    }

    return monto;
}

void sumarPedidoCliente(int idCliente){

    stCliente aux;
    int flag = 0;
    int reg;
    FILE * buf = fopen(archivoClientes, "r+b");

    if(buf){
        reg = buscarClienteId(idCliente);
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fread(&aux, sizeof(stCliente), 1, buf);
        aux.cantidadPedidos++;
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fwrite(&aux, sizeof(stCliente), 1, buf);
        fclose(buf);
    }
}

int bajaPedido(int reg){

    stPedido aux;
    int flag;
    FILE * buf = fopen(archivoPedidos, "r+b");

    if(buf){
        fseek(buf, sizeof(stPedido) * (reg - 1), 0);
        fread(&aux, sizeof(stPedido), 1, buf);
        if(aux.estadoPedido == 1){
            aux.estadoPedido = 0;
            flag = 0;
        }
        else{
            aux.estadoPedido = 1;
            flag = 1;
        }
        fseek(buf, sizeof(stPedido) * (reg - 1), 0);
        fwrite(&aux, sizeof(stPedido), 1, buf);
        fclose(buf);
    }

    return flag;
}

void restarPedidoCliente(int idCliente){

    stCliente aux;
    int flag = 0;
    int reg;
    FILE * buf = fopen(archivoClientes, "r+b");

    if(buf){
        reg = buscarClienteId(idCliente);
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fread(&aux, sizeof(stCliente), 1, buf);
        aux.cantidadPedidos--;
        fseek(buf, sizeof(stCliente) * (reg - 1), 0);
        fwrite(&aux, sizeof(stCliente), 1, buf);
        fclose(buf);
    }
}

int buscarPedido(stPedido *aux){

    char opcion;
    int idPedido;
    int idCliente;
    int reg = -1;

    do{
        system("cls");
        menuBuscarPedido(&opcion);
        switch(opcion){

            case 49://por id pedido
                printf("ID Pedido: ");
                scanf("%i", &idPedido);
                reg = buscarPedidoIdPedido(idPedido);
                break;

            case 50://por id cliente
                printf("ID Cliente: ");
                scanf("%i", &idCliente);
                reg = buscarPedidoIdCliente(idCliente);
                break;

            default:
                printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                system("pause");
        }
    }while(opcion != 49 && opcion != 50);

    if(reg != -1){//se encontró el cliente buscado y se guarda en aux para retornarlo y mostrarlo en el main
        FILE * buf = fopen(archivoPedidos, "rb");
        if(buf){
            fseek(buf, sizeof(stPedido) * (reg - 1), 0);
            fread(aux, sizeof(stPedido), 1, buf);
            fclose(buf);
        }
    }

    return reg;
}

void menuBuscarPedido(char *opcion){

    printf("Buscar por:");
    printf(RESALTADOR_T "\n 1\tID Pedido");
    printf("\n 2\tID Cliente");
    printf(NEUTRA_T "\nIngrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

int buscarPedidoIdPedido(int idPedido){

    int reg = -1;
    stPedido aux;
    FILE * buf = fopen(archivoPedidos, "rb");

    if(buf){
        while(fread(&aux, sizeof(stPedido), 1, buf) > 0 && reg == -1){
            if(aux.idPedido == idPedido){
                reg = ftell(buf) / sizeof(stPedido);
            }
        }
        fclose(buf);
    }

    return reg;
}

int buscarPedidoIdCliente(int idCliente){

    int reg = -1;
    stPedido aux;
    char control;
    FILE * buf = fopen(archivoPedidos, "rb");

    if(buf){
        while(fread(&aux, sizeof(stPedido), 1, buf) > 0 && reg == -1){
            if(aux.idCliente == idCliente){
                printf("Fecha %i/%i/%i  ", aux.fecha.dia, aux.fecha.mes, aux.fecha.anio);
                printf ("ID Pedido: %i  ", aux.idPedido);
                printf("Monto " RESALTADOR_T "%$%.2f" NEUTRA_T "?  s/n ", aux.monto);//verificación si hay más pedidos del cliente
                fflush(stdin);
                control = getche();
                printf("\n");
                if(control == 's' || control == 'S'){
                    reg = ftell(buf) / sizeof(stPedido);
                }
            }
        }
        fclose(buf);
    }

    return reg;
}

void mostrarPedido(stPedido aux){

    gotoxy (2,1); printf("ID Pedido: %i", aux.idPedido);
    gotoxy (40,1); printf("Fecha: %i/%i/%i", aux.fecha.dia, aux.fecha.mes, aux.fecha.anio);
    gotoxy (2,2); printf("ID Cliente: %i", aux.idCliente);

    if(aux.estadoPedido == 1){
        gotoxy (2,4); printf(VERDE_T "ACTIVO");
    }
    else{
        gotoxy (2,4); printf(ROJO_T "CANCELADO");
    }

    if(aux.estadoEntrega == 0){
        gotoxy (2,5); printf(ROJO_T "PENDIENTE DE ENTREGA");
    }
    else{
        gotoxy (2,5); printf(VERDE_T "ENTREGADO");
    }

    if(aux.estadoPago == 0){
        gotoxy (2,6); printf(ROJO_T "PENDIENTE DE PAGO");
    }
    else{
        gotoxy (2,6);printf(VERDE_T "PAGADO");
    }

    gotoxy (2,8); printf (RESALTADOR_T "------------------------------------------------------\n" );
    gotoxy (2,9); printf ("| Cant");
    gotoxy (10,9); printf ("|       Producto");
    gotoxy (40,9); printf ("| Subtotal");
    gotoxy (55,9); printf ("|");
    gotoxy (2,10); printf ("------------------------------------------------------\n" );

    int y = 11;
    mostrarProductosPedidos(aux.productosPedidos, aux.validosProductosPedidos, &y);

    gotoxy (2,y); printf ("------------------------------------------------------\n");
    y++;
    gotoxy (2,y); printf ("|");
    gotoxy (10,y); printf ("|");
    gotoxy (30,y); printf("Total:");
    gotoxy (40,y); printf ("| $%.2f\n", aux.monto);
    gotoxy (55,y); printf ("|");
    y++;
    gotoxy (2,y); printf ("------------------------------------------------------\n"NEUTRA_T);

    printf ("\n");

}

void mostrarProductosPedidos(stProductoPedido arreglo[], int validos, int * y){

    int i;

    for(i = 0; i < validos; i ++){
        if(arreglo[i].estado == 1){//solamente se muestran los productos pedidos visibles
            gotoxy (2,*y); printf("| %.2f", arreglo[i].cantidad);
            gotoxy (10,*y);printf ("| %s", arreglo[i].nombre);
            gotoxy (40,*y); printf ("| $%.2f", arreglo[i].precioVenta);
            gotoxy (55,*y); printf ("|");
            *y = *y + 1;
        }
    }
}

void modificarPedido(int reg){

    stPedido aux;
    int idCliente;
    char opcion;
    int flag = -1;
    FILE * buf = fopen(archivoPedidos, "r+b");

    if(buf){
        fseek(buf, sizeof(stPedido) * (reg - 1), 0);
        fread(&aux, sizeof(stPedido), 1, buf);
        do{
            system("cls");
            menuModificarPedido(&aux, &opcion);
            switch(opcion){

                case 49://id cliente
                    idCliente = aux.idCliente;//guarda id por si el nuevo no se encuentra o confirma
                    aux.idCliente = validarClientePedido(&flag);
                    if(flag == -1){//cliente no encontrado o no confirmado
                        printf(ROJO_T "Cliente no encontrado o no confirmado\n" NEUTRA_T);
                        aux.idCliente = idCliente;//no cambia dni porque el nuevo existe
                    }
                    system("pause");
                    break;

                case 50://agregar productos
                    aux.validosProductosPedidos = cargarProductosPedidos(aux.productosPedidos, aux.validosProductosPedidos, dimArr);
                    aux.monto = calcularMonto(aux.productosPedidos, aux.validosProductosPedidos);
                    printf("\n");
                    system("pause");
                    break;

                case 51://quitar productos
                    quitarProductosPedidos(aux.productosPedidos, aux.validosProductosPedidos);
                    aux.monto = calcularMonto(aux.productosPedidos, aux.validosProductosPedidos);
                    system("pause");
                    break;

                case 52://estado entrega
                    if(aux.estadoEntrega == 0){
                        aux.estadoEntrega = 1;
                        printf(VERDE_T "Pedido entregado\n" NEUTRA_T);
                    }
                    else{
                        aux.estadoEntrega = 0;
                        printf(ROJO_T "Pedido pendiente de entrega\n" NEUTRA_T);
                    }
                    system("pause");
                    break;

                case 53://estado pago
                    if(aux.estadoPago == 0){
                        aux.estadoPago = 1;
                        printf(VERDE_T "Pedido pagado\n" NEUTRA_T);
                    }
                    else{
                        aux.estadoPago = 0;
                        printf(ROJO_T "Pedido pendiente de pago\n" NEUTRA_T);
                    }
                    system("pause");
                    break;

                case 48://finalizar
                    opcionGuardar(&opcion);
                    if(opcion == 's' || opcion == 'S'){
                        fseek(buf, sizeof(stPedido) * (reg - 1), 0);
                        fwrite(&aux, sizeof(stPedido), 1, buf);
                        fclose(buf);
                        if(flag != -1){//si se cambio el id cliente
                            sumarPedidoCliente(aux.idCliente);//se suma un pedido al nuevo id cliente
                            restarPedidoCliente(idCliente);//se resta un pedido al viejo id cliente
                        }
                        printf(VERDE_T "\nCambios guardados\n" NEUTRA_T);
                        opcion = '0';
                    }
                    else{
                        printf(ROJO_T "\nCambios descartados\n" NEUTRA_T);
                        opcion = '0';
                    }
                    break;

                default:
                    printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                    system("pause");
            }
        }while(opcion != 48);
    }
}

void menuModificarPedido(stPedido *aux, char *opcion){

    mostrarPedido(*aux);//muestra el pedido a modificar y los campos que van siendo modificados
    printf("\nModificar:");
    printf(RESALTADOR_T "\n 1\tID Cliente");
    printf("\n 2\tAgregar productos");
    printf("\n 3\tQuitar productos");
    printf("\n 4\tEstado entrega");
    printf("\n 5\tEstado pago");
    printf("\n 0\tFinalizar");
    printf(NEUTRA_T "\nIngrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void quitarProductosPedidos(stProductoPedido arreglo[], int validos){

    int i;
    char control;

    for(i = 0; i < validos; i ++){
        if(arreglo[i].estado == 1){//solamente se pueden quitar los visibles
            printf("Quitar \"%s\"? s/n ", arreglo[i].nombre);
            fflush(stdin);
            control = getche();
            printf("\n");
            if(control == 's' || control == 'S'){
                arreglo[i].estado = 0;
            }
        }
    }
}

int cargarArregloPedidos(stPedido arreglo[], int dimension){

    int i = 0;
    stPedido aux;
    FILE * buf = fopen(archivoPedidos, "rb");

    while(fread(&aux, sizeof(stPedido), 1, buf) > 0 && i < dimension){
        arreglo[i] = aux;
        i++;
    }

    return i;
}

void menuOrdenarPedidos(char *opcion){

    printf("Ordenar por:");
    printf(RESALTADOR_T "\n 1\tID Pedido");
    printf("\n 2\tID Cliente");
    printf("\n 3\tFecha");
    printf(NEUTRA_T "\nMostrar:");
    printf(RESALTADOR_T "\n 4\tPedidos por cliente");
    printf(NEUTRA_T "\nIngrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void ordenarPedidosIdPedido(stPedido arreglo[], int validos){

    int i = 0;
    int posMenor = 0;
    stPedido aux;

    while (i < validos - 1){
        posMenor = aux_ordenarPedidosIdPedido(arreglo, i, validos);
        aux = arreglo[posMenor];
        arreglo[posMenor] = arreglo[i];
        arreglo[i] = aux;
        i++;
    }
}

int aux_ordenarPedidosIdPedido(stPedido arreglo[], int pos, int validos){

    int posMenor = pos;
    int i = pos + 1;
    stPedido menor = arreglo[pos];

    while(i < validos){
        if(menor.idPedido > arreglo[i].idPedido){
            menor = arreglo[i];
            posMenor = i;
        }
        i++;
    }

    return posMenor;
}

void ordenarPedidosIdCliente(stPedido arreglo[], int validos){

    int i = 0;
    int posMenor = 0;
    stPedido aux;

    while (i < validos - 1){
        posMenor = aux_ordenarPedidosIdCliente(arreglo, i, validos);
        aux = arreglo[posMenor];
        arreglo[posMenor] = arreglo[i];
        arreglo[i] = aux;
        i++;
    }
}

int aux_ordenarPedidosIdCliente(stPedido arreglo[], int pos, int validos){

    int posMenor = pos;
    int i = pos + 1;
    stPedido menor = arreglo[pos];

    while(i < validos){
        if(menor.idCliente > arreglo[i].idCliente){
            menor = arreglo[i];
            posMenor = i;
        }
        i++;
    }

    return posMenor;
}

void ordenarPedidosFecha(stPedido arreglo[], int validos){

    int i;
    int j;
    stPedido aux;

    for(i = 0; i < validos; i ++){
        for(int j = i+1; j < validos; j++){
            if(arreglo[j].fecha.anio < arreglo[i].fecha.anio){
                aux = arreglo[j];
                arreglo[j] = arreglo[i];
                arreglo[i] = aux;
            }
            else if (arreglo[j].fecha.anio == arreglo[i].fecha.anio){
                if(arreglo[j].fecha.mes < arreglo[i].fecha.mes){
                    aux = arreglo[j];
                    arreglo[j] = arreglo[i];
                    arreglo[i] = aux;
                }
                else if(arreglo[j].fecha.mes == arreglo[i].fecha.mes){
                    if(arreglo[j].fecha.dia <= arreglo[i].fecha.dia){
                        aux = arreglo[j];
                        arreglo[j] = arreglo[i];
                        arreglo[i] = aux;
                    }
                }
            }
        }
    }
}

void menuMostrarPedidos(char *opcion){

    printf("Mostrar:");
    printf(RESALTADOR_T "\n 1\tActivos");
    printf("\n 2\tActivos pagados");
    printf("\n 3\tActivos pendientes de pago");
    printf("\n 4\tActivos entregados");
    printf("\n 5\tActivos pendientes de entrega");
    printf("\n 6\tCancelados");
    printf(NEUTRA_T "\nIngrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void indicePedidosLista (int y){

    gotoxy (2,y); printf (RESALTADOR_T "| FECHA");
    gotoxy (12,y); printf ("| ID P");
    gotoxy (20,y); printf ("| ID C");
    gotoxy (28,y); printf ("| MONTO");
    gotoxy (40,y); printf ("| PAGO");
    gotoxy (52,y); printf ("| ENTREGA");
    gotoxy (65,y); printf ("| ESTADO");
    gotoxy (75,y); printf ("|");
    printf ("\n  --------------------------------------------------------------------------\n");
    printf (NEUTRA_T"\n");
}

void mostrarPedidoPorLista (stPedido aux, int y){

    gotoxy (2,y); printf (NEUTRA_T "| %i/%i/%i", aux.fecha.dia, aux.fecha.mes, aux.fecha.anio);
    gotoxy (12,y); printf ("| %i", aux.idPedido);
    gotoxy (20,y); printf ("| %i", aux.idCliente);
    gotoxy (28,y); printf ("| %.2f", aux.monto);

    if(aux.estadoPago == 0){
        gotoxy (40,y); printf("|" ROJO_T "PENDIENTE");
    }
    else{
        gotoxy (40,y);printf(NEUTRA_T "|" VERDE_T "PAGADO");
    }

    if(aux.estadoEntrega == 0){
        gotoxy (52,y); printf(NEUTRA_T "|" ROJO_T "PENDIENTE");
    }
    else{
        gotoxy (52,y); printf(NEUTRA_T "|" VERDE_T "ENTREGADO");
    }

    if(aux.estadoPedido == 1){
        gotoxy (65,y); printf(NEUTRA_T "|" VERDE_T "ACTIVO");
    }
    else{
        gotoxy (65,y); printf(NEUTRA_T "|" ROJO_T "CANCELADO");
    }
    gotoxy (75,y); printf (NEUTRA_T "|\n");
}

void mostrarPedidosXCliente(stPedido arreglo[], int validos, int idCliente, int y){

    int i;

    for(i = 0; i < validos; i++){
        if(arreglo[i].idCliente == idCliente){
            mostrarPedidoPorLista(arreglo[i], y);
            y++;
        }
    }
}

void mostrarPedidosActivos(stPedido arreglo[], int validos, int y){

    int i;

    for(i = 0; i < validos; i++){
        if(arreglo[i].estadoPedido == 1){
            mostrarPedidoPorLista(arreglo[i], y);
            y++;
        }
    }
}

void mostrarPedidosPagados(stPedido arreglo[], int validos, int y){

    int i;

    for(i = 0; i < validos; i++){
        if(arreglo[i].estadoPago == 1){
            mostrarPedidoPorLista(arreglo[i], y);
            y ++;
        }
    }
}

void mostrarPedidosPagoPendiente(stPedido arreglo[], int validos, int y){

    int i;

    for(i = 0; i < validos; i++){
        if(arreglo[i].estadoPago == 0){
            mostrarPedidoPorLista(arreglo[i], y);
            y ++;
        }
    }
}

void mostrarPedidosEntregados(stPedido arreglo[], int validos, int y){

    int i;

    for(i = 0; i < validos; i++){
        if(arreglo[i].estadoEntrega == 1){
            mostrarPedidoPorLista(arreglo[i], y);
            y ++;
        }
    }
}

void mostrarPedidosEntregaPendiente(stPedido arreglo[], int validos, int y){

    int i;

    for(i = 0; i < validos; i++){
        if(arreglo[i].estadoEntrega == 0){
            mostrarPedidoPorLista(arreglo[i], y);
            y ++;
        }
    }
}

void mostrarPedidosCancelados(stPedido arreglo[], int validos, int y){

    int i;

    for(i = 0; i < validos; i++){
        if(arreglo[i].estadoPedido == 0){
            mostrarPedidoPorLista(arreglo[i], y);
            y ++;
        }
    }
}

//////////////////////////////////////////////////FUNCIONES PRODUCTOS//////////////////////////////////////////////////

void menuProductos(char *opcion){

    printf("\tPRODUCTOS\n");
    printf("------------------------------\n");
    printf(RESALTADOR_T " 1\tNuevo\n");
    printf(" 2\tConsulta\n");
    printf(" 3\tModificacion\n");
    printf(" 4\tAumento\n");
    printf(" 5\tListados\n");
    printf(" ESC\tMenu principal\n");
    printf(NEUTRA_T "Ingrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

stProducto cargarProducto(){

    stProducto aux;

    cargarCategoriaProducto(&aux.categoria);

    aux.idProducto = generarIdProducto(aux.categoria) + 1;

    cargarNombreProducto(aux.nombre);

    cargarMarcaProducto(aux.marca);

    cargarProveedorProducto(aux.proveedor);

    cargarDescripcionProducto(aux.descripcion);

    cargarPrecioCostoProducto(&aux.precioCosto);

    cargarPorcentajeGananciaProducto(&aux.porcentajeGanancia);

    calcularPrecioVentaProducto(&aux.precioVenta, aux.precioCosto, aux.porcentajeGanancia);

    return aux;
}

void cargarCategoriaProducto(int *categoria){

    do{
        printf("Categoria (1 Bolsas 2 Ladrillos 3 Aridos 4 Hierros 5 Vigas 6 Fletes 7 Otros): ");
        scanf ("%i", categoria);
        if(*categoria < 1 || *categoria > 7){
            printf(ROJO_T "Categoria invalida\n" NEUTRA_T);
        }
    }while(*categoria < 1 || *categoria > 7);
}

int generarIdProducto(int categoria){

    stProducto aux;
    int idProducto = categoria * 1000;
    FILE * buf = fopen(archivoProductos, "rb");

    if(buf){
        while(fread(&aux, sizeof(stProducto), 1, buf) > 0){
            if(aux.categoria == categoria){
                idProducto++;//se incrementa el id por cada producto de la misma categoría
            }
        }
        fclose(buf);
    }

    return idProducto;
}

void cargarNombreProducto(char nombre[]){

    do{
        printf("Nombre: ");
        fflush(stdin);
        fgets(nombre, dimStr, stdin);
        strtok(nombre, "\n");
        if(nombre[0] == '\n'){
            printf(RESALTADOR_T "Campo obligatorio\n" NEUTRA_T);
        }
    }while(nombre[0] == '\n');

    for(int i = 0; nombre[i]; i++)
        nombre[i] = toupper(nombre[i]);
}

void cargarMarcaProducto(char marca[]){

    printf("Marca: ");
    fflush (stdin);
    fgets(marca, dimStr, stdin);
    strtok(marca, "\n");

    for(int i = 0; marca[i]; i++)
        marca[i] = toupper(marca[i]);
}

void cargarProveedorProducto(char proveedor[]){

    printf("Proveedor: ");
    fflush(stdin);
    fgets(proveedor, dimStr, stdin);
    strtok(proveedor, "\n");

    for(int i = 0; proveedor[i]; i++)
        proveedor[i] = toupper(proveedor[i]);
}

void cargarDescripcionProducto(char descripcion[]){

    printf("Descripcion: ");
    fflush(stdin);
    fgets(descripcion, dimStr, stdin);
    strtok(descripcion, "\n");

    for(int i = 0; descripcion[i]; i++)
        descripcion[i] = toupper(descripcion[i]);
}

void cargarPrecioCostoProducto(float *precioCosto){

    printf("Precio de costo: $");
    scanf("%f", precioCosto);
}

void cargarPorcentajeGananciaProducto(float *porcentajeGanancia){

    printf("Porcentaje de ganancia: ");
    scanf("%f", porcentajeGanancia);
}

void calcularPrecioVentaProducto(float *precioVenta, float precioCosto, float porcentajeGanancia){

    (*precioVenta) = precioCosto + (precioCosto * (porcentajeGanancia / 100));
}

int buscarProducto(stProducto *aux){

    char opcion;
    int id;
    char nombre[dimStr];
    int reg = -1;

    do{
        system("cls");
        menuBuscarProducto(&opcion);
        switch(opcion){

            case 49://por id
                printf("ID: ");
                scanf("%i", &id);
                reg = buscarProductoId(id);
                break;

            case 50://por nombre
                printf("Nombre: ");
                fflush(stdin);
                fgets(nombre, dimStr, stdin);
                strtok(nombre, "\n");
                for(int i = 0; nombre[i]; i++)
                    nombre[i] = toupper(nombre[i]);
                reg = buscarProductoNombre(nombre);
                break;

            default:
                printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                system("pause");
        }
    }while(opcion != 49 && opcion != 50);

    if(reg != -1){//se encontró el producto buscado y se guarda en aux para retornarlo y mostrarlo en el main
        FILE * buf = fopen(archivoProductos, "rb");
        if(buf){
            fseek(buf, sizeof(stProducto) * (reg - 1), 0);
            fread(aux, sizeof(stProducto), 1, buf);
            fclose(buf);
        }
    }

    return reg;
}

void menuBuscarProducto(char *opcion){

    printf("Buscar producto por:");
    printf(RESALTADOR_T "\n 1\tID");
    printf("\n 2\tNombre");
    printf(NEUTRA_T "\nIngrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

int buscarProductoId(int id){

    int reg = -1;
    stProducto aux;
    FILE * buf = fopen(archivoProductos, "rb");

    if(buf){
        while(fread(&aux, sizeof(stProducto), 1, buf) > 0 && reg == -1){
            if(aux.idProducto == id){
                reg = ftell(buf) / sizeof(stProducto);
            }
        }
        fclose(buf);
    }

    return reg;
}

int buscarProductoNombre(char nombre[]){

    int reg = -1;
    char control;
    stProducto aux;
    FILE * buf = fopen(archivoProductos, "rb");

    for (int i = 0; nombre [i]; i++)
        nombre[i] = toupper (nombre[i]);

    if(buf){
        while(fread(&aux, sizeof(stProducto), 1, buf) > 0 && reg == -1){
            if(strstr(aux.nombre, nombre) != NULL){
                printf(RESALTADOR_T "%s %s %s" NEUTRA_T "?", aux.nombre, aux.marca, aux.descripcion);
                printf ("s/n ");//verificación si hay más productos con el mismo nombre
                fflush(stdin);
                control = getche();
                printf("\n");
                if(control == 's' || control == 'S'){
                    reg = ftell(buf) / sizeof(stProducto);
                }
            }
        }
        fclose(buf);
    }

    return reg;
}

void mostrarProducto(stProducto aux){
    gotoxy (1, 1); printf(RESALTADOR_T "ID:" NEUTRA_T ".............................");
    gotoxy (30, 1); printf (RESALTADOR_T "%i", aux.idProducto);

    gotoxy (1, 2); printf("TIPO:" NEUTRA_T "........................." RESALTADOR_T);
    if (aux.categoria == 1){
        gotoxy (30, 2); printf ("BOLSA");
    }
    else if(aux.categoria == 2){
        gotoxy (30, 2); printf("LADRILLO");
    }
    else if(aux.categoria == 3){
        gotoxy (30, 2); printf("ARIDO");
    }
    else if(aux.categoria == 4){
        gotoxy (30, 2); printf("HIERRO");
    }
    else if(aux.categoria == 5){
        gotoxy (30, 2); printf("VIGA");
    }
    else if(aux.categoria == 6){
        gotoxy (30, 2); printf("FLETE");
    }
    else{
        gotoxy (30, 2); printf("OTRO");
    }

    gotoxy (1, 3); printf("NOMBRE:" NEUTRA_T "........................" RESALTADOR_T);
    gotoxy (30, 3); printf ("%s", aux.nombre);

    gotoxy (1, 4); printf("MARCA:" NEUTRA_T "........................." RESALTADOR_T);
    gotoxy (30, 4); printf ("%s", aux.marca);

    gotoxy (1, 5); printf("DESCRIPCION:" NEUTRA_T "..................." RESALTADOR_T);
    gotoxy (30, 5); printf ("%s", aux.descripcion);

    gotoxy (1, 6); printf("PROVEEDOR:" NEUTRA_T "....................." RESALTADOR_T);
    gotoxy (30, 6); printf ("%s", aux.proveedor);

    gotoxy (1, 7); printf("PRECIO DE COSTO:" NEUTRA_T "................" RESALTADOR_T);
    gotoxy (30, 7); printf ("$%.2f", aux.precioCosto);

    gotoxy (1, 8); printf("PORCENTAJE DE GANANCIA:" NEUTRA_T "........." RESALTADOR_T);
    gotoxy (30, 8);printf ("%.2f%%", aux.porcentajeGanancia);

    gotoxy (1, 9); printf("PRECIO DE VENTA:" NEUTRA_T "................" RESALTADOR_T);
    gotoxy (30, 9); printf ("$%.2f\n" NEUTRA_T, aux.precioVenta);

    printf ("\n");
}

void modificarProducto(int reg){

    stProducto aux;
    char opcion;
    FILE * buf = fopen(archivoProductos, "r+b");

    if(buf){
        fseek(buf, sizeof(stProducto) * (reg - 1), 0);
        fread(&aux, sizeof(stProducto), 1, buf);
        do{
            system("cls");
            menuModificarProducto(&aux, &opcion);
            switch(opcion){

                case 49://nombre
                    cargarNombreProducto(aux.nombre);
                    system("pause");
                    break;

                case 50://marca
                    cargarMarcaProducto(aux.marca);
                    system("pause");
                    break;

                case 51://proveedor
                    cargarProveedorProducto(aux.proveedor);
                    system("pause");
                    break;

                case 52://descripcion
                    cargarDescripcionProducto(aux.descripcion);
                    system("pause");
                    break;

                case 53://precio de costo
                    cargarPrecioCostoProducto(&aux.precioCosto);
                    calcularPrecioVentaProducto(&aux.precioVenta, aux.precioCosto, aux.porcentajeGanancia);
                    system("pause");
                    break;

                case 54://porcentaje de ganancia
                    cargarPorcentajeGananciaProducto(&aux.porcentajeGanancia);
                    calcularPrecioVentaProducto(&aux.precioVenta, aux.precioCosto, aux.porcentajeGanancia);
                    system("pause");
                    break;

                case 48://finalizar
                    opcionGuardar(&opcion);
                    if(opcion == 's' || opcion == 'S'){
                        fseek(buf, sizeof(stProducto) * (reg - 1), 0);
                        fwrite(&aux, sizeof(stProducto), 1, buf);
                        fclose(buf);
                        printf(VERDE_T "\nCambios guardados\n" NEUTRA_T);
                        opcion = '0';
                    }
                    else{
                        printf(ROJO_T "\nCambios descartados\n" NEUTRA_T);
                        opcion = '0';
                    }
                    break;

                default:
                    printf(ROJO_T "Opcion invalida\n" NEUTRA_T);
                    system("pause");
            }
        }while(opcion != 48);
    }
}

void menuModificarProducto(stProducto *aux, char *opcion){

    mostrarProducto(*aux);//muestra el producto a modificar y los campos que van siendo modificados
    printf("\nModificar:");
    printf(RESALTADOR_T "\n 1\tNombre");
    printf("\n 2\tMarca");
    printf("\n 3\tProveedor");
    printf("\n 4\tDescripcion");
    printf("\n 5\tPrecio de costo");
    printf("\n 6\tPorcentaje de ganancia");
    printf("\n 0\tFinalizar");
    printf(NEUTRA_T "\nIngrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void aumentarCostoCategoria(int categoria, float aumento){

    stProducto aux;
    FILE * buf = fopen(archivoProductos, "r+b");

    if(buf){
        while(fread(&aux, sizeof(stProducto), 1, buf) > 0){
            if(aux.categoria == categoria){
                aux.precioCosto = aux.precioCosto + (aux.precioCosto * (aumento / 100));
                calcularPrecioVentaProducto(&aux.precioVenta, aux.precioCosto, aux.porcentajeGanancia);
                fseek(buf, sizeof(stProducto) * (-1), 1);
                fwrite(&aux, sizeof(stProducto), 1, buf);
                fseek(buf, 0, 1);
            }
        }
        fclose(buf);
    }
}

int cargarArregloProductos(stProducto arreglo[], int dimension){

    int i = 0;
    stProducto aux;
    FILE * buf = fopen(archivoProductos, "rb");

    while(fread(&aux, sizeof(stProducto), 1, buf) > 0 && i < dimension){
        arreglo[i] = aux;
        i++;
    }

    return i;
}

void menuOrdenarProductos(char *opcion){

    printf("Ordenar por:");
    printf(RESALTADOR_T "\n 1\tID");
    printf("\n 2\tNombre");
    printf("\n 3\tMarca");
    printf(NEUTRA_T "\nIngrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void ordenarProductosId(stProducto arreglo[], int validos){

    int i = 0;
    int posMenor = 0;
    stProducto aux;

    while (i < validos - 1){
        posMenor = aux_OrdenarProductosId(arreglo, i, validos);
        aux = arreglo[posMenor];
        arreglo[posMenor] = arreglo[i];
        arreglo[i] = aux;
        i++;
    }
}

int aux_OrdenarProductosId(stProducto arreglo[], int pos, int validos){

    int posMenor = pos;
    int i = pos + 1;
    stProducto menor = arreglo[pos];

    while(i < validos){
        if(menor.idProducto > arreglo[i].idProducto){
            menor = arreglo[i];
            posMenor = i;
        }
        i++;
    }

    return posMenor;
}

void ordenarProductosNombre(stProducto arreglo[], int validos){

    int i = 0;

    while (i < validos - 1){
        aux_OrdenarProductosNombre(arreglo, i, arreglo[i+1]);
        i++;
    }
}

void aux_OrdenarProductosNombre(stProducto arreglo[], int u, stProducto producto){

    while(u >= 0 && strcmpi(producto.nombre, arreglo[u].nombre) < 0){
        arreglo[u+1] = arreglo[u];
        u--;
    }
    arreglo[u+1] = producto;
}

void ordenarProductosMarca(stProducto arreglo[], int validos){

    int i = 0;

    while (i < validos - 1){
        aux_OrdenarProductosMarca(arreglo, i, arreglo[i+1]);
        i++;
    }
}

void aux_OrdenarProductosMarca(stProducto arreglo[], int u, stProducto producto){

    while(u >= 0 && strcmpi(producto.marca, arreglo[u].marca) < 0){
        arreglo[u+1] = arreglo[u];
        u--;
    }
    arreglo[u+1] = producto;
}

void indiceProductosLista (int y){

    gotoxy (2,y); printf (RESALTADOR_T "| ID");
    gotoxy (10,y); printf ("| TIPO");
    gotoxy (22,y); printf ("|   NOMBRE");
    gotoxy (37,y); printf ("|   MARCA");
    gotoxy (50,y); printf ("| DESCRIPCION");
    gotoxy (67,y); printf ("| COSTO");
    gotoxy (82,y); printf ("| %% GANANCIA");
    gotoxy (95,y); printf ("| VENTA");
    gotoxy (107,y); printf ("| PROVEEDOR");
    gotoxy (125,y); printf ("|");

    printf ("\n  ----------------------------------------------------------------------------------------------------------------------------\n" NEUTRA_T);
}

void mostrarProductoPorLista(stProducto aux, int y){

    gotoxy (2, y); printf("| %i", aux.idProducto);

    if (aux.categoria == 1){
        gotoxy (10, y); printf ("| BOLSA");
    }
    else if(aux.categoria == 2){
        gotoxy (10, y); printf("| LADRILLO");
    }
    else if(aux.categoria == 3){
        gotoxy (10, y); printf("| ARIDO");
    }
    else if(aux.categoria == 4){
        gotoxy (10, y); printf("| HIERRO");
    }
    else if(aux.categoria == 5){
        gotoxy (10, y); printf("| VIGA");
    }
    else if(aux.categoria == 6){
        gotoxy (10, y); printf("| FLETE");
    }
    else{
        gotoxy (10, y); printf("| OTROS");
    }

    gotoxy (22, y); printf("| %s", aux.nombre);
    gotoxy (37, y); printf("| %s", aux.marca);
    gotoxy (50, y); printf("| %s", aux.descripcion);
    gotoxy (67, y); printf("| $%.2f", aux.precioCosto);
    gotoxy (82, y); printf("| %.2f%%", aux.porcentajeGanancia);
    gotoxy (95, y); printf("| " RESALTADOR_T "$%.2f", aux.precioVenta);
    gotoxy (107, y); printf(NEUTRA_T "| %s", aux.proveedor);
    gotoxy (125,y); printf ("|");

}

void menuMostrarProductos(char *opcion){

    printf("Mostrar:");
    printf(RESALTADOR_T "\n 1\tTodos");
    printf("\n 2\tPor categoria");
    printf(NEUTRA_T "\nIngrese una opcion: ");
    fflush(stdin);
    (*opcion) = getche();
    printf("\n");
}

void mostrarProductos(stProducto arreglo[], int validos, int y){

    int i;

    for(i = 0; i < validos; i++){
        mostrarProductoPorLista (arreglo[i], y);
        y ++;
    }
}

void mostrarProductosCategoria(stProducto arreglo[], int validos, int categoria, int y){

    int i;

    for(i = 0; i < validos; i++){
        if(arreglo[i].categoria == categoria){
            mostrarProductoPorLista(arreglo[i], y);
            y ++;
        }
    }
    printf ("\n");
}
