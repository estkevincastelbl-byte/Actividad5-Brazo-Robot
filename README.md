# Actividad 5 — Control de brazo robótico con ESP32 y Python

## Objetivo
Desarrollar un sistema en el que una ESP32 lea sensores de posición, envíe los datos al computador mediante UART/USB y reciba órdenes desde Python para controlar las articulaciones y la pinza de un brazo robótico.

## Arquitectura
`Sensores → ESP32 → UART/USB → Python → comandos → ESP32 → servomotores`

El proyecto está separado en tres partes para facilitar su prueba: firmware de ESP32, programa de control en Python y modelo URDF del brazo.

## Archivos
- `esp32/brazo_robot.ino`: lectura de sensores, transmisión serial y control de servos.
- `python/control_brazo.py`: recibe datos UART y permite mandar movimientos.
- `python/requirements.txt`: dependencia `pyserial`.
- `urdf/brazo_robot.urdf`: modelo sencillo del brazo para visualización.
- `evidencias/`: carpeta para agregar capturas y enlaces del video.

## Conexiones sugeridas
| Elemento | ESP32 |
|---|---|
| Potenciómetro base | GPIO 34 |
| Potenciómetro brazo | GPIO 35 |
| Potenciómetro pinza | GPIO 32 |
| Servo base | GPIO 18 |
| Servo brazo | GPIO 19 |
| Servo pinza | GPIO 21 |

**Importante:** los servomotores deben alimentarse preferiblemente desde una fuente externa de 5 V. El GND de esa fuente y el GND de la ESP32 deben estar unidos.

## Protocolo UART
La ESP32 transmite cada 200 ms:
`SENS,base,brazo,pinza`

Python puede enviar:
- `MOVE,90,120,40`
- `OPEN`
- `CLOSE`

La ESP32 responde con un `ACK` cuando ejecuta una orden.

## Cómo ejecutar
1. Instalar la librería `ESP32Servo` en Arduino IDE.
2. Abrir `esp32/brazo_robot.ino`, seleccionar la ESP32 y cargarlo.
3. En el PC instalar Python.
4. Abrir una terminal dentro de la carpeta `python`.
5. Ejecutar `pip install -r requirements.txt`.
6. Cambiar `COM5` en `control_brazo.py` por el puerto real de la ESP32.
7. Cerrar el Monitor Serial de Arduino IDE.
8. Ejecutar `python control_brazo.py`.

## Prueba de movimientos
En la consola:
- `m 90 90 45` mueve las tres articulaciones.
- `a` abre la pinza.
- `c` cierra la pinza.
- `q` termina el programa.

Al mismo tiempo se muestran los valores recibidos desde los tres sensores.

## Validación en tiempo real
La comunicación se valida observando que los valores `SENS` cambien al mover los potenciómetros y que la ESP32 responda `ACK` después de una orden. Esto permite demostrar comunicación bidireccional.

## Modelo URDF
El archivo `urdf/brazo_robot.urdf` contiene un modelo propio y sencillo con una base, dos eslabones y una pinza. Puede abrirse en un visualizador URDF compatible para verificar las articulaciones.

## Evidencias para la entrega
Agregar en `evidencias/`:
1. Captura de la ESP32 conectada.
2. Captura de Python recibiendo sensores.
3. Captura del modelo URDF.
4. Video corto mostrando apertura/cierre y movimiento.

## Funcionamiento
La ESP32 adquiere las señales analógicas y las convierte a valores angulares. Los datos se transmiten por comunicación serial a 115200 baudios. Python interpreta los mensajes recibidos y permite enviar nuevas posiciones. La ESP32 procesa esas órdenes y genera las señales necesarias para los servomotores.

## Autor
Actividad académica — implementación propia.
