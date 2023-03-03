// v0.2 versijos programa

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <random>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <chrono>

struct studentas {

    std::string vardas;
    std::string pavarde;
    std::vector <int> pazymiai;
    int egzaminas;
    double galutinis_balas;
    double mediana;

};

int mokiniu_dydis = 0;
std::vector <studentas> asmenys;

void atsitiktiniu_reiksmiu_generavimas(studentas& asmuo){

// Generuojamas atsitiktinis kiekis pažymių(1-40; galima keisti). Bei kiekvienas
// individualus pažymys. Ir sukuriamas naujas masyvas, kuris būtent atvaizduoja
// studento pažymius.

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> atsitiktinis_numeris(1, 40);
    std::uniform_int_distribution<> pazymys(1, 10);

    int pazymiu_kiekis = atsitiktinis_numeris(eng);

    for(int i =0; i < pazymiu_kiekis;i++){
        asmuo.pazymiai.push_back(pazymys(eng));
    }

    asmuo.egzaminas = pazymys(eng);

    std::cout << "Sugeneruoti pazymiai: ";
    for(int j =0; j < pazymiu_kiekis; j++){
        std::cout << asmuo.pazymiai[j] << " ";
    }
    std::cout << "\nSugeneruotas egzamino rezultatas: " << asmuo.egzaminas << "\n";
    std::cout << "-------------------------------------\n\n";
};

void medianos_skaiciavimas(studentas& asmuo){

// Skaičiuoja medianą iš studento gautų pažymių. Masyvas yra surūšiuojamas didėjimo tvarka
// ir mediana apskaičiuojama pagal formulę.

    std::sort(asmuo.pazymiai.begin(), asmuo.pazymiai.end());

    if(asmuo.pazymiai.size() % 2 == 1){
            int indeksas_medianos = (asmuo.pazymiai.size() + 1) / 2;
            asmuo.mediana = asmuo.pazymiai[indeksas_medianos - 1];
    }
    else{
            int pirmas_vidurinis_skaicius = asmuo.pazymiai.size() / 2 - 1;
            int antras_vidurinis_skaicius = asmuo.pazymiai.size() / 2;
            double pazymys_pirmas = asmuo.pazymiai[pirmas_vidurinis_skaicius];
            double pazymys_antras = asmuo.pazymiai[antras_vidurinis_skaicius];
            asmuo.mediana = (pazymys_pirmas + pazymys_antras) / 2;
    }
};

void galutinio_balo_skaiciavimas(studentas& asmuo){

// Skaičiuoja galutinį balą pagal pažymių vidurkį ir egzamino balą

    double vidurkis = 0.0;
    
    for(int i=0; i < asmuo.pazymiai.size();i++){
        vidurkis += asmuo.pazymiai[i];
    }
    vidurkis = vidurkis / asmuo.pazymiai.size();
    
    asmuo.galutinis_balas = (0.4 * vidurkis) + (0.6 * asmuo.egzaminas);
};

void pazymiu_suvedimas(studentas& asmuo){

// Leidžia vartotojui įvesti neribotą kiekį pažymių.
    int pasirinkimas = 0;

        while(std::cin >> pasirinkimas){

            if(pasirinkimas < 1 || pasirinkimas > 10){
                std::cout << "Pažymys gali būti tik tarp 1-10!";
            }
            else{
                asmuo.pazymiai.push_back(pasirinkimas);
            }
        }
};

void egzamino_suvedimas(studentas& asmuo){

// Leidžia vartotojui įvesti egzamino balą, bei tikrinama, kad įvestis būtų tinkama
// (pvž. ne raidės)

    int pasirinkimas;
    std::cout << "Studento egzamino rezultatas: ";
    std::cin >> pasirinkimas;

    if(pasirinkimas > 10 || pasirinkimas < 1){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEgzamino rezultatas gali buti tik tarp 1-10!\n";
        egzamino_suvedimas(asmuo);
    }
    else{
        asmuo.egzaminas = pasirinkimas;
    }
};

