### Übersicht interne Verknüpfungen

Das Logikmodul erlaubt 2 Arten von internen Verknüpfungen, damit Hilfswerte und Zwischenergebnisse von Kanal zu Kanal nicht über den Bus ausgetauscht werden müssen.

Die eine Möglichkeit der Verknüpfung, genannt Interner Eingang, erlaubt es, die internen Eingänge eines Kanals mit dem internen Ausgang eines anderen Kanals zu verbinden. Dies ist unter Interne Eingänge beschrieben.

Es gibt die Möglichkeit, einen Eingang oder einen Ausgang direkt mit einem Kommunikationsobjekt (KO) zu verknüpfen (über dessen KO-Nummer) und so den Wert von diesem KO intern (statt über eine GA) zu bekommen.

Da es bei bis zu 99 Kanälen sehr schwer sein kann, den Überblick über alle intern Verknüpfungen zu behalten, soll die Übersichtstabelle auf dieser Seite dabei helfen.


### Anzeige

Das Feld Anzeige bestimmt, welche Elemente in der Tabelle dargestellt werden.

#### Mit Logikbeschriftungen

Die Tabelle zeigt neben der Spalte L*n* (*n* ist die Nummer des Logikkanals) auch den Beschriftungstext, der für diesen Kanal vergeben wurde. Dies ist die ausführlichere Variante, benötigt aber pro dargestelltem Logikkanal eine zusätzliche Zeile.

#### Ohne Logikbeschriftungen

Es gibt nur eine Spalte mit den Logiknummern L*n*, aber ohne deren Texte. Diese Darstellung ist kompakter und erlaubt es, mehr Ein- und Ausgänge und deren interne KO-Verknüpfungen pro Seite zu sehen.

#### Nur Kanäle mit Verknüpfungen

Diese Ansicht zeigt nur Logikkanäle, die auch wirklich interne Verknüpfungen enthalten. Kanäle ohne interne Verknüpfungen werden nicht dargestellt.

#### Alle Kanäle

Diese Ansicht zeigt alle definierbaren Kanäle.

### Übersichtstabelle mit internen Verknüpfungen

Die Tabelle enthält 5 Spalten und bis zu 5 Zeilen pro Logikkanal. Alle eingabebereiten Felder kommen auch so in der Kanaldefinition selbst vor und haben die gleiche Funktion.

#### Spalte 1 (ohne Überschrift)

Diese Spalte zeigt, welcher Logikkanal L*n* dargestellt wird und um welchen Eingang es geht (E1, E2, I1 oder I2).

#### Spalte Logiktext / Eingang

Die in dieser Spalte erscheinenden Textfelder enthalten die Beschriftungen, die man dem Logikkanal bzw. den Eingängen gegeben hat. Die Textfelder sind änderbar.

#### Spalte KO / Interner Eingang

Diese Spalte muss man unterschiedlich interpretieren, je nachdem, ob es sich um Eingänge mit KO-Verknüpfungen oder um interne Eingänge handelt.

Bei KO-Verknüpfungen zeigt diese Spalte die KO-Nummern der Eingänge und wie sie ermittelt werden. Der Wert "Eigenes KO" zeigt immer die dann automatisch dem Eingang zugeordnete KO-Nummer, beim Wert "Bestehendes KO" erscheint ein Eingabefeld, in dem man die KO-Nummer eingeben kann. Steht da "Relatives KO", erscheint ein Eigabefeld, in dem man die Anzahl der KO angeben kann, die man vor- oder zurückspringen möchte (relative Angabe). Hinter dem Eingabefeld steht dann die ausgerechnete KO-Nummer, bei der man dann landet. Details kann man unter Kommunikationsobjekt für Eingang nachlesen.

Bei internen Eingängen zeigt diese Spalte die Nummer des Kanals mit dessen Ausgang dieser Eingang verknüpft ist und wie dieser ermittelt wird. Beim Wert "absolut" erscheint ein Eingabefeld, in dem man die Kanalnummer des Kanals eingeben kann. Beim Wert "relativ" erscheint ein Eingabefeld, in dem man die Anzahl der Kanäle, um die man vor- oder zurückspringen will, angeben kann. Dahinter erscheint noch die Nummer des Kanals, bei dem man landet.

#### Spalte Ausgang

Das in dieser Spalte erscheinende Textfeld enthält die Beschriftung, die man dem Ausgang gegeben hat. Das Textfeld ist änderbar.

#### Spalte Kommunikationsobjekt

In dieser Spalte sieht man alle möglichen Verknüpfungen von Ausgängen mit externen KO. Dazu zählen die KO, an die der Ausgang zusätzlich zum eigenen KO senden kann (Zusatz) und die KO, deren Wert dieser Ausgang lesen und senden kann (Wert). Da es beides jeweils getrennt für das EIN- und das AUS-Signal gibt, ergeben sich bis zu 4 Zeilen "Zusatz-EIN", "Zusatz-AUS", "Wert-EIN" und "Wert-AUS"
In dieser Spalte sieht man, ob für das EIN-Signal oder das AUS-Signal ein zusätzliches KO gewählt wurde und welche Nummer es hat.

Das Auswahlfeld dahinter zeigt "Eigenes KO", falls kein zusätzliches KO gewählt wurde, gefolgt von der Nummer des eigenen KO dieses Ausgangs.
Wählt man in dem Auswahlfeld "Absolutes KO", erscheint ein Eingabefeld, in dem man die Nummer des KO angeben kann, das genutzt werden soll. Wählt man "Relatives KO", erscheint ein Eingabefeld, in dem man die Anzahl der KO angibt, die man vor- oder zurückspringen möchte. Dahinter erscheint die berechnete KO-Nummer, bei der man dann landet.
Details kann man unter Kommunikationsobjekt für Ausgang nachlesen.

