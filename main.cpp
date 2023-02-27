// v.01 versijos C masyvo programa (nenaudojami vektoriai)

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
    double galutinis_balas;
    double mediana;

};

int mokiniu_dydis = 0;
int mokiniu_maksimumas = 1;
studentas* asmenys = new studentas[mokiniu_maksimumas];


int atsitiktiniu_reiksmiu_generavimas(studentas* asmuo){

// Generuojamas atsitiktinis kiekis pažymių(1-40; galima keisti). Bei kiekvienas
// individualus pažymys. Ir sukuriamas naujas masyvas, kuris būtent atvaizduoja
// studento pažymius.

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> atsitiktinis_numeris(1, 40);
    std::uniform_int_distribution<> pazymys(1, 10);

    int pazymiu_kiekis = atsitiktinis_numeris(eng);
    asmuo->pazymiai = new int[pazymiu_kiekis];

    for(int i =0; i < pazymiu_kiekis;i++){
        asmuo->pazymiai[i] = pazymys(eng);
    }

    asmuo->egzaminas = pazymys(eng);

    std::cout << "Sugeneruoti pazymiai: ";
    for(int j =0; j < pazymiu_kiekis; j++){
        std::cout << asmuo->pazymiai[j] << " ";
    }
    std::cout << "\nSugeneruotas egzamino rezultatas: " << asmuo->egzaminas << "\n";
    std::cout << "-------------------------------------\n\n";

//Gražina masyvo dydį kitoms funkcijoms.
    return pazymiu_kiekis;
};

void medianos_skaiciavimas(studentas* asmuo, int pazymiu_skaicius){

// Skaičiuoja medianą iš studento gautų pažymių. Masyvas yra surūšiuojamas didėjimo tvarka
// ir mediana apskaičiuojama pagal formulę.
    std::sort(asmuo->pazymiai,asmuo->pazymiai + pazymiu_skaicius);

    if(pazymiu_skaicius % 2 == 1){
            int indeksas_medianos = (pazymiu_skaicius + 1) / 2;
            asmuo->mediana = asmuo->pazymiai[indeksas_medianos - 1];
    }
    else{
            int pirmas_vidurinis_skaicius = pazymiu_skaicius / 2 - 1;
            int antras_vidurinis_skaicius = pazymiu_skaicius / 2;
            double pazymys_pirmas = asmuo->pazymiai[pirmas_vidurinis_skaicius];
            double pazymys_antras = asmuo->pazymiai[antras_vidurinis_skaicius];
            asmuo->mediana = (pazymys_pirmas + pazymys_antras) / 2;
    }
};

void galutinio_balo_skaiciavimas(studentas* asmuo, int pazymiu_skaicius){

// Skaičiuoja galutinį balą pagal pažymių vidurkį ir egzamino balą

    double vidurkis = 0.0;
    
    for(int i=0; i < pazymiu_skaicius;i++){
        vidurkis += asmuo->pazymiai[i];
    }
    vidurkis = vidurkis / pazymiu_skaicius;
    
    asmuo->galutinis_balas = (0.4 * vidurkis) + (0.6 * asmuo->egzaminas);
};

int pazymiu_suvedimas(studentas* asmuo){

// Leidžia vartotojui savarankiškai įvesti neribotą kiekį pažymių. Pasiekus didžiausią
// limitą yra sukuriamas didesnis masyvas, senas turinys nukopijuojamas bei ištrinamas
// senas masyvas

    delete[] asmuo->pazymiai;

    int pasirinkimas = 0;
    int dabartinis_dydis = 0;
    int maksimalus_dydis = 10;
    int* pazymiu_masyvas = new int[maksimalus_dydis];


        while(std::cin >> pasirinkimas){

            if(pasirinkimas < 1 || pasirinkimas > 10){
                std::cout << "Pažymys gali būti tik tarp 1-10!";
            }

            else if(dabartinis_dydis == maksimalus_dydis - 1){
                int* naujas_pazymiu_masyvas = new int[maksimalus_dydis * 2];
                std::copy(pazymiu_masyvas, pazymiu_masyvas + maksimalus_dydis, naujas_pazymiu_masyvas);
                delete[] pazymiu_masyvas;
                pazymiu_masyvas = naujas_pazymiu_masyvas;
                maksimalus_dydis *= 2;
                pazymiu_masyvas[dabartinis_dydis] = pasirinkimas;
                dabartinis_dydis++;

            }
            else{
                pazymiu_masyvas[dabartinis_dydis] = pasirinkimas;
                dabartinis_dydis++;
            }
        }

    asmuo->pazymiai = new int[dabartinis_dydis + 1];
    std::copy(pazymiu_masyvas, pazymiu_masyvas + dabartinis_dydis + 1, asmuo->pazymiai);
    delete[] pazymiu_masyvas;

    return dabartinis_dydis;
};

void egzamino_suvedimas(studentas* asmuo){

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
        asmuo->egzaminas = pasirinkimas;
    }
};

void duomenu_suvedimas(studentas* asmuo){

// Tikrina ar vartotojo vardo įvestis yra iš raidžių ir ar neviršija nurodyto
// skaitmenų kiekio. Vyksta tol, kol įvestis tenkins sąlygas.

    std::cout << "\nStudento vardas: ";
    bool yra_vardas = false;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (!yra_vardas || asmuo->vardas.length() < 1 || asmuo->vardas.length() > 20) {

        std::getline(std::cin, asmuo->vardas);
        yra_vardas = true;   

        for (char c : asmuo->vardas) {
            if (!std::isalpha(c)) {
                yra_vardas = false;
                std::cout << "\nVarda gali sudaryti tik raides!\n";
                std::cout << "Vardas: ";
                break;
            }
        }
        if(asmuo->vardas.length() < 1 || asmuo->vardas.length() > 20){
            std::cout << "\nVardas gali tureti tik 1-20 raidziu!\n";
            std::cout << "Vardas: ";
        }
    }

// Tikrina ar vartotojo pavardės įvestis yra iš raidžių ir ar neviršija nurodyto
// skaitmenų kiekio. Vyksta tol, kol įvestis tenkins sąlygas.

    std::cout << "Studento pavarde: ";
    bool yra_pavarde = false;

     while (!yra_pavarde || asmuo->pavarde.length() < 1 || asmuo->pavarde.length() > 20) {

        std::getline(std::cin, asmuo->pavarde);
        yra_pavarde = true;   

        for (char c : asmuo->pavarde) {
            if (!std::isalpha(c)) {
                yra_pavarde = false;
                std::cout << "\nPavarde gali sudaryti tik raides!\n";
                std::cout << "Pavarde: ";
                break;
            }
        }
        if(asmuo->pavarde.length() < 1 || asmuo->pavarde.length() > 20){
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
        int pazymiu_kiekis = atsitiktiniu_reiksmiu_generavimas(asmuo);
        galutinio_balo_skaiciavimas(asmuo,pazymiu_kiekis);
        medianos_skaiciavimas(asmuo, pazymiu_kiekis);
        return;
    }

// Pažymių įvedimas savarankiškai. Tikrinama, kad būtų minimalus pažymių kiekis
// bei, kad įvestis būtų tinkama(pvž. skaičius, o ne raidės)

    std::cout << "[Spausk raide, kad baigti ivedima]\n";
    std::cout << "Studento pazymiai: ";

    int dabartinis_dydis = pazymiu_suvedimas(asmuo);
    while(dabartinis_dydis == 0){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Turite ivesti bent viena pazymi:";
        dabartinis_dydis = pazymiu_suvedimas(asmuo);
    }

// Rodomi įvesti pažymiai. Kviečiama funkcija, kur reikės įvesti egzamino balą.
// Bei kviečiamos funkcijos, kur apskaičiuos galutinį balą, bei medianą.

    std::cout << "\nIvesti pazymiai: ";
        for(int t=0;t < dabartinis_dydis; t++){
            std::cout << asmuo->pazymiai[t] << " ";
        }

    std::cout << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    egzamino_suvedimas(asmuo);
    galutinio_balo_skaiciavimas(asmuo,dabartinis_dydis);
    medianos_skaiciavimas(asmuo, dabartinis_dydis);
    std::cout << "-------------------------------------\n\n";
};

void vidurkio_vaizdavimas(studentas* asmuo, int mokiniu_dydis){
    
    std::cout << "\nPavarde              Vardas               Galutinis (Vid.)\n";
    std::cout << "------------------------------------------------------------\n";

    for(int x = 0; x < mokiniu_dydis ; x++){

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
void medianos_vaizdavimas(studentas* asmuo, int mokiniu_dydis){

    std::cout << "Pavarde              Vardas               Galutinis (Med.)\n";
    std::cout << "------------------------------------------------------------\n";

    for(int x = 0; x < mokiniu_dydis ; x++){

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
        vidurkio_vaizdavimas(asmenys, mokiniu_dydis);
    }
    else if(pasirinkimas == "m"){
        medianos_vaizdavimas(asmenys, mokiniu_dydis);
    }
};

void prideti_mokini(){

// Tikrina vartotojo įvesti ir didina studentų masyvą
// jeigu vartotojas nori pridėti naują įrašą

    std::string ivestis;

    do{
        std::cout << "Ar norite įvesti naują mokinį?\n";
        std::cout << "[t]-TAIP      [kita raide]-NE\n";
        std::cin >> ivestis;
        std::transform(ivestis.begin(), ivestis.end(), ivestis.begin(),
        [](unsigned char c){ return std::tolower(c); });

        if(ivestis == "t"){
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
    }while(ivestis == "t");
};

int main(){

// Programos paleidimas

    do{
        prideti_mokini();
        if(mokiniu_dydis == 0){
            std::cout << "\nTurite ivesti bent viena mokini!\n\n";
        }
    }while(mokiniu_dydis == 0);

    rezultatu_vaizdavimas();

    return 1;
};