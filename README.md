# 🛩️ Controle de Manobras de um Drone com FreeRTOS

Este projeto simula o controle de manobras de um drone utilizando o sistema operacional de tempo real **FreeRTOS**, implementando tarefas concorrentes para representar os comandos de **guinada**, **arfagem** e **rolagem**. Cada tarefa ajusta a rotação dos motores de forma independente para representar o comportamento físico da aeronave.

---

## 📁 Estrutura do Projeto

O código-fonte principal está localizado em: example.c

---

## 🚀 Objetivo

Para que um drone possa voar, é necessário controlar a rotação de suas hélices de forma independente. Isso permite:

- Manobrar em três eixos:
  - **Guinada** — Rotação no eixo vertical
  - **Arfagem** — Inclinação para frente/trás
  - **Rolagem** — Inclinação lateral (direita/esquerda)

---

## ⚙️ Implementação

O projeto implementa **três tarefas** FreeRTOS:

| Tarefa         | Função                  | Velocidade | Período |
|----------------|-------------------------|------------|---------|
| `vTaskGuinada` | Simula rotação do drone no eixo vertical (guinada) | 100      | 10 ms  |
| `vTaskArfagem` | Simula inclinação para frente/trás (arfagem)       | 25       | 40 ms  |
| `vTaskRolagem` | Simula inclinação lateral esquerda/direita (rolagem) | 50      | 20 ms  |

Essas tarefas compartilham o controle dos **quatro motores** do drone e utilizam um **semáforo binário** (`xSemaphore`) para garantir exclusão mútua durante a alteração dos valores.

---

## 🧠 Lógica de Controle

### 🎮 Manobras simuladas

#### 🌀 Guinada
- **Sentido horário**: aumenta `motor0` e `motor2`; diminui `motor1` e `motor3`.
- **Sentido anti-horário**: diminui `motor0` e `motor2`; aumenta `motor1` e `motor3`.

#### ↔️ Arfagem
- **Frente**: aumenta `motor2` e `motor3`; diminui `motor0` e `motor1`.
- **Trás**: aumenta `motor0` e `motor1`; diminui `motor2` e `motor3`.

#### ⤴️ Rolagem
- **Esquerda**: aumenta `motor1` e `motor2`; diminui `motor0` e `motor3`.
- **Direita**: aumenta `motor0` e `motor3`; diminui `motor1` e `motor2`.

---

## 🧰 Tecnologias Utilizadas

### 🧠 FreeRTOS

[**FreeRTOS**](https://www.freertos.org/) é um sistema operacional de tempo real de código aberto, amplamente utilizado em sistemas embarcados.

### 💻 Linguagem C

O projeto foi totalmente desenvolvido em **C**, linguagem de programação padrão para sistemas embarcados.
