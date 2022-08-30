# Plant-Watering-System

## Pflanzen Bewässerungssystem für 5 Pflanzen
von Niko

[Arduino UNO](https://www.ebay.de/itm/144138039161)

Pin A1 bis A5 Feuchtigkeitssensoren für die Erde

[Analog Capacitive Soil Moisture Sensor](https://www.ebay.de/itm/164657628668)


Pin 6 Überlaufsensor
[YL-69 Feuchtigkeitssensor (nicht perfekt da kabel korrodieren aber bis jetzt keine Alternative)](https://www.ebay.de/itm/203252815145)

Pin 7 Tanküberprüfung
[Schwimmerschalter Pegelschalter Füllstandsschalter SensorSchwimmerNiveauschalter](https://www.ebay.de/itm/384891203932)

Relaiskarte (diese würde ich nicht empfehlen da die Karte fehlerhaft ist, benötigt aber nur 2 Signalleitungen und Strom)

[ICStation ICSE014A 8 Channel, Micro USB, DC 5V, 700mA](http://www.icstation.com/icstation-channel-icse014a-micro-switch-relay-module-upper-computer-control-board-icse014a-p-5185.html)

[Alternative Relaiskarte (benötigt 8x output vom Arduino und Strom)](https://www.ebay.de/itm/252355367721)

[Wasserpumpe bürstenlos 12V, 350mA, 4,2W, 240L/h, Hubhöhe 3m, Anschlüsse da = 8mm, Maße lxbxh=55x37x43mm](https://www.ebay.de/itm/353246497633)

  Magnetventile 12V, <160mA, <3W, 0,6Bar, N/C (normaly closed), Anschlüsse da = 4mm
  https://www.ebay.de/itm/352962597146

  StepDown Regler 12V zu 5V, 3A max. USB
  https://www.ebay.de/itm/162759316733

  StepUp Regler 5V zu 12V
  https://www.ebay.de/itm/201278090992

  5x Dioden z.B. 1N4004
  (Rote) LED (zeigt leeren Tank und/oder Überlauf an)
  Im Elektroladen oder im Netz

  Kabel mit kleinem Querschnitt 0,75mm²?
  ca. 10m Rot (Sensoren, Magnetventile, sonstiges)
  ca. 10m Schwarz (Sensoren, Magnetventile, sonstiges)
  ca. 4m Gelb (Sensorensignal)
  ca. 4m für das Überlaufsensor Kabel

  Schläuche
  ca.2m di=4mm
  ca.6m di=8mm
  Im Baumarkt oder im Netz kaufen

  Schlauchverbinder
  4x T-Stück 8mm
  5x Adapter von 8mm auf 4mm
  https://www.ebay.de/itm/311415522853


  Kanister min. 10L
  Im Baumarkt oder im Netz kaufen

Tipps

1. Länge der Schläuche und Kabel muss jeder für sich berechnen. Wenn die Pflanzen nebeneinander stehen reichen die Längen die ich angegeben habe für fünf Pflanzen
2. Die 4mm Schläuche sollten so kurz wie möglich sein da sonst der Druck abfällt ???
3. Alle Schläuche sollten etwas härter sein damit sie nicht knicken
4. Tropfer sehen cool aus aber es geht auch mit dem Schlauch in der Erde
5. Darauf achten dass die Pumpe durch die Öffnung des Kanisters passt
6. Die Dioden werden unbedingt benötigt da der Arduino sonst von der Selbstinduktionsspannung der Magnetventile einen Stromschlag bekommt (trotz der Relais)
7. StepDown oder StepUp Regler kaufen je nach dem ob man ein 5V oder ein 12V Netzteil hat. Man kann auch eine Powerbank und ein Solarmodul statt einem Netzteil nutzen. Es wäre vom Vorteil wenn die Powerbank gleichzeitig laden und entladen kann sonst wird nur gegossen wenn die Sonne nicht scheint.
8. Der Arduino Uno hat sechs analoge Eingänge für die Feuchtigkeitssensoren. somit könnte man sechs Pflanzen bewässern.
9. Die Feuchtigkeitssensoren für die Erde sind nicht ganz präzise und müssten für jede Pflanze selbst eingestellt werden. Wenn die Elektronik des Sensors nass wird meldet er dem Arduino "Trocken" und übergießt die Pflanzen. Daher ist der Überlaufsensor sinnvoll. Bei Benutzung von Tropfern sollte man die Sensoren vor Wasser schützen z.B. alte Deckel in denen man ein Loch für die Kabel bohrt


Preise Stand 08.2022
13  Kanister
8   Pume
30  Schläuche
14  Schlauchverbinder
30  5x Magnetventile
9   StepUp Regler (StepDown 3)
10  Arduino Uno
10  Relaiskarte 8 Kanäle
7   5x Feuchtigkeitssensoren
3   Uberlaufsensor
5   Tanksensor
20  Kabel
1   5x Dioden + LED

160€ Summe
