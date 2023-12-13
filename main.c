/*
Ejercicio 2
– Abrir y cargar data de un fichero binario que contiene nombre de
alumnos, notas de 10 asignaturas de los alumnos (enteros) y un float
        como estatura para cada uno de los alumnos (se carga utilizando una
        función)
– Modificar las notas de 10 asignaturas de un alumno (la posición del
alumno se pasa en una función)
– Guardar los data tras la modificación anterior en un fichero (el fichero
                                                                 es pedido al usuario) (en una función)
*//*


#include <stdio.h>


int main() {
    FILE *fichero;
    char nombre[50];
    int notas[9];
    float altura;
    char respuesta;
    #define MAX 1000
    int q;
    printf("How many students do you want?");
    scanf("%d", &q);


for (int i = 0; i < q; i++) {



    do {
        // Preguntar al usuario su nombre, edad y altura
        printf("Ingrese su nombre:");
        fflush(stdin); //Limpia el buffer
        fgets(nombre, MAX, stdin); //
        fflush(stdin); //Limpia el buffer

        */
/*scanf("%s", nombre);*//*


        for (int i = 0; i <10 ; i++) {
            printf("Ingrese su nota numero %d:", i);
            scanf("%d", &notas[i]);



        }



        printf("Ingrese su altura: ");
        scanf("%f", &altura);

        // Abrir el fichero en modo de escritura (si no existe, se crea; si existe, se sobrescribe)
        fichero = fopen("data.bin", "w");

        // Verificar si el fichero se ha abierto correctamente
        if (fichero == NULL) {
            printf("Error al abrir el fichero.\n");
            return 1;  // Salir del programa con código de error
        }

        // Escribir los data en el fichero
        fprintf(fichero, "Nombre: %s", nombre); //Por la funcion gets me mete un/0 que es un salto de linea

        //print grades of the student
        for (int i = 0; i < 10; ++i) {
            fprintf(fichero, "Nota numero %d es %d \n", i, notas[i]);

        }


        fprintf(fichero, "Altura: %.2f\n", altura);

        // Cerrar el fichero
        fclose(fichero);

        // Informar al usuario que los data han sido guardados
        printf("Los data han sido guardados en el fichero.\n");

        // Preguntar al usuario si quiere imprimir los data
        printf("Quieres imprimir los data? (s/n): ");
        scanf(" %c", &respuesta);

        // Verificar la respuesta del usuario
        if (respuesta == 's' || respuesta == 'S') {
            // Abrir el fichero en modo de lectura
            fichero = fopen("data.bin", "r");

            // Verificar si el fichero se ha abierto correctamente
            if (fichero == NULL) {
                printf("Error al abrir el fichero para leer.\n");
                return 1;  // Salir del programa con código de error
            }

            // Leer y mostrar los data del fichero
            char caracter;
            while ((caracter = fgetc(fichero)) != EOF) { //No se entiende ni el pijo Guarrada
                //Correccion: El bucle a lo largo Esta en la pizarra probablemente habra una foto en el grupo
                printf("%c", caracter);
            }

            // Cerrar el fichero
            fclose(fichero);
        }

        // Preguntar al usuario si desea repetir el proceso
        printf("Quieres ingresar nuevos data? (s/n): ");
        scanf(" %c", &respuesta);

    } while (respuesta == 's' || respuesta == 'S');




}




    return 0;  // Salir del programa con éxito



}
*/





#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_STUDENTS 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int grades[10];
    float height;
} Student;

void saveDataToFile(Student student, FILE *file) {
    fprintf(file, "%s\n", student.name);

    // Print grades of the student
    for (int i = 0; i < 10; ++i) {
        fprintf(file, "%d ", student.grades[i]);
    }

    fprintf(file, "%.2f\n", student.height);
}

void printStudentOptions(Student students[], int numStudents) {
    printf("Options:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%d. %s\n", i + 1, students[i].name);
    }
}

void printStudentData(FILE *file, int selectedStudent, Student students[]) {
    char line[MAX_NAME_LENGTH + 50];  // Adjust the buffer size as needed

    // Skip lines until the selected student
    for (int i = 0; i < selectedStudent; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Error reading data.\n");
            return;
        }
    }

    // Print the data for the selected student
    if (fgets(line, sizeof(line), file) != NULL) {
        printf("Data for %s:\n", students[selectedStudent - 1].name);

        // Tokenize the line to extract grades and height
        char *token = strtok(line, " \n");
        int index = 0;

        while (token != NULL) {
            if (index < 10) {
                printf("Grade %d: %s\n", index + 1, token);
            } else {
                printf("Height: %s\n", token);
            }

            token = strtok(NULL, " \n");
            index++;
        }
    } else {
        printf("Invalid student index.\n");
    }
}

int main() {
    FILE *file;
    char response;
    int numStudents;
    int selectedStudent;

    printf("How many students do you want to input? ");
    scanf("%d", &numStudents);

    Student students[MAX_STUDENTS];

    // Input data for each student
    for (int i = 0; i < numStudents; i++) {
        printf("Enter the full name of student %d (with spaces): ", i + 1);
        scanf(" %[^\n]s", students[i].name);

        for (int j = 0; j < 10; j++) {
            printf("Enter grade number %d for %s: ", j + 1, students[i].name);
            scanf("%d", &students[i].grades[j]);
        }

        printf("Enter the height of student %d: ", i + 1);
        scanf("%f", &students[i].height);

        // Clear the newline character from the buffer
        getchar();
    }

    // Open the file in write mode
    file = fopen("data.bin", "w");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Save the student data to the file for all students
    for (int i = 0; i < numStudents; i++) {
        saveDataToFile(students[i], file);
    }

    // Close the file
    fclose(file);

    do {
        // Ask the user if they want to print the data
        printf("Do you want to print the data? (y/n): ");
        scanf(" %c", &response);

        if (response == 'y' || response == 'Y') {
            // Open the file in read mode
            file = fopen("data.bin", "r");

            // Check if the file opened successfully
            if (file == NULL) {
                printf("Error opening the file for reading.\n");
                return 1;
            }

            // Print student options
            printStudentOptions(students, numStudents);

            // Ask the user which student's data they want to print
            printf("Select the student whose data you want to print (1 to %d): ", numStudents);
            scanf("%d", &selectedStudent);

            // Check the selected student index
            if (selectedStudent >= 1 && selectedStudent <= numStudents) {
                // Print the data for the selected student
                printStudentData(file, selectedStudent, students);
            } else {
                printf("Invalid student index.\n");
            }

            // Close the file
            fclose(file);
        }
    } while (response == 'y' || response == 'Y');

    return 0;
}

