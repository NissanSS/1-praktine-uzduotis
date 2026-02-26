#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

struct Rates {
    double bendras;
    double pirkti;
    double parduoti;
};

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string toUpper(string s) {
    for (char &c : s) c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
    return s;
}

bool isSupportedCurrency(const string& c) {
    return (c == "EUR" || c == "GBP" || c == "USD" || c == "INR");
}

Rates getRates(const string& code) {
    const Rates GBP{0.8729, 0.8600, 0.9220};
    const Rates USD{1.1793, 1.1460, 1.2340};
    const Rates INR{104.6918, 101.3862, 107.8546};

    if (code == "GBP") return GBP;
    if (code == "USD") return USD;
    return INR;
}

int main() {
    cout << fixed << setprecision(2);

    cout << "== VALIUTOS ==" << endl;
    cout << "Palaikomos valiutos: EUR, GBP, USD, INR" << endl;

    // 1) Pirma valiuta
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

    // 2) Pora su EUR
    string nonEur;
    Rates r{};

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
        r = getRates(nonEur);
    } else {
        nonEur = first;
        r = getRates(nonEur);
        cout << "Pasirinkai " << nonEur << ". Visi veiksmai bus tik su EUR." << endl;
    }

    // 3) Veiksmas
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

    // 4) Pusė darbo: veikia palyginimas ir pirkimas (pardavimas dar bus kitame commit)
    double amount = 0.0;

    if (action == 1) {
        int dir = 0;
        while (true) {
            cout << "\nKryptis:\n";
            cout << "1 - EUR -> " << nonEur << "\n";
            cout << "2 - " << nonEur << " -> EUR\n";
            cout << "Pasirink (1/2): ";
            if (!(cin >> dir)) { clearInput(); continue; }
            if (dir != 1 && dir != 2) {
                cout << "Neteisinga kryptis." << endl;
                continue;
            }
            break;
        }

        while (true) {
            cout << "Ivesk kieki: ";
            if (!(cin >> amount)) { clearInput(); continue; }
            if (amount < 0) { cout << "Suma negali buti neigiama." << endl; continue; }
            break;
        }

        if (dir == 1) {
            double result = amount * r.bendras;
            cout << amount << " EUR = " << result << " " << nonEur << " (bendras)" << endl;
        } else {
            double result = amount / r.bendras;
            cout << amount << " " << nonEur << " = " << result << " EUR (bendras)" << endl;
        }
    }
    else if (action == 2) {
        while (true) {
            cout << "Ivesk kiek EUR nori pirkti: ";
            if (!(cin >> amount)) { clearInput(); continue; }
            if (amount < 0) { cout << "Suma negali buti neigiama." << endl; continue; }
            break;
        }

        double result = amount * r.pirkti;
        cout << "Uz " << amount << " EUR gausi " << result << " " << nonEur << " (pirkti)" << endl;
    }
    else {
        cout << "\n[Puse darbo] Pardavimo funkcija bus prideta kitame atnaujinime." << endl;
    }

    return 0;
}