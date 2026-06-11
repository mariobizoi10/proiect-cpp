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
    if (!fin.is_open()) {
        return lista;
    }
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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Eroare: Lipseste comanda.\n";
        std::cout << "Exemplu: ./app_1.exe vizualizare_note 1\n";
        return 1;
    }

    std::string comanda = argv[1];

    // incarcam datele din fisiere
    std::vector<Elev> elevi = citesteDinFisier<Elev>(CALE_ELEVI);
    std::vector<Nota> note = citesteDinFisier<Nota>(CALE_NOTE);
    std::vector<Absenta> absente = citesteDinFisier<Absenta>(CALE_ABSENTE);
    std::vector<CerereMotivare> cereri = citesteDinFisier<CerereMotivare>(CALE_CERERI);

    if (comanda == "vizualizare_note") {
        if (argc != 3 && argc != 4) {
            std::cout << "Folosire: ./app_1.exe vizualizare_note <id_elev> [materie]\n";
            return 1;
        }
        int id = std::stoi(argv[2]);

        if (argc == 3) {
            // afisam toate notele grupate pe materii
            std::map<std::string, std::vector<double>> notePeMaterii;
            for (const auto& n : note) {
                if (n.getIdElev() == id) {
                    notePeMaterii[n.getMaterie()].push_back(n.getValoare());
                }
            }

            if (notePeMaterii.empty()) {
                std::cout << "Elevul nu are nicio nota.\n";
            } else {
                std::cout << "Notele elevului cu ID " << id << ":\n";
                for (const auto& pereche : notePeMaterii) {
                    std::cout << pereche.first << ": ";
                    for (double val : pereche.second) {
                        std::cout << val << " ";
                    }
                    std::cout << "\n";
                }
            }
        }
        else if (argc == 4) {
            // afisam notele doar pentru o materie specifica
            std::string materie = argv[3];
            bool gasit = false;
            std::cout << "Note la " << materie << " pentru elevul cu ID " << id << ":\n";
            for (const auto& n : note) {
                if (n.getIdElev() == id && n.getMaterie() == materie) {
                    std::cout << "Nota: " << n.getValoare() << " | Data: " << n.getData() << "\n";
                    gasit = true;
                }
            }
            if (!gasit) {
                std::cout << "Nu exista note la aceasta materie.\n";
            }
        }
    }
    else if (comanda == "vizualizare_absente") {
        if (argc != 3) {
            std::cout << "Folosire: ./app_1.exe vizualizare_absente <id_elev>\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        bool areAbsente = false;

        std::cout << "Absentele elevului cu ID " << id << ":\n";
        for (const auto& a : absente) {
            if (a.getIdElev() == id) {
                std::cout << a.getMaterie() << " - Data: " << a.getData()
                          << " - Status: " << (a.isMotivata() ? "Motivata" : "Nemotivata") << "\n";
                areAbsente = true;
            }
        }
        if (!areAbsente) {
            std::cout << "Elevul nu are nicio absenta.\n";
        }
    }
    else if (comanda == "vizualizare_situatie") {
        if (argc != 3) {
            std::cout << "Folosire: ./app_1.exe vizualizare_situatie <id_elev>\n";
            return 1;
        }
        int id = std::stoi(argv[2]);

        // cautam elevul
        bool elevExista = false;
        for (const auto& e : elevi) {
            if (e.getId() == id) {
                std::cout << "Situatia scolara pentru: " << formateazaNume(e.getNume()) << " (Clasa " << e.getClasa() << ")\n";
                elevExista = true;
                break;
            }
        }

        if (!elevExista) {
            std::cout << "Nu exista niciun elev cu ID-ul " << id << ".\n";
            return 1;
        }

        // afisam note si medii
        std::map<std::string, std::vector<double>> notePeMaterii;
        for (const auto& n : note) {
            if (n.getIdElev() == id) {
                notePeMaterii[n.getMaterie()].push_back(n.getValoare());
            }
        }

        std::cout << "\n--- NOTE SI MEDII ---\n";
        if (notePeMaterii.empty()) {
            std::cout << "Nu are nicio nota.\n";
        } else {
            for (const auto& pereche : notePeMaterii) {
                double suma = 0;
                for (double val : pereche.second) suma += val;
                double medie = suma / pereche.second.size();
                std::cout << pereche.first << " | Note: ";
                for (double val : pereche.second) std::cout << val << " ";
                std::cout << "| Media: " << std::fixed << std::setprecision(2) << medie << "\n";
            }
        }

        // afisam absente
        std::cout << "\n--- ABSENTE ---\n";
        bool areAbsente = false;
        int nemotivate = 0;
        for (const auto& a : absente) {
            if (a.getIdElev() == id) {
                std::cout << a.getMaterie() << " - " << a.getData() << " (" << (a.isMotivata() ? "Motivata" : "Nemotivata") << ")\n";
                if (!a.isMotivata()) nemotivate++;
                areAbsente = true;
            }
        }
        if (!areAbsente) std::cout << "Nu are nicio absenta.\n";
        else std::cout << "Total absente nemotivate: " << nemotivate << "\n";
    }
    else if (comanda == "depunere_cerere_motivare") {
        if (argc != 7) {
            std::cout << "Folosire: ./app_1.exe depunere_cerere_motivare <id> <materie> <zi> <luna> <an>\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        std::string materie = argv[3];
        Data data(std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6]));

        // verificam daca exista absenta si daca nu e deja motivata
        bool existaAbsenta = false;
        for (const auto& a : absente) {
            if (a.getIdElev() == id && a.getMaterie() == materie && a.getData() == data) {
                if (a.isMotivata()) {
                    std::cout << "Absenta este deja motivata.\n";
                    return 1;
                }
                existaAbsenta = true;
                break;
            }
        }

        if (!existaAbsenta) {
            std::cout << "Nu exista o absenta nemotivata cu aceste date.\n";
            return 1;
        }

        // verificam sa nu fi depus deja o cerere pentru aceasta absenta
        for (const auto& c : cereri) {
            if (c.getIdElev() == id && c.getMaterie() == materie && c.getData() == data) {
                std::cout << "Exista deja o cerere depusa pentru aceasta absenta.\n";
                return 1;
            }
        }

        CerereMotivare cerereNoua(id, materie, data);
        cereri.push_back(cerereNoua);
        scrieInFisier(cereri, CALE_CERERI);
        std::cout << "Cererea a fost depusa cu succes.\n";
    }
    else if (comanda == "vizualizare_cereri") {
        if (argc != 3) {
            std::cout << "Folosire: ./app_1.exe vizualizare_cereri <id_elev>\n";
            return 1;
        }
        int id = std::stoi(argv[2]);
        bool areCereri = false;

        std::cout << "Cererile de motivare pentru elevul cu ID " << id << ":\n";
        for (const auto& c : cereri) {
            if (c.getIdElev() == id) {
                std::cout << "Materie: " << c.getMaterie() << " | Data: " << c.getData() << "\n";
                areCereri = true;
            }
        }
        if (!areCereri) {
            std::cout << "Nu exista nicio cerere depusa.\n";
        }
    }
    else {
        std::cout << "Comanda necunoscuta: " << comanda << "\n";
        return 1;
    }

    return 0;
}