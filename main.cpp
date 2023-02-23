// TAI YRA C MASYVO VERSIJA

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>

struct studentas {

    std::string vardas;
    std::string pavarde;
    int* pazymiai;
    int egzaminas;
    double galutinis;
    double mediana;

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
    std::cin >> asmuo->vardas;

    std::cout << "Studento pavarde: ";
    std::cin >> asmuo->pavarde;

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

void duomenu_isvedimas(studentas* asmuo, int skaicius){

    std::cout << "Pavarde     Vardas          Galutinis (Vid.)    Galutinis (Med.)\n";
    std::cout << "-----------------------------------------------------------------\n";

    for(int i=0; i < skaicius; i++){

    std::cout << std::fixed << std::setprecision(2);
    std::cout << asmuo[i].pavarde <<
                 "    " <<
                 asmuo[i].vardas <<
                 "           " <<
                asmuo[i].galutinis <<
                "                " <<
                asmuo[i].mediana << std::endl;
    }
};


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

    duomenu_isvedimas(asmenys, mokiniu_dydis);




    return 1;
};