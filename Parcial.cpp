// Parcial.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <mysql.h>
#include <iostream>
#include <locale.h>
#include <string>
using namespace std;

int q_estado;
MYSQL* conectar;
void menu();
void crud_marcas();
void crear_marca();
void leer_marcas();
void actualizar_marca();
void eliminar_marca();
void crud_productos();
void crear_producto();
void leer_productos();
void actualizar_producto();
void eliminar_producto();

int main()
{
    conectar = mysql_init(0);
    conectar = mysql_real_connect(conectar, "localhost", "root", "david2021", "parcial", 3306, NULL, 0);
    if (conectar) {
        //setlocale(LC_ALL, "spanish");
        menu();
    }
    else {
        cout << "Error en la conexión..." << endl;
    }
    system("pause");
    return 0;
}

void menu() {
    int opcion;

    while (true) {

        cout << "Menú" << endl;
        cout << "    1.Marcas" << endl;
        cout << "    2.Productos" << endl;
        cout << "    3.Salir\n" << endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                crud_marcas();
                break;
            case 2:
                crud_productos();
                break;
            case 3:
                exit(1);
            default:
                cout << "\nLa opción ingresada es incorrecta\n" << endl;
                break;
        }

        cout << "---------------------------------------\n" << endl;

    }
}

void crud_marcas() {
    int opcion;
    bool bandera = true;

    while (bandera) {

        cout << "\nMarcas" << endl;
        cout << "    1.Crear" << endl;
        cout << "    2.Leer" << endl;
        cout << "    3.Actualizar" << endl;
        cout << "    4.Eliminar" << endl;
        cout << "    5.Regresar\n" << endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cin.ignore();
                crear_marca();
                break;
            case 2:
                leer_marcas();
                break;
            case 3:
                actualizar_marca();
                break;
            case 4:
                eliminar_marca();
                break;
            case 5:
                bandera = false;
                break;
            default:
                cout << "\nLa opción ingresada es incorrecta\n" << endl;
                break;
        }

        cout << "\n---------------------------------------" << endl;

    }
}

void crear_marca() {
    string marca, consulta;
    cout << "\nNombre de la marca: ";
    getline(cin, marca);
    consulta = "INSERT INTO marcas(marca) VALUES('" + marca + "');";
    const char* i = consulta.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Marca ingresada con éxito" << endl;
        leer_marcas();
    }
    else {
        cout << "Error al ingresar marca" << endl;
    }
}

void leer_marcas() {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    consulta = "SELECT * FROM parcial.marcas;";
    const char* i = consulta.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        cout << "\n--------------------------" << endl;
        cout << "id\t| marca" << endl;
        cout << "--------------------------" << endl;
        while (fila = mysql_fetch_row(resultado)) {
            cout << fila[0] << "\t| " << fila[1] << endl;
            cout << "--------------------------" << endl;
        }
    }
    else {
        cout << "Error al leer marcas" << endl;
    }
}

void actualizar_marca() {
    int id;
    string marca, consulta;

    leer_marcas();

    cout << "\nId de la marca: "; 
    cin >> id;

    cin.ignore();

    cout << "\nNombre de la marca: ";
    getline(cin, marca);

    consulta = "UPDATE marcas SET marca = '" + marca + "' WHERE id = " + to_string(id);
    const char* i = consulta.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Marca actualizada con éxito" << endl;
        leer_marcas();
    }
    else {
        cout << "Error al actualizar marca" << endl;
    }
}

void eliminar_marca() {
    int id;
    string marca, consulta;

    leer_marcas();

    cout << "\nId de la marca: ";
    cin >> id;

    consulta = "DELETE FROM marcas WHERE marcas.id = " + to_string(id);
    const char* i = consulta.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Marca eliminada con éxito" << endl;
        leer_marcas();
    }
    else {
        cout << "Error al eliminar marca" << endl;
    }
}

void crud_productos() {
    int opcion;
    bool bandera = true;

    while (bandera) {

        cout << "\nProductos" << endl;
        cout << "    1.Crear" << endl;
        cout << "    2.Leer" << endl;
        cout << "    3.Actualizar" << endl;
        cout << "    4.Eliminar" << endl;
        cout << "    5.Regresar\n" << endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cin.ignore();
            crear_producto();
            break;
        case 2:
            leer_productos();
            break;
        case 3:
            actualizar_producto();
            break;
        case 4:
            eliminar_producto();
            break;
        case 5:
            bandera = false;
            break;
        default:
            cout << "\nLa opción ingresada es incorrecta\n" << endl;
            break;
        }

        cout << "\n---------------------------------------" << endl;

    }
}

void crear_producto() {
    int existencia, id_marca;
    double precio_costo, precio_venta;
    string producto, descripcion, consulta;

    cout << "\nNombre del producto: ";
    getline(cin, producto);

    cout << "\nDescripción: ";
    getline(cin, descripcion);

    cout << "\nPrecio de costo: ";
    cin >> precio_costo;

    cout << "\nPrecio de venta: ";
    cin >> precio_venta;

    cout << "\nExistencia: ";
    cin >> existencia;

    leer_marcas();
    cout << "\nId de la marca: ";
    cin >> id_marca;

    consulta = "INSERT INTO productos(producto, descripcion, precio_costo, precio_venta, existencia, fecha_ingreso, id_marca) VALUES('" + producto + "', '" + descripcion + "', '" + to_string(precio_costo) + "', '" + to_string(precio_venta) + "', '" + to_string(existencia) + "', CURRENT_TIMESTAMP(), '" + to_string(id_marca) +"');";
    const char* i = consulta.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Producto ingresado con éxito" << endl;
        leer_productos();
    }
    else {
        cout << "Error al ingresar producto" << endl;
    }
}

void leer_productos() {
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    string consulta;
    consulta = "SELECT * FROM productos LEFT JOIN marcas ON productos.id_marca = marcas.id;";
    const char* i = consulta.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        resultado = mysql_store_result(conectar);
        cout << "\n-------------------------------------------------------------------------------------------------------------" << endl;
        cout << "id\t| producto\t| precio_costo\t| precio_venta\t| existencia\t| fecha_ingreso\t| marca" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------" << endl;
        while (fila = mysql_fetch_row(resultado)) {
            cout << fila[0] << "\t| " << fila[1] << "\t| " << fila[2] << "\t| " << fila[4] << "\t| " << fila[5] << "\t| " << fila[6] << "\t| " << fila[7] << "\t| " << fila[10] <<endl;
            cout << "-------------------------------------------------------------------------------------------------------------" << endl;
        }
    }
    else {
        cout << "Error al leer productos" << endl;
    }
}

void actualizar_producto() {
    int id_producto, existencia, id_marca;
    double precio_costo, precio_venta;
    string producto, descripcion, consulta;

    leer_productos();

    cout << "\nId del producto: ";
    cin >> id_producto;
    cin.ignore();

    cout << "\nNombre del producto: ";
    getline(cin, producto);

    cout << "\nDescripción: ";
    getline(cin, descripcion);

    cout << "\nPrecio de costo: ";
    cin >> precio_costo;

    cout << "\nPrecio de venta: ";
    cin >> precio_venta;

    cout << "\nExistencia: ";
    cin >> existencia;

    leer_marcas();
    cout << "\nId de la marca: ";
    cin >> id_marca;

    consulta = "UPDATE productos SET producto = '" + producto + "', descripcion = '" + descripcion +"', precio_costo = '" + to_string(precio_costo) + "', precio_venta = '" + to_string(precio_venta) + "', existencia = '" + to_string(existencia) + "', fecha_ingreso = CURRENT_TIMESTAMP(), id_marca = " + to_string(id_marca) + " WHERE id = " + to_string(id_producto);
    const char* i = consulta.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Producto actualizado con éxito" << endl;
        leer_productos();
    }
    else {
        cout << "Error al actualizar producto" << endl;
    }
}

void eliminar_producto() {
    int id;
    string producto, consulta;

    leer_productos();

    cout << "\nId del producto: ";
    cin >> id;

    consulta = "DELETE FROM productos WHERE productos.id = " + to_string(id);
    const char* i = consulta.c_str();
    q_estado = mysql_query(conectar, i);
    if (!q_estado) {
        cout << "Producto eliminado " << endl;
        leer_productos();
    }
    else {
        cout << "Error al eliminar producto" << endl;
    }
}
