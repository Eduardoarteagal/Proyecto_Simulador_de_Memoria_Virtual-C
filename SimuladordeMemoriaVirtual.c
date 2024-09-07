#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MEMORIA_FISICA 1024 // Tamaño de la memoria física (en bytes)
#define TAM_PAGINA 64          // Tamaño de una página (en bytes)
#define NUM_PAGINAS (TAM_MEMORIA_FISICA / TAM_PAGINA) // Número de páginas en la memoria
#define NUM_SEGMENTOS 4       // Número de segmentos (por simplicidad)

// Estructura para la tabla de páginas
typedef struct {
    int pagina;  // Índice de la página
    int marco;   // Índice del marco en memoria física
    int valido;  // Indica si la página es válida
} TablaPagina;

// Estructura para la tabla de segmentos
typedef struct {
    int segmento; // Índice del segmento
    int base;     // Dirección base del segmento
    int limite;   // Tamaño del segmento
    int valido;   // Indica si el segmento es válido
} TablaSegmento;

// Memoria física (simulada)
char memoriaFisica[TAM_MEMORIA_FISICA];

// Tablas de páginas y segmentos
TablaPagina tablaPaginas[NUM_PAGINAS];
TablaSegmento tablaSegmentos[NUM_SEGMENTOS];

// Inicializa las tablas de páginas y segmentos
void inicializar() {
    for (int i = 0; i < NUM_PAGINAS; i++) {
        tablaPaginas[i].pagina = i;
        tablaPaginas[i].marco = -1;
        tablaPaginas[i].valido = 0;
    }

    for (int i = 0; i < NUM_SEGMENTOS; i++) {
        tablaSegmentos[i].segmento = i;
        tablaSegmentos[i].base = -1;
        tablaSegmentos[i].limite = 0;
        tablaSegmentos[i].valido = 0;
    }
}

// Asigna una página en memoria física
int asignarPagina(int pagina) {
    for (int i = 0; i < NUM_PAGINAS; i++) {
        if (!tablaPaginas[i].valido) {
            tablaPaginas[i].marco = pagina;
            tablaPaginas[i].valido = 1;
            return i;
        }
    }
    return -1; // No hay espacio
}

// Asigna un segmento en memoria física
int asignarSegmento(int segmento, int base, int limite) {
    for (int i = 0; i < NUM_SEGMENTOS; i++) {
        if (!tablaSegmentos[i].valido) {
            tablaSegmentos[i].base = base;
            tablaSegmentos[i].limite = limite;
            tablaSegmentos[i].valido = 1;
            return i;
        }
    }
    return -1; // No hay espacio
}

// Muestra la tabla de páginas
void mostrarTablaPaginas() {
    printf("\n--- Tabla de Paginas ---\n");
    for (int i = 0; i < NUM_PAGINAS; i++) {
        if (tablaPaginas[i].valido) {
            printf("Pagina %d -> Marco %d\n", tablaPaginas[i].pagina, tablaPaginas[i].marco);
        }
    }
}

// Muestra la tabla de segmentos
void mostrarTablaSegmentos() {
    printf("\n--- Tabla de Segmentos ---\n");
    for (int i = 0; i < NUM_SEGMENTOS; i++) {
        if (tablaSegmentos[i].valido) {
            printf("Segmento %d -> Base %d, Limite %d\n",
                   tablaSegmentos[i].segmento, tablaSegmentos[i].base, tablaSegmentos[i].limite);
        }
    }
}

int main() {
    inicializar();

    // Ejemplo de asignación de páginas y segmentos
    int pagina1 = asignarPagina(0);
    int pagina2 = asignarPagina(1);
    int segmento1 = asignarSegmento(0, 0, 128);
    int segmento2 = asignarSegmento(1, 128, 256);

    // Mostrar tablas
    mostrarTablaPaginas();
    mostrarTablaSegmentos();

    return 0;
}
