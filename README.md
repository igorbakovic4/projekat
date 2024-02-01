# Projekat
## Implementacija komande nalik grep komandi

Komanda pronalazi reci ili delove reci koje joj prosledimo u fajlu koji prosledimo.

### Kako se kompajlira

Kompajlira se komandom gcc na sledeci nacin: <br>
  --> <b>gcc find.c -o find</b> <--
  <img src="/slike/0.png">

### Kako se koristi
Komanda se koristi pomocu komande ./find sa 2 argumenta: rec (ili deo reci koji trazimo) i putanja ka fajlu u kojem trazimo, na sledeci nacin:<br>
./find (STRING) (FAJL)

<img src="/slike/1.png">
<img src="/slike/2.png">

Dodatne komande:<br>
<ul>
  <li>./find -c (STRING) (FAJL) --> ispisuje broj redova iz (FAJL) u kojima se pojavljuje (STRING)</li>
    <img src="/slike/3.png">
  <li>./find -n (STRING) (FAJL) --> ispisuje redove iz (FAJL) u kojima se pojavljuje (STRING)</li>
    <img src="/slike/4.png">
  <li>./find -v (STRING) (FAJL) --> ispisuje redove iz (FAJL) u kojima se ne pojavljuje (STRING)</li>
    <img src="/slike/5.png">
  <li>./find -i (STRING) (FAJL) --> klasicno pretrazivanje, samo sto nije CASE-SENSITIVE</li>
    <img src="/slike/6.png">
  <li>./find -w (STRING) (FAJL) --> pretrazuje (STRING) ali samo gde se pojavljuje kao jedna rec</li>
    <img src="/slike/7.png">
</ul>

