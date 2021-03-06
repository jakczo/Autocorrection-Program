# <p align="center"> Autocorrection-program (November 2017) </p>
C++/Assembler language program simulating the operation of autocorrect using the Levenshtein (Editing Distance) Algorithm. 
Below I place a copy of the final report (in Polish language) containing all the information about the Autocorrection Program.


# <p align="center"> Miara odległości edycyjnej z wykorzystaniem algorytmu Levenshteina </p>

## Spis treści:

### 1. [Temat projektu](#-1-temat-projektu-): 
   - [Opis zasady działania algorytmu Levenshteina](#opis-zasady-dzia%C5%82ania-algorytmu-levenshteina-krok-po-kroku) 
   - [Analiza zadania, modyfikacja algorytmu, uzasadnienie](#analiza-zadania-modyfikacja-algorytmu-uzasadnienie)
   - [Założenia projektowe](#za%C5%82o%C5%BCenia-projektowe)
   - [Funkcjonalność programu](#funkcjonalno%C5%9B%C4%87-programu)

### 2. [Specyfikacja wewnętrzna](#-2-specyfikacja-wewn%C4%99trzna-):
   - [Opis programu w języku wysokiego poziomu](#opis-programu-w-j%C4%99zyku-wysokiego-poziomu)
   - [Opis funkcji bibliotek DLL](#opis-funkcji-z-bibliotek-dll)
   - [Schemat blokowy algorytmu](#schemat-blokowy-algorytmu)

### 3. [Specyfikacja zewnętrzna](#-3-specyfikacja-zewn%C4%99trzna-programu-):
   - [Struktura danych wejściowych](#struktura-danych-wej%C5%9Bciowych)
   - [Komunikaty](#komunikaty)

### 4. [Uruchamianie i testowanie](#-4-uruchamianie-i-testowanie-):
   - [Testowanie](#testowanie)
   - [Wyniki czasowe](#wyniki-czasowe)

### 5. [Analiza działania programu](#-5-analiza-dzia%C5%82ania-programu-)

### 6. [Wnioski](#-6-wnioski-)

## <p align="center"> 1. Temat projektu </p>

Tematem projektu było napisanie programu używającego algorytmu Levenshteina do znalezienia słowa o najmniejszej odległości edycyjnej, względem słowa wpisanego przez użytkownika.
   
#### Opis zasady działania algorytmu Levenshteina krok po kroku:

Algorytm Levenshteina służy do liczenia odległości edycyjnej między dwoma wyrazami, czyli najmniejszej liczby działań prostych (wstawienie, usunięcie lub zamiana znaku), dzięki którym można przekształcić jeden ciąg znaków w drugi.

Na początek, przytoczę matematyczną definicję algorytmu Levenshteina:

![Alt text](images/1.png?raw=true "matematyczna definicja algorytmu Levenshteina. Źródło: Wikipedia.")
 
Wytłumaczenie:

Aby obliczyć odległość edycyjną algorytmem Levenshteina, należy utworzyć tablicę o wymiarach n+1 na m+1, gdzie n i m to odpowiednio długości porównywanych ciągów znaków. Pierwszą kolumnę i wiersz wypełniamy wartościami od 0 do odpowiednio n i m, gdzie wartość 0 jest dla nich wspólna. Następnie bierzemy kolejne wartości wiersza i porównujremy literkę dotyczącą tego wiersza z literką dotyczącą kolumny. Dokonujemy porównania liter na zasadzie każdy z każdym. Przy każdym porównaniu ustawiany jest koszt: jeśli literki są identyczne, to koszt wynosi 0, jeśli nie, to 1. Po porównaniu możemy przystąpić do wypełnienia komórki wartością, która jest minimum z:

- wartości komórki leżącej bezpośrednio nad naszą aktualną komórką zwiększonej o 1
- wartości komórki leżącej bezpośrednio na lewo od naszej aktualnej komórki zwiększonej o 1
- wartości komórki leżącej bezpośrednio w lewą-górną stronę od aktualnej komórki + koszt

Po wykonaniu wszystkich porównań, naszą odległością edycyjną będzie wartość w komórce [n+1,m+1].
Jako przykład, obliczę odległość edycyjną dwóch słów: kot i pies.

![Alt text](images/2.png?raw=true "wizualizacja macierzy wartości w Algorytmie Levenshteina. Źródło – wykonanie własne.")

Zdjęcie przedstawia tablicę (macierz) 4 x 5 której wymiary obliczyliśmy poprzez dodanie do długości słowa „kot” liczby „1”: (3 + 1 = 4) oraz do długości słowa „pies” liczby „1”: (4+1 = 5).
Mając tablicę 4 x 5, pierwszą wartością jaką obliczamy, jest wartość komórki (1,1) – wspólna komórka kolumny o indeksie „1” i wiersza o indeksie „1”. Wyciągamy teraz minimum z wartości:
						
- komórka po lewej (1,0) = 1 i dodajemy do niej 1 = 2
- komórka powyżej (0,1) = 1 i dodajemy do niej 1 = 2
- komórka na lewy-górny ukos od naszej (0,0) = 0 i dodajemy koszt = 1, gdyż „K” =/= „P”

Tak więc MIN(2, 2, 1)  = 1 i taką wartość wpisujemy do komórki (1,1).

![Alt text](images/3.png?raw=true "wizualizacja macierzy wartości w Algorytmie Levenshteina –wypełnienie pierwszej komórki. Źródło – wykonanie własne.")

Teraz przesuwamy się komórkę niżej do następnego wiersza. Tą komórkę (2,1) wypełnimy wartością minimum z wartości:

- komórka po lewej (2,0) = 2 i dodajemy do niej 1 = 3
- komórka powyżej (1,1)=1 i dodajemy do niej 1 = 2
- komórka na lewy-górny ukos od naszej (1,0)=1 i dodajemy do niej koszt = 1, gdyż „O” =/= „P”

MIN(3, 2, 2) = 2 i to wpisujemy do aktualnej komórki (2,1).

![Alt text](images/4.png?raw=true "wizualizacja macierzy wartości w Algorytmie Levenshteina – wypełnienie drugiej komórki. Źródło – wykonanie własne.")

Analogicznie robimy dla komórki (3,1), której wartość to będzie MIN(4, 3, 3) = 3.

![Alt text](images/5.png?raw=true "wizualizacja macierzy wartości w Algorytmie Levenshteina – wypełnienie pierwszej kolumny wartości. Źródło – wykonanie własne.")

Teraz przechodzimy do kolejnej kolumny, wybieramy pierwszą komórkę (1,2), wybieramy minimum z wartości po lewej (1+1=2), powyżej (2+1=3) i na ukos (1+koszt (=1, bo „K” =/= „I”) = 2), 
czyli MIN(2, 3, 2) = 2 i wpisujemy.

![Alt text](images/6.png?raw=true "wizualizacja macierzy wartości w Algorytmie Levenshteina – kontynuacja. Źródło – wykonanie własne. ")

Czynność wykonujemy, aż nie wypełnimy całej tablicy.

![Alt text](images/7.png?raw=true "wizualizacja macierzy wartości w Algorytmie Levenshteina – rezultat. Źródło – wykonanie własne.")

Wartość w ostatniej komórce naszej tablicy, w tym przypadku (3,4), jest naszą odległością edycyjną, co oznacza, że aby słowo „KOT” zamienić przy użyciu operacji prostych w słowo „PIES” należy wykonać co najmniej 4 takie operacje.

#### Analiza zadania, modyfikacja algorytmu, uzasadnienie:

Algorytm obliczający odległość Levenshteina napisany w pseudokodzie:

![Alt text](images/8.png?raw=true "algorytm Levenshteina przedstawiony za pomocą pseudokodu. Źródło – Wikipedia.")

Tak jak widać w powyższym pseudokodzie, funkcja wykonująca algorytm Levenshteina musi przyjmować dwa słowa, które są tutaj reprezentowane jako tablica typu char o ilości elementów odpowiednio m i n. Następnie funkcja musi stworzyć macierz o wspomnianych na początku wymiarach m+1 na n+1. Pierwsza pętla wypełni „zerową” kolumnę indeksami, a druga pętla „zerowy” wiersz, zgodnie z początkowymi ustaleniami. Punktem kulminacyjnym są dwie pętle, jedna zagnieżdżona w drugiej, które będą przechodzić po kolejnych elementach tablicy używając zmiennych używanych do iterowania jako indeksów tablicy. Na samym końcu funkcja zwraca zawartość ostatniego elementu tablicy tam, gdzie funkcja została wywołana.

Modyfikacje algorytmu:

Już na starcie projektowania mojego programu zauważyłem, że przekazywane do funkcji tablice znaków będą różne i z góry nie jestem stwierdzić ile ich będzie i jak długie będą, stąd pamięć potrzebną na przechowywanie elementów tablicy zdecydowałem się alokować dynamicznie. Ta zmiana wpłynęła na kolejny aspekt mojego projektu, jakim było zaalokowanie dynamicznie tablic w bibliotekach. Na początku założyłem sobie, że zadania w projekcie rozdzielę tak: częścią obliczeniową zajmą się biblioteki napisane w C++ i Asemblerze, a całą resztą główna część programu, toteż założyłem, że tworzeniem tablicy również może zająć się główny program, a sama funkcja obliczająca odległość edycyjną będzie otrzymywała oprócz słów, referencję na wskaźnik na tablicę, a jeśli decyduję się deklarować tablicę poza bibliotekami, w funkcji już nie będę musiał sprawdzać długości ciągu znaków - zrobię to wcześniej, w programie głównym, aby móc zadeklarować odpowiednią ilość wierszy i kolumn, a następnie przekaże obliczone długości jako argumenty funkcji, aby znała długość słów.

Gdy doszedłem do projektowania funkcji w asemblerze, napotkałem kolejny problem, który wpłynął na zmodyfikowanie nie tylko argumentów przekazywanych funkcji, ale także algorytmu:

![Alt text](images/9.png?raw=true "graficzne przedstawienie rozkładu pamięci podczas deklarowania tablicy statycznej i dynamiczne. Źródło – wykonanie własne.")

Powyższe zdjęcie obrazuje zasadę alokowania pamięci dla tablic statycznych, dynamicznych jednowymiarowych i dynamicznych wielowymiarowych.

Z założenia sama nazwa tablicy, jest też wskaźnikiem na pierwszy jej element, toteż nie dziwi fakt, że dynamicznie alokowana tablica jednowymiarowa nie różni się zasadą działania od tej alokowanej statycznie. Wskaźnik będący na stosie wskazuje na pierwszy element tablicy zaalokowany w pamięci. Wszystko zmienia się, gdy do deklarowania tablicy dynamicznej, wielowymiarowej używam wskaźnika na tablicę wskaźników itd. W moim programie potrzebuję dwuwymiarowej tablicy, więc dynamicznie zaalokowana tablica byłaby wskaźnikiem na tablicę wskaźników na elementy. To powoduje, że wskaźnik na tablicę wskaźników mam na stosie, więc nie ma problemu z poruszaniem się po tablicy wskaźników w pamięci, natomiast dostanie się do wartości w tablicach, na które wskazują wskaźniki z tablicy wskaźników czyni nie lada gratkę. Taka pamięć nie jest zaalokowana koło siebie, jak to jest przy statycznych tablicach, tylko jest rozmieszczona w różnych miejscach pamięci – tam, gdzie akurat było wystarczająco wolnego miejsca. O ile napisanie funkcji w języku C++, która będzie operować na tak podanych wartościach, nie jest zbytnim problemem, tak napisanie funkcji w języku asemblera jest problematyczne. Moim celem było dostawanie się do odpowiednich wartości zaalokowanych w tablicy, dodając offset tyle razy, aż się dostanę do właściwego elementu.
Podsumowując potrzebowałem alokować pamięć dynamicznie i mieć wszystko w jednym miejscu, aby bezproblemowo się poruszać po zaalokowanych elementach tablicy. Odpowiednim rozwiązaniem było wyeliminowanie tablicy dwuwymiarowej o wymiarach m+1 na n+1 i zastąpienie jej tablicą jednowymiarową o długości (m+1) * (n+1). 

To pociągnęło za sobą konieczność zmiany alogrytmu obsługującego taki model:

![Alt text](images/10.png?raw=true "wizualizacja macierzy wartości w Algorytmie Levenshteina przed modyfikacją. Źródło – wykonanie własne.")

na algorytm obsługujący taki model:

![Alt text](images/11.png?raw=true "wizualizacja macierzy wartości w Algorytmie Levenshteina po zmodyfikowaniu. Źródło – wykonanie własne.")

W rezultacie potrzebowałem tylko przechowywać adres pierwszego elementu w wybranym rejestrze, a następnie wedle uznania poruszanie się przy użyciu offsetu (przesunięcia względem początku) poruszałem się po tablicy.

#### Założenia projektowe:

- Projekt składa się z trzech części: programu głównego napisanego w c++ oraz dwóch bibliotek dll napisanych w c++ i asemblerze;
- Użytkownik wybiera bibliotekę (C++ i ASM) oraz ilość wątków (od 1 do 64);
- Użytkownik wpisuje ciąg znaków, program wypisuje ciąg znaków o najmniejszej odległości edycyjnej;
- Wczytanie pliku z liczbą 1000 oraz 2,5 mln wyrazów oraz losowych sekwencji DNA o różnych długościach;
- Dynamiczna alokacja (zmienna liczba danych o zmiennej długości);
- Program wykonuje operuje na macierzy m+1 na n+1 zastąpionej tablicą jednowymiarową o długości (m+1) * (n+1).
- Jeśli jest więcej słów o tej samej długości, zostanie wypisane ostatnie wyliczone słowo;

#### Funkcjonalność programu:

Program powinien dzielić się na dwie części: program główny napisany w języku C++ oraz dwie biblioteki, z których jedna napisana jest również w języku C++, a druga w języku asemblera.
Program główny ma wczytywać dane z pliku zewnętrznego, umożliwiać podstawową komunikację na poziomie użytkownik – program, program – użytkownik, obslugiwać wielowątkowość. Ponadto główny program powinien prowadzić pomiar czasu od zainicjalizowania pierwszego wątku, do zakończenia ostatniego wątku (nie wliczając czasu wczytywania danych), ma umożliwić użytkownikowi wybór biblioteki, której program ma użyć do obliczenia odległości edycyjnej oraz wybór liczby wątków (od 1 do 64). Biblioteki napisane w C++ i Asemblerze mają za zadanie obliczyć odległość edycyjną między dwoma ciągami znaków z użyciem zaimplementowanego algorytmu i następnie zwrócenie wyniku do funkcji wywołującej.

## <p align="center"> 2. Specyfikacja wewnętrzna </p>

#### Opis programu w języku wysokiego poziomu:

Część wysokopoziomowa programu została napisana w C++. Interfejs użytkownika wyświetlany jest w konsoli. Za zarządzanie wielowątkowością w aplikacji odpowiedzialna jest klasa Thread. Użytkownik może wybrać bibliotekę, której chce użyć wybierając jedną z dwóch dostępnych opcji podczas startu programu. Wczytywanie wyborów użytkownika jest zabezpieczone na wypadek wpisania nieprawidłowych informacji lub nieprawidłowej ilości wątków. Program zaczyna swe obliczenia po wybraniu przez użytkownika liczby wątków.
	
#### Opis funkcji z bibliotek DLL:

Funkcja Levenshtein występująca w obu wersjach biblioteki służy obliczaniu odległości edycyjnej dwóch ciągów znaków przy użyciu zaimplementowanego algorytmu Levenshteina. Funkcja będąca w bibliotekach zajmuje się w programie częścią stricte matematyczną. Przyjmuje ona jako parametry wskaźnik na tablicę jednowymiarową, przekształconą z macierzy dwuwymiarowej, używaną do obliczenia odległości edycyjnej, wskaźniki na wybrane tablice znaków, które wcześniej zostały wczytane z pliku wejściowego oraz długości tych tablic wymagane do zapętlania operacji na tablicy. Jako wynik otrzymujemy odległość edycyjną, która jest zapisana po wykonaniu algorytmu w ostatniej komórce tablicy.
W wersji asemblerowej starałem się trzymać konwencji odpowiedniego korzystania z rejestrów, to znaczy przykładowo zmienne licznikowe były przetwarzane w rejestrze licznikowym RCX, rejestr RAX służył mi do operacji arytmetycznych, RSI jako wskaźnik źródła, a RBP jako wskaźnik do danych w segmencie stosu, gdy używałem zmiennych lokalnych znajdujących się na stosie. Z powodu dużej ilości danych wejściowych, na starcie musiałem zająć rejestry RSI, gdzie zapisałem adres pierwszego elementu tablicy matrix, R11 gdzie zapisałem adres tablicy znaków s1, analogicznie w R12 zapisałem adres dla s2, jako, rejestr R9 z wartością dimension_1 nadpisałem wynikiem operacji dimension_1 x dimension_2, natomiast w R10 zapisałem wartość dimension_2. Gdy zaczęło mi brakować rejestrów, korzystałem z przesunięcia bitowego – rejestrów 64bitowych używałem jako dwóch rejestrów 32bitowych, gdzie na młodszej połówce zapisywalem zmienną, której wartość nie przekraczała 32 bitów, następnie przesuwałem zawartość rejestru o 32 bity w lewo i żeby nie utracić przechowywanej wartości, dodawałem zmienną 32bitową w formie 64bitowej do rejestru.
	
#### Schemat blokowy algorytmu:


![Alt text](images/12.png?raw=true "schemat blokowy funkcji w DLL. Źródło – wykonanie własne.")

## <p align="center"> 3. Specyfikacja zewnętrzna programu </p>

#### Struktura danych wejściowych:

Dane wejściowe zawarte są w jednym pliku .txt. Na pojedynczy zestaw danych wejściowych składa się 1000 wyrazów w języku angielskim i kilkanaście sekwencji DNA.

![Alt text](images/13.png?raw=true "przykład danych wejściowych. Źródło – wykonanie własne.")

![Alt text](images/14.png?raw=true "przykład danych wejściowych. Źródło – wykonanie własne.")

#### Komunikaty:

Podczas używania programu użytkownik widzi komunikaty w oknie konsoli. Komunikaty dotyczą wyboru biblioteki, podania liczby wątków, podania ciągu znaków lub sekwencji DNA, rezultatu działania programu lub braku pliku wejściowego.
	
## <p align="center"> 4. Uruchamianie i testowanie </p>

#### Testowanie:

Dane wejściowe testowe do pomiarów:

![Alt text](images/15.png?raw=true "przykład danych testowych. Źródło – wykonanie własne.")

Założenia dotyczące danych testowych:
- Ciągi znaków są różnej długości.
- Wyrazy mają po kilka odpowiedników z małą odległością edycyjną.
- Wyrazy pociadają białe znaki, takie jak „spacja”.

#### Wyniki czasowe:

Program został przeze mnie przetestowany przy użyciu pliku wejściowego testowego oraz pliku wejściowego zawierającego 1000 wyrazów i kilkanaście sekwencji DNA. Dla obu zestawów danych wejściowych przetestowałem po dwa rodzaje bibliotek: C++ i ASM niezoptymalizowany oraz C++ i ASM zoptymalizowany.

Na wykresach kolory oznaczają odpowienio:

![Alt text](images/16.png?raw=true "oznaczenia. Źródło - wykonanie własne.")

Poniższe wykresy słupkowe obrazują uzyskane wyniki czasowe (w milisekundach) w zależności od ilości użytych wątków:

![Alt text](images/17.png?raw=true "Wykres przedstawiający szybkość wykonania operacji dla niezoptymalizowanych bibliotek DLL napisanych kolejno w C++ i asemblerze, operujących na plikach wejściowych testowych. Źródło - wykonanie własne.")

![Alt text](images/18.png?raw=true "Wykres przedstawiający szybkość wykonania operacji dla zoptymalizowanych bibliotek DLL napisanych kolejno w C++ i asemblerze, operujących na plikach wejściowych testowych. Źródło - wykonanie własne.")

![Alt text](images/19.png?raw=true "Wykres przedstawiający szybkość wykonania operacji dla niezoptymalizowanych bibliotek DLL napisanych kolejno w C++ i asemblerze, operujących na plikach wejściowych z zasobem 1000 wyrazów i kilkunastu sekwencji DNA. Źródło - wykonanie własne.")

![Alt text](images/20.png?raw=true "Wykres przedstawiający szybkość wykonania operacji dla zoptymalizowanych bibliotek DLL napisanych kolejno w C++ i asemblerze, operujących na plikach wejściowych z zasobem 1000 wyrazów i kilkunastu sekwencji DNA. Źródło - wykonanie własne.")

## <p align="center"> 5. Analiza działania programu </p>

Do przeprowadzenia analizy działania programu wykorzystałem wbudowane w kompilator Visual Studio 15 narzędzie diagnostyczne „Performance Profiler”.

![Alt text](images/21.png?raw=true "zużycie procesora dla DLL napisanej w C++. Źródło - wykonanie własne.")

Po uruchomieniu tego narzędzia, mogłem zbadać zużycie procesora podczas działania mojego programu - w wersji zoptymalizowanej wyniosło ono około 10%.

![Alt text](images/22.png?raw=true "zużycie procesora dla DLL napisanej w C++. Źródło - wykonanie własne.")
![Alt text](images/23.png?raw=true "rejon krytyczny. Źródło - wykonanie własne.")

Narzędzia wbudowane w Visual Studio 2015 pozwalają na dokładniejsze zbadanie działania programu, z dokładnością do poszczególnych funkcji. Zagłębienie się w diagram wizualizacji pozwoliło mi odnaleźć rejon krytyczny aplikacji, a co za tym idzie - odpowiedź na pytanie, która funkcja najbardziej obciąża procesor.

![Alt text](images/24.png?raw=true "rejon krytyczny. Źródło - wykonanie własne.")

Jak widać na załączonych zdjęciach, najbardziej obciążającą funkcją w aplikacji (ponad 94% obciążenia procesora przypada właśnie na nią) jest funkcja wczytująca funkcję z biblioteki DLL, w tym przypadku napisanej w C++ w wersji zoptymalizowanej.

Wywołując funkcję z biblioteki DLL napisanej w asemblerze w wersji zoptymalizowanej, diagnostyka wygląda następująco:

![Alt text](images/25.png?raw=true "zużycie procesora dla DLL napisanej w asemblerze. Źródło - wykonanie własne.")
![Alt text](images/26.png?raw=true "zużycie procesora dla DLL napisanej w asemblerze. Źródło - wykonanie własne.")

![Alt text](images/27.png?raw=true "rejon krytyczny. Źródło - wykonanie własne.")
![Alt text](images/28.png?raw=true "rejon krytyczny. Źródło - wykonanie własne.")

Wyniki dla wywołania funkcji z biblioteki DLL napisanej w asemblerze w wersji zoptymalizowanej niewiele odbiegają od tych uzyskanych podczas wywołania funkcji z biblioteki DLL napisanej w C++ w wersji zoptymalizowanej. Wynika to z tego, że najbardziej obciążająca procesor w tej aplikacji funkcja jest taka sama dla obu wersji bibliotek – funkcja wywołująca wspomniane biblioteki. Różnią się trochę sposobem wywołania funkcji w danej bibliotece, ale zasada jest ta sama, stąd podobne wyniki.

Dla niezoptymalizowanych wersji bibliotek DLL C++ i ASM diagnostyka wygląda tak:

- Niezoptymalizowana biblioteka DLL napisana w C++:

![Alt text](images/29.png?raw=true "niezoptymalizowana biblioteka DLL napisana w C++. Źródło - wykonanie własne.")

- Niezoptymalizowana biblioteka DLL napisana w asemblerze:

![Alt text](images/30.png?raw=true "niezoptymalizowana biblioteka DLL napisana w asemblerze. Źródło - wykonanie własne.")

Wyniki niezoptymalizowanych wersji bibliotek są do siebie podobne, ale różnią się od wyników zoptymalizowanych bibliotek, gdyż – ponownie – funkcja w niezoptymalizowanych bibliotekach jest ta sama dla obu wersji, lecz w zoptymalizowanych wersjach ona już nie występuje. Jest to funkcja związana z biblioteką VLD, której używałem do wyszukiwania i informowania o wyciekach pamięci.
W wersji zoptymalizowanej funkcja tej biblioteki nie jest już wywoływana.

## <p align="center"> 6. Wnioski </p>

Napisanie pierwszy raz biblioteki w języku asemblerowym (ASM w wersji kompilatora Visual C++) było dla mnie nie lada wyzwaniem. Napisanie części głównej programu, jak i biblioteki w C++ nie wykraczało poza moje umiejętności, natomiast już samo podłączenie biblioteki w asemblerze i pobieranie z niej funkcji wymagało dłuższej chwili. Po przypomnieniu sobie wiadomości z laboratorium oraz wykładów, zagłębieniu się w tematyce i skupieniu się tylko na napisaniu biblioteki w asemblerze, samo programowanie nie było już takie złe. Aby uczynić kod czytelniejszym, skorzystałem z rozszerzenia do Visual Studio 15, jakim jest AsmDude – asystant programowania w asemblerze, który zmienia kod wizualnie, bo dodaje kolory do składni asemblera, ale także zawiera opisy rejestrów, podpowiedzi rozkazów i ich objaśnienia wraz z rozpiską czasu trwania każdego rozkazu podczas użycia dla danych rejestrów, a także inne narzędzia rodem ze środowiska dla języka wysokiego poziomu, co w znacznej mierze ułatwiło mi pisanie kodu. To co przykuło moją uwagę, to praktycznie pełna swoboda dostępu, a ograniczeniem dla programisty była tylko własna kreatywność i logika. Mimo, że nie udało mi się uzyskać dużo lepszych wyników biblioteki napisanej w asemblerze od biblioteki napisanej w języku C++, to wynika to raczej ze źle przemyślanego algorytmu, niż z mojej rozrzutności w kodzie w języku asemblera. Algorytm Levenshteina nie ma przygotowanej odgórnie macierzy wartości, tylko kolejno wartości są obliczane z poprzednich trzech, dlatego niemożliwym było znaczne zaoszczędzenie czasu wykorzystując rozkazy wektorowe do głównych obliczeń, a ponadto obecne kompilatory C/C++ są na tyle wydajne, że program napisany w jednym z tych języków potrafi doścignąć ten napisany w asemblerze. Moja propozycja rozwiązania problemu z użyciem rejestrów MMX do obliczania indeksów tablicy przyspieszyła kod w asemblerze, ale nieznacznie. Chciałbym również zaznaczyć, że pisząc bibliotekę w asemblerze pisałem ją w taki sposób, aby była jak najbardziej czytelna. Obserwując zależność czasową od liczby wątków można zauważyć, że średnio najlepsze czasy program dla obu bibliotek osiągał pracując na jednym wątku. Jest to zachowanie nietypowe i najprawdopodobniej wynika ono z charakterytyki klasy Thread w języku C++.
