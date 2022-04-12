# 1. **Mahjong Solitaire**
To gra polegająca na znajdowaniu par jednakowych płytek i usuwaniu ich z planszy
według ściśle określonych reguł. Płytki można usunać tylko wtedy, gdy nie są one zablokowane, to znaczy, że plytka nie jest przykryta inną lub nie sąsiaduje z lewej i prawej strony z innymi. Rozgrywka kończy się wtedy, gdy usuniemy wszystkie pary z planszy. 

![](../MahjongSolitaire/resources/game_demo.gif)

# 2. **Ustawienia**
W celu zmiany ustawien w aktualnej wersji programu, nalezy odszukac plik 'config.txt'. Za pomocą słów kluczowych i wartości liczbowych zmieniamy wartosci ustawień.

PRZYKŁAD:
```
FULLSCREEN 1		 <- ustawia pełny ekran
SCREEN_WIDTH 1600	 <- ustawia szerokość okna na 1600 pikseli
SCREEN_HEIGHT 900	 <- ustawia wysokość okna na 900 pikseli
```

# 3. **Modyfikowanie**
Program umożliwia modyfikowanie warstwy video poprzez podmiane tekstur i czcionki. Można to zrobić na 2 sposoby. Pierwszy polega na dosłownym podmienieniu poszczególnych plikow. Zachowując te same nazwy plików. Drugim sposobem jest modyfikowanie ścieżek w plikach: **'textures_paths.txt'** oraz **'font_path.txt.'** Za pomoca komend oznaczajacych odpowiednie tekstury mozemy wskazywac cale sciezki do szukanego pliku.

PRZYKŁAD:
```
BAMBOO_THREE E:/Inne_tekstury/bamboo_3.png	 <- ustawienie ścieżki dla tekstury BAMBOO_THREE
FONT E:/Inne_czcionki/Merienda-Regular.ttf	 <- ustawia ścieżke do alternatywnej czcionki
```

# 4. **Spis komend**
W przypadku gdy pliki w folderze **'data'** zostaną źle nadpisane możesz skorzystac z poniższej listy komend zawierajacej wszystkie niezbędne słowa kluczowe dla poszczególnych plikow. W razie skasowania zawartosci pliku **'readme.txt'** wystarczy usunąć go trwale. Program w takim wypadku wykryje brak pliku i stworzy go na nowo.

### Lista komend:
1) **dla pliku 'textures_paths.txt'**
* SIGN_RED_ONE,
* SIGN_RED_TWO,
* SIGN_RED_THREE,
* SIGN_RED_FOUR,
* SIGN_RED_FIVE,
* SIGN_GREEN,
* SIGN_GOLD_ONE,
* SIGN_GOLD_TWO,
* SIGN_GOLD_THREE,
* SIGN_GOLD_FOUR,
* SIGN_BLACK_ONE,
* SIGN_BLACK_TWO,
* SIGN_BLACK_THREE,
* SIGN_BLACK_FOUR,
* SIGN_RECTANGLE,
* SIGNS_ONE,
* SIGNS_TWO,
* SIGNS_THREE,
* SIGNS_FOUR,
* SIGNS_FIVE,
* SIGNS_SIX,
* SIGNS_SEVEN,
* SIGNS_EIGHT,
* SIGNS_NINE,
* DOTS_ONE,
* DOTS_TWO,
* DOTS_THREE,
* DOTS_FOUR,
* DOTS_FIVE,
* DOTS_SIX,
* DOTS_SEVEN,
* DOTS_EIGHT,
* DOTS_NINE,
* BAMBOO_ONE,
* BAMBOO_TWO,
* BAMBOO_THREE,
* BAMBOO_FOUR,
* BAMBOO_FIVE,
* BAMBOO_SIX,
* BAMBOO_SEVEN,
* BAMBOO_EIGHT,
* BAMBOO_NINE,
* DEFAULT,
* SELECTED,
* HELP.

2) **dla pliku 'icon_path.txt'**
* ICON

3) **dla pliku 'font_path.txt'**
* FONT

4) **dla pliku 'pattern_path.txt'**
* PATTERN

# 5. Przykładowy wzór dla planszy:
Program umożliwia wstawianie dowolnej planszy do gry przez użytkownika. 

### PRZYKŁAD:
```
W 12
H 8
PATTERN
897650056798
700000000007
600110001106
500101110105
500100100105
600100000106
700000000007
654321123456
```
### REZULTAT:

![](../MahjongSolitaire/resources/custom_pattern_example.PNG)
---

# 6. Elementy wykonane/niewykonane:
* [X] wczytywanie różnych kształtów plansz
* [X] mechanizm osiągnięć oparty na wzorcu obserwator
* [X] dokumentowanie statystyk, które generowane są do plików .CSV
* [X] umożliwienie łatwej podmiany plików graficznych, dzięki czemu szatę wizualną można dostosować samemu
* [X] odwzorowanie pełnej mechaniki [Mahjong Solitaire](https://www.kurnik.pl/mahjong/) na której się wzorowałem
* [ ] interaktywne menu graficzne
* [ ] generowanie różnych serii permutacji danej planszy tak, aby 2 graczy na różnych komputerach mogło zmierzyć się ze sobą w takich samych konfiguracjach

# 7. Źródła wykorzystywane w projekcie:
* [SDL2](https://www.libsdl.org/download-2.0.php)
* [Mahjong tileset designed by Code Inferno](www.codeinferno.com)

# 8. Autor projektu

| Imię | Nazwisko|github|
|------|---------|----|
|Michał|Jackowski|[jacek13](https://github.com/jacek13)|