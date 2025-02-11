﻿### Dokumentation


Eine vollständige Applikationsbeschreibung ist unter folgendem Link verfügbar: https://github.com/OpenKNX/OFM-LogicModule/blob/v1/doc/Applikationsbeschreibung-Logik.md

Weitere Produktinformationen sind in unserem Wiki verfügbar: https://github.com/OpenKNX/OpenKNX/wiki/Produktinfo-Logikmodul

Es gibt bis zu 99 Logikkanäle (abhängig von der Applikation, in die das Logikmodul integriert ist) mit folgenden Features:

Logikfunktionen mit bis zu 2 externen und 2 internen Eingängen

* UND
* ODER
* EXOR
* TOR/Sperre
* Zeitschaltuhr
* Schalter
* RS-Flipflop

Einstellbare Ausgangstrigger

* Bei Wertänderung am Ausgang
* Bei jedem Eingangstelegramm
* Nur beim Eingangstelegramm am Eingang 1 oder am Eingang 2

Mehrere Kanäle können zu größeren Logikblöcken zusammengefasst werden

Eingänge unterstützen DPT 1, 2, 5, 5.001, 6, 7, 8, 9, 12, 13, 14, 17

Ausgänge unterstützen zusätzlich den DPT 16

Generische Konvertierung zwischen Ein- und Ausgangs-DPT

Alle Ein- und Ausgänge können ihre Werte invertieren

Eingänge können aktiv Werte lesen

* beim Startup
* Zyklisch mit einstellbarer Zeit
* Zyklisch bis die erste Antwort kommt

Wiederholfilter: Wenn mehrfach EIN- oder AUS-Telegramme hintereinander kommen, kann man

* Alle Wiederholungen durchlassen
* Nur EIN-Wiederholungen durchlassen, AUS nur einmal
* Nur AUS-Wiederholungen durchlassen, EIN nur einmal
* EIN- und AUS-Telegramm nur einmal durchlassen

Zeitglieder am Ausgang

* Treppenlicht mit Verlängerung und vorzeitigem Ausschalten (einstellbar)
* Einschaltverzögerung mit einstellbarer Aktion bei vorzeitigem AUS/wiederholtem EIN
* Ausschaltverzögerung mit einstellbarer Aktion bei vorzeitigem EIN/wiederholtem AUS
* Blinken mit wählbarem Puls-Pausen-Verhältnis

Zyklisch senden getrennt einstellbar für EIN- und AUS-Telegramm

Ausgangsfilter: nur EIN-, nur AUS oder beides durchlassen

Ausgangskonverter

* Für EIN oder AUS wird der Wert eines anderen DPT gesendet
* Für EIN oder AUS wird der Wert eines Eingangs gesendet
* Für EIN oder AUS kann das Ergebnis einer Standardformel oder einer Benutzerformel verwendet werden

User-spezifische (mathematische) Formeln sind in die Firmware einbaubar

Sonderfunktionen

* Die Funktion "Gerät zurücksetzen" (sonst nur über die ETS machbar)
* Akustische Signalisierung über einen Buzzer (sofern entsprechende Hardware vorhanden ist)
* Optische Signalisierung mittels einer RGB-LED (sofern entsprechende Hardware vorhanden ist)

Zeitschaltuhren

* Als Jahresschaltuhr mit 4 Schaltzeiten oder als Tages-/Wochenschaltuhr mit 8 Schaltzeiten
* Feiertage berücksichtigen (oder ignorieren)
* Urlaub berücksichtigen (oder ignorieren)
* Tag/Monat berücksichtigen (bei Jahresschaltuhren)
* Wochentag/Stunde/Minute berücksichtigen (bei allen Schaltuhren)
* Sonnenstandsbezogene Schaltzeiten:
* Sonnenauf-/-untergang +/- Stunden/Minuten
* Sonnenauf-/-untergang, aber frühstens/spätestens um ...
* Sonnenauf-/-untergang, mit Angabe des Sonnenstands als Winkel über/unter dem Horizont
* Jede Stunde zu bestimmten Minuten schalten
* Jeder Schaltvorgang kann dann wie bei jedem Logikkanal auch alle Ausgangsfunktionen haben
* Beim Neustart des Logikmoduls den zeitlich letzten Schaltzeitpunkt berechnen und erneut ausgeben

Weitere Features:

* Komplexe Benutzerformeln können in der ETS eingegeben, getestet und die Ergebnisse überprüft werden. Diese Formeln können dann im Ausgangskonverter einer Logik genutzt werden.
* Ein Eingang kann intern (ohne externe GA) mit jedem KO des Moduls verbunden werden.

  * Das erlaubt große Logiken ohne den Bus Zwischenergebnissen "vollzumüllen"
  * Da jedes KO geht, kann beim Sensormodul oder Enocean-Gateway z.B. direkt ein Sensorausgang verbunden werden und mit Logiken versehen werden.

* Ein Ausgang kann nicht nur über das ihm eigentlich zugeordnete KO, sondern über einen beliebiges anderes KO senden, auch ein KO eines anderen Moduls. Dadurch kann die Logik Funktionalitäten anderer Kanäle erweitern oder mehrere Logikkanäle einen Ausgang nutzen und somit wie eine "große" Logik funktionieren.

* Ein Toreingang kann auch ein Impulseingang sein (reagiert nur auf 1, wobei Tor geöffnet und sofort geschlossen wird)

  * Erlaubt diskrete getaktete Werte auf den Bus zu senden
  * Kann zur Synchronisation von Werten genutzt werden

* Speichern von Werten über einen Stromausfall hinweg 
* Senden von gespeicherten Werten nach einem Neustart

