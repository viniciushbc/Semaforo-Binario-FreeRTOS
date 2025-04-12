#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "basic_io.h"
#include <time.h>
#include <stdlib.h>

// Protótipo das tarefas

// Os parâmtros difinirão a direção da manobra

void vTaskGuinada(void* pvParameters);
// pvParameters(1) = Gira no sentido horário
// pvParameters(0) = Giora no sentido anti-horário
static int sentidoHorario = 1;
static int sentidoAntiHorario = 0;

void vTaskArfagem(void *pvParameters);
// pvParameters(1) = Se move para frente
// pvParameters(0) = Se move para trás
static int frente = 1;
static int tras = 0;

void vTaskRolagem(void *pvParameters);
// pvParameters(1) = Se move para a esquerda
// pvParameters(0) = Se move para a direita
static int esquerda = 1;
static int direita = 0;


// Criando a variável para o semáforo
xSemaphoreHandle xSemaphore = NULL;

// Criando um display para cada um dos motores do drone
char bufferMotor0[10];
char bufferMotor1[10];
char bufferMotor2[10];
char bufferMotor3[10];

int motor0 = 500;
int motor1 = 500;
int motor2 = 500;
int motor3 = 500;

int main_(void)
{
		// Função para criar um semáforo binário
	    vSemaphoreCreateBinary(xSemaphore);

		// Criando as três tarefas 
		xTaskCreate(vTaskGuinada, "Guinada", 1000, (void*)&sentidoHorario, 1, NULL);
		xTaskCreate(vTaskArfagem, "Arfagem", 1000, (void*)&frente, 1, NULL);
		xTaskCreate(vTaskRolagem, "Rolagem", 1000, (void*)&esquerda, 1, NULL);


		// Inicializa o escalonador
		vTaskStartScheduler();

	for (;; );
	return 0;
}

void vTaskGuinada(void* pvParameters)
{
	int sentido = *((int*)pvParameters);

	for (;; )
	{

		if (xSemaphore != NULL) {

			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				// Sentido horário
				if (sentido == 1) {
					vPrintString("Guinada sentido horario:\n\n");

					motor0 += 100;
					motor1 -= 50;
					motor2 += 100;
					motor3 -= 50;

					// Incrementar motor0
					sprintf(bufferMotor0, "Motor 0: %d\n", motor0);
					vPrintString(bufferMotor0);

					// Decrementar motor1
					sprintf(bufferMotor1, "Motor 1: %d\n", motor1);
					vPrintString(bufferMotor1);

					// Incrementar motor 2
					sprintf(bufferMotor2, "Motor 2: %d\n", motor2);
					vPrintString(bufferMotor2);

					// Decrementar motor3
					sprintf(bufferMotor3, "Motor 3: %d\n", motor3);
					vPrintString(bufferMotor3);

					vPrintString("------------------------------\n");

				}
				// Sentido anti-horário
				else {
					vPrintString("Guinada sentido anti-horario:\n\n");

					motor0 -= 50;
					motor1 += 100;
					motor2 -= 50;
					motor3 += 100;

					// Decrementar motor0
					sprintf(bufferMotor0, "Motor 0: %d\n", motor0);
					vPrintString(bufferMotor0);

					// Incrementar motor1
					sprintf(bufferMotor1, "Motor 1: %d\n", motor1);
					vPrintString(bufferMotor1);

					// Decrementar motor 2
					sprintf(bufferMotor2, "Motor 2: %d\n", motor2);
					vPrintString(bufferMotor2);

					// Incrementar motor3
					sprintf(bufferMotor3, "Motor 3: %d\n", motor3);
					vPrintString(bufferMotor3);

					vPrintString("------------------------------\n");

				}
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			// imprime a mensagem caso o semáforo não tenha sido criado
			printf("O semáforo não foi criado\n");
		}
		// Delay de 10ms
		vTaskDelay(portTICK_RATE_MS * 10);
	}
	// A função vTaskDelete() permite liberar explicitamente a tarefa
	vTaskDelete(NULL);
}

