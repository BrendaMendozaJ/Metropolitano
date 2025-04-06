#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Estacion {    // estructura para representar una estación
    int ingresan;    // Personas que entran a la estación
    int destino[13]; // Personas que van a cada estación
};
void imprimir_encabezado() {
    printf("   Estacion   Ingresan   ");
    for (int i=0;i<13;i++) {
        printf(" Dest%d ",i+1);
    }
    printf("\n");
}
void imprimir_fila(int num_estacion, struct Estacion *estacion) {
    printf("%9d   %8d   ", num_estacion, estacion->ingresan);
    for (int i=0; i<13;i++) {
        printf("%6d ", estacion->destino[i]);
    }
    printf("\n");
}
int generar_ingreso(int min, int max, int estacion) { //numero aleatorio de personas que ingresan a una estación
    if (estacion==13) {  //si es la estación 13, el número de ingresos siempre es 0 porque es el último paradero y es unidireccional
        return 0;
    }
    return rand()%(max-min+1)+min;
}
void distribuir_personas(struct Estacion *estacion, int total_ingresos, int estacion_origen) { // distribuir personas aleatoriamente a diferentes estaciones
    int ingresos_restantes = total_ingresos;
    for (int i=0;i<13;i++) {
        estacion->destino[i]=0;
    }

    // distribuir personas basadas en la estación de origen
    int i=estacion_origen;
    while (i<13) {
        int personas_a_destino=rand()%(ingresos_restantes+1);
        estacion->destino[i]=personas_a_destino;
        ingresos_restantes-=personas_a_destino;
        i++;
    }
}
int main() {
    printf("Simulación de flujo de personas del metropolitano\n");
    srand(time(NULL));
    struct Estacion estaciones[13]={0};
 
    int total_recogido_por_hora = 0; // Inicializamos el total recogido por hora en 0
    
    int rangos[13][2]={   // Array de rangos para el número de personas que ingresan a cada estación
        {10, 20}, {20, 30}, {30, 40}, {50, 60}, {60, 70}, {70, 80}, {80, 90},
        {90, 100}, {80, 90}, {80, 90}, {50, 70}, {20, 30}, {20, 30}
    };
    
    for (int hora=6;hora<= 24;hora++) { // Para el número de horas
        printf("\n%d horas:\n",hora);
        imprimir_encabezado();
        
        total_recogido_por_hora = 0;
        
        for (int j= 0;j<13;j++) {
            
            estaciones[j].ingresan=generar_ingreso(rangos[j][0],rangos[j][1],j+1); // Genera un número aleatorio de personas que ingresan a la estación

            distribuir_personas(&estaciones[j],estaciones[j].ingresan, j + 1);

            imprimir_fila(j+1,&estaciones[j]);
            
            // sumamos el número de personas ingresadas a todas las estaciones para obtener el total recogido por el autobús
            total_recogido_por_hora += estaciones[j].ingresan;
        }

        printf("\ntotal recogido por el bus en esta hora: %d personas\n", total_recogido_por_hora);
        printf("Presiona enter para continuar con la siguiente hora...");
        getchar();
    }

    return 0;
}

