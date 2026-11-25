#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int movimiento_valido(char pos_actual[2], char pos_nueva[2]) {
    int dx = abs(pos_actual[0] - pos_nueva[0]);
    int dy = abs(pos_actual[1] - pos_nueva[1]);
    return ((dx == 1 && dy == 2) || (dx == 2 && dy == 1));
}

void verificar_movimientos(char ak[3], char *cadena) {
    char *mov = strtok(cadena, " ");
    char pos_actual[2] = {ak[0], ak[1]};
    int i = 1;

    while (mov != NULL) {
        if (mov[0] != 'K') {
            printf("movimiento INCORRECTO falla letra %c no pertenece a un caballo.\n", mov[0]);
            return;
        }

        char pos_nueva[2] = {mov[1], mov[2]};

        if (!movimiento_valido(pos_actual, pos_nueva)) {
            printf("INCORRECTO falla en el movimiento %d.\n", i);
            return;
        }

        pos_actual[0] = pos_nueva[0];
        pos_actual[1] = pos_nueva[1];
        mov = strtok(NULL, " ");
        i++;
    }
    printf("movimiento CORRECTO.\n");
}

int main() {
    char movs_originales[] = "Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8";
    
    // Utilizamos la estructura timespec para medir el tiempo con mayor precisión
    // Ya que clock() redondea los nanosegundos y el resultado sale en 0 como se observó en la prueba de rendimiento
    struct timespec inicio, fin;
    double tiempo_total;
    
    // Captura el tiempo en nanosegundos
    timespec_get(&inicio, TIME_UTC);
    
    for (int j = 0; j < 10; j++) {
        char buffer[2500];
        strcpy(buffer, movs_originales);
        
        char *mov = strtok(buffer, " ");
        char pos_actual[2] = {'a', '2'};
        int i = 1;
        while (mov != NULL) {
            if (mov[0] != 'K') break;
            char pos_nueva[2] = {mov[1], mov[2]};
            if (!movimiento_valido(pos_actual, pos_nueva)) break;
            pos_actual[0] = pos_nueva[0]; pos_actual[1] = pos_nueva[1];
            mov = strtok(NULL, " ");
            i++;
        }
    }
    
    timespec_get(&fin, TIME_UTC);
    
    // Calcula la diferencia sumando los segundos y los nanosegundos convertidos
    tiempo_total = (double)(fin.tv_sec - inicio.tv_sec) + 
                   (double)(fin.tv_nsec - inicio.tv_nsec) / 1000000000.0;

    FILE *archivo = fopen("resultado.txt", "a");
    if (archivo != NULL) {
        // Usamos %1.9f para obligar a mostrar más decimales
        fprintf(archivo, "Tiempo C (10 iteraciones, 500 movs): %1.9f segundos\n", tiempo_total);
        fclose(archivo);
    }
    
    printf("Prueba de rendimiento finalizada en C. Tiempo detectado: %1.9f s\n", tiempo_total);
    return 0;
}