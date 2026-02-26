#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

string toUpper(string s) {
    for (char &c : s) c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
    return s;
}

bool isSupportedCurrency(const string& c) {
    return (c == "EUR" || c == "GBP" || c == "USD" || c == "INR");
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    cout << fixed << setprecision(2);

    cout << "== VALIUTOS ==" << endl;
    cout << "Palaikomos valiutos: EUR, GBP, USD, INR" << endl;

    string first;
    while (true) {
        cout << "Ivesk pirma valiuta (pvz. EUR): ";
        cin >> first;
        first = toUpper(first);

        if (!isSupportedCurrency(first)) {
            cout << "Neteisinga valiuta. Bandyk dar karta." << endl;
            continue;
        }
        break;
    }

    string nonEur;
    if (first == "EUR") {
        while (true) {
            cout << "I kokia valiuta dirbsi (GBP/USD/INR): ";
            cin >> nonEur;
            nonEur = toUpper(nonEur);

            if (nonEur == "EUR") {
                cout << "Reikia pasirinkti ne EUR valiuta." << endl;
                continue;
            }
            if (!(nonEur == "GBP" || nonEur == "USD" || nonEur == "INR")) {
                cout << "Neteisinga valiuta. Galimos: GBP, USD, INR." << endl;
                continue;
            }
            break;
        }
    } else {
        nonEur = first;
        cout << "Pasirinkai " << nonEur << ". Visi veiksmai bus tik su EUR." << endl;
    }

    int action = 0;
    while (true) {
        cout << "\nPasirink veiksma:" << endl;
        cout << "1 - Valiutos kurso palyginimas (EUR <-> " << nonEur << ")" << endl;
        cout << "2 - Pirkti valiuta (EUR -> " << nonEur << ")" << endl;
        cout << "3 - Parduoti valiuta (" << nonEur << " -> EUR)" << endl;
        cout << "Pasirinkimas (1/2/3): ";

        if (!(cin >> action)) { clearInput(); continue; }
        if (action < 1 || action > 3) {
            cout << "Neteisingas pasirinkimas." << endl;
            continue;
        }
        break;
    }

    cout << "\n[Darbo pradzia] Pasirinkta valiutu pora: EUR <-> " << nonEur
         << ", veiksmas: " << action << endl;
    cout << "Konvertavimo logika bus prideta kitame atnaujinime." << endl;

    return 0;
}