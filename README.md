# Projekat
## Implementacija funkcije nalik grep funkciji

Funkcija se naziva find i pokrece se komandom ./find

### Kako se koristi
Klasicno koriscenje: <br>
  <ul><li>./find (STRING) (FAJL)</li></ul>

Dodatne komande:<br>
<ul>
  <li>./find -c (STRING) (FAJL) --> ispisuje broj redova iz (FAJL) u kojima se pojavljuje (STRING)</li>
  <li>./find -n (STRING) (FAJL) --> ispisuje redove iz (FAJL) u kojima se pojavljuje (STRING)</li>
  <li>./find -v (STRING) (FAJL) --> ispisuje redove iz (FAJL) u kojima se ne pojavljuje (STRING)</li>
  <li>./find -i (STRING) (FAJL) --> klasicno pretrazivanje, samo sto nije case-sensitive</li>
  <li>./find -w (STRING) (FAJL) --> pretrazuje (STRING) ali samo gde se pojavljuje kao jedna rec</li>
</ul>
