#pragma once
#include "hotel_header.h"
#include "grup_header.h"

void afisare_cereri()
{
    ifstream in("cereri_cazare.txt");
    Grup G;
    int indice = 0;

    cout<<"\n---------------------\n\n";
    while((in >> G).good())
    {
        cout << "indice: " << indice++ << '\n';
        cout << G ;
        cout << "\n---------------------\n\n";
        G = Grup();
    }
}

vector<Grup> extrage_cereri()
{
    vector<Grup> cereri = vector<Grup>();
    Grup G;

    ifstream in("cereri_cazare.txt");
    while((in >> G).good())
    {
        cereri.push_back(G);
        G = Grup();
    }

    return cereri;
}

void afisare_cazari()
{
    ifstream in("cazari.txt");
    Grup G;
    int indice = 0;
    int nrCazari = 0;

    in >> nrCazari;

    cout<<"\n---------------------\n\n";

    for (int i = 0; i < nrCazari; i++)
    {
        cout << "indice: " << indice++ << '\n';
        G = Grup::citesteGrupCazat(in);
        Grup::scrieGrupCazat(cout, G);
        cout << "\n---------------------\n\n";
        G = Grup();
    }

    return;
}

vector<Grup> extrage_cazari()
{
    ifstream in("cazari.txt");
    vector<Grup> cazari = vector<Grup>();
    Grup G;
    int nrCazari = 0;

    in >> nrCazari;

    for (int i = 0; i < nrCazari; i++)
    {
        G = Grup::citesteGrupCazat(in);
        cazari.push_back(G);
        G = Grup();
    }

    return cazari;
}

void adauga_cerere()
{
    ofstream out("cereri_cazare.txt", ofstream :: app);

    Grup G;
    cin >> G;
    out << G;
}

void adauga_hotel()
{
    ofstream out("hotel.txt");

    Hotel H;
    cin >> H;
    out << H;
}

void anuleaza_cerere()
{
    int x, nr = 0;
    Grup G;
    vector<Grup> w;

    ifstream in("cereri_cazare.txt");

    cout << "Cererile de cazare sunt:" << '\n';

    while(in >> G)
    {
        nr++;
        w.push_back(G);
        cout << "Cererea cu numarul " << nr << " :" << '\n';
        cout << G << '\n';
        G = Grup();
        cout << "-----------------------";
    }

    in.close();

    cout << "Alegeti cererea pe care doriti sa o anulati:" << '\n';

    cin >> x;

    w.erase(w.begin() + (x - 1));
    nr--;

    ofstream out("cereri_cazare.txt");
    cout << "Cererile ramase sunt:" << '\n';

    for(int i = 0; i <  w.size(); i++)
    {
        out << w[i];
        cout << "Cererea cu numarul "<< i << ":" << '\n';
        cout << w[i];
        cout << " ------------------------";
    }

    out.close();
}

void cazeaza(Hotel H)
{
    ifstream in("cereri_cazare.txt");
    ofstream out("cazari_confirmate.txt", ofstream::app);

    Grup G;
    int indice_cerere_operata;
    Grup cerere_operata;

    cout << "Cererile active sunt:\n";
    afisare_cereri();

    vector<Grup> cereri = extrage_cereri();

    cout << "Selectati cererea pe care doriti sa o operati introducand indicele:\n";
    cin >> indice_cerere_operata;
    if (indice_cerere_operata < 0 || indice_cerere_operata >= cereri.size()) {
        cout << "Indicele introdus este incorect.\n";
        return;
    }

    G = cereri[indice_cerere_operata];
    cout << "Cererea selectata este urmatoarea:\n";
    cout << G;

    string numeSala = "";
    vector<SalaConferinta> saliConferinta = H.getSaliConferinta();
    for (int i = 0; i < H.get_nrSaliConferinta(); i++) {
        if (G.get_tipSala() == saliConferinta[i].get_tip() && G.get_nrParticipanti() < saliConferinta[i].get_capacitate())
            numeSala = saliConferinta[i].get_nume();
    }

    if (numeSala == "")
    {
        cout << "Nu a fost gasita o sala de sedinte pentru cererea selectata.\n";
        return;
    }

    cout << "\n\nCazarile confirmate sunt:\n";
    afisare_cazari();

    vector<Grup> cazari = extrage_cazari();

    in.close();
    out.close();

    bool cazat = false;

    for(int i = 1; i <= 365 - G.get_perioada(); i++)
    {
        bool gasit_interval = true;
        int nrCamereOcupate = 0;
        int nrApartamenteOcupate = 0;
        int minNrCamereLibere = 999999;
        int minNrApartamenteLibere = 999999;
        int contor = 0;

        for(int j = i; j <= i + G.get_perioada() && gasit_interval == true; j++, contor++)
        {
            nrCamereOcupate = 0;
            nrApartamenteOcupate = 0;

            for (int k = 0; k < cazari.size(); k++)
            {
                if (j >= cazari[k].get_sosire() && j <= cazari[k].get_sosire() + cazari[k].get_perioada()) {
                    nrCamereOcupate += cazari[k].get_nrCamereOcupate();
                    nrApartamenteOcupate += cazari[k].get_nrApartamenteOcupate();
                }
            }

            if (H.get_nrCamere() - nrCamereOcupate < minNrCamereLibere)
                minNrCamereLibere = H.get_nrCamere() - nrCamereOcupate;
            if (H.get_nrApartamente() - nrApartamenteOcupate < minNrApartamenteLibere)
                minNrApartamenteLibere = H.get_nrApartamente() - nrApartamenteOcupate;

            if ((H.get_nrCamere() - nrCamereOcupate) * 2 + (H.get_nrApartamente() - nrApartamenteOcupate) * 4 < G.get_nrParticipanti())
                gasit_interval = false;
        }

        nrApartamenteOcupate = 0;
        nrCamereOcupate = 0;
        int nrApartamenteLibere = minNrApartamenteLibere;
        int nrCamereLibere = minNrCamereLibere;

        if (contor == G.get_perioada() + 1)
        {
            cazat = true;
            cout << "Grupul va fi cazat pe o perioada de " << G.get_perioada() << " zile, incepand cu ziua " << i << '\n';

            int nrPersoaneDeCazat = G.get_nrParticipanti();

            while (nrApartamenteLibere > 0 && nrPersoaneDeCazat >= 4) {
                nrApartamenteOcupate++;
                nrApartamenteLibere--;
                nrPersoaneDeCazat -= 4;
            }
            if (nrApartamenteLibere >= 1 && (nrCamereLibere == 0 || (nrPersoaneDeCazat == 3 && nrCamereLibere < 2)) ) {
                nrApartamenteLibere--;
                nrApartamenteOcupate++;
                nrPersoaneDeCazat = 0;
            }
            while (nrCamereLibere > 0 && nrPersoaneDeCazat >= 2) {
                nrCamereLibere--;
                nrCamereOcupate++;
                nrPersoaneDeCazat -= 2;
            }
            if (nrCamereLibere > 0 && nrPersoaneDeCazat == 1) {
                nrCamereLibere--;
                nrCamereOcupate++;
                nrPersoaneDeCazat = 0;
            }

            G.cazeaza(i, nrCamereOcupate, nrApartamenteOcupate, numeSala);

            ofstream c("cazari.txt");
            cazari.push_back(G);

            c << cazari.size() << "\n";
            for(int k = 0; k < cazari.size(); k++)
                Grup::scrieGrupCazat(c, cazari[k]);

            c.close();

            ofstream cc("cereri_cazare.txt");
            cereri.erase(cereri.begin() + indice_cerere_operata);

            for (int k = 0; k < cereri.size(); k++)
                cc << cereri[k];

            cc.close();

            break;
        }
    }

    if (cazat == false)
        cout << "Nu a fost gasita o perioada pentru cazarea grupului selectat!\n";

}