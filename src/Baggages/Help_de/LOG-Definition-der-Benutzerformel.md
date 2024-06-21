### Formeldefinition

Hier wird die Benutzerformel eingegeben. Es wird normale C Formelsyntax unterstützt. Es stehen die unten aufgeführten Variablen, Konstanten, Operatoren und Funktionen zur Verfügung. Das Ergebnis der Formel wird immer dem Ausgang zugewiesen.

Benutzerformeln werden immer mit dem Datentyp double (Fließkommazahl) berechnet. Alle Eingangsgrößen werden in double umgewandelt, dann wird gerechnet, anschließend wird das Ergebnis von double im Ausgangskonverter in den Ziel-DPT gewandelt.

Eine Benutzerfunktion kann aus maximal 99 Zeichen bestehen. In einer Benutzerfunktion können auch andere Benutzerfunktionen aufgerufen werden.

Um die Lesbarkeit einer Benutzerfunktion zu erhöhen, können neue Zeilen eingefügt werden. Da die ETS keine mehrzeiligen Eingabefelder zulässt, wird das gleiche Verfahren wie bei Kommentarfeldern verwendet: Die Zeichenfolge *\n*, gefolgt von einem Klick auf die Taste "Neue Zeilen aus '\n' machen".

Eine Formel kann auch mit der Taste "Formel prüfen" auf ihre syntaktische Korrektheit geprüft werden. Dies passiert durch eine Online-Verbindung mit dem Gerät selbst. Damit die Taste "Formel prüfen" verfügbar ist, muss das Gerät der ETS bekannt sein. Dafür muss es mindestens einmal programmiert worden sein.

Groß- und Kleinschreibung ist für die Formelauswertung nicht relevant. Man sollte die Formeln so notieren, dass die Lesbarkeit für einen selbst am höchsten ist.

#### Variable E1 - Eingang 1

E1 wird in der Formel als der aktuelle Wert vom Eingang 1 interpretiert. Der Wert wird generisch in eine Fließkommazahl gewandelt (double in C++) und dann mit dem Wert weitergerechnet.

#### Variable E2 - Eingang 2

E2 wird in der Formel als der aktuelle Wert vom Eingang 2 interpretiert. Der Wert wird generisch in eine Fließkommazahl gewandelt (double in C++) und dann mit dem Wert weitergerechnet.

#### Variable A - Ausgang

A wird in der Formel als der aktuelle Wert vom Ausgang interpretiert. Der Wert wird generisch in eine Fließkommazahl gewandelt (double in C++) und dann mit dem Wert weitergerechnet.

#### Konstante e - Eulersche Zahl

Die Konstante e wird mit dem Wert der Eulerschen Zahl belegt.

#### Konstante pi - Kreiszahl

Die Konstante pi wird mit dem Wert der Kreiszahl belegt.

#### Operatoren

Folgende Operatoren sind verfügbar:

* '+' - Addition
* '-' - Subtraktion
* '*' - Multiplikation
* '/' - Division
* '*' - Multiplikation
* '^' - Potenz
* '%' - Modulo
* '==' - Gleich
* '!=' - Ungleich
* '<' - Kleiner
* '<=' - Kleiner gleich
* '>' - Größer
* '>=' - Größer gleich
* '!' - Logisches 'Nicht'
* '&&' - Logisches 'Und'
* '||' - Logisches 'Oder'

#### Funktionen

Folgende Funktionen sind verfügbar:

* 'abs(x)' - Absolutwert
* 'acos(x)' - Arcuscosinus
* 'asin(x)' - Arcussinus
* 'atan(x)' - Arcustangens
* 'ceil(x)' - Aufrunden
* 'cos(x)' - Cosinus
* 'cosh(x)' - Cosinus hyperbolicus
* 'exp(x)' - Exponent 
* 'fac(x)' - Fakultät
* 'floor(x)' - Abrunden
* 'ln(x)' - natürlicher Logarithmus
* 'log(x)' - Logarithmus zur Basis 10
* 'ncr(x,y)' - ??
* 'npr(x,y)' - ??
* 'pow(x,y)' - Potenz
* 'sin(x)' - Sinus
* 'sinh(x)' - Sinus hyperbolicus
* 'sqrt(x)' - Quadratwurzel
* 'tan(x)' - Tangens
* 'tanh(x)' - Tangens hyperbolicus
* 'nan()' - Not-A-Number (liefert ungültigen Funktionswert)
* 'if(c,a,b)' - Wenn c wahr ist, dann a sonst b
* 'b*n*(e1,e2,a)' - Benutzerfunktion *n* (für n=1 bis n=30)