void duomenu_suvedimas(studentas& asmuo){

// Tikrina ar vartotojo vardo įvestis yra iš raidžių ir ar neviršija nurodyto
// skaitmenų kiekio. Vyksta tol, kol įvestis tenkins sąlygas.

    std::cout << "\nStudento vardas: ";
    bool yra_vardas = false;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (!yra_vardas || asmuo.vardas.length() < 1 || asmuo.vardas.length() > 20) {

        std::getline(std::cin, asmuo.vardas);
        yra_vardas = true;   

        for (char c : asmuo.vardas) {
            if (!std::isalpha(c)) {
                yra_vardas = false;
                std::cout << "\nVarda gali sudaryti tik raides!\n";
                std::cout << "Vardas: ";
                break;
            }
        }
        if(asmuo.vardas.length() < 1 || asmuo.vardas.length() > 20){
            std::cout << "\nVardas gali tureti tik 1-20 raidziu!\n";
            std::cout << "Vardas: ";
        }
    }

// Tikrina ar vartotojo pavardės įvestis yra iš raidžių ir ar neviršija nurodyto
// skaitmenų kiekio. Vyksta tol, kol įvestis tenkins sąlygas.

    std::cout << "Studento pavarde: ";
    bool yra_pavarde = false;

     while (!yra_pavarde || asmuo.pavarde.length() < 1 || asmuo.pavarde.length() > 20) {

        std::getline(std::cin, asmuo.pavarde);
        yra_pavarde = true;   

        for (char c : asmuo.pavarde) {
            if (!std::isalpha(c)) {
                yra_pavarde = false;
                std::cout << "\nPavarde gali sudaryti tik raides!\n";
                std::cout << "Pavarde: ";
                break;
            }
        }
        if(asmuo.pavarde.length() < 1 || asmuo.pavarde.length() > 20){
            std::cout << "\nPavarde gali tureti tik 1-20 raidziu!\n";
            std::cout << "Pavarde: ";
        }
    }

// Pagal vartotojo įvestį yra iškviečiama funkcija, kuri atsitiktinai generuos
// pažymius arba vartotojui leis savarankiškai juos įvesti.

    std::cout << "\nAr noretumete atsitiktinai sugeneruoti pažymių ir egzamino rezultatus?\n";
    std::cout << "[random]-TAIP     [betkuri raide]-NE\n";
    std::string ivestis;
    std::cin >> ivestis;
    std::transform(ivestis.begin(), ivestis.end(), ivestis.begin(),
    [](unsigned char c){ return std::tolower(c); });

    std::cout << std::endl;

    if(ivestis == "random"){
        atsitiktiniu_reiksmiu_generavimas(asmuo);
        galutinio_balo_skaiciavimas(asmuo);
        medianos_skaiciavimas(asmuo);
        return;
    }

// Pažymių įvedimas savarankiškai. Tikrinama, kad būtų minimalus pažymių kiekis
// bei, kad įvestis būtų tinkama(pvž. skaičius, o ne raidės)

    std::cout << "[Spausk raide, kad baigti ivedima]\n";
    std::cout << "Studento pazymiai: ";

    pazymiu_suvedimas(asmuo);
    while(asmuo.pazymiai.size() == 0){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Turite ivesti bent viena pazymi:";
        pazymiu_suvedimas(asmuo);
    }

// Rodomi įvesti pažymiai. Kviečiama funkcija, kur reikės įvesti egzamino balą.
// Bei kviečiamos funkcijos, kur apskaičiuos galutinį balą, bei medianą.

    std::cout << "\nIvesti pazymiai: ";
        for(int t=0;t < asmuo.pazymiai.size(); t++){
            std::cout << asmuo.pazymiai[t] << " ";
        }

    std::cout << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    egzamino_suvedimas(asmuo);
    galutinio_balo_skaiciavimas(asmuo);
    medianos_skaiciavimas(asmuo);
    std::cout << "-------------------------------------\n\n";
};

