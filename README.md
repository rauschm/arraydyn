# arraydyn
Arrays in C++ sind statisch, die Größen der einzelnen Dimensionen müssen zur
Compilezeit bekannt sein. Das Template **Araydyn**<T,N> bietet dynamische Arrays,
bei denen zur Compilezeit nur der Typ **T** und die Anzahl der Dimensionen **N**
bekannt sein  müssen.
```
size_t d = 8;
Arrraydyn<int,3>  wuerfel(d,d,d);
```
Der Zugriff auf die dynamischen Arrays erfolgt aber weiterhn in der üblichen Form:
```
wuerfel[1][2][3] = 42;
```
Der Datentyp ist sehr leichtgewichtig. Er bietet nur:
+ Allokierung von Speicher (im Konstruktor)
+ Freigabe des allokierten Speichers (im Destruktor)
+ Zugriff in der C/C++-üblichen Notation
+ Konvertierung in einen Pointer auf das erste Element

Insbesondere werden für die Array-Elemente keine Konstruktoren und Destruktoren aufgerufen
und es findet auch sonst keinerlei Intialisierung des allokierten Speichers statt.

Dafür ist die Performance hervorragend. Bei Verwendung des GCC ist sie identisch mit der
bei statischen Arrays. Bei MSVC ist sie leider nur halb so schnell.
