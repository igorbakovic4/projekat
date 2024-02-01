# Projekat
## Implementacija komande nalik grep komandi

Komanda pronalazi reci ili delove reci koje joj prosledimo u fajlu koji prosledimo.

### Kako se kompajlira

Kompajlira se komandom gcc na sledeci nacin: <br>

  <img src="/slike/0.png">

### Kako se koristi
Pokrece se komandom ./find sa 2 argumenta: rec (ili deo reci koji trazimo) i putanja ka fajlu u kojem trazimo, na sledeci nacin:<br>
./find (STRING) (FAJL)

<img src="/slike/1.png">
<img src="/slike/2.png">

Dodatne komande:<br>
<ul>
  <li>./find -c (STRING) (FAJL) --> ispisuje broj redova iz (FAJL) u kojima se pojavljuje (STRING)</li><br>
    <img src="/slike/3.png"><br><br>
  <li>./find -n (STRING) (FAJL) --> ispisuje redove iz (FAJL) u kojima se pojavljuje (STRING)</li><br>
    <img src="/slike/4.png"><br><br>
  <li>./find -v (STRING) (FAJL) --> ispisuje redove iz (FAJL) u kojima se ne pojavljuje (STRING)</li><br>
    <img src="/slike/5.png"><br><br>
  <li>./find -i (STRING) (FAJL) --> klasicno pretrazivanje, samo sto nije CASE-SENSITIVE</li><br>
    <img src="/slike/6.png"><br><br>
  <li>./find -w (STRING) (FAJL) --> pretrazuje (STRING) ali samo gde se pojavljuje kao jedna rec</li><br>
    <img src="/slike/7.png"><br><br>
</ul>

