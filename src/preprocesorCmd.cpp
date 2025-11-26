#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

bool preprocessCmdFile(const char* sFileName)
{
    std::string input = sFileName;
    std::string output = input + ".pp";    // wynik po preprocesorze

    // Uruchomienie preprocesora GCC (cpp)
    std::string cmd = "cpp -P \"" + input + "\" \"" + output + "\"";
    int status = system(cmd.c_str());
    if (status != 0) {
        std::cerr << "!!! Nie udało się uruchomić preprocesora cpp.\n";
        return false;
    }

    return true;
}

bool openCommandFile(std::string sFileName)
{
    std::string output = sFileName + ".pp";    // wynik po preprocesorze

    // Wczytanie przetworzonego pliku
    std::ifstream f(output);
    if (!f) {
        std::cerr << "!!! Nie mozna otworzyc pliku wynikowego: " << output << "\n";
        return false;
    }

    std::cout << "=== Plik po preprocessingu ===\n";
    std::cout << f.rdbuf() << "\n";
    std::cout << "==============================\n";

    // parsowanie output

    return true;
}
