  // 19.09.2022
  // -------------------- HIER WERTE EINSTELLEN --------------------

  #include <SoftwareSerial.h>
  SoftwareSerial relaiskarte(8, 9);                                           // RX, TX
  int i;                                                                      // Variable für Countdown
  int vortest = 20;                                                           // Zeit des Vortests in Sekunden
  int looptime = 120;                                                         // Nächste Überprüfung der Feuchtigkeitssensoren in Minuten
  int loopoverflow = 30;                                                      // Nächste Überprüfung des Überlaufsensors in Minuten
  int looptank = 1;                                                           // Nächste Überprüfung des Tanksensors in Minuten
  // bei diesen Sensorwerten wird jede Pflanze gegossen
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
  delay(4);
  relaiskarte.write((byte)B11111101);                                         // K7 öfnen (unbenutztes Relais)
  delay(200);                                                                 // kurzes klicken
  relaiskarte.write((byte)B11111111);                                         // Alle Relais aus
  delay(200);
  relaiskarte.write((byte)B11111101);                                         // K7 öfnen (unbenutztes Relais)
  delay(200);
  relaiskarte.write((byte)B11111111);                                         // Alle Relais aus
  delay(100);                                                                 // Sicherheitspause

  // ARDUINO BAUD RATE UND PINBELEGUNG
  Serial.begin(9600);                                                         // Serial-Port öffnen und auf 9600 Baud setzen
  pinMode(A1, INPUT);                                                         // Pin A1 Analog IN (Feuchtigkeitssensor1)
  pinMode(A2, INPUT);                                                         // Pin A2 Analog IN (Feuchtigkeitssensor2)
  pinMode(A3, INPUT);                                                         // Pin A3 Analog IN (Feuchtigkeitssensor3)
  pinMode(A4, INPUT);                                                         // Pin A4 Analog IN (Feuchtigkeitssensor4)
  pinMode(A5, INPUT);                                                         // Pin A5 Analog IN (Feuchtigkeitssensor5)
  pinMode(5, OUTPUT);                                                         // Pin 5 Digital OUT (LED)
  pinMode(6, INPUT);                                                          // Pin 6 Digital IN (Überlaufsensor)
  pinMode(7, INPUT_PULLUP);                                                   // Pin 7 Digital IN (Schwimmerschalter Wassertank)

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
  Serial.print("Zeit des Vortests in Sekunden\n");                            // Textausgabe
  Serial.println(vortest);                                                    // Wertausgabe
  Serial.print("Zeit der gesamten Schleife in Minuten\n");                    // Textausgabe  
  Serial.println(looptime);                                                   // Wertausgabe
  Serial.print("Zeit der nächsten Überlaufsensorüberprüfung bei Überschwämmung in Minuten\n"); // Textausgabe
  Serial.println(loopoverflow);                                               // Wertausgabe
  Serial.print("Zeit der nächsten Wasserstandsüberprüfung bei leerem Tank in Minuten\n"); // Textausgabe
  Serial.println(looptank);                                                   // Wertausgabe
  Serial.print("Gießwerte der einzelnen Sensoren\n");                         // Textausgabe
  Serial.println(value1);                                                     // Wertausgabe
  Serial.println(value2);                                                     // Wertausgabe
  Serial.println(value3);                                                     // Wertausgabe
  Serial.println(value4);                                                     // Wertausgabe
  Serial.println(value5);                                                     // Wertausgabe
  Serial.print("Zeit des Gießens in Milisekunden\n");                         // Textausgabe
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

  // SENSOR 1 (Blumenkasten R)
  delay(1000);                                                                // Lesepause
  int Feuchtigkeitssensor1 = analogRead(A1);                                  // Pinsignal in Variable Feuchtigkeitssensor speichern
  int Prozentwert1 = map(Feuchtigkeitssensor1, 30, 600, 100, 0);              // ungefähre Prozentangabe durch Mapping
  Serial.print("\n\nPflanze 1 (Blumenkasten R) \nFeuchtigkeit in prozent: "); // Textausgabe
  Serial.println(Prozentwert1);                                               // Ausgabe Prozentwert
  Serial.print("Messwert: ");                                                 // Textausgabe
  Serial.println(Feuchtigkeitssensor1);                                       // Sensorwert Ausgabe
  if (Feuchtigkeitssensor1 < value1) {                                        // wenn Wert kleiner als ... (feuchte Erde)
    Serial.print("Pflanze 1 hat ausreichend Wasser\n");                       // Textausgabe
    relaiskarte.write((byte)B11111101);                                       // K7 (unbenutztes Relais)
    delay(4);                                                                 // kurzes klicken
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  } else {
    relaiskarte.write((byte)B01111110);                                       // K1,8 (Relais für Magnetventil und Pumpe)
    Serial.print("Pflanze 1 wird gegossen\n");                                // Textausgabe
    delay(pump);                                                              // Pumpzeit oben einstellen
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  }

  // SENSOR 2 (Blumenkasten L)
  delay(1000);                                                                // Lesepause
  int Feuchtigkeitssensor2 = analogRead(A2);                                  // Pinsignal in Variable Feuchtigkeitssensor speichern
  int Prozentwert2 = map(Feuchtigkeitssensor2, 30, 600, 100, 0);              // ungefähre Prozentangabe durch Mapping
  Serial.print("\nPflanze 2 (Blumenkasten L) \nFeuchtigkeit in prozent: ");   // Textausgabe
  Serial.println(Prozentwert2);                                               // Ausgabe Prozentwert
  Serial.print("Messwert: ");                                                 // Textausgabe
  Serial.println(Feuchtigkeitssensor2);                                       // Sensorwert Ausgabe
  if (Feuchtigkeitssensor2 < value2) {                                        // wenn Wert kleiner als ... (feuchte Erde)
    Serial.print("Pflanze 2 hat ausreichend Wasser\n");                       // Textausgabe
    relaiskarte.write((byte)B11111101);                                       // K7 (unbenutztes Relais)
    delay(4);                                                                 // kurzes klicken
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  } else {
    relaiskarte.write((byte)B10111110);                                       // K2,8 (Relais für Magnetventil und Pumpe)
    Serial.print("Pflanze 2 wird gegossen\n");                                // Textausgabe
    delay(pump);                                                              // Pumpzeit oben einstellen
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  }

  // SENSOR 3 (Glas Physalis)
  delay(1000);                                                                // Lesepause
  int Feuchtigkeitssensor3 = analogRead(A3);                                  // Pinsignal in Variable Feuchtigkeitssensor speichern
  int Prozentwert3 = map(Feuchtigkeitssensor3, 30, 600, 100, 0);              // ungefähre Prozentangabe durch Mapping
  Serial.print("\nPflanze 3 (Glas Physalis) \nFeuchtigkeit in prozent: ");    // Textausgabe
  Serial.println(Prozentwert3);                                               // Ausgabe Prozentwert
  Serial.print("Messwert: ");                                                 // Textausgabe
  Serial.println(Feuchtigkeitssensor3);                                       // Sensorwert Ausgabe
  if (Feuchtigkeitssensor3 < value3) {                                        // wenn Wert kleiner als ... (feuchte Erde)
    Serial.print("Pflanze 3 hat ausreichend Wasser\n");                       // Textausgabe
    relaiskarte.write((byte)B11111101);                                       // K7 (unbenutztes Relais)
    delay(4);                                                                 // kurzes klicken
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  } else {
    relaiskarte.write((byte)B11011110);                                       // K3,8 (Relais für Magnetventil und Pumpe)
    Serial.print("Pflanze 3 wird gegossen\n");                                // Textausgabe
    delay(10000);                                                             // Pumpzeit oben einstellen
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  }

  // SENSOR 4 (Topf Jostabeeren)
  delay(1000);                                                                // Lesepause
  int Feuchtigkeitssensor4 = analogRead(A4);                                  // Pinsignal in Variable Feuchtigkeitssensor speichern
  int Prozentwert4 = map(Feuchtigkeitssensor4, 200, 600, 100, 0);             // ungefähre Prozentangabe durch Mapping
  Serial.print("\nPflanze 4 (Topf Jostabeeren) \nFeuchtigkeit in prozent: "); // Textausgabe
  Serial.println(Prozentwert4);                                               // Ausgabe Prozentwert
  Serial.print("Messwert: ");                                                 // Textausgabe
  Serial.println(Feuchtigkeitssensor4);                                       // Sensorwert Ausgabe
  if (Feuchtigkeitssensor4 < value4) {                                        // wenn Wert kleiner als ... (feuchte Erde)
    Serial.print("Pflanze 4 hat ausreichend Wasser\n");                       // Textausgabe
    relaiskarte.write((byte)B11111101);                                       // K7 (unbenutztes Relais)
    delay(4);                                                                 // kurzes klicken
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  } else {
    relaiskarte.write((byte)B11101110);                                       // K4,8 (Relais für Magnetventil und Pumpe)
    Serial.print("Pflanze 4 wird gegossen\n");                                // Textausgabe
    delay(pump);                                                              // Pumpzeit oben einstellen
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  }

  // SENSOR 5 (Topf kleine Chilis)
  delay(1000);                                                                // Lesepause
  int Feuchtigkeitssensor5 = analogRead(A5);                                  // Pinsignal in Variable Feuchtigkeitssensor speichern
  int Prozentwert5 = map(Feuchtigkeitssensor5, 30, 600, 100, 0);              // ungefähre Prozentangabe durch Mapping
  Serial.print("\nPflanze 5 (Topf kleine Chilis) \nFeuchtigkeit in prozent: "); // Textausgabe
  Serial.println(Prozentwert5);                                               // Ausgabe Prozentwert
  Serial.print("Messwert: ");                                                 // Textausgabe
  Serial.println(Feuchtigkeitssensor5);                                       // Sensorwert Ausgabe
  if (Feuchtigkeitssensor5 < value5) {                                        // wenn Wert kleiner als ... (feuchte Erde)
    Serial.print("Pflanze 5 hat ausreichend Wasser\n");                       // Textausgabe
    relaiskarte.write((byte)B11111101);                                       // K7 (unbenutztes Relais)
    delay(4);                                                                 // kurzes klicken
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  } else {
    relaiskarte.write((byte)B11110110);                                       // K5,8 (Relais für Magnetventil und Pumpe)
    Serial.print("Pflanze 5 wird gegossen\n");                                // Textausgabe
    delay(pump);                                                              // Pumpzeit oben einstellen
    relaiskarte.write((byte)B11111111);                                       // Alle Relais aus
  }

  // ENDE
  delay(1000); // Lesepause
  i = (looptime);                                                             // Countdownzeit oben einstellen
  while (i != 0) {
    for (i; i > 0; i--) {
      Serial.print("\nNächste Überprüfung sobald der Countdown abläuft (Angaben in Minuten)\n");  // Textausgabe
      Serial.println(i);
      delay(1000);                                                            // Lesepause
      Serial.print("\nMesswerte der Sensoren:\n");                            // Textausgabe
      Serial.println(analogRead(A1));                                         // Sensorwert Ausgabe
      Serial.println(analogRead(A2));                                         // Sensorwert Ausgabe
      Serial.println(analogRead(A3));                                         // Sensorwert Ausgabe
      Serial.println(analogRead(A4));                                         // Sensorwert Ausgabe
      Serial.println(analogRead(A5));                                         // Sensorwert Ausgabe
      delay(59000);
    }
  }

}
