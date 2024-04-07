#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	config = config_create("cliente.config");
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	valor = config_get_string_value(config,"CLAVE");

	logger = log_create("tp0.log","PROCCESS 0 ",false,LOG_LEVEL_INFO);
	
	/* ---------------- LEER DE CONSOLA ---------------- */
	

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje(ip, conexion);	
	
	// Armamos y enviamos el paquete
	
	paquete(conexion, logger);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
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

	do
	{
		leido = readline(">");		
		if (strcmp(leido,""))
		{		
			log_info(logger,leido);			
			free(leido);
		}
	} while (strcmp(leido,""));
}

void paquete(int conexion, t_log* logger)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
	paquete = crear_paquete();
	
	do
	{
		leido = readline(">");		
		if (strcmp(leido,""))
		{	
			log_info(logger,leido);	
			agregar_a_paquete(paquete,leido,strlen(leido)+1);
			
			free(leido);		
			
		}
	} while (strcmp(leido,""));
	enviar_paquete(paquete,conexion);	
	eliminar_paquete(paquete);
	// Leemos y esta vez agregamos las lineas al paquete
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
	exit(EXIT_SUCCESS);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