void vTaskArfagem(void* pvParameters)
{
	int direcao = *((int*)pvParameters);

	for (;; )
	{
		// Verificando se o semáforo foi criado antes de utilizá-lo
		if (xSemaphore != NULL) {

			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {
				
				// Frente
				if (direcao == 1) {
					vPrintString("Arfagem para Frente:\n\n");

					motor0 -= 10;
					motor1 -= 10;
					motor2 += 25;
					motor3 += 25;

					// Decrementar motor0
					sprintf(bufferMotor0, "Motor 0: %d\n", motor0);
					vPrintString(bufferMotor0);

					// Decrementar motor1
					sprintf(bufferMotor1, "Motor 1: %d\n", motor1);
					vPrintString(bufferMotor1);

					// Incrementar motor 2
					sprintf(bufferMotor2, "Motor 2: %d\n", motor2);
					vPrintString(bufferMotor2);

					// Incrementar motor3
					sprintf(bufferMotor3, "Motor 3: %d\n", motor3);
					vPrintString(bufferMotor3);

					vPrintString("------------------------------\n");

				}
				// Trás
				else {
					vPrintString("Arfagem para Trás:\n\n");

					motor0 += 25;
					motor1 += 25;
					motor2 -= 10;
					motor3 -= 10;

					// Incrementar motor0
					sprintf(bufferMotor0, "Motor 0: %d\n", motor0);
					vPrintString(bufferMotor0);

					// Incrementar motor1
					sprintf(bufferMotor1, "Motor 1: %d\n", motor1);
					vPrintString(bufferMotor1);

					// Decrementar motor 2
					sprintf(bufferMotor2, "Motor 2: %d\n", motor2);
					vPrintString(bufferMotor2);

					// Decrementar motor3
					sprintf(bufferMotor3, "Motor 3: %d\n", motor3);
					vPrintString(bufferMotor3);

					vPrintString("------------------------------\n");
				}
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			printf("O semáforo não foi criado\n");
		}
		// Delay de 40ms
		vTaskDelay(portTICK_RATE_MS * 40);
	}

	vTaskDelete(NULL);
}

void vTaskRolagem(void* pvParameters)
{
	int direcao = *((int*)pvParameters);
	for (;; )
	{
		
		if (xSemaphore != NULL) {

			if (xSemaphoreTake(xSemaphore, (portTickType)10) == pdTRUE) {

				// Esquerda
				if (direcao == 1) {
					vPrintString("Rolagem para a Esquerda:\n\n");

					motor0 -= 20;
					motor1 += 50;
					motor2 += 50;
					motor3 -= 20;

					// Decrementar motor0
					sprintf(bufferMotor0, "Motor 0: %d\n", motor0);
					vPrintString(bufferMotor0);

					// Incrementar motor1
					sprintf(bufferMotor1, "Motor 1: %d\n", motor1);
					vPrintString(bufferMotor1);

					// Incrementar motor 2
					sprintf(bufferMotor2, "Motor 2: %d\n", motor2);
					vPrintString(bufferMotor2);

					// Decrementar motor3
					sprintf(bufferMotor3, "Motor 3: %d\n", motor3);
					vPrintString(bufferMotor3);

					vPrintString("------------------------------\n");

				}
				// Direita
				else {
					vPrintString("Rolagem para a Direita:\n\n");

					motor0 += 50;
					motor1 -= 20;
					motor2 -= 20;
					motor3 += 50;

					// Incrementar motor0
					sprintf(bufferMotor0, "Motor 0: %d\n", motor0);
					vPrintString(bufferMotor0);

					// Decrementar motor1
					sprintf(bufferMotor1, "Motor 1: %d\n", motor1);
					vPrintString(bufferMotor1);

					// Decrementar motor 2
					sprintf(bufferMotor2, "Motor 2: %d\n", motor2);
					vPrintString(bufferMotor2);

					// Incrementar motor3
					sprintf(bufferMotor3, "Motor 3: %d\n", motor3);
					vPrintString(bufferMotor3);

					vPrintString("------------------------------\n");
				}
				xSemaphoreGive(xSemaphore);
			}
		}
		else
		{
			printf("O semáforo não foi criado\n");
		}
		// Delay de 20ms
		vTaskDelay(portTICK_RATE_MS * 20);
	}
	vTaskDelete(NULL);
}



