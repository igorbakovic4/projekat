# Projekat
## Implementacija komande nalik grep komandi

Komanda pronalazi reci ili delove reci koje joj prosledimo u fajlu koji prosledimo.

### Kako se koristi
Komanda se koristi pomocu komande ./find sa 2 argumenta: rec ili deo reci koji trazimo i putanja ka fajlu u kojem trazimo<br>
./find (STRING) (FAJL)

Dodatne komande:<br>
<ul>
  <li>./find -c (STRING) (FAJL) --> ispisuje broj redova iz (FAJL) u kojima se pojavljuje (STRING)</li>
  <li>./find -n (STRING) (FAJL) --> ispisuje redove iz (FAJL) u kojima se pojavljuje (STRING)</li>
  <li>./find -v (STRING) (FAJL) --> ispisuje redove iz (FAJL) u kojima se ne pojavljuje (STRING)</li>
  <li>./find -i (STRING) (FAJL) --> klasicno pretrazivanje, samo sto nije CASE-SENSITIVE</li>
  <li>./find -w (STRING) (FAJL) --> pretrazuje (STRING) ali samo gde se pojavljuje kao jedna rec</li>
</ul>
