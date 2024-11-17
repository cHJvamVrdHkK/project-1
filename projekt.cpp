#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("Zapis.txt");
    std::string odczyt = {};
    if (!inputFile.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku do odczytu!" << std::endl;
        return 1;
    }

    // Wyświetl zawartość pliku
    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
    }
    inputFile.close();

    // Otwórz plik w trybie dopisywania
    std::ofstream outputFile("Zapis.txt", std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku do dopisania!" << std::endl;
        return 1;
    }

    //uzupełnij tablice
    std::string Nkonfig[5] = {};
    for(int i = 0; i < 5; i++){
        std::cin >> Nkonfig[i];
    }
    for(int j = 0; j < 5; j++){
        outputFile << Nkonfig[j] << "; ";
    }
    //przejdź do nowej linii
    outputFile << std::endl;
    outputFile.close();
    return 0;
}