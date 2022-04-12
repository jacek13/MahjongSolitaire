Plik README
Autor: Michal Jackowski
Wersja: Mahjong 0.17 z dnia Apr 30 2021

1. Mahjong Solitaire
Mahjong jednoosobowy to gra polegajaca na znajdowaniu par jednakowych plytek i usuwaniu ich z planszy
wedlug scisle okreslonych regul. Plytki mozna usunac tylko wtedy, gdy nie sa one zablokowane, to znaczy, 
ze plytka nie jest przykryta inna lub nie sasiaduje z lewej i prawej strony z innymi. Rozgrywka konczy
siê wtedy, gdy usuniemy wszystkie pary z planszy. 

2. Ustawienia
W celu zmiany ustawien w aktualnej wersji programu, nalezy odszukac plik 'config.txt'
Za pomoca slow kluczowych i wartosci liczbowych zmieniamy wartosci ustawien.

PRZYKLAD:
FULLSCREEN 1		 <- ustawia pelny ekran
SCREEN_WIDTH 1600	 <- ustawia szerokosc okna na 1600 pikseli
SCREEN_HEIGHT 900	 <- ustawia wysokosc okna na 900 pikseli

3. Modyfikowanie
Program umozliwia modyfikowanie warstwy video poprzez podmiane tekstur i czcionki.
Mozna to zrobic na 2 sposoby. Pierwszy polega na doslownym podmienieniu poszczegolnych plikow. 
Zachowujac te same nazwy plikow. Drugim sposobem jest modyfikowanie sciezek w plikach: 'textures_paths.txt' oraz 'font_path.txt.'
Za pomoca komend oznaczajacych odpowiednie tekstury mozemy wskazywac cale sciezki do szukanego pliku.

PRZYKLAD:
BAMBOO_THREE E:/Inne_tekstury/bamboo_3.png	 <- ustawienie sciezki dla tekstury BAMBOO_THREE
FONT E:/Inne_czcionki/Merienda-Regular.ttf	 <- ustawia sciezke do alternatywnej czcionki

4. Spis komend
W przypadku gdy pliki w folderze data zostana zle nadpisane mozesz skorzystac z ponizszej listy komend zawierajacej
wszystkie niezbedne slowa kluczowe dla poszczegolnych plikow. W razie skasowania zawartosci pliku 'readme.txt' wystarczy usunac go trwale.
Program w takim wypadku wykryje brak pliku i stworzy go na nowo

Lista komend:
1) dla pliku 'textures_paths.txt'
SIGN_RED_ONE,
SIGN_RED_TWO,
SIGN_RED_THREE,
SIGN_RED_FOUR,
SIGN_RED_FIVE,
SIGN_GREEN,
SIGN_GOLD_ONE,
SIGN_GOLD_TWO,
SIGN_GOLD_THREE,
SIGN_GOLD_FOUR,
SIGN_BLACK_ONE,
SIGN_BLACK_TWO,
SIGN_BLACK_THREE,
SIGN_BLACK_FOUR,
SIGN_RECTANGLE,
SIGNS_ONE,
SIGNS_TWO,
SIGNS_THREE,
SIGNS_FOUR,
SIGNS_FIVE,
SIGNS_SIX,
SIGNS_SEVEN,
SIGNS_EIGHT,
SIGNS_NINE,
DOTS_ONE,
DOTS_TWO,
DOTS_THREE,
DOTS_FOUR,
DOTS_FIVE,
DOTS_SIX,
DOTS_SEVEN,
DOTS_EIGHT,
DOTS_NINE,
BAMBOO_ONE,
BAMBOO_TWO,
BAMBOO_THREE,
BAMBOO_FOUR,
BAMBOO_FIVE,
BAMBOO_SIX,
BAMBOO_SEVEN,
BAMBOO_EIGHT,
BAMBOO_NINE,
DEFAULT,
SELECTED,
HELP.

2) dla pliku 'icon_path.txt'
ICON

3) dla pliku 'font_path.txt'
FONT

4) dla pliku 'pattern_path.txt'
PATTERN

5. Przykladowy wzor dla planszy:
W 12
H 8
111111111111
000001100000
000112211000
011123321110
011123321110
000112211000
000001100000
111111111111

