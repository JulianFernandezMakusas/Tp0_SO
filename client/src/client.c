#include "client.h"
#include <commons/log.h>
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;
	t_log* logger;
	t_config* config;
	t_log_level* level;
	/* ---------------- LOGGING ---------------- */

	logger = log_create("tp0.log", "Prueba_Logger", true, LOG_LEVEL_INFO);
	log_info(logger, "Prueba de log info");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	char fileConfigPath[] = "/home/utnso/tp0/client/tp0.config";
	char *path = realpath(fileConfigPath, NULL);
	config = config_create(path);
	if (config == NULL) {
	    printf("No se creo el archivo de configuracion");
	}

	char *keyClave = "CLAVE";
	if (config_has_property(config, keyClave) == true) {
		valor = config_get_string_value(config, keyClave);
		log_info(logger, valor);
	} else {
		printf("No tiene clave");
	}

	char *keyIP = "IP";
	if (config_has_property(config, keyIP) == true) {
		ip = config_get_string_value(config, keyIP);
		log_info(logger, ip);
	} else {
		printf("No tiene ip");
	}

	char *keyPuerto = "PUERTO";
	if (config_has_property(config, keyPuerto) == true) {
		puerto = config_get_string_value(config, keyPuerto);
		log_info(logger, puerto);
	} else {
		printf("No tiene puerto");
	}

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/

}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	while(strcmp(leido, "") != 0) {
		leido = readline("TPSO> ");
		log_info(logger, leido);
	}

	free(1);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
	while(strcmp(leido, "") != 0) {
		leido = readline("TPSO> ");
		int tamanio = strlen(leido) + 1;
		agregar_a_paquete(paquete, leido, tamanio);
	}

	enviar_paquete(paquete, conexion);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
