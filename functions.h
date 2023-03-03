#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

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
extern int mokiniu_dydis;
extern std::vector <studentas> asmenys;

void atsitiktiniu_reiksmiu_generavimas(studentas& asmuo);
void medianos_skaiciavimas(studentas& asmuo);
void galutinio_balo_skaiciavimas(studentas& asmuo);
void pazymiu_suvedimas(studentas& asmuo);
void egzamino_suvedimas(studentas& asmuo);
void duomenu_suvedimas(studentas& asmuo);
void vidurkio_vaizdavimas(std::vector<studentas> &asmuo);
void medianos_vaizdavimas(std::vector<studentas> &asmuo);
void rezultatu_vaizdavimas();
void prideti_mokini();
std::string irasymo_pasirinkimas();
bool pavardes_rusiavimas(const studentas& asmuo1, const studentas& asmuo2);
void failo_nuskaitymas();

#endif