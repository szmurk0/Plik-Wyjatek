#include <iostream>
#include <fstream>
#include <string>
#include <exception>

using namespace std;

/*
!!!Uwaga!!! Plik testowalny powinien się znajdować w miejscu w projekcie tam gdzie plik .exe / .cpp
*/

class BrakPlikuException : public exception { // Własny wyjątek
private:
    string komunikat;
public:
    BrakPlikuException(const string& nazwaPliku) {
        komunikat = "Błąd: Nie można otworzyć pliku '" + nazwaPliku + "'";
    }

    const char* what() const noexcept override {
        return komunikat.c_str();
    }
};


void otworzPlik(const string& nazwaPliku) { // Funkcja do otwierania pliku
    ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        throw BrakPlikuException(nazwaPliku);
    }

    cout << "Plik '" << nazwaPliku << "' został pomyślnie otwarty.\n";

    string linia;
    while (getline(plik, linia)) {
        cout << linia << '\n';
    }

    plik.close();
}

int main() {
    string nazwa;

    cout << "Podaj nazwę pliku do otwarcia: ";
    cin >> nazwa;

    try {
        otworzPlik(nazwa);
    }
    catch (const BrakPlikuException& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
