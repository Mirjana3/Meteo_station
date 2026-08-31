# Meteo Stanica

Jednostavna meteorološka stanica izrađena na Arduino (Croduino) platformi u sklopu kolegija **Računalni sustavi stvarnog vremena**.

Sustav mjeri temperaturu i relativnu vlažnost zraka te ih prikazuje na LCD zaslonu u stvarnom vremenu. Korisnik putem membranske tipkovnice može postaviti temperaturni prag pri kojem se automatski aktivira LED indikator.

## Funkcionalnosti

- Kontinuirano očitavanje temperature i vlage sa senzora DHT11
- Prikaz izmjerenih vrijednosti na LCD zaslonu 16x2 (I2C)
- Unos i postavljanje temperaturnog praga putem membranske tipkovnice 4x4
- Automatska LED signalizacija kada temperatura pređe zadani prag

## Korištene komponente

| Komponenta | Namjena |
|---|---|
| Croduino (Arduino kompatibilna pločica) | Glavni mikroupravljač |
| DHT11 | Senzor temperature i vlage |
| LCD 16x2 s I2C adapterom | Prikaz podataka |
| Membranska tipkovnica 4x4 | Korisnički unos |
| LED dioda + otpornik 220 Ω | Vizualna signalizacija |

## Povezivanje komponenti

- DHT11 → digitalni pin 2 (podatkovni), 5V, GND
- LCD (I2C) → SDA na A4, SCL na A5
- Tipkovnica → redovi na pinove 3–6, stupci na pinove 7–10
- LED indikator → digitalni pin 11 (preko otpornika 220 Ω)

Detaljna blok shema i shema spajanja nalaze se u dokumentaciji projekta.

## Korištene biblioteke

- `DHT.h` – očitavanje temperature i vlage
- `Wire.h` – I2C komunikacija
- `LiquidCrystal_I2C.h` – upravljanje LCD zaslonom
- `Keypad.h` – očitavanje membranske tipkovnice

## Kako pokrenuti

1. Otvoriti `MeteoStanica.ino` u Arduino IDE-u
2. Instalirati potrebne biblioteke (Library Manager → DHT sensor library, LiquidCrystal I2C, Keypad)
3. Spojiti komponente prema shemi
4. Odabrati odgovarajuću pločicu i port, te uploadati kod na uređaj

## Način rada

Nakon pokretanja sustav prikazuje uvodnu poruku, zatim prelazi u standardni način rada u kojem se svake sekunde ažuriraju izmjerene vrijednosti temperature i vlage na LCD zaslonu.

Pritiskom tipke `#` korisnik ulazi u način za postavljanje novog temperaturnog praga, unosi željenu vrijednost brojevima te je potvrđuje tipkom `*`. Kada temperatura dosegne ili prijeđe postavljeni prag, LED dioda se automatski uključuje.
