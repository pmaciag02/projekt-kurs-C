# Projekt na Kurs C

### autor: Patryk Maciąg
### rodzaj projektu: gra "kolorowe kulki"



## Zasady
* Gra rozgrywa się na planszy 9x9.
* Co turę na planszy pojawiają się 3 nowe kulki, o losowych kolorach i w losowych miejscach. Pod planszą, obok sumy punktów, widnieją wylosowane kolory na następną turę.
* Ruch polega na wybraniu kulki, a następnie docelowego miejsca, do którego przesunie się kulka. Może to być dowolne miejsce na planszy, pod warunkiem, że istnieje do niego "wolna" (bez kolorów po drodze) ścieżka, składająca się z ruchów pionowych i poziomych.
* Jeśli na planszy zostanie ustawione przynajmniej 5 kulek w cięgłej linii (pion, poziom, skos), to za każdą kulkę zostaje przyznany 1 punkt, a kolory znikają z planszy.
* Cel gry: jak największa liczba zdobytych punktów.
* Gra kończy się, przy braku możliwości kolejnej tury.
* Uruchomienie gry:
	make
	./main

PS: gra nie jest najładniej/najczytelniej napisana... jak widać warto podzielić kod na kilka plików :)
