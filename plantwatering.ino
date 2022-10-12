  // 12.10.2022
  // -------------------- HIER WERTE EINSTELLEN --------------------

  #include <SoftwareSerial.h>
  SoftwareSerial relaiskarte(8, 9);                                           // RX, TX
  int i;                                                                      // Variable für Countdown
  int vortest = 20;                                                           // Zeit des Vortests in Sekunden
  int looptime = 120;                                                         // Nächste Überprüfung der Feuchtigkeitssensoren in Minuten
  int loopoverflow = 30;                                                      // Nächste Überprüfung des Überlaufsensors in Minuten
  int looptank = 1;                                                           // Nächste Überprüfung des Tanksensors in Minuten
  // bei diesen Werten der Feuchtigkeitssensoren wird jede Pflanze gegossen
  int value1 = 330;                                                           // Blumenkasten R
  int value2 = 300;                                                           // Blumenkasten L (neuer sensor)
  int value3 = 300;                                                           // Glas Physalis
  int value4 = 300;                                                           // Jostabeeren (neuer sensor)
  int value5 = 320;                                                           // Topf Chili
  int pump = 10000;                                                           // Zeit wie lange die Pumpe läuft in Milisekunden

  // **********************************************************************************************************************************

void setup() {
  // RELAISKARTE
  delay(4);                                                                   // Sicherheitspause
  relaiskarte.begin(9600);                                                    // Baudrate der Relaiskarte auf 9600 Baud setzen
  delay(4);											                                              // Sicherheitspause
  relaiskarte.write((byte)0x50);                                              // Startbyte (Fehler: öffnet Relais K1,3,5,8)
  delay(4);                                                                   // Sicherheitspause
  relaiskarte.write((byte)0x51);                                              // Endbyte (Fehler: öffnet Relais K1,3,5)
  delay(4);                                                                   // Sicherheitspause
  relaiskarte.write((byte)B11111101);                                         // K7 öffnen (freies Relais)
  delay(100);                                                                 // kurzes klicken
  relaiskarte.write((byte)B11111111);                                         // Alle Relais aus
  delay(100);
  relaiskarte.write((byte)B11111101);                                         // K7 öffnen (freies Relais)
  delay(100);                                                                 // kurzes klicken
  relaiskarte.write((byte)B11111111);                                         // Alle Relais aus
  delay(100);                                                                 // Sicherheitspause

  // ARDUINO BAUD RATE UND PINBELEGUNG
  Serial.begin(9600);                                                         // Serial-Port öffnen und auf 9600 Baud setzen
  pinMode(A1, INPUT);                                                         // Signal Feuchtigkeitssensor 1
  pinMode(A2, INPUT);                                                         // Signal Feuchtigkeitssensor 2
  pinMode(A3, INPUT);                                                         // Signal Feuchtigkeitssensor 3
  pinMode(A4, INPUT);                                                         // Signal Feuchtigkeitssensor 4
  pinMode(A5, INPUT);                                                         // Signal Feuchtigkeitssensor 5
  pinMode(5, OUTPUT);                                                         // Signal Ausgang für LED
  pinMode(6, INPUT);                                                          // Signal Überlaufsensor
  pinMode(7, INPUT_PULLUP);                                                   // Signal Schwimmerschalter Wassertank

  // VORTEST SENSOREN
  Serial.print("\nMesswerte der Sensoren:\n");                                // Textausgabe
  Serial.println(analogRead(A1));                                             // Sensorwert Ausgabe
  Serial.println(analogRead(A2));                                             // Sensorwert Ausgabe
  Serial.println(analogRead(A3));                                             // Sensorwert Ausgabe
  Serial.println(analogRead(A4));                                             // Sensorwert Ausgabe
  Serial.println(analogRead(A5));                                             // Sensorwert Ausgabe
  delay(1000);                                                                // Lesepause
  Serial.print("\n\n\nBitte warten\nSensoren ermitteln den genauen Feuchtigkeitswert\n"); // Textausgabe
  i = (vortest);                                                              // Countdownzeit oben einstellen
  for (i; i > 0; i--) {
    Serial.println(i);
    delay(1000);
  }
  Serial.print("\nMesswerte der Sensoren:\n");                                // Textausgabe
  Serial.println(analogRead(A1));                                             // Sensorwert Ausgabe
  Serial.println(analogRead(A2));                                             // Sensorwert Ausgabe
  Serial.println(analogRead(A3));                                             // Sensorwert Ausgabe
  Serial.println(analogRead(A4));                                             // Textausgabe
  Serial.println(analogRead(A5));                                             // Textausgabe
  delay(3000);                                                                // Lesepause
  Serial.print("\nBereit\n");                                                 // Textausgabe
  delay(1000);                                                                // Lesepause
  Serial.print("\nVoreingestellte Werte\n");                                  // Textausgabe
  Serial.print("Vortestzeit s: ");                                            // Textausgabe
  Serial.println(vortest);                                                    // Wertausgabe
  Serial.print("Gesamte Loopzeit m: ");                                       // Textausgabe  
  Serial.println(looptime);                                                   // Wertausgabe
  Serial.print("Zeit Überlaufsensorloop m: ");                                // Textausgabe
  Serial.println(loopoverflow);                                               // Wertausgabe
  Serial.print("Zeit Schwimmerloop m: ");                                     // Textausgabe
  Serial.println(looptank);                                                   // Wertausgabe
  Serial.print("Gießwerte Feuchtigkeitssensoren:\n");                         // Textausgabe
  Serial.println(value1);                                                     // Wertausgabe
  Serial.println(value2);                                                     // Wertausgabe
  Serial.println(value3);                                                     // Wertausgabe
  Serial.println(value4);                                                     // Wertausgabe
  Serial.println(value5);                                                     // Wertausgabe
  Serial.print("Gießzeit ms: ");                                              // Textausgabe
  Serial.println(pump);                                                       // Wertausgabe
  delay(1000);                                                                // Lesepause

  // **********************************************************************************************************************************

}
void loop() {

  Serial.print("\nLoopbeginn\n");                                             // Textausgabe

  // ÜBERLAUFSENSOR
  delay(1000);                                                                // Lesepause
  while (!digitalRead(6)) {                                                   // solange Überlaufsensor false (also nass)
    Serial.print("\nALARM! Blumentöpfe laufen über! \nPause bis das Wasser verdunstet ist (Angaben in Minuten)\n");  // Textausgabe
    digitalWrite(5, HIGH);                                                    // LED an
    i = (loopoverflow);                                                       // Countdownzeit oben einstellen
    while (i != 0) {
      for (i; i > 0; i--) {
        Serial.println(i);
        delay(60000);
      }
    }
  }
  digitalWrite(5, LOW);                                                       // LED aus
  Serial.print("\nÜberlaufsensor OK\n");                                      // Textausgabe

  // TANKÜBERPRÜFUNG
  delay(1000);                                                                // Lesepause
  int Tanksensor = digitalRead(7);                                            // Signal am Pin auslesen und in Variable Tanksensor speichern
  delay(10);                                                                  // Sicherheitspause
  while (digitalRead(7)) {                                                    // solange Tanksensor true (also trocken)
    Serial.print("\nWassertank ist Leer! Bitte auffüllen!\nPause bis zur nächsten Wasserstandsabfrage (Angaben in Minuten)\n"); // Textausgabe
    digitalWrite(5, HIGH);                                                    // LED an
    i = (looptank);                                                           // Countdownzeit oben einstellen
    while (i != 0) {
      for (i; i > 0; i--) {
        Serial.println(i);
        delay(60000);
      }
    }
  }
  digitalWrite(5, LOW);                                                       // LED aus
  Serial.print("\nWasserstand im Tank ist über minimum\n");                   // Textausgabe

  int humSen1 = analogRead(A1);                                               // Pinsignal in Variable Feuchtigkeitssensor speichern
  int humSen2 = analogRead(A2);                                               // Pinsignal in Variable Feuchtigkeitssensor speichern
  int humSen3 = analogRead(A3);                                               // Pinsignal in Variable Feuchtigkeitssensor speichern
  int humSen4 = analogRead(A4);                                               // Pinsignal in Variable Feuchtigkeitssensor speichern
  int humSen5 = analogRead(A5);                                               // Pinsignal in Variable Feuchtigkeitssensor speichern

  // SENSOR 1 (Blumenkasten R)
  delay(1000);                                                                // Lesepause
  if (humSen1 < value1) {                                                     // wenn Sensorwert kleiner als ... (feuchte Erde)
    Serial.print("\n1. Blumenkasten R hat ausreichend Wasser\nMesswert: ");   // Textausgabe
    Serial.println(humSen1);                                                  // Sensorwert Ausgabe
    relaiskarte.write((byte)B11111101);                                       // K7 (freies Relais)
    delay(4);                                                                 // kurzes klicken
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  } else {
    relaiskarte.write((byte)B01111110);                                       // K1,8 (Relais für Magnetventil und Pumpe)
    Serial.print("\n1. Blumenkasten R wird gegossen\nMesswert vor dem Gießen: "); // Textausgabe
    Serial.println(humSen1);                                                  // Sensorwert Ausgabe
    delay(pump);                                                              // Pumpzeit oben einstellen
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  }

  // SENSOR 2 (Blumenkasten L)
  delay(500);                                                                 // Lesepause
  if (humSen2 < value2) {                                                     // wenn Sensorwert kleiner als ... (feuchte Erde)
    Serial.print("\n2. Blumenkasten L hat ausreichend Wasser\nMesswert: ");   // Textausgabe
    Serial.println(humSen2);                                                  // Sensorwert Ausgabe
    relaiskarte.write((byte)B11111101);                                       // K7 (freies Relais)
    delay(4);                                                                 // kurzes klicken
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  } else {
    relaiskarte.write((byte)B10111110);                                       // K2,8 (Relais für Magnetventil und Pumpe)
    Serial.print("\n2. Blumenkasten L wird gegossen\nMesswert vor dem Gießen: "); // Textausgabe
    Serial.println(humSen2);                                     // Sensorwert Ausgabe
    delay(pump);                                                              // Pumpzeit oben einstellen
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  }

  // SENSOR 3 (Glas Physalis)
  delay(500);                                                                 // Lesepause
  if (humSen3 < value3) {                                                     // wenn Sensorwert kleiner als ... (feuchte Erde)
    Serial.print("\n3. Glas Physalis hat ausreichend Wasser\nMesswert: ");    // Textausgabe
    Serial.println(humSen3);                                                  // Sensorwert Ausgabe
    relaiskarte.write((byte)B11111101);                                       // K7 (freies Relais)
    delay(4);                                                                 // kurzes klicken
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  } else {
    relaiskarte.write((byte)B11011110);                                       // K3,8 (Relais für Magnetventil und Pumpe)
    Serial.print("\n3. Glas Physalis wird gegossen\nMesswert vor dem Gießen: "); // Textausgabe
    Serial.println(humSen3);                                                  // Sensorwert Ausgabe
    delay(10000);                                                             // Pumpzeit oben einstellen
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  }

  // SENSOR 4 (Topf Jostabeeren)
  delay(500);                                                                 // Lesepause
  if (humSen4 < value4) {                                                     // wenn Sensorwert kleiner als ... (feuchte Erde)
    Serial.print("\n4. Topf Jostabeeren hat ausreichend Wasser\nMesswert: "); // Textausgabe
    Serial.println(humSen4);                                                  // Sensorwert Ausgabe
    relaiskarte.write((byte)B11111101);                                       // K7 (freies Relais)
    delay(4);                                                                 // kurzes klicken
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  } else {
    relaiskarte.write((byte)B11101110);                                       // K4,8 (Relais für Magnetventil und Pumpe)
    Serial.print("\n4. Topf Jostabeeren wird gegossen\nMesswert vor dem Gießen: "); // Textausgabe
    Serial.println(humSen4);                                                  // Sensorwert Ausgabe
    delay(pump);                                                              // Pumpzeit oben einstellen
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  }

  // SENSOR 5 (Topf kleine Chilis)
  delay(500);                                                                 // Lesepause
  if (humSen5 < value5) {                                                     // wenn Sensorwert kleiner als ... (feuchte Erde)
    Serial.print("\n5. Topf kleine Chilis hat ausreichend Wasser\nMesswert: "); // Textausgabe
    Serial.println(humSen5);                                                  // Sensorwert Ausgabe
    relaiskarte.write((byte)B11111101);                                       // K7 (freies Relais)
    delay(4);                                                                 // kurzes klicken
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  } else {
    relaiskarte.write((byte)B11110110);                                       // K5,8 (Relais für Magnetventil und Pumpe)
    Serial.print("\n5. Topf kleine Chilis wird gegossen\nMesswert vor dem Gießen: "); // Textausgabe
    Serial.println(humSen5);                                                  // Sensorwert Ausgabe
    delay(pump);                                                              // Pumpzeit oben einstellen
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  }
/**/
  // ENDE
  delay(1000);                                                                // Lesepause
  relaiskarte.write((byte)B11111111);                                         // Alle Relais aus (zur Sicherheit noch mal)
  i = (looptime);                                                             // Countdownzeit oben einstellen
  while (i != 0) {
    for (i; i > 0; i--) {
      Serial.print("\nNächste Überprüfung in Minuten: ");                     // Textausgabe
      Serial.println(i);
      Serial.print("\nMesswerte der Sensoren:\n");                            // Textausgabe
      Serial.println(analogRead(A1));                                         // Sensorwert Ausgabe
      Serial.println(analogRead(A2));                                         // Sensorwert Ausgabe
      Serial.println(analogRead(A3));                                         // Sensorwert Ausgabe
      Serial.println(analogRead(A4));                                         // Sensorwert Ausgabe
      Serial.println(analogRead(A5));                                         // Sensorwert Ausgabe
      delay(60000);
    }
  }

}
