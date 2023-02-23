// TAI YRA C MASYVO VERSIJA

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>

const int skaicius = 3;

struct studentas {

    std::string vardas;
    std::string pavarde;
    int* pazymiai;
    int egzaminas;
    double galutinis;
    double mediana;

};

void medianos_skaiciavimas(studentas* asmuo){

    int dydis = sizeof(asmuo->pazymiai) / sizeof(int);
    std::sort(asmuo->pazymiai,asmuo->pazymiai + dydis);

    if(dydis % 2 == 1){
            int indeksas = (dydis + 1) / 2;
            asmuo->mediana = asmuo->pazymiai[indeksas - 1];
    }
    else{
            int indeksas_pirmas = dydis / 2 - 1;
            int indeksas_antras = dydis / 2;
            double pazymys_pirmas = asmuo->pazymiai[indeksas_pirmas];
            double pazymys_antras = asmuo->pazymiai[indeksas_antras];
            asmuo->mediana = (pazymys_pirmas + pazymys_antras) / 2;
    }
};

void galutinio_balo_skaiciavimas(studentas* asmuo){

    double vidurkis;
    int dydis = sizeof(asmuo->pazymiai) / sizeof(int);
    
    for(int i=0; i < dydis;i++){
        vidurkis += asmuo->pazymiai[i];
    }
    vidurkis = vidurkis / dydis;
    
    asmuo->galutinis = (0.4 * vidurkis) + (0.6 * asmuo->egzaminas);
};

void duomenu_suvedimas(studentas* asmuo){

    for(int i =0; i < skaicius;i++){
    std::cout << "[" << i+1 << "]\n";
    std::cout << "Studento vardas: ";
    std::cin >> asmuo[i].vardas;

    std::cout << "Studento pavarde: ";
    std::cin >> asmuo[i].pavarde;

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

    asmuo[i].pazymiai = new int[pradinis_dydis + 1];
    std::copy(pazymiu_masyvas, pazymiu_masyvas + pradinis_dydis + 1, asmuo[i].pazymiai);
    delete[] pazymiu_masyvas;
    

    std::cout << "TESTINGAS: ";
        for(int t=0;t < pradinis_dydis; t++){
            std::cout << asmuo[i].pazymiai[t];
        }
    std::cout << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Studento egzamino rezultatas: ";
    std::cin >> asmuo[i].egzaminas;
    std::cout << std::endl;

    galutinio_balo_skaiciavimas(&asmuo[i]);
    medianos_skaiciavimas(&asmuo[i]);
    }
};

void duomenu_isvedimas(studentas* asmuo){

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

    studentas* asmenys = new studentas[skaicius];

    duomenu_suvedimas(asmenys);
    duomenu_isvedimas(asmenys);





    return 1;
};