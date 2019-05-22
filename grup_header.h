#ifndef GRUP_HEADER_H
#define GRUP_HEADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Participant {
private:
    static int idGenerator;
    int id;
    string nume;
    int camera;
    bool micDejun;
public:
    Participant()
    {

    }
    Participant(string nume, int camera)
    {
        this->nume = nume;
        this->camera = camera;
        this->id = idGenerator;
        idGenerator++ ;
    }
    Participant(string nume)
    {
        this->nume = nume;
        this->id = idGenerator;
        idGenerator++ ;
    }
    //destructorul ramane gol deoarece stringul se va distruge singur
    ~Participant() {}
    friend istream &operator>>(istream &input, Participant &p)
    {
        input >> p.nume;
        string i;
        input >> i;
        if(i == "da")
            p.micDejun = true;
        else if(i == "nu")
            p.micDejun = false;
        else throw invalid_argument("Error! Must specifiy if the person wants breakfast or not");
        return input;

    }
    friend ostream &operator<<(ostream &output, const Participant &p)
    {
        output << p.nume << '\n';
        if(p.micDejun == true)
            output << "da" << '\n';
        else if(p.micDejun == false)
            output << "nu" << '\n';
        return output;
    }

    static Participant citesteParticipantCazat(istream &input)
    {
        string temp;
        Participant p;

        input >> p.nume;
        input >> temp;
        if (temp == "da")
            p.micDejun = true;
        else
            p.micDejun = false;

        return p;
    }

    static void scrieParticipantCazat(ostream &output, Participant p)
    {
        output << p.nume << '\n';
        if(p.micDejun == true)
            output << "da" << '\n';
        else if(p.micDejun == false)
            output << "nu" << '\n';
    }
};

int Participant::idGenerator = 1;

class Grup{
private:
    static int idGrupGenerator;
    int id;
    int nrParticipanti;
    vector<Participant> participanti;
    int perioada;
    int sosire;
    int nrSala;
    string tipSala;
    string numeSala;
    int nrCamereOcupate;
    int nrApartamenteOcupate;

public:
    Grup()
    {

    }
    Grup(int nrParticipanti, int perioada, vector<Participant> participanti)
    {
        this->id = idGrupGenerator;
        idGrupGenerator++;
        this->nrParticipanti = nrParticipanti;
        this->perioada = perioada;
        this->participanti = participanti;
    }
    ~Grup()
    {

    }
    friend istream &operator >> (istream &input, Grup &G)
    {
        Participant temp;
        try {
            input >> G.nrParticipanti;
            for(int i = 0; i < G.nrParticipanti; i++)
            {
                input >> temp;
                G.participanti.push_back(temp);
            }
            input >> G.perioada;
            if(G.perioada < 1 || G.perioada > 10)
                throw invalid_argument("Perioada de sedere trebuie sa fie de minim o noapte, respectiv maxim 10 nopti");
            input >> G.tipSala;
        }
        catch(exception e) {

        }


        return input;
    }
    friend ostream &operator <<(ostream &output, const Grup &G)
    {
        output << G.nrParticipanti;
        output << '\n';
        for(int i = 0; i < G.nrParticipanti; i++)
            output << G.participanti[i];
        output << G.perioada << '\n';
        output << G.tipSala <<'\n';
        return output;
    }

    static Grup citesteGrupCazat(istream &input)
    {
        Grup G;
        Participant temp;
        try {
            input >> G.nrParticipanti;
            for(int i = 0; i < G.nrParticipanti; i++)
            {
                temp = Participant::citesteParticipantCazat(input);
                G.participanti.push_back(temp);
            }
            input >> G.perioada;
            input >> G.sosire;
            if(G.perioada < 1 || G.perioada > 10)
                throw invalid_argument("Perioada de sedere trebuie sa fie de minim o noapte, respectiv maxim 10 nopti");
            input >> G.nrCamereOcupate;
            input >> G.nrApartamenteOcupate;
            input >> G.tipSala;
            input.get();
            getline(input, G.numeSala);
            //input.get();
        }
        catch(exception e) {

        }

        return G;
    }

    static void scrieGrupCazat(ostream &output, Grup G)
    {
        output << G.nrParticipanti;
        output << '\n';
        for(int i = 0; i < G.nrParticipanti; i++)
            Participant::scrieParticipantCazat(output, G.participanti[i]);
        output << G.perioada << '\n';
        output << G.sosire << '\n';
        output << G.nrCamereOcupate << " " << G.nrApartamenteOcupate << '\n';
        output << G.tipSala <<'\n';
        output << G.numeSala << '\n';
    }

    /*
     * Metode Get + Set
     */

    int get_id()
    {
        return id;
    }
    int get_nrParticipanti()
    {
        return nrParticipanti;
    }
    vector<Participant> get_participanti()
    {
        return participanti;
    }
    string get_tipSala()
    {
        return tipSala;
    }
    int get_perioada()
    {
        return perioada;
    }
    int get_sosire()
    {
        return sosire;
    }
    int get_nrCamereOcupate()
    {
        return nrCamereOcupate;
    }
    int get_nrApartamenteOcupate()
    {
        return nrApartamenteOcupate;
    }
    void set_sosire(int sosire)
    {
        this->sosire = sosire;
    }
    void set_nrCamereOcupate(int nrCamereOcupate)
    {
        this->nrCamereOcupate = nrCamereOcupate;
    }
    void set_nrApartamenteOcupate(int nrApartamenteOcupate)
    {
        this->nrApartamenteOcupate = nrApartamenteOcupate;
    }
    void set_numeSala(string numeSala)
    {
        this->numeSala = numeSala;
    }

    void cazeaza(int sosire, int nrCamereOcupate, int nrApartamenteOcupate, string numeSala)
    {
        this->sosire = sosire;
        this->nrCamereOcupate = nrCamereOcupate;
        this->nrApartamenteOcupate = nrApartamenteOcupate;
        this->numeSala = numeSala;
    }

    void citire_CazariConfirmate(istream &in, Grup &G)
    {
        Participant temp;

        in >> G.nrParticipanti;
        for(int i = 0; i < G.nrParticipanti; i++)
        {
            in>> temp;
            G.participanti.push_back(temp);
        }
        in >> G.perioada;
        if(G.perioada < 1 || G.perioada > 10)
            throw invalid_argument("Perioada de sedere trebuie sa fie de minim o noapte, respectiv maxim 10 nopti");
        in >> G.sosire;
        in >> G.tipSala;

    }
    void afisare_CazariConfirmate(ostream &out, Grup &G)
    {
        out <<G.nrParticipanti << '\n';
        for(int i = 0; i < G.nrParticipanti; i++)
            out << G.participanti[i];
        out << G.perioada << '\n';
        out << G.sosire << '\n';
        out << G.tipSala <<'\n';
    }

};

int Grup:: idGrupGenerator = 1;


#endif