void vidurkio_vaizdavimas(std::vector<studentas> &asmuo){
    
    std::cout << "\nPavarde              Vardas               Galutinis (Vid.)\n";
    std::cout << "------------------------------------------------------------\n";

    for(int x = 0; x < asmuo.size() ; x++){

// "tarpai" kintamieji padaro, kad lygiavimas galutiniame
// rezultate būtų gražus

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

        std::cout << asmuo[x].galutinis_balas << std::endl;
    }
    std::cout << "\n";
}
void medianos_vaizdavimas(std::vector<studentas> &asmuo){

    std::cout << "Pavarde              Vardas               Galutinis (Med.)\n";
    std::cout << "------------------------------------------------------------\n";

    for(int x = 0; x < asmuo.size() ; x++){

// "tarpai" kintamieji padaro, kad lygiavimas galutiniame
// rezultate būtų gražus

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
    std::cout << "\n";
}

void rezultatu_vaizdavimas(){

// Tikrina vartotojo įvestį ir pagal pasirinkimą
// atitinkamai atvaizduoja studentus ir jų rezultatus

    std::cout << "\nNorite rezultatus matyti pagal vidurkį ar medianą?\n";
    std::cout << "[v] - VIDURKIS     [m] - MEDIANA\n";
    std::string pasirinkimas;
    std::cin >> pasirinkimas;
    std::transform(pasirinkimas.begin(), pasirinkimas.end(), pasirinkimas.begin(),
    [](unsigned char c){ return std::tolower(c); });

    std::cout << std::endl;

    while(pasirinkimas != "v" && pasirinkimas != "m"){
        std::cout << "Galite pasirinkti tik:\n";
        std::cout << "[v] - VIDURKIS     [m] - MEDIANA\n";
        std::cin >> pasirinkimas;
    }
    if(pasirinkimas == "v"){
        vidurkio_vaizdavimas(asmenys);
    }
    else if(pasirinkimas == "m"){
        medianos_vaizdavimas(asmenys);
    }
};

void prideti_mokini(){

// Tikrina vartotojo įvestį ir didina studentų masyvą
// jeigu vartotojas nori pridėti naują įrašą

    std::string ivestis;

    do{
        std::cout << "Ar norite įvesti naują mokinį?\n";
        std::cout << "[t]-TAIP      [kita raide]-NE\n";
        std::cin >> ivestis;
        std::transform(ivestis.begin(), ivestis.end(), ivestis.begin(),
        [](unsigned char c){ return std::tolower(c); });

        if(ivestis == "t"){
            asmenys.push_back(studentas());
            duomenu_suvedimas(asmenys[mokiniu_dydis]);
            mokiniu_dydis++;
        }
    }while(ivestis == "t");
};

std::string irasymo_pasirinkimas(){

    std::string ivestis;

    std::cout << "Ar norite nuskaityti duomenis is failo ar irasyti savarankiskai?\n";
    std::cout << "[failas] - Failo nuskaitymas       [sav] - Savarankiskai\n";

    std::cin >> ivestis;
    while(ivestis != "failas" && ivestis != "sav"){
        std::cout<< "Galite pasirinkti tik [failas] arba [sav]!\n";
        std::cin >> ivestis;
        std::cout << std::endl;
    }

    return ivestis;
};

bool pavardes_rusiavimas(const studentas& asmuo1, const studentas& asmuo2){
    return asmuo1.pavarde < asmuo2.pavarde;
}

void failo_nuskaitymas(){

    // Duoda vartotojui pasirinkti failą, kurį jis nori atidaryti

    std::cout << "\nIrasykite failo pavadinima:   ";
    std::string ivestis;
    std::cin >> ivestis;

    std::string failo_pavadinimas = "./failai/" + ivestis;
    std::ifstream skaitomas_failas(failo_pavadinimas);

    while (!skaitomas_failas.is_open()) {
        std::cout << "Tokio failo nera! Pabandykite dar karta!\n";
        std::cin >> ivestis;
        std::cout << std::endl;
        failo_pavadinimas = "./failai/" + ivestis;
        skaitomas_failas = std::ifstream(failo_pavadinimas);
    };

    // Pradedamas skaičiavimas, kuris parodo kiek laiko truko failo nuskaitymas ir įrašymas

    auto start = std::chrono::high_resolution_clock::now(); auto st=start;

    std::string nuskaityta_eilute;
    std::vector<std::string> nuskaitytas_failas;

    std::cout << "\nIrasomi duomenys....\n";

    // Skaitoma atidaryto failo kiekviena eilutė

    while (std::getline(skaitomas_failas, nuskaityta_eilute)) {
        nuskaitytas_failas.push_back(nuskaityta_eilute);
    };

    skaitomas_failas.close();
    nuskaitytas_failas.erase(nuskaitytas_failas.begin());

    // Nuskaityti failo duomenys pertvarkomi
    // (Atskiriami vardai, pavardes, pazymiai, egzaminai)

    std::vector<std::vector<std::string>> rezultatas;

    for (const std::string& x : nuskaitytas_failas) {

            std::istringstream neisskaidyta_eilute(x);
            std::vector<std::string> isskaidyti_zodziai;
            std::string zodis;

            while (neisskaidyta_eilute >> zodis) {
                isskaidyti_zodziai.push_back(zodis);
            }
            rezultatas.push_back(isskaidyti_zodziai);
        }

    // Kiekvienoje iteracijoje sukuriamas naujas studento objektas

    for(int i = 0; i < rezultatas.size() ; i++){

        asmenys.push_back(studentas());
    
        for(int j = 0; j < rezultatas[i].size() ; j++){
        
            if(j == 0){
                asmenys[i].vardas = rezultatas[i][j];
            }
            else if(j == 1){
                asmenys[i].pavarde = rezultatas[i][j];
            }
            else if(j > 1 && j < rezultatas[i].size() - 1){
                try{
                    int reiksme = std::stoi(rezultatas[i][j]);
                    asmenys[i].pazymiai.push_back(reiksme);
                }
                catch (const std::invalid_argument& e) {
                    continue;
                }
            }
            else if(j == rezultatas[i].size() - 1){
                try{
                int reiksme = std::stoi(rezultatas[i][j]);
                asmenys[i].egzaminas = reiksme;
                }
                catch (const std::invalid_argument& e) {
                    continue;
                }
            }   
        }
        galutinio_balo_skaiciavimas(asmenys[i]);
        medianos_skaiciavimas(asmenys[i]);
    }

    // Duomenu įrašymas į naują failą

    std::ofstream rezultatu_failas; 
    rezultatu_failas.open("rezultatas.txt");

    std::sort(asmenys.begin(), asmenys.end(), pavardes_rusiavimas);

    if (rezultatu_failas.is_open()) { 

            rezultatu_failas << "Pavarde              Vardas               Galutinis (Vid.)        Galutinis (Med.)\n";
            
            rezultatu_failas << "-----------------------------------------------------------------------------------------\n";


        for(int x = 0; x < asmenys.size() ; x++){

        // "tarpai" kintamieji padaro, kad lygiavimas galutiniame
        // rezultate būtų gražus

            int tarpai_1 = 21 - asmenys[x].pavarde.length();
            int tarpai_2 = 21 - asmenys[x].vardas.length();

            rezultatu_failas << std::fixed << std::setprecision(2);

            rezultatu_failas << asmenys[x].pavarde;
            for(int i = 0; i < tarpai_1; i++){
                rezultatu_failas << " ";
            }

            rezultatu_failas << asmenys[x].vardas;
            for(int j = 0; j < tarpai_2; j++){
            rezultatu_failas << " ";
            }

            rezultatu_failas << asmenys[x].galutinis_balas;
            for(int j = 0; j < 20; j++){
            rezultatu_failas << " ";

            }
            rezultatu_failas << asmenys[x].mediana << std::endl;
        }
    }
    else {
        std::cout << "Ivyko klaida\n";
    }

    rezultatu_failas.close();
    std::cout << "\nSekmingai irasyta!\n";

    // Parodoma operacijos trukmė vartotojui

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start; // Skirtumas (s)
    std::cout << "\nFailo nuskaitymas tiesiai į eilučių vektorių užtruko: "<< diff.count() << " s\n\n";   
};

int main(){

// Programos paleidimas

    std::string vartotojo_pasirinkimas = irasymo_pasirinkimas();

    if(vartotojo_pasirinkimas == "sav"){
        do{
            prideti_mokini();
            if(asmenys.size() == 0){
                std::cout << "\nTurite ivesti bent viena mokini!\n\n";
            }
    }while(asmenys.size() == 0);
    }

    else if(vartotojo_pasirinkimas == "failas"){
        failo_nuskaitymas();
        return 1;
    }

    rezultatu_vaizdavimas();

    return 1;
};