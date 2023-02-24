// TAI YRA C MASYVO VERSIJA

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <random>
#include <string>
#include <cctype>

struct studentas {

    std::string vardas;
    std::string pavarde;
    int* pazymiai;
    int egzaminas;
    double galutinis;
    double mediana;

};
int atsitiktiniu_reiksmiu_generavimas(studentas* asmuo){

    std::random_device rd;
    std::mt19937 eng(rd());

    std::uniform_int_distribution<> pazymiu_skaicius(1, 20);
    std::uniform_int_distribution<> pazymys(1, 10);

    int indekso_numeris = pazymiu_skaicius(eng);
    asmuo->pazymiai = new int[indekso_numeris];

    for(int i =0; i < indekso_numeris;i++){
        asmuo->pazymiai[i] = pazymys(eng);
    }

    asmuo->egzaminas = pazymys(eng);

    return indekso_numeris;

};

void medianos_skaiciavimas(studentas* asmuo, int indeksas){

    std::sort(asmuo->pazymiai,asmuo->pazymiai + indeksas);

    if(indeksas % 2 == 1){
            int indeksas_masyvo = (indeksas + 1) / 2;
            asmuo->mediana = asmuo->pazymiai[indeksas_masyvo - 1];
    }
    else{
            int indeksas_pirmas = indeksas / 2 - 1;
            int indeksas_antras = indeksas / 2;
            double pazymys_pirmas = asmuo->pazymiai[indeksas_pirmas];
            double pazymys_antras = asmuo->pazymiai[indeksas_antras];
            asmuo->mediana = (pazymys_pirmas + pazymys_antras) / 2;
    }
};

void galutinio_balo_skaiciavimas(studentas* asmuo, int indeksas){

    double vidurkis = 0.0;
    
    for(int i=0; i < indeksas;i++){
        vidurkis += asmuo->pazymiai[i];
    }
    vidurkis = vidurkis / indeksas;
    
    asmuo->galutinis = (0.4 * vidurkis) + (0.6 * asmuo->egzaminas);
};

void duomenu_suvedimas(studentas* asmuo){

    std::cout << "Studento vardas: ";

    bool yra_vardas = false;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (!yra_vardas || asmuo->vardas.length() < 1 || asmuo->vardas.length() > 20) {

        std::getline(std::cin, asmuo->vardas);

        yra_vardas = true;   
        for (char c : asmuo->vardas) {
            if (!std::isalpha(c)) {
                yra_vardas = false;
                std::cout << "Varda gali sudaryti tik raides!\n";
                break;
            }
        }

        if(asmuo->vardas.length() < 1 || asmuo->vardas.length() > 20){
            std::cout << "Vardas gali tureti tik 1-20 raidziu!\n";
        }
    }

    std::cout << "Studento pavarde: ";

    bool yra_pavarde = false;

     while (!yra_pavarde || asmuo->pavarde.length() < 1 || asmuo->pavarde.length() > 20) {

        std::getline(std::cin, asmuo->pavarde);

        yra_pavarde = true;   
        for (char c : asmuo->pavarde) {
            if (!std::isalpha(c)) {
                yra_pavarde = false;
                std::cout << "Pavarde gali sudaryti tik raides!\n";
                break;
            }
        }

        if(asmuo->pavarde.length() < 1 || asmuo->pavarde.length() > 20){
            std::cout << "Pavarde gali tureti tik 1-20 raidziu!\n";
        }
    }

    std::cout << "Ar noretumete atsitiktinai sugeneruotri pažymių ir egzamino rezultatus?\n";
    std::cout << "[random]-TAIP     [betkuri raide]-NE\n";
    std::string input;
    std::cin >> input;

    if(input == "random"){
        int skaiciukas = atsitiktiniu_reiksmiu_generavimas(asmuo);
        galutinio_balo_skaiciavimas(asmuo,skaiciukas);
        medianos_skaiciavimas(asmuo, skaiciukas);
        return;
    }

    std::cout << "Studento pazymiai: ";

    
    int pasirinkimas = 0;
    int pradinis_dydis = 0;
    int maksimalus_dydis = 10;
    int* pazymiu_masyvas = new int[maksimalus_dydis];


        while(std::cin >> pasirinkimas){

            if(pasirinkimas < 1 || pasirinkimas > 10){
                std::cout << "Pažymys gali būti tik tarp 1-10!";
            }

            else if(pradinis_dydis == maksimalus_dydis - 1){
                int* naujas_pazymiu_masyvas = new int[maksimalus_dydis * 2];
                std::copy(pazymiu_masyvas, pazymiu_masyvas + maksimalus_dydis, naujas_pazymiu_masyvas);
                delete[] pazymiu_masyvas;
                pazymiu_masyvas = naujas_pazymiu_masyvas;
                maksimalus_dydis *= 2;
                pazymiu_masyvas[pradinis_dydis] = pasirinkimas;
                pradinis_dydis++;

            }
            else{
                pazymiu_masyvas[pradinis_dydis] = pasirinkimas;
                pradinis_dydis++;
            }
        }

    asmuo->pazymiai = new int[pradinis_dydis + 1];
    std::copy(pazymiu_masyvas, pazymiu_masyvas + pradinis_dydis + 1, asmuo->pazymiai);
    delete[] pazymiu_masyvas;
    

    std::cout << "TESTINGAS: ";
        for(int t=0;t < pradinis_dydis; t++){
            std::cout << asmuo->pazymiai[t];
        }
    std::cout << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Studento egzamino rezultatas: ";
    std::cin >> asmuo->egzaminas;
    std::cout << std::endl;

    galutinio_balo_skaiciavimas(asmuo,pradinis_dydis);
    medianos_skaiciavimas(asmuo, pradinis_dydis);
    
};

void duomenu_isvedimas_vidurkis(studentas* asmuo, int skaicius){

    std::cout << "Pavarde              Vardas             Galutinis (Vid.)\n";
    std::cout << "------------------------------------------------------------\n";

    for(int x = 0; x < skaicius ; x++){

        int tarpai_1 = 21 - asmuo[x].pavarde.length();
        int tarpai_2 = 21 - asmuo[x].vardas.length();

        std::cout << std::fixed << std::setprecision(2);

        std::cout << asmuo[x].pavarde;
        for(int i = 0; i < tarpai_1; i++){
            std::cout << " ";
        }

        std::cout << asmuo[x].vardas;
        for(int j = 0; j < tarpai_2; j++){
        std::cout << " ";
        }

        std::cout << asmuo[x].galutinis << std::endl;
    }
}
void duomenu_isvedimas_mediana(studentas* asmuo, int skaicius){

    std::cout << "Pavarde              Vardas             Galutinis (Med.)\n";
    std::cout << "------------------------------------------------------------\n";

    for(int x = 0; x < skaicius ; x++){

        int tarpai_1 = 21 - asmuo[x].pavarde.length();
        int tarpai_2 = 21 - asmuo[x].vardas.length();

        std::cout << std::fixed << std::setprecision(2);

        std::cout << asmuo[x].pavarde;
        for(int i = 0; i < tarpai_1; i++){
            std::cout << " ";
        }

        std::cout << asmuo[x].vardas;
        for(int j = 0; j < tarpai_2; j++){
        std::cout << " ";
        }

        std::cout << asmuo[x].mediana << std::endl;
    }
}

int main(){

    std::string user_input;
    int mokiniu_dydis = 0;
    int mokiniu_maksimumas = 1;
    studentas* asmenys = new studentas[mokiniu_maksimumas];

    do{
        std::cout << "Ar norite įvesti naują mokįnį?\n";
        std::cout << "[t]-TAIP [kita raide]-NE\n";
        std::cin >> user_input;
        if(user_input == "t"){
            if(mokiniu_dydis == mokiniu_maksimumas){
                    studentas* naujas_mokiniu_masyvas = new studentas[mokiniu_maksimumas + 1];
                    std::copy(asmenys, asmenys + mokiniu_maksimumas, naujas_mokiniu_masyvas);
                    delete[] asmenys;
                    asmenys = naujas_mokiniu_masyvas;
                    mokiniu_maksimumas++;
            }
        
            mokiniu_dydis++;
            duomenu_suvedimas(&asmenys[mokiniu_dydis - 1]);
        }
    }while(user_input == "t");

    std::cout << "Norite rezultatus matyti pagal vidurkį ar medianą?\n";
    std::cout << "[v] - VIDURKIS     [m] - MEDIANA\n";
    std::cin >> user_input;

    while(user_input != "v" && user_input != "m"){
        std::cout << "Galite pasirinkti tik:\n";
        std::cout << "[v] - VIDURKIS     [m] - MEDIANA\n";
        std::cin >> user_input;
    }
    if(user_input == "v"){
        duomenu_isvedimas_vidurkis(asmenys, mokiniu_dydis);
    }
    else if(user_input == "m"){
        duomenu_isvedimas_mediana(asmenys, mokiniu_dydis);
    }


    return 1;
};