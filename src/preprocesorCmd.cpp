#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int preprocessCmdFile(const char* sFileName)
{
    std::string input = sFileName;
    std::string output = input + ".pp";    // wynik po preprocesorze

    // Uruchomienie preprocesora GCC (cpp)
    std::string cmd = "cpp -P \"" + input + "\" \"" + output + "\"";
    int status = system(cmd.c_str());
    if (status != 0) {
        std::cerr << "!!! Nie udało się uruchomić preprocesora cpp.\n";
        return 2;
    }

    // Wczytanie przetworzonego pliku
    std::ifstream f(output);
    if (!f) {
        std::cerr << "!!! Nie mozna otworzyc pliku wynikowego: " << output << "\n";
        return 3;
    }

    // --- W tym miejscu wczytujesz gotowy tekst do własnego parsera ---
    std::cout << "=== Plik po preprocessingu ===\n";
    std::cout << f.rdbuf() << "\n";

    // parse(output); // <- tu wywołujesz swój parser

    return 0;
}
