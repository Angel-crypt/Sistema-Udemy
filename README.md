# Sistema de Gestión Empresarial UDEMY

Este proyecto tiene como objetivo desarrollar un sistema de software para UDEMY que gestione el inventario de cursos y la inscripción de estudiantes. El sistema permitirá a los administradores realizar operaciones CRUD (Crear, Leer, Actualizar, Eliminar) sobre cursos, estudiantes e inscripciones, y a los clientes ver cursos, gestionar un carrito de compras e inscribirse en los cursos.

## Índice

1. [Resumen Ejecutivo](#resumen-ejecutivo)
2. [Resumen de Necesidad del Público General](#resumen-de-necesidad-del-público-general)
3. [Introducción](#introducción)
4. [Acrónimos y Definiciones Utilizados](#acrónimos-y-definiciones-utilizados)
5. [Aplicación en el Contexto de Instalación y Compilación](#aplicación-en-el-contexto-de-instalación-y-compilación)
6. [Especificaciones de Requisitos](#especificaciones-de-requisitos)
   - [Requisitos Funcionales](#requisitos-funcionales)
   - [Requisitos No Funcionales](#requisitos-no-funcionales)
7. [Análisis y Diseño del Sistema](#análisis-y-diseño-del-sistema)
   - [Gestión de Cursos](#gestión-de-cursos)
   - [Gestión de Estudiantes](#gestión-de-estudiantes)
   - [Gestión de Inscripciones](#gestión-de-inscripciones)
   - [Carrito de Compras](#carrito-de-compras)
8. [Diagrama de Actividades](#diagrama-de-actividades)
9. [Librerías Utilizadas](#librerías-utilizadas)
10. [Estructura del Código](#estructura-del-código)
11. [Pruebas](#pruebas)
12. [Manual de Usuario](#manual-de-usuario)
13. [Guía de Uso](#guía-de-uso)
14. [Solución de Problemas Comunes](#solución-de-problemas-comunes)
15. [Mantenimiento y Actualizaciones](#mantenimiento-y-actualizaciones)
16. [Plan de Mantenimiento](#plan-de-mantenimiento)
17. [Registro de Cambios](#registro-de-cambios)
18. [Anexos](#anexos)
19. [Referencias](#referencias)

## Resumen Ejecutivo

Este proyecto tiene como objetivo desarrollar un sistema de software para UDEMY que gestione el inventario de cursos y la inscripción de estudiantes. El sistema permitirá a los administradores realizar operaciones CRUD (Crear, Leer, Actualizar, Eliminar) sobre cursos, estudiantes e inscripciones, y a los clientes ver cursos, gestionar un carrito de compras e inscribirse en los cursos. Se espera que el programa facilite la administración de cursos y estudiantes, mejorando la eficiencia operativa de UDEMY y proporcionando una experiencia de usuario fluida para los estudiantes.

## Resumen de Necesidad del Público General

- **Acceso a la Educación de Calidad**: Programas educativos bien estructurados con relevancia de alto aprendizaje.
- **Flexibilidad y Conveniencia**: Cursos disponibles en cualquier momento y lugar.
- **Costo-Efectividad**: Acceso asequible comparado con instituciones tradicionales.
- **Certificación y Reconocimiento**: Certificados avalados en el mercado laboral.
- **Actualización Constante**: Contenido y material actualizados continuamente.

## Introducción

- **Propósito del documento**: Describe el diseño, implementación y uso del sistema de gestión de inventarios de cursos e inscripción de estudiantes para UDEMY.
- **Alcance del proyecto**: Desarrollo de funcionalidades para la gestión de cursos, estudiantes, inscripciones y carrito de compras. Implementado en C++ y utilizando archivos para manejo de datos.

## Acrónimos y Definiciones Utilizados

- **CRUD**: Create, Read, Update, Delete (Crear, Leer, Actualizar, Eliminar).
- **ID**: Identificador único.
- **C++**: Lenguaje de programación utilizado.
- **VS Code**: Editor de código fuente.
- **MinGW**: Entorno de desarrollo para Windows.
- **GCC**: GNU Compiler Collection.
- **g++**: Compilador de C++.
- **IDE**: Integrated Development Environment.
- **PATH**: Variable de entorno para ejecutables.
- **Extensión de VS Code**: Complementos que añaden funcionalidad.
- **Paleta de Comandos**: Interfaz en VS Code para ejecutar comandos.
- **Terminal Integrada**: Consola dentro de VS Code.
- **fstream**: Biblioteca estándar de C++ para manejo de archivos.
- **stdout**: Salida estándar del programa.
- **stderr**: Salida de error estándar del programa.

## Aplicación en el Contexto de Instalación y Compilación

- **VS Code**: Editor para escribir y compilar el código C++.
- **MinGW/gcc**: Compilador para convertir código C++ en ejecutable.
- **PATH**: Configuración del sistema para g++.
- **Extensión de C/C++ en VS Code**: Añade soporte para desarrollar y depurar en C++.
- **Terminal Integrada**: Compilar y ejecutar el programa dentro de VS Code.
- **fstream**: Biblioteca para leer y escribir archivos .txt.

## Especificaciones de Requisitos

### Requisitos Funcionales

- **Gestión de Cursos**:
  - Agregar, listar, modificar y eliminar cursos.
- **Gestión de Estudiantes**:
  - Agregar, listar, modificar y eliminar estudiantes.
- **Gestión de Inscripciones**:
  - Agregar, listar y eliminar inscripciones.
- **Carrito de Compras**:
  - Agregar, eliminar cursos del carrito, mostrar carrito y procesar compra.
- **Visualización de Cursos Disponibles**:
  - Mostrar una lista de cursos disponibles para los estudiantes.
- **Restricciones**:
  - Un estudiante no puede estar inscrito en dos cursos al mismo tiempo.

### Requisitos No Funcionales

- **Interfaz de Usuario**:
  - Operación desde la terminal, interfaz clara y fácil de usar.
- **Seguridad**:
  - Operaciones CRUD solo para administradores.
- **Rendimiento**:
  - Manejo de un número significativo de cursos y estudiantes sin degradar el rendimiento.
- **Mantenimiento**:
  - Código bien documentado para facilitar futuras actualizaciones y mantenimiento.

## Análisis y Diseño del Sistema

El sistema se divide en varias funcionalidades clave, implementadas a través de funciones específicas en el código.

### Gestión de Cursos

- **Agregar Curso**: Permite agregar nuevos cursos.
- **Listar Cursos**: Muestra todos los cursos disponibles.
- **Modificar Curso**: (Funcionalidad por implementar).
- **Eliminar Curso**: (Funcionalidad por implementar).

### Gestión de Estudiantes

- **Agregar Estudiante**: Permite agregar nuevos estudiantes.
- **Listar Estudiantes**: Muestra todos los estudiantes registrados.
- **Verificar Usuario**: Verifica la existencia de un estudiante basado en su ID.

### Gestión de Inscripciones

- **Listar Inscripciones**: Muestra todas las inscripciones realizadas.

### Carrito de Compras

- **Agregar Curso al Carrito**: Permite agregar cursos al carrito de compras.
- **Eliminar Curso del Carrito**: Permite eliminar cursos del carrito.
- **Mostrar Carrito**: Muestra el contenido del carrito y el costo total.
- **Procesar Compra**: (Funcionalidad por implementar).

## Diagrama de Actividades

El diagrama de actividades muestra la estructura y lógica del sistema subdividido en funciones y procesos, facilitando la comprensión del flujo de trabajo y operaciones del sistema.

## Librerías Utilizadas

- **fstream**: Manejo de operaciones de entrada y salida en archivos.
- **std**: Uso de funcionalidades estándar de C++.

## Estructura del Código

El código está organizado en módulos que corresponden a las funcionalidades clave del sistema, asegurando una estructura clara y mantenible.

## Pruebas

Se han realizado pruebas para verificar el correcto funcionamiento de cada funcionalidad implementada, garantizando la estabilidad y fiabilidad del sistema.

## Manual de Usuario

El manual de usuario proporciona instrucciones detalladas sobre cómo utilizar el sistema, incluyendo ejemplos de uso y explicaciones de cada funcionalidad.

## Guía de Uso

La guía de uso ofrece pasos detallados para instalar, compilar y ejecutar el sistema, así como solucionar problemas comunes que puedan surgir durante su uso.

## Solución de Problemas Comunes

Se incluye una sección dedicada a la solución de problemas comunes que los usuarios pueden encontrar, ofreciendo soluciones y recomendaciones.

## Mantenimiento y Actualizaciones

Se detalla el plan de mantenimiento y actualizaciones, asegurando que el sistema se mantenga actualizado y operativo a lo largo del tiempo.

## Plan de Mantenimiento

El plan de mantenimiento incluye tareas regulares de revisión y actualización del sistema para garantizar su buen funcionamiento y adaptación a nuevas necesidades.

## Registro de Cambios

Se lleva un registro detallado de todos los cambios realizados en el sistema, facilitando el seguimiento y la gestión de versiones.

## Anexos

Incluye documentos adicionales y recursos complementarios relacionados con el proyecto.

## Referencias

Se listan todas las fuentes y referencias utilizadas durante el desarrollo del proyecto.

---

### Alumnos:
- Angel Santiago Cruz Rodriguez
- Mauricio Gonzalez Sanchez
- Karina Ibarra Morales

### Maestro:
- Armando Soto Valdez
