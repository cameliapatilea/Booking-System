#ifndef HOTEL_HEADER_H
#define HOTEL_HEADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
class Incapere{
private:
    int id;
    static int idIncapereGenerator;
public:
    Incapere()
    {
        this->id = idIncapereGenerator;
        idIncapereGenerator++;
    }
    int get_id()
    {
        return id;
    }
};
int Incapere::idIncapereGenerator = 1;


class Camera: public Incapere{
private:
    static int capacitate;
    int nrCamera;
    bool ocupat;
public:
    Camera()
    {
        nrCamera = 0;
        ocupat = false;
    }
    Camera(int nrCamera, bool ocupat) {
        this->nrCamera = nrCamera;
        this->ocupat = ocupat;
    }
    ~Camera()
    {
        ocupat = false;
    }
    friend istream &operator >> (istream &input, Camera &c)
    {
        input >> c.nrCamera;
        return input;
    }
    friend ostream &operator << (ostream &output, const Camera &c)
    {
        output << c.nrCamera << '\n';
        return output;
    }
    /*
     * Metode Get + Set
     */
    bool get_ocupat()
    {
        return ocupat;
    }
    int get_nrCamera() const
    {
        return nrCamera;
    }

};
int Camera::capacitate = 2;


class Apartament:  public Incapere {
private:
    static int capacitate;
    int nrApartament;
    bool ocupat;

public:
    Apartament()
    {
        nrApartament = 0;
        ocupat = false;
    }
    Apartament(int nrApartament, bool ocupat)
    {
        this->nrApartament = nrApartament;
        this->ocupat = ocupat;
    }
    ~Apartament()
    {
        ocupat = false;
    }
    friend istream& operator >> (istream &input, Apartament &a)
    {
        input >> a.nrApartament;
        return input;
    }
    friend ostream& operator << (ostream &output, const Apartament &a)
    {
        output << a.nrApartament << '\n';
        return output;
    }
    /*
     * Metode Get  + Set
     */
    bool get_ocupat() const
    {
        return ocupat;
    }
    int get_nrApartament() const
    {
        return nrApartament;
    }

};
int Apartament::capacitate = 4;

class SalaConferinta:public Incapere{
private:
    string nume;
    bool proiector;
    string tip;
    int capacitate;
    int nrMese;
    vector<int> mese;
    bool ocupat;
    int nrSala;
public:
    SalaConferinta()
    {
        proiector = false;
        ocupat = false;
        nrSala = 0;
        nrMese = 0;
        capacitate = 0;

    }
    SalaConferinta(string nume, bool ocupat)
    {
        this->nume = nume;
        this->ocupat = ocupat;
    }
    ~SalaConferinta()
    {
        proiector = false;
        ocupat = false;
        nrSala = 0;
        nrMese = 0;
        capacitate = 0;
    }
    friend istream& operator>>(istream &input, SalaConferinta &s)
    {
        string temp;
        input.get();
        getline(input, s.nume);

        input >> temp;
        if (temp == "da") {
            s.proiector = true;
        }
        else {
            s.proiector = false;
        }
        input >> s.tip;

        if(s.tip == "individual")
        {
            input >> s.nrMese;
            int x;
            for(int i = 0; i < s.nrMese; i++)
            {
                input >> x;
                if(x < 4 || x > 8)
                    throw invalid_argument("Masa trebuie sa aiba intre 4 si 8 locuri");
                else {
                    s.mese.push_back(x);
                    s.capacitate += x;
                }
            }
        }
        else if (s.tip == "scena")
        {
            input >> s.capacitate;
        }
        else
            throw invalid_argument("Nu exista o astfel de sala de conferinte");
        return input;

    }
    friend ostream& operator<<(ostream &output, const SalaConferinta &s)
    {


        output << s.nume << '\n';
        output << s.tip << '\n';
        output << s.capacitate << '\n';
        if(s.tip == "individual")
        {
            output << s.nrMese << '\n';
            for(int i = 0; i < s.nrMese; i++)
                output << s.mese[i] << " ";
        }
        return output;

    }
    /*
     * Metode Get + Set
     */
    int get_nrMese() const
    {
        return nrMese;
    }
    int get_capacitate() const
    {
        return capacitate;
    }
    bool get_ocupat() const
    {
        return ocupat;
    }
    int get_nrSala() const
    {
        return nrSala;
    }
    vector<int> get_mese() const
    {
        return mese;
    }
    string get_nume() const
    {
        return nume;
    }
    string get_tip() const
    {
        return tip;
    }
    bool get_proiector() const
    {
        return proiector;
    }
};


class Hotel{
private:
    string nume;
    int nrIncaperiDestinateCazarii;
    int capacitateRestaurant;
    int capacitateDeCazare;
    int nrCamere;
    vector<Camera> camere;
    int nrApartamente;
    vector<Apartament> apartamente;
    int nrSaliConferinta;
    vector<SalaConferinta> saliConferinta;
public:
    Hotel()
    {
        nume = "";
        nrIncaperiDestinateCazarii = 0;
        capacitateRestaurant = 0;
        capacitateDeCazare = 0;
        nrCamere = 0;
        camere = vector<Camera>();
        nrApartamente = 0;
        apartamente = vector<Apartament>();
        nrSaliConferinta = 0;
        saliConferinta = vector<SalaConferinta>();
    }

    Hotel(string nume, int capacitateRestaurant,
          int nrCamere, vector<Camera> camere,
          int nrApartamente, vector<Apartament> apartamente,
          int nrSaliConferinta, vector<SalaConferinta>)
    {
        this->nume = nume;
        this->capacitateRestaurant = capacitateRestaurant;

        this->nrCamere = nrCamere;
        this->camere = camere;

        this->nrApartamente = nrApartamente;
        this->apartamente = apartamente;

        this->nrSaliConferinta = nrSaliConferinta;
        this->saliConferinta = saliConferinta;

        this->capacitateDeCazare = 2 * nrCamere + 4 * nrApartamente;
        this->nrIncaperiDestinateCazarii = nrCamere + nrApartamente;
    }

    ~Hotel() {}

    friend istream &operator>>(istream &input, Hotel &h)
    {
        int x;

        getline(input, h.nume);
        input >> h.nrCamere;
        for (int i = 0; i < h.nrCamere; i++)
        {
            input>>x;
            h.camere.push_back(Camera(x, false));
        }
        input >> h.nrApartamente;
        for (int i = 0; i < h.nrApartamente; i++)
        {
            input>>x;
            h.apartamente.push_back(Apartament(x, false));
        }
        input >> h.nrSaliConferinta;

        for (int i = 0; i < h.nrSaliConferinta; i++)
        {
            input.get();
            SalaConferinta sc;
            input >> sc;
            h.saliConferinta.push_back(sc);
        }
        input >> h.capacitateRestaurant;

        return input;
    }
    friend ostream &operator<<(ostream &output, const Hotel &h)
    {
        output << h.nume << '\n';
        output << h.nrCamere << '\n';
        for (int i = 0; i < h.nrCamere; i++) {
            output << h.camere[i].get_nrCamera() << " ";
        }
        output << '\n';
        output << h.nrApartamente << '\n';
        for (int i = 0; i < h.nrApartamente; i++) {
            output << h.apartamente[i].get_nrApartament() << " ";
        }
        output << '\n';
        output << h.nrSaliConferinta << '\n';
        for (int i = 0; i < h.nrSaliConferinta; i++) {
            output << h.saliConferinta[i].get_nume() << '\n';
            if (h.saliConferinta[i].get_proiector() == true)
                output << "da\n";
            else
                output << "nu\n";
            output << h.saliConferinta[i].get_tip() << '\n';
            if (h.saliConferinta[i].get_tip() == "individual") {
                output << h.saliConferinta[i].get_nrMese() << '\n';
                vector<int> mese = h.saliConferinta[i].get_mese();
                for (int j = 0; j < h.saliConferinta[i].get_nrMese(); j++)
                    output << mese[j] << " ";
                output << '\n';
            }
            else
                output << h.saliConferinta[i].get_capacitate() << '\n';
        }

        output << h.capacitateRestaurant << '\n';
        return output;
    }

    /*
     * Metode Get + Set
     */
    string get_nume() const
    {
        return nume;
    }
    int get_nrIncaperiDestinateCazarii() const
    {
        return nrIncaperiDestinateCazarii;
    }
    int get_capacitateDeCazare() const
    {
        return capacitateDeCazare;
    }
    int get_capacitateRestaurant() const
    {
        return capacitateRestaurant;
    }
    int get_nrCamere() const
    {
        return nrCamere;
    }
    vector<Camera> get_camere() const
    {
        return camere;
    }
    int get_nrApartamente() const
    {
        return nrApartamente;
    }
    vector<Apartament> getApartamente() const
    {
        return apartamente;
    }
    int get_nrSaliConferinta() const
    {
        return nrSaliConferinta;
    }
    vector<SalaConferinta> getSaliConferinta() const
    {
        return saliConferinta;
    }

};


#endif