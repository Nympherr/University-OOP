#include <iostream>
#include <algorithm>
#include <iomanip>

const int skaicius = 3;

struct studentas {

    std::string vardas;
    std::string pavarde;
    int pazymiai[skaicius];
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

    std::cout << "Studento vardas: ";
    std::cin >> asmuo[i].vardas;

    std::cout << "Studento pavarde: ";
    std::cin >> asmuo[i].pavarde;

    std::cout << "Studento pazymiai: ";
    for(int j = 0; j < skaicius; j++){
            std::cin >> asmuo[i].pazymiai[j];
    }

    std::cout << "Studento egzamino rezultatas: ";
    std::cin >> asmuo[i].egzaminas;

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

    studentas asmenys[skaicius];

    duomenu_suvedimas(asmenys);
    duomenu_isvedimas(asmenys);





    return 1;
};