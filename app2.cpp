#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iomanip>

#include "shared/classes/Elev.h"
#include "shared/classes/Nota.h"
#include "shared/classes/Absenta.h"
#include "shared/classes/CerereMotivare.h"
#include "shared/classes/Data.h"

// cai catre fisiere
const std::string CALE_ELEVI = "shared/files/elevi.txt";
const std::string CALE_NOTE = "shared/files/note.txt";
const std::string CALE_ABSENTE = "shared/files/absente.txt";
const std::string CALE_CERERI = "shared/files/cereri_motivare.txt";

// functii pentru citire si scriere
template <typename T>
std::vector<T> citesteDinFisier(const std::string& cale) {
    std::vector<T> lista;
    std::ifstream fin(cale);
    T obiect;
    while (fin >> obiect) {
        lista.push_back(obiect);
    }
    fin.close();
    return lista;
}

template <typename T>
void scrieInFisier(const std::vector<T>& lista, const std::string& cale) {
    std::ofstream fout(cale);
    for (const auto& obiect : lista) {
        fout << obiect << "\n";
    }
    fout.close();
}

// inlocuim _ cu spatiu pentru afisare
std::string formateazaNume(std::string nume) {
    for (size_t i = 0; i < nume.length(); i++) {
        if (nume[i] == '_') {
            nume[i] = ' ';
        }
    }
    return nume;
}

// calculam si afisam mediile pe materii
void afiseazaMediiElev(int idElev, const std::vector<Nota>& note) {
    std::map<std::string, std::vector<double>> notePeMaterii;
    
    for (const auto& n : note) {
        if (n.getIdElev() == idElev) {
            notePeMaterii[n.getMaterie()].push_back(n.getValoare());
        }
    }

    if (notePeMaterii.empty()) {
        std::cout << "Elevul nu are nicio nota in catalog.\n";
        return;
    }

    std::cout << "Situate note si medii:\n";
    for (const auto& pereche : notePeMaterii) {
        double suma = 0;
        for (double val : pereche.second) {
            suma += val;
        }
        double medie = suma / pereche.second.size();
        std::cout << "Materie: " << pereche.first 
                  << " | Note: ";
        for (double val : pereche.second) {
            std::cout << val << " ";
        }
        std::cout << "| Media: " << std::fixed << std::setprecision(2) << medie << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Eroare: Lipseste comanda.\n";
        std::cout << "Exemplu: ./app_2.exe vizualizare_catalog\n";
        return 1;
    }

    std::string comanda = argv[1];

    // incarcam datele din fisiere
    std::vector<Elev> elevi = citesteDinFisier<Elev>(CALE_ELEVI);
    std::vector<Nota> note = citesteDinFisier<Nota>(CALE_NOTE);
    std::vector<Absenta> absente = citesteDinFisier<Absenta>(CALE_ABSENTE);
    std::vector<CerereMotivare> cereri = citesteDinFisier<CerereMotivare>(CALE_CERERI);

    // validare argumente si executie comenzi
    if (comanda == "vizualizare_catalog") {
        if (argc != 2) {
            std::cout << "Aceasta comanda nu primeste argumente.\n";
            return 1;
        }
        std::cout << "--- CATALOG COMPLET ---" << std::endl;
        for (const auto& e : elevi) {
            std::cout << "ID: " << e.getId() << " | Nume: " << formateazaNume(e.getNume()) 
                      << " | Clasa: " << e.getClasa() << "\n";
            afiseazaMediiElev(e.getId(), note);
            std::cout << "------------------------\n";
        }
    }
    else if (comanda == "vizualizare_elev") {
        if (argc != 3) {
            std::cout << "Folosire: ./app_2.exe vizualizare_elev <id_elev>\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        bool gasit = false;
        for (const auto& e : elevi) {
            if (e.getId() == id) {
                gasit = true;
                std::cout << "Date elev: " << formateazaNume(e.getNume()) << ", Clasa " << e.getClasa() << "\n";
                afiseazaMediiElev(id, note);
                
                std::cout << "\nAbsente:\n";
                bool areAbsente = false;
                for (const auto& a : absente) {
                    if (a.getIdElev() == id) {
                        areAbsente = true;
                        std::cout << a.getMaterie() << " - Data: " << a.getData() 
                                  << " - Status: " << (a.isMotivata() ? "Motivata" : "Nemotivata") << "\n";
                    }
                }
                if (!areAbsente) std::cout << "Nu are nicio absenta.\n";
                break;
            }
        }
        if (!gasit) std::cout << "Nu exista niciun elev cu ID-ul " << id << ".\n";
    }
    else if (comanda == "adaugare_elev") {
        if (argc != 5) {
            std::cout << "Folosire: ./app_2.exe adaugare_elev <id> <nume_complet> <clasa>\n";
            std::cout << "Atentie: Folositi _ in loc de spatiu pentru nume (ex: Popa_Ion)\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        std::string nume = argv[3];
        int clasa = std::stoi(argv[4]);

        for (const auto& e : elevi) {
            if (e.getId() == id) {
                std::cout << "Exista deja un elev cu acest ID.\n";
                return 1;
            }
        }

        Elev elevNou(id, nume, clasa);
        elevi.push_back(elevNou);
        scrieInFisier(elevi, CALE_ELEVI);
        std::cout << "Elevul " << formateazaNume(nume) << " a fost adaugat cu succes.\n";
    }
    else if (comanda == "stergere_elev") {
        if (argc != 3) {
            std::cout << "Folosire: ./app_2.exe stergere_elev <id_elev>\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        
        auto it = std::remove_if(elevi.begin(), elevi.end(), [id](const Elev& e) {
            return e.getId() == id;
        });
        
        if (it != elevi.end()) {
            elevi.erase(it, elevi.end());
            scrieInFisier(elevi, CALE_ELEVI);
            
            // stergem si notele, absentele si cererile asociate elevului
            note.erase(std::remove_if(note.begin(), note.end(), [id](const Nota& n) { return n.getIdElev() == id; }), note.end());
            absente.erase(std::remove_if(absente.begin(), absente.end(), [id](const Absenta& a) { return a.getIdElev() == id; }), absente.end());
            cereri.erase(std::remove_if(cereri.begin(), cereri.end(), [id](const CerereMotivare& c) { return c.getIdElev() == id; }), cereri.end());
            
            scrieInFisier(note, CALE_NOTE);
            scrieInFisier(absente, CALE_ABSENTE);
            scrieInFisier(cereri, CALE_CERERI);
            
            std::cout << "Elevul si toate datele sale au fost sterse.\n";
        } else {
            std::cout << "Nu exista niciun elev cu ID-ul " << id << ".\n";
        }
    }
    else if (comanda == "adaugare_nota") {
        if (argc != 8) {
            std::cout << "Folosire: ./app_2.exe adaugare_nota <id> <materie> <valoare> <zi> <luna> <an>\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        std::string materie = argv[3];
        double valoare = std::stod(argv[4]);
        Data data(std::stoi(argv[5]), std::stoi(argv[6]), std::stoi(argv[7]));

        bool elevExista = false;
        for (const auto& e : elevi) if (e.getId() == id) elevExista = true;
        
        if (!elevExista) {
            std::cout << "Nu exista niciun elev cu ID-ul " << id << ".\n";
            return 1;
        }

        Nota notaNoua(id, materie, valoare, data);
        note.push_back(notaNoua);
        scrieInFisier(note, CALE_NOTE);
        std::cout << "Nota adaugata cu succes.\n";
    }
    else if (comanda == "stergere_nota") {
        if (argc != 7) {
            std::cout << "Folosire: ./app_2.exe stergere_nota <id> <materie> <zi> <luna> <an>\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        std::string materie = argv[3];
        Data data(std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6]));

        auto it = std::remove_if(note.begin(), note.end(), [&](const Nota& n) {
            return n.getIdElev() == id && n.getMaterie() == materie && n.getData() == data;
        });

        if (it != note.end()) {
            note.erase(it, note.end());
            scrieInFisier(note, CALE_NOTE);
            std::cout << "Nota a fost stearsa.\n";
        } else {
            std::cout << "Nu s-a gasit nota cu aceste detalii.\n";
        }
    }
    else if (comanda == "adaugare_absenta") {
        if (argc != 7) {
            std::cout << "Folosire: ./app_2.exe adaugare_absenta <id> <materie> <zi> <luna> <an>\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        std::string materie = argv[3];
        Data data(std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6]));

        bool elevExista = false;
        for (const auto& e : elevi) if (e.getId() == id) elevExista = true;
        
        if (!elevExista) {
            std::cout << "Nu exista niciun elev cu ID-ul " << id << ".\n";
            return 1;
        }

        Absenta absentaNoua(id, materie, data, false);
        absente.push_back(absentaNoua);
        scrieInFisier(absente, CALE_ABSENTE);
        std::cout << "Absenta adaugata cu succes.\n";
    }
    else if (comanda == "stergere_absenta") {
        if (argc != 7) {
            std::cout << "Folosire: ./app_2.exe stergere_absenta <id> <materie> <zi> <luna> <an>\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        std::string materie = argv[3];
        Data data(std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6]));

        auto it = std::remove_if(absente.begin(), absente.end(), [&](const Absenta& a) {
            return a.getIdElev() == id && a.getMaterie() == materie && a.getData() == data;
        });

        if (it != absente.end()) {
            absente.erase(it, absente.end());
            scrieInFisier(absente, CALE_ABSENTE);
            std::cout << "Absenta a fost stearsa.\n";
        } else {
            std::cout << "Nu s-a gasit absenta cu aceste detalii.\n";
        }
    }
    else if (comanda == "motivare_absenta") {
        if (argc != 7) {
            std::cout << "Folosire: ./app_2.exe motivare_absenta <id> <materie> <zi> <luna> <an>\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        std::string materie = argv[3];
        Data data(std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6]));

        bool gasita = false;
        for (auto& a : absente) {
            if (a.getIdElev() == id && a.getMaterie() == materie && a.getData() == data) {
                a.setMotivata(true);
                gasita = true;
                break;
            }
        }

        if (gasita) {
            scrieInFisier(absente, CALE_ABSENTE);
            std::cout << "Absenta a fost motivata.\n";
        } else {
            std::cout << "Nu s-a gasit absenta pentru a fi motivata.\n";
        }
    }
    else if (comanda == "vizualizare_cereri") {
        if (argc != 2) {
            std::cout << "Aceasta comanda nu primeste argumente.\n";
            return 1;
        }
        std::cout << "--- CERERI DE MOTIVARE ---\n";
        if (cereri.empty()) {
            std::cout << "Nu exista nicio cerere depusa.\n";
        } else {
            for (const auto& c : cereri) {
                std::cout << "ID Elev: " << c.getIdElev() << " | Materie: " << c.getMaterie() 
                          << " | Data: " << c.getData() << "\n";
            }
        }
    }
    else if (comanda == "aprobare_cerere") {
        if (argc != 7) {
            std::cout << "Folosire: ./app_2.exe aprobare_cerere <id> <materie> <zi> <luna> <an>\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        std::string materie = argv[3];
        Data data(std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6]));

        // cautam cererea
        auto itCerere = std::remove_if(cereri.begin(), cereri.end(), [&](const CerereMotivare& c) {
            return c.getIdElev() == id && c.getMaterie() == materie && c.getData() == data;
        });

        if (itCerere != cereri.end()) {
            cereri.erase(itCerere, cereri.end());
            scrieInFisier(cereri, CALE_CERERI);

            // motivam absenta corespunzatoare
            bool absentaGasita = false;
            for (auto& a : absente) {
                if (a.getIdElev() == id && a.getMaterie() == materie && a.getData() == data) {
                    a.setMotivata(true);
                    absentaGasita = true;
                    break;
                }
            }
            scrieInFisier(absente, CALE_ABSENTE);
            
            if (absentaGasita) {
                std::cout << "Cererea a fost aprobata, absenta a fost motivata si cererea a fost stearsa din lista.\n";
            } else {
                std::cout << "Cererea a fost stearsa, dar nu s-a gasit absenta corespunzatoare in catalog.\n";
            }
        } else {
            std::cout << "Nu exista nicio cerere cu aceste detalii.\n";
        }
    }
    else {
        std::cout << "Comanda necunoscuta: " << comanda << "\n";
        return 1;
    }

    return 0;
}