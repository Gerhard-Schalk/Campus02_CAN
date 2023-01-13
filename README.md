# CAN-Bus Lab

## Mit dem privaten WLAN verbinden
SSID: `A1-4883e1`

WPA2 PWD: `pe5fixhe7f9c`


## Via SSH mit dem Raspberry Pi verbinden
Verbind via SSH: `ssh pi@raspberrypi`

Pi PWD: `Campus02#ADT`


## Privates Verzeichnis erstellen
```
cd CAN_Lab/
```
```
mkdir <Ihr Name>
```
```
cd <Ihr Name>
```
```
cp ~/CAN_Src/can_example.c can_example.c
```

Beispiel:
```
cd CAN_Lab/
```
```
mkdir gs
```
```
cd gs
```
```
cp ~/CAN_Src/can_example.c can_example.c
```
```
ls
```


## C-Beispiel mit GCC kompilieren
```
gcc can_example.c -o can_example.out
```


## C-Beispiel ausführen
```
./can_example.out
```


## C-Beispeil mit Nano Editor ergänzen
```
nano can_example.c
```

Anschließend erneut kompilieren und ausführen.


