"""
Actividad 5 - Control UART de brazo robótico
Instalar: pip install pyserial
Ejecutar: python control_brazo.py
"""
import serial
import threading
import time

PUERTO = "COM5"       # CAMBIAR por el puerto de tu ESP32
BAUDIOS = 115200

esp = serial.Serial(PUERTO, BAUDIOS, timeout=0.2)
time.sleep(2)

def recibir():
    while True:
        try:
            linea = esp.readline().decode(errors="ignore").strip()
            if linea:
                if linea.startswith("SENS,"):
                    _, base, brazo, pinza = linea.split(",")
                    print(f"\rSensores -> Base:{base}°  Brazo:{brazo}°  Pinza:{pinza}°   ", end="")
                else:
                    print("\nESP32:", linea)
        except Exception:
            break

threading.Thread(target=recibir, daemon=True).start()

print("CONTROL DEL BRAZO")
print("m base brazo pinza  -> ejemplo: m 90 120 40")
print("a = abrir pinza | c = cerrar pinza | q = salir")

while True:
    cmd = input("\n> ").strip().lower()
    if cmd == "q":
        break
    elif cmd == "a":
        esp.write(b"OPEN\n")
    elif cmd == "c":
        esp.write(b"CLOSE\n")
    elif cmd.startswith("m "):
        try:
            _, base, brazo, pinza = cmd.split()
            base = max(0,min(180,int(base)))
            brazo = max(0,min(180,int(brazo)))
            pinza = max(0,min(90,int(pinza)))
            esp.write(f"MOVE,{base},{brazo},{pinza}\n".encode())
        except ValueError:
            print("Formato: m 90 120 40")
    else:
        print("Comando no reconocido.")

esp.close()
