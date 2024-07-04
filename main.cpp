/************************************************
Un sistema para la administración y gestión de inventario de cursos,
así como la inscripción de estudiantes, para mejorar la venta y gestión de
los cursos en la plataforma UDEMY. El sistema debe permitir a los administradores
realizar operaciones CRUD sobre los cursos y estudiantes, gestionar inscripciones
y garantizar que los estudiantes no se inscriban en más de un curso al mismo
tiempo. También debe permitir a los clientes ver cursos disponibles, agregarlos a
un carrito de compras y proceder con el pago para completar la inscripción.

Angel S. Cruz Rodriguez
Mauricio Gonzalez Sanchez
Karina P. Ibarra Morales

Global University
Programacion Orientada a Objetos
Armando Soto Valdez

04-Julio-2024
************************************************/

// !Librerias
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// !Funciones generales
// Verficar entrada de dato
int verificacion(int minimo, int maximo)
{
    int dato, intentos = 1;
    while (intentos <= 3)
    {
        cout << "Por favor, seleccione una opcion: ";
        if (cin >> dato)
        {
            if (dato >= minimo && dato <= maximo)
            {
                return dato;
            }
            else
            {
                cout << "Opcion no valida. Intento " << intentos << " de 3." << endl;
            }
        }
        else
        {
            cout << "Entrada invalida. Intento " << intentos << " de 3." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        intentos++;
    }
    cout << "Y tu tiempo se acabo...." << endl;
    cout << "Saliendo del programa..." << endl;
    return -1;
}
// Unir elementos de un vector en una cadena
string join(const vector<string> &vec, const string &delimiter)
{
    string result;
    for (const auto &str : vec)
    {
        result += str + delimiter;
    }
    result.pop_back();
    return result;
}
// Generar identificador
string generarIdentificador(const string &dato1, const string &dato2) {
    if (dato1.size() < 3 || dato2.size() < 3) {
        throw invalid_argument("Las cadenas de entrada deben tener al menos 3 caracteres.");
    }
    srand(static_cast<unsigned int>(time(nullptr)));
    string id = dato1.substr(0, 3) + "-" + dato2.substr(0, 3) + "-";
    id += to_string(rand() % 1000); // Genera un numero aleatorio de 3 digitos
    return id;
}
// Verificar la existencia del usuario
bool verificarUsuario(const string &id)
{
    fstream file("..\\listaAlumnos.txt", ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string segment;
            vector<string> userData;

            while (getline(ss, segment, '/'))
            {
                userData.push_back(segment);
            }

            if (userData.size() >= 4 && userData[0] == "'" + id + "'")
            {
                cout << "Usuario encontrado: " << userData[1] << endl; // Imprimir nombre del usuario
                cout << "Carrera: " << userData[3] << endl; // Imprimir carrera del usuario
                cout << "Correo: " << userData[2] << endl; // Imprimir correo del usuario
                cout << "---------------------------" << endl;
                file.close();
                return true;
            }
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo de alumnos." << endl;
    }
    return false;
}
// Verificar la existencia del curso
bool verificarCurso(const string &id)
{
    fstream file("..\\listaCursos.txt", ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line.find(id) != string::npos)
            {
                file.close();
                return true;
            }
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
    return false; // Indica que no se encontró el curso
}
// Obtener costo del curso
int costoCurso(const string &id)
{
    fstream file("..\\listaCursos.txt", ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line.find(id) != string::npos)
            {
                stringstream ss(line);
                string segment;
                vector<string> courseData;
                while (getline(ss, segment, '/'))
                {
                    courseData.push_back(segment);
                }
                if (courseData.size() >= 6)
                {
                    file.close();
                    return stoi(courseData[5].substr(1)); // Eliminar '$' y convertir a entero
                }
            }
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
    return -1; // Indica que no se encontró el curso
}
// Obtener capacidad maxima del curso
int capacidadCurso(const string &id)
{
    fstream file("..\\listaCursos.txt", ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line.find(id) != string::npos)
            {
                stringstream ss(line);
                string segment;
                vector<string> courseData;
                while (getline(ss, segment, '/'))
                {
                    courseData.push_back(segment);
                }
                if (courseData.size() >= 6)
                {
                    file.close();
                    return stoi(courseData[4].substr(1)); // Eliminar '#' y convertir a entero
                }
            }
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
    return -1; // Indica que no se encontró el curso
}
// Obtener numero de inscritos en el curso
int inscritosCurso(const string &id)
{
    fstream file("..\\listaCursos.txt", ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line.find(id) != string::npos)
            {
                stringstream ss(line);
                string segment;
                vector<string> courseData;
                while (getline(ss, segment, '/'))
                {
                    courseData.push_back(segment);
                }
                if (courseData.size() >= 6)
                {
                    file.close();
                    return stoi(courseData[6]); // Convertir a entero
                }
            }
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
    return -1; // Indica que no se encontró el curso
}
// Obtener la cantidad de cursos incritos por un alumno
int verificarCantidadCursos(const string &alumnoId)
{
    fstream file("..\\listaAlumnos.txt", ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line.find(alumnoId) != string::npos)
            {
                stringstream ss(line);
                string segment;
                vector<string> alumnoData;
                while (getline(ss, segment, '/'))
                {
                    alumnoData.push_back(segment);
                }
                if (alumnoData.size() >= 5)
                {
                    file.close();
                    return stoi(alumnoData[4]); // Obtener y devolver la cantidad de cursos
                }
            }
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
    return -1; // Indica que no se encontró el alumno
}
// Función para verificar si hay cupo disponible en un curso
bool verificarCupoCurso(const string &idCurso)
{
    int capacidad = capacidadCurso(idCurso);
    int inscritos = inscritosCurso(idCurso);

    if (capacidad == -1 || inscritos == -1)
    {
        cout << "Error al verificar la capacidad o el numero de inscritos del curso." << endl;
        return false;
    }

    return inscritos < capacidad;
}
// Actualizar el número de cursos por alumno
void actualizarCursosInscritosAlumno(const string &usuarioId, int nuevosCursosInscritos)
{
    ifstream file("..\\listaAlumnos.txt");
    ofstream outFile("..\\listaAlumnos.txt", ios::in | ios::out);

    if (!file.is_open() || !outFile.is_open())
    {
        cout << "Error al abrir el archivo de alumnos." << endl;
        return;
    }

    string line;
    outFile.seekp(0, ios::beg);

    while (getline(file, line))
    {
        if (line.find(usuarioId) != string::npos)
        {
            stringstream ss(line);
            string segment;
            vector<string> alumnoData;

            while (getline(ss, segment, '/'))
            {
                alumnoData.push_back(segment);
            }

            if (alumnoData.size() >= 5)
            {
                alumnoData[4] = to_string(nuevosCursosInscritos);
                outFile << join(alumnoData, "/") << endl;
            }
            else
            {
                outFile << line << endl;
            }
        }
        else
        {
            outFile << line << endl;
        }
    }

    file.close();
    outFile.close();
}
// Actualizar el número de inscritos en un curso
void actualizarInscritosCurso(const string &id)
{
    fstream inFile("..\\listaCursos.txt", ios::in);
    ofstream outFile("..\\listaCursos_temp.txt");

    if (!inFile.is_open() || !outFile.is_open())
    {
        cout << "Error al abrir el archivo de cursos." << endl;
        return;
    }

    bool cursoEncontrado = false;
    string line;
    while (getline(inFile, line))
    {
        if (line.find(id) != string::npos)
        {
            cursoEncontrado = true;
            stringstream ss(line);
            string segment;
            vector<string> courseData;
            while (getline(ss, segment, '/'))
            {
                courseData.push_back(segment);
            }
            if (courseData.size() >= 6)
            {
                int nuevosInscritos = stoi(courseData[6]) + 1;
                courseData[6] = to_string(nuevosInscritos);
                line = "";
                for (const auto &data : courseData)
                {
                    line += data + '/';
                }
                line.pop_back();
            }
        }
        outFile << line << endl;
    }
    inFile.close();
    outFile.close();

    if (!cursoEncontrado)
    {
        cout << "No se pudo procesar: " << id << endl;
    }
    else
    {
        remove("..\\listaCursos.txt");
        rename("..\\listaCursos_temp.txt", "..\\listaCursos.txt");
    }
}
// Función para obtener un entero del usuario
int obtenerEntero(const string &mensaje)
{
    int numero;
    string entrada;
    while (true)
    {
        cout << mensaje;
        getline(cin, entrada);
        stringstream ss(entrada);
        if (ss >> numero && ss.eof())
        {
            return numero;
        }
        cout << "Por favor ingresa un numero entero valido." << endl;
    }
}

// !Estructuras
struct CarritoCompras
{
    vector<string> cursoIDs;
    int costoTotal = 0;
    string usuarioID;
};

// !Funciones para Administrador
// ?Gestion de Cursos
// Agregar Curso
void agregarCurso(){
    string id;
    string nombre, etiqueta, profesor;
    string inscritos;
    int capacidad, costo;

    // Pedir datos del curso
    cout << "Ingresa el nombre del curso: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Ingresa la etiqueta del curso: ";
    getline(cin, etiqueta);
    cout << "Ingresa el profesor del curso: ";
    getline(cin, profesor);
    capacidad = obtenerEntero("Ingresa la capacidad maxima del curso: ");
    costo = obtenerEntero("Ingresa el costo del curso: $");

    // Generar identificador
    try
    {
        id = generarIdentificador(etiqueta, profesor);
    }
    catch (const invalid_argument &e)
    {
        cout << e.what() << " Regresando al menu principal." << endl;
        return; // Salir de la función sin agregar el curso
    }

    // Escribir los datos en el archivo
    fstream file("..\\listaCursos.txt", ios::in | ios::out | ios::app);
    if (file.is_open())
    {
        file <<"'" << id << "'/" << nombre << "/" << etiqueta << "/" << profesor << "/#" << capacidad<< "/$" << costo<< "/0"<< endl;
        file.close();
        cout << "Curso '" << nombre << "' fue agregado correctamento con el Id: " << id << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
// Modificar Curso
void modificarCurso() {
    string id, nombre, etiqueta, profesor, capacidad, costo;
    bool cursoEncontrado = false;

    // Pedir el ID del curso a modificar
    cout << "Ingrese el ID del curso que desea modificar: ";
    cin >> id;

    // Abrir el archivo de cursos para lectura y escritura
    fstream inFile("..\\listaCursos.txt", ios::in);
    ofstream outFile("..\\listaCursos_temp.txt");

    if (inFile.is_open() && outFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            if (line.find(id) != string::npos) {
                cursoEncontrado = true;
                stringstream ss(line);
                string segment;
                vector<string> courseData;
                while (getline(ss, segment, '/')) {
                    courseData.push_back(segment);
                }

                if (courseData.size() >= 6) {
                    // Mostrar datos actuales del curso
                    cout << "Datos actuales del curso:" << endl;
                    cout << "Nombre: " << courseData[1] << endl;
                    cout << "Etiqueta: " << courseData[2] << endl;
                    cout << "Profesor: " << courseData[3] << endl;
                    cout << "Capacidad: " << courseData[4].substr(1) << endl; // Eliminar '#'
                    cout << "Costo: " << courseData[5].substr(1) << endl; // Eliminar '$'

                    // Pedir nuevos datos del curso
                    cout << "Ingrese el nuevo nombre del curso (o presione Enter para mantener el actual): ";
                    cin.ignore();
                    getline(cin, nombre);
                    if (nombre.empty()) nombre = courseData[1];

                    cout << "Ingrese la nueva etiqueta del curso (o presione Enter para mantener la actual): ";
                    getline(cin, etiqueta);
                    if (etiqueta.empty()) etiqueta = courseData[2];

                    cout << "Ingrese el nuevo profesor del curso (o presione Enter para mantener el actual): ";
                    getline(cin, profesor);
                    if (profesor.empty()) profesor = courseData[3];

                    cout << "Ingrese la nueva capacidad maxima del curso (o presione Enter para mantener la actual): ";
                    getline(cin, capacidad);
                    if (capacidad.empty()) capacidad = courseData[4].substr(1);

                    cout << "Ingrese el nuevo costo del curso (o presione Enter para mantener el actual): ";
                    getline(cin, costo);
                    if (costo.empty()) costo = courseData[5].substr(1);

                    // Actualizar los datos del curso
                    line = "'" + id + "'/" + nombre + "/" + etiqueta + "/" + profesor + "/#" + capacidad + "/$" + costo + "/" + courseData[6];
                }
            }
            outFile << line << endl;
        }

        inFile.close();
        outFile.close();

        if (cursoEncontrado) {
            // Reemplazar el archivo original con el archivo temporal
            remove("..\\listaCursos.txt");
            rename("..\\listaCursos_temp.txt", "..\\listaCursos.txt");
            cout << "Curso modificado exitosamente." << endl;
        } else {
            cout << "Curso no encontrado: " << id << endl;
        }
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
//Eliminar curso
void eliminarCurso() {
    string id;
    bool cursoEncontrado = false;

    // Pedir el ID del curso a eliminar
    cout << "Ingrese el ID del curso que desea eliminar: ";
    cin >> id;

    // Abrir el archivo de cursos para lectura y escritura
    fstream inFile("..\\listaCursos.txt", ios::in);
    ofstream outFile("..\\listaCursos_temp.txt");

    if (inFile.is_open() && outFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            if (line.find(id) == string::npos) {
                // Escribir en el archivo temporal solo las líneas que no corresponden al ID del curso a eliminar
                outFile << line << endl;
            } else {
                cursoEncontrado = true;
            }
        }

        inFile.close();
        outFile.close();

        if (cursoEncontrado) {
            // Reemplazar el archivo original con el archivo temporal
            remove("..\\listaCursos.txt");
            rename("..\\listaCursos_temp.txt", "..\\listaCursos.txt");
            cout << "Curso eliminado exitosamente." << endl;
        } else {
            cout << "Curso no encontrado: " << id << endl;
        }
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
// Listar Cursos
void listarCursos(){
    fstream file("..\\listaCursos.txt", ios::in | ios::out | ios::app);
    if (file.is_open())
    {
        cout << "Cursos Registrados" << endl;
        file.seekg(0, ios::beg); // Mover el cursor al principio para leer desde el inicio
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
// ?Gestion de Alumnos
// Agregar Alumno
void agregarAlumno(){
    string id;
    string nombre, correo, carrera;

    // Pedir datos del alumno
    cout << "Ingresa el nombre del alumno: ";
    cin >> nombre;
    cout << "Ingresa el correo del alumno: ";
    cin >> correo;
    cout << "Ingresa la carrera del alumno: ";
    cin >> carrera;
    // Generar identificador
    try
    {
        id = generarIdentificador(nombre, carrera);
    }
    catch (const invalid_argument &e)
    {
        cout << e.what() << " Regresando al menu principal." << endl;
        return; // Salir de la función sin agregar el curso
    }

    // Escribir los datos en el archivo
    fstream file("..\\listaAlumnos.txt", ios::in | ios::out | ios::app);
    if (file.is_open())
    {
        file <<"'" << id << "'/" << nombre << "/" << correo << "/" << carrera << "/0"<< endl;
        file.close();
        cout << "Alumno " << nombre << " fue agregado correctamento con el Id: " << id << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
// Listar Alumnos
void listarAlumnos()
{
    fstream file("..\\listaAlumnos.txt", ios::in);

    if (file.is_open())
    {
        // Verificar si el archivo está vacío
        file.seekg(0, ios::end);
        if (file.tellg() == 0)
        {
            cout << "El archivo está vacío." << endl;
        }
        else
        {
            // Mover el cursor al principio para leer desde el inicio
            file.seekg(0, ios::beg);
            cout << "Lista de alumnos registrados" << endl;
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
// Modificar alumno
void modificarAlumno()
{
    string id, nombre, correo, carrera;
    bool alumnoEncontrado = false;

    // Pedir el ID del alumno a modificar
    cout << "Ingrese el ID del alumno que desea modificar: ";
    cin >> id;

    // Abrir el archivo de alumnos para lectura
    fstream inFile("..\\listaAlumnos.txt", ios::in);
    ofstream outFile("..\\listaAlumnos_temp.txt");

    if (inFile.is_open() && outFile.is_open())
    {
        // Verificar si el archivo está vacío
        inFile.seekg(0, ios::end);
        if (inFile.tellg() == 0)
        {
            cout << "El archivo está vacío." << endl;
        }
        else
        {
            // Mover el cursor al principio para leer desde el inicio
            inFile.seekg(0, ios::beg);
            string line;
            while (getline(inFile, line))
            {
                if (line.find(id) != string::npos)
                {
                    alumnoEncontrado = true;
                    stringstream ss(line);
                    string segment;
                    vector<string> alumnoData;
                    while (getline(ss, segment, '/'))
                    {
                        alumnoData.push_back(segment);
                    }

                    if (alumnoData.size() >= 5)
                    {
                        // Mostrar datos actuales del alumno
                        cout << "Datos actuales del alumno:" << endl;
                        cout << "Nombre: " << alumnoData[1] << endl;
                        cout << "Correo: " << alumnoData[2] << endl;
                        cout << "Carrera: " << alumnoData[3] << endl;

                        // Pedir nuevos datos del alumno
                        cout << "Ingrese el nuevo nombre del alumno (o presione Enter para mantener el actual): ";
                        cin.ignore();
                        getline(cin, nombre);
                        if (nombre.empty())
                            nombre = alumnoData[1];

                        cout << "Ingrese el nuevo correo del alumno (o presione Enter para mantener el actual): ";
                        getline(cin, correo);
                        if (correo.empty())
                            correo = alumnoData[2];

                        cout << "Ingrese la nueva carrera del alumno (o presione Enter para mantener la actual): ";
                        getline(cin, carrera);
                        if (carrera.empty())
                            carrera = alumnoData[3];

                        // Actualizar los datos del alumno
                        line = "'" + id + "'/" + nombre + "/" + correo + "/" + carrera + "/" + alumnoData[4];
                    }
                }
                outFile << line << endl;
            }
        }

        inFile.close();
        outFile.close();

        if (alumnoEncontrado)
        {
            // Reemplazar el archivo original con el archivo temporal
            remove("..\\listaAlumnos.txt");
            rename("..\\listaAlumnos_temp.txt", "..\\listaAlumnos.txt");
            cout << "Alumno modificado exitosamente." << endl;
        }
        else
        {
            cout << "Alumno no encontrado: " << id << endl;
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
// Eliminar alumno
void eliminarAlumno()
{
    string id;
    bool alumnoEncontrado = false;

    // Abrir el archivo de alumnos para lectura
    fstream inFile("..\\listaAlumnos.txt", ios::in);
    ofstream outFile("..\\listaAlumnos_temp.txt");

    if (inFile.is_open() && outFile.is_open())
    {
        // Verificar si el archivo está vacío
        inFile.seekg(0, ios::end);
        if (inFile.tellg() == 0)
        {
            cout << "El archivo está vacío." << endl;
        }
        else
        {
            // Pedir el ID del alumno a eliminar
            cout << "Ingrese el ID del alumno que desea eliminar: ";
            cin >> id;
            // Mover el cursor al principio para leer desde el inicio
            inFile.seekg(0, ios::beg);
            string line;
            while (getline(inFile, line))
            {
                if (line.find(id) == string::npos)
                {
                    // Escribir en el archivo temporal solo las líneas que no corresponden al ID del alumno a eliminar
                    outFile << line << endl;
                }
                else
                {
                    alumnoEncontrado = true;
                }
            }
        }

        inFile.close();
        outFile.close();

        if (alumnoEncontrado)
        {
            // Reemplazar el archivo original con el archivo temporal
            remove("..\\listaAlumnos.txt");
            rename("..\\listaAlumnos_temp.txt", "..\\listaAlumnos.txt");
            cout << "Alumno eliminado exitosamente." << endl;
        }
        else
        {
            cout << "Alumno no encontrado: " << id << endl;
            // Eliminar el archivo temporal si no se encontró el alumno
            remove("..\\listaAlumnos_temp.txt");
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
// ?Gestion de Inscripciones
// Listar Inscripciones
void listarInscripciones(){
    fstream file("..\\listaInscripciones.txt", ios::in);

    if (file.is_open())
    {
        // Mover el cursor al final del archivo para verificar si está vacío
        file.seekg(0, ios::end);
        if (file.tellg() == 0)
        {
            cout << "El archivo esta vacio." << endl;
        }
        else
        {
            // Mover el cursor al principio para leer desde el inicio
            file.seekg(0, ios::beg);
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
// Eliminar Inscripcion
void eliminarInscripciones()
{
    string id;
    bool inscripcionEncontrado = false;

    // Abrir el archivo de inscripciones para lectura y escritura
    fstream inFile("..\\listaInscripciones.txt", ios::in);
    ofstream outFile("..\\listaInscripciones_temp.txt");

    if (inFile.is_open() && outFile.is_open())
    {
        // Verificar si el archivo está vacío
        inFile.seekg(0, ios::end);
        if (inFile.tellg() == 0)
        {
            cout << "El archivo está vacío." << endl;
        }
        else
        {
            // Pedir el ID de la inscripción a eliminar
            cout << "Ingrese el ID de la inscripción que desea eliminar: ";
            cin >> id;
            // Mover el cursor al principio para leer desde el inicio
            inFile.seekg(0, ios::beg);
            string line;
            while (getline(inFile, line))
            {
                if (line.find(id) == string::npos)
                {
                    // Escribir en el archivo temporal solo las líneas que no corresponden al ID de la inscripción a eliminar
                    outFile << line << endl;
                }
                else
                {
                    inscripcionEncontrado = true;
                }
            }
        }

        inFile.close();
        outFile.close();

        if (inscripcionEncontrado)
        {
            // Reemplazar el archivo original con el archivo temporal
            remove("..\\listaInscripciones.txt");
            rename("..\\listaInscripciones_temp.txt", "..\\listaInscripciones.txt");
            cout << "Inscripción eliminada exitosamente." << endl;
        }
        else
        {
            cout << "Inscripción no encontrada: " << id << endl;
            // Eliminar el archivo temporal si no se encontró la inscripción
            remove("..\\listaInscripciones_temp.txt");
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

// !Funciones para Cliente
// ?Ver cursos disponibles
void verCursos()
{
    fstream file("..\\listaCursos.txt", ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string segment;
            vector<string> courseData;

            while (getline(ss, segment, '/'))
            {
                courseData.push_back(segment);
            }

            if (courseData.size() >= 6)
            { // Asegurarse de que hay suficientes elementos
                cout << "---------------------------" << endl;
                cout << "ID: " << courseData[0] << endl;
                cout << "Nombre del curso: " << courseData[1] << endl;
                cout << "Etiqueta: " << courseData[2] << endl;
                cout << "Profesor: " << courseData[3] << endl;
                cout << "Numero maximo de alumnos inscritos: " << courseData[4] << endl;
                cout << "Costo: " << courseData[5] << endl;
                cout << "Numero de inscritos: " << (courseData.size() > 6 ? courseData[6] : "0") << endl;
                cout << "---------------------------" << endl;
                cout << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
// ?Gestion de Carrito
// Agregar curso al carrito
void agregarCarrito(CarritoCompras &carrito, const string &id)
{
    if (carrito.cursoIDs.size() >= 2)
    {
        cout << "No puede agregar mas de 2 cursos al carrito." << endl;
        return;
    }
    if (!verificarCupoCurso(id))
    {
        cout << "No hay cupo disponible en el curso: " << id << endl;
        return;
    }
    if (verificarCurso(id))
    {
        int costo = costoCurso(id);
        if (costo >= 0)
        {
            carrito.cursoIDs.push_back(id);
            carrito.costoTotal += costo;
            cout << "Curso agregado: " << id << endl;
        }
        else
        {
            cout << "Error al obtener el costo del curso: " << id << endl;
        }
    }
    else
    {
        cout << "Curso no encontrado: " << id << endl;
    }
}
// Eliminar curso del carrito
void eliminarCarrito(CarritoCompras &carrito, const string &id)
{
    auto it = find(carrito.cursoIDs.begin(), carrito.cursoIDs.end(), id);
    if (it != carrito.cursoIDs.end())
    {
        int costo = costoCurso(id);
        carrito.cursoIDs.erase(it);
        carrito.costoTotal -= costo;
        cout << "Curso eliminado: " << id << endl;
    }
    else
    {
        cout << "Curso no encontrado en el carrito: " << id << endl;
    }
}
// Mostrar carrito
void mostrarCarrito(const CarritoCompras &carrito, const string &usuarioId)
{
    cout << "Carrito de " << usuarioId << ":" << endl;
    for (const auto &id : carrito.cursoIDs)
    {
        int costoAcutal = costoCurso(id);
        int max = capacidadCurso(id);
        cout << "  * " << id << " -> $" << costoAcutal << " -> #" << max << endl;
    }
    cout << "Costo total del carrito: $" << carrito.costoTotal << endl;
}
// Funcion para procesar la compra
void procesarCompra(CarritoCompras &carrito, const string &usuarioId)
{
    int cursosIncritos = verificarCantidadCursos(usuarioId);
    srand(static_cast<unsigned int>(time(nullptr)));
    if (cursosIncritos == 2)
    {
        cout << "No puede inscribirse en más de 2 cursos a la vez." << endl;
        return;
    }
    else if (cursosIncritos == -1)
    {
        cout << "Error al verificar la cantidad de cursos inscritos." << endl;
        return;
    }

    ofstream inscripcionesFile("..\\listaInscripciones.txt", ios::out | ios::app);
    if (!inscripcionesFile.is_open())
    {
        cout << "Error al abrir el archivo de inscripciones." << endl;
        return;
    }

    for (const string &idCurso : carrito.cursoIDs)
    {
        int idInscripcion = rand() % 1000;

        // Obtener fecha actual para la inscripción
        time_t now = time(0);
        tm *localTime = localtime(&now);
        char fecha[80];
        strftime(fecha, 80, "%Y-%m-%d %H:%M:%S", localTime);

        // Registrar la inscripción en el archivo de inscripciones
        inscripcionesFile << idInscripcion << "/" << usuarioId << "/" << idCurso << "/" << fecha << endl;

        // Actualizar el archivo de cursos con el nuevo número de inscritos
        actualizarInscritosCurso(idCurso);

        // Actualizar el archivo de alumnos con el nuevo número de cursos inscritos
        cursosIncritos++;
        actualizarCursosInscritosAlumno(usuarioId, cursosIncritos);
    }

    inscripcionesFile.close();

    cout << "Compra procesada con exito para los cursos en el carrito." << endl;

    // Limpiar el carrito después de procesar la compra
    carrito.cursoIDs.clear();
    carrito.costoTotal = 0;
}
// ?Menu Carrito de compras
int menuCarrito(){
    system("cls");
    cout << "Menu de Compras" << endl;
    cout << "-----------------------" << endl;
    cout << "1 - Agregar curso al carrito" << endl;
    cout << "2 - Eliminar curso del carrito" << endl;
    cout << "3 - Mostrar carrito" << endl;
    cout << "4 - Procesar compra" << endl;
    cout << "5 - Salir" << endl;
    cout << "-----------------------" << endl << endl;
    int menuCarrito = verificacion(1, 5);

    return menuCarrito;
}
// ?Manejar Carrito
void manejarCarrito(const string &usuarioId)
{
    int opcionCarrito = 0;
    CarritoCompras carrito;
    string cursoId;
    do
    {
        opcionCarrito = menuCarrito();
        switch (opcionCarrito)
        {
            case 1:
                system("cls");
                cout << "Ingrese el ID del curso que desea agregar al carrito: ";
                cin >> cursoId;
                agregarCarrito(carrito, cursoId); // Pasar carrito y usuarioId al agregar el curso
                system("pause");
                break;
            case 2:
                system("cls");
                cout << "Ingrese el ID del curso que desea eliminar del carrito: ";
                cin >> cursoId;
                eliminarCarrito(carrito, cursoId); // Pasar carrito y usuarioId al eliminar el curso
                system("pause");
                break;
            case 3:
                system("cls");
                cout << "Mostrar carrito" << endl;
                mostrarCarrito(carrito, usuarioId); // Pasar usuarioId al mostrar el carrito
                system("pause");
                break;
            case 4:
                system("cls");
                cout << "Procesar compra" << endl;
                procesarCompra(carrito, usuarioId); // Pasar usuarioId al procesar la compra
                system("pause");
                break;
        }
    } while (opcionCarrito != 5);
}
// ?Acceder a tienda
bool accesoTienda(){
    CarritoCompras carrito;

    string alumnoId;
    bool permitirInteraccion = false;

    cout << "Ingrese su ID de alumno para continuar: ";
    cin >> alumnoId;

    if (verificarUsuario(alumnoId))
    {
        permitirInteraccion = true;
        system("pause");
        system("cls");
        cout << "Usuario verificado. Puede interactuar con el carrito." << endl;
        manejarCarrito(alumnoId);
    }
    else
    {
        cout << "Usuario no encontrado. No puede interactuar con el carrito." << endl;
    }

    return permitirInteraccion;
}

// !Interaccion de menus y acciones
// Seleccion Usuario
int menuPrincipal() {
    system("cls");
    cout << "Lista de usuarios disponibles" << endl;
    cout << "-----------------------" << endl;
    cout << "1 - Administrador" << endl;
    cout << "2 - Cliente" << endl;
    cout << "3 - Salir" << endl;
    cout << "-----------------------" << endl;
    int opcionUsuario = verificacion(1, 3);

    return opcionUsuario;
}
// !Menu Aministrador
// Menu de administrador
int menuAdministrador() {
    system("cls");
    cout << "Menu de administrador" << endl;
    cout << "-----------------------" << endl;
    cout << "1 - Cursos" << endl;
    cout << "2 - Alumnos" << endl;
    cout << "3 - Inscripciones" << endl;
    cout << "4 - Atras" << endl;
    cout << "-----------------------" << endl << endl;
    int opcionAdmin = verificacion(1, 4);

    return opcionAdmin;
}
// Menu de gestion de cursos
int menuCursos() {
    system("cls");
    cout << "Gestion de Cursos" << endl;
    cout << "-----------------------" << endl;
    cout << "1 - Agregar curso" << endl;
    cout << "2 - Modificar curso" << endl;
    cout << "3 - Eliminar Curso" << endl;
    cout << "4 - Listar cursos" << endl;
    cout << "5 - Atras" << endl;
    cout << "-----------------------" << endl << endl;
    int opcionCursos = verificacion(1, 5);

    return opcionCursos;
}
// Menu de gestion de alumnos
int menuAlumnos() {
    system("cls");
    cout << "Gestion de Alumnos" << endl;
    cout << "-----------------------" << endl;
    cout << "1 - Agregar alumno" << endl;
    cout << "2 - Modificar alumno" << endl;
    cout << "3 - Eliminar alumno" << endl;
    cout << "4 - Listar alumnos" << endl;
    cout << "5 - Atras" << endl;
    cout << "-----------------------" << endl << endl;
    int opcionAlumnos = verificacion(1, 5);

    return opcionAlumnos;
}
// Menu de gestion de inscripciones
int menuInscripciones() {
    system("cls");
    cout << "Gestion de Inscripciones" << endl;
    cout << "-----------------------" << endl;
    cout << "1 - Listar inscripciones" << endl;
    cout << "2 - Eliminar inscripcion" << endl;
    cout << "3 - Atras" << endl;
    cout << "-----------------------" << endl << endl;
    int opcionInscripciones = verificacion(1, 3);

    return opcionInscripciones;
}
// !Menu Cliente
// Menu de cliente
int menuCliente() {
    system("cls");
    cout << "Menu de usuario" << endl;
    cout << "-----------------------" << endl;
    cout << "1 - Ver cursos disponibles" << endl;
    cout << "2 - Acceder a la tienda" << endl;
    cout << "3 - Salir" << endl;
    cout << "-----------------------" << endl << endl;
    int menuCliente = verificacion(1, 3);

    return menuCliente;
}
// !Acciones Administrador
// Acciones sobre cursos
void manejarCursos() {
    int opcionCursos = menuCursos();
    switch (opcionCursos) {
        case 1:
            system("cls");
            cout << "Agregar curso" << endl;
            agregarCurso();
            system("pause");
            break;
        case 2:
            system("cls");
            cout << "Modificar curso" << endl;
            modificarCurso();
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "Eliminar curso" << endl;
            eliminarCurso();
            system("pause");
            break;
        case 4:
            system("cls");
            listarCursos();
            system("pause");
            break;
    }
}
// Acciones sobre alumnos
void manejarAlumnos() {
    int opcionAlumnos = menuAlumnos();
    switch (opcionAlumnos) {
        case 1:
            system("cls");
            cout << "Agregar alumno" << endl;
            agregarAlumno();
            system("pause");
            break;
        case 2:
            system("cls");
            cout << "Modificar alumno" << endl;
            modificarAlumno();
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "Eliminar alumno" << endl;
            eliminarAlumno();
            system("pause");
            break;
        case 4:
            system("cls");
            listarAlumnos();
            system("pause");
            break;
    }
}
// Acciones sobre Inscripciones
void manejarInscripciones() {
    int opcionInscripciones = menuInscripciones();
    switch (opcionInscripciones) {
        case 1:
            system("cls");
            cout << "Lista inscripciones" << endl << endl;
            listarInscripciones();
            system("pause");
            break;
        case 2:
            system("cls");
            cout << "Eliminar inscripcion" << endl;
            eliminarInscripciones();
            system("pause");
            break;
    }
}
// !Acciones disponibles para Administrador
void manejarAdministrador() {
    int opcionAdministrador = 0;
    do {
        opcionAdministrador = menuAdministrador();
        switch (opcionAdministrador) {
            case 1:
                system("cls");
                manejarCursos();
                system("pause");
                break;
            case 2:
                system("cls");
                manejarAlumnos();
                system("pause");
                break;
            case 3:
                system("cls");
                manejarInscripciones();
                system("pause");
                break;
        }
    } while (opcionAdministrador != 4);
}
// !Acciones disponibles para cliente
void manejarCliente() {
    int opcionCliente = 0;
    do {
        opcionCliente = menuCliente();
        switch (opcionCliente) {
            case 1:
                system("cls");
                cout << "Cursos disponibles en el sistema" << endl << endl;
                verCursos();
                system("pause");
                break;
            case 2:
                system("cls");
                cout << "Bienvenido a la tienda de cursos" << endl;
                accesoTienda();
                system("pause");
                break;
        }
    } while (opcionCliente != 3);
}

// !Funcion principal
int main() {
    //cout << "\033[42m\033[97m";

    cout << "*****************************************" << endl;
    cout << "*          Bienvenido a UDEMY           *" << endl;
    cout << "*  Sistema de Gestion de Cursos Online  *" << endl;
    cout << "*****************************************" << endl << endl;
    cout << "*  Por favor, presione cualquier tecla para continuar.    *" << endl;

    system("pause");

    while (true) {
        int opcionUsuario = menuPrincipal();

        if (opcionUsuario == -1)
        {
            cout << "Error en la seleccion. Saliendo del programa..." << endl;
            break;
        }

        if (opcionUsuario == 3)
        {
            cout << "Saliendo del programa..." << endl;
            break;
        }

        switch (opcionUsuario) {
            case 1:
                manejarAdministrador();
                break;
            case 2:
                manejarCliente();
                break;
        }
    }

    return 0;
}
