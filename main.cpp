#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "sistem_cazare.h"

using namespace std;

ifstream f("date.in");
ofstream g("date.out");


int main() {

    int rol;

    cout << "Pentru a efectua o cerere de cazare, introduceti 1." << '\n';
    cout << "Pentru a adauga un hotel, introduceti 2." << '\n';
    cout << "Pentru a administra hotelul, introduceti 3." << '\n';

    cin >> rol;
    switch(rol)
    {
        case 1:
            adauga_cerere();
            break;
        case 2:
            adauga_hotel();
            break;
        case 3:
        {
            Hotel H;
            ifstream hf("hotel.txt");
            hf >> H;
            hf.close();

            if (H.get_nume() == "") {
                cout << "Inainte de a putea opera asupra hotelului este necesara definirea lui.\n";
            }
            else {
                int y;
                cout << "Pentru a vizualiza cererile, introduceti 1." << '\n';
                cout << "Pentru a anula o cerere, introduceti 2." << '\n';
                cout << "Pentru a opera o cerere si a o confirma, introduceti 3." << '\n';
                cout << "Pentru a vizualiza cazarile confirmate, introduceti 4." << '\n';
                cin >> y;
                switch(y)
                {
                    case 1:
                        afisare_cereri();
                        break;
                    case 2:
                        anuleaza_cerere();
                        break;
                    case 3:
                        cazeaza(H);
                        break;
                    case 4:
                        afisare_cazari();
                        break;
                    default:
                        cout << "Optiunea introdusa nu este valida" << '\n';
                }
            }
        }
            break;
        default:
            cout << "Optiunea introdusa nu este valida" << '\n';
            break;

    }

}