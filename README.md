# Konverter GPS koordinata

## Komponente
- ESP32
- ILI9341 TFT displej
- Taster (button)

## Opis projekta
Ovaj projekat omogućava unos NMEA RMC rečenice preko Serial terminala. Nakon unosa rečenice i pritiska na taster, uređaj parsira rečenicu, izdvaja GPS koordinate (geografsku širinu i dužinu) i prikazuje ih na ILI9341 displeju u dva formata:
- DMM (stepeni i decimalni minuti)
- Decimalni stepeni

### Primer NMEA RMC rečenice
```
$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A
```

U ovom primeru:
- Geografska širina (latitude): `4807.038` N
- Geografska dužina (longitude): `01131.000` E

Ove vrednosti su u DMM formatu. Nakon konverzije, prikazuju se i u decimalnim stepenima (npr. latitude=48.1173, longitude=11.5167).

## Uputstvo za korišćenje
1. Pokrenite simulaciju ili povežite ESP32 sa računarom.
2. Otvorite Serial Monitor i unesite NMEA RMC rečenicu.
3. Pritisnite taster povezan na ESP32 (pin 15).
4. Na displeju će biti prikazane koordinate u oba formata.

## Pokretanje u Wokwi simulatoru
Projekat možete pokrenuti i direktno u Wokwi simulatoru na sledećem linku:
[https://wokwi.com/projects/434292467147615233](https://wokwi.com/projects/434292467147615233)

## Autor
Nemanja Božilović, ITS 05/24 