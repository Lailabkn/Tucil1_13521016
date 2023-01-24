#include <iostream>
#include <vector>
#include <sstream>
#include <istream>
#include <fstream>
#include <cstdlib>
#include <chrono>

using namespace std;

// variabel global
void inputanUser(vector<string> *kartuu);
bool iskartu(string kartu);
vector<string> pengubahKartu(vector<string> kartuu);
void kartuKeAngka(vector<string> strkartu, vector<double> *dblkartu);
void bruteForceSolver24(vector<double> kartuList, string *hasil, int *counthasil);
bool isSame(vector<vector<double>> permutasi, double a, double b, double c, double d);
void permutasiKurung(double a, double b, double c, double d, string *hasil, int *counthasil, bool *is24);
void permutasiOperan(double a, double b, double c, double d, string *hasil, int *counthasil, bool *is24, int brType);
double operan(double a, double b, char op);
string angkaKeKartu(double a);



void inputanUser(vector<string> *kartuu) {
    string tipeInputan;
    string lineInputan, kartu, namaFile, stemp;
    int i;
    int M;
    bool baik;
    ifstream ok;

    cout << "Masukkan tipe inputan (file atau keyboard): " << endl;
    cout << "1. Keyboard" << endl;
    cout << "2. File" << endl;
    cout << "3. Random" << endl;
    cout << "Pilihan: ";
    getline(cin, tipeInputan);

    if (tipeInputan == "1") {
        baik = false;
        M = 0;
        do {
            cout << "Masukkan 4 kartu : ";
            getline(cin, lineInputan);
            stringstream ss(lineInputan);

            M = 0; kartu.clear();
            while (ss >> kartu){
                if (iskartu(kartu)) {
                    kartuu->push_back(kartu);
                    M++;
                }
                else {
                    break;
                }
            }

            if (M == 4) {
                baik = true;
            }
            else {
                cout << "Input tidak valid, Ulangi!" << endl;
            }
        } while (!baik);
    }
    else if (tipeInputan == "2") {
        cout << "Masukkan nama file : ";
        getline(cin, stemp);
        namaFile = "test/" + stemp;

        ok.open(namaFile);
        if (ok.fail()) {
            ok.clear();
            cout << "File tidak ditemukan\n" << "exiting program..." << endl;
            exit(1); 
        }
        getline(ok, lineInputan);
        ok.close();

        stringstream ss(lineInputan);

        M = 0;
        while(ss >> kartu) {
            if (iskartu(kartu)) {
                kartuu->push_back(kartu);
                M++;
            }
            else {
                break;
            }
        }

        if (M != 4) {
            cout << "Isi file tidak valid!" << endl;
            exit(1);
        }
    }
    else if (tipeInputan == "3") {
        srand(time(NULL));

        for (i = 0; i < 4; i++) {
            kartuu->push_back(to_string(rand() % 13 + 1));
        }
        *kartuu = pengubahKartu(*kartuu);
    }
    else {
        cout << "Input tidak valid, exiting program..." << endl;
        exit(1);
    }
}

bool iskartu(string kartu) {
    if (kartu == "A" || kartu == "J" || kartu == "Q" || kartu == "K")
    {
        return true;
    }
    else if (kartu == "1" || kartu == "2" || kartu == "3" || kartu == "4" || kartu == "5" || kartu == "6" || kartu == "7" || kartu == "8" || kartu == "9" || kartu == "10" || kartu == "11" || kartu == "12" || kartu == "13")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void kartuKeAngka(vector<string> strkartu, vector<double> *dblkartu) {
    int i;
    string kartu;

    i = 0;
    do
    {
        if (strkartu[i] == "A")
        {
            dblkartu->push_back(1);
        }
        else if (strkartu[i] == "J")
        {
            dblkartu->push_back(11);
        }
        else if (strkartu[i] == "Q")
        {
            dblkartu->push_back(12);
        }
        else if (strkartu[i] == "K")
        {
            dblkartu->push_back(13);
        }
        else
        {
            dblkartu->push_back(stod(strkartu[i]));
        }
        i++;
    } while (i < 4);
}

vector<string> pengubahKartu(vector<string> strkartu) {
    int i;
    string kartu;

    for (i = 0; i < 4; i++)
    {
        if (strkartu[i] == "1")
        {
            strkartu[i] = "A";
        }
        else if (strkartu[i] == "11")
        {
            strkartu[i] = "J";
        }
        else if (strkartu[i] == "12")
        {
            strkartu[i] = "Q";
        }
        else if (strkartu[i] == "13")
        {
            strkartu[i] = "K";
        }
    }

    return strkartu;
}

// Proses
void bruteForceSolver24(vector<double> kartuList, string *hasil, int *counthasil) {
    vector<vector<double>> dbkartuuPermutation;
    double a, b, c, d; 
    int i, j, k, l;
    bool is24;
    int M = 0;

    is24 = false;
    *counthasil = 0;

    // Permutasi
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 4; k++)
            {
                for (l = 0; l < 4; l++)
                {
                    if (i != j && i != k && i != l && j != k && j != l && k != l)
                    {
                        a = kartuList[i];
                        b = kartuList[j];
                        c = kartuList[k];
                        d = kartuList[l];

                        if (!isSame(dbkartuuPermutation, a, b, c, d))
                        {
                            dbkartuuPermutation.push_back({ a, b, c, d });
                            permutasiKurung(a, b, c, d, hasil, counthasil, &is24);
                        }
                    }
                }
            }
        }
    }
}

bool isSame(vector<vector<double>> permutasi, double a, double b, double c, double d) {
    int i, j;
    bool isSame = false;

    for (i = 0; i < permutasi.size(); i++)
    {
        if (permutasi[i][0] == a && permutasi[i][1] == b && permutasi[i][2] == c && permutasi[i][3] == d)
        {
            isSame = true;
        }
    }

    return isSame;
}

void permutasiKurung(double a, double b, double c, double d, string *hasil, int *counthasil, bool *is24) {
    int i = 1;

    for (i = 1; i <= 5; i++)
    {
        permutasiOperan(a, b, c, d, hasil, counthasil, is24, i);
    }
}

void permutasiOperan(double a, double b, double c, double d, string *hasil, int *counthasil, bool *is24, int Tipe) {
    string op = "+-*/";
    string temphasil;
    int i, j, k;
    double aa, bb, cc, dblhasil;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 4; k++)
            {
                dblhasil = 0;
                aa = operan(a, b, op[i]);
                bb = operan(b, c, op[j]);
                cc = operan(c, d, op[k]);
                
                switch (Tipe)
                {
                case 1:
                    dblhasil = operan(aa, cc, op[j]);
                    temphasil = "(" + angkaKeKartu(a) + " " + op[i] + " " + angkaKeKartu(b) + ") " + op[j] + " (" + angkaKeKartu(c) + " " + op[k] + " " + angkaKeKartu(d) + ")";
                    break;
                case 2:
                    dblhasil = operan(operan(aa, c, op[j]), d, op[k]);
                    temphasil = "((" + angkaKeKartu(a) + " " + op[i] + " " + angkaKeKartu(b) + ") " + op[j] + " " + angkaKeKartu(c) + ") " + op[k] + " " + angkaKeKartu(d);
                    break;
                case 3:
                    dblhasil = operan(operan(a, bb, op[i]), d, op[k]);
                    temphasil = "(" + angkaKeKartu(a) + " " + op[i] + " (" + angkaKeKartu(b) + " " + op[j] + " " + angkaKeKartu(c) + ")) " + op[k] + " " + angkaKeKartu(d);
                    break;
                case 4:
                    dblhasil = operan(a, operan(bb, d, op[k]), op[i]);
                    temphasil = angkaKeKartu(a) + " " + op[i] + " ((" + angkaKeKartu(b) + " " + op[j] + " " + angkaKeKartu(c) + ") " + op[k] + " " + angkaKeKartu(d) + ")";
                    break;
                case 5:
                    dblhasil = operan(a, operan(b, cc, op[j]), op[i]);
                    temphasil = angkaKeKartu(a) + " " + op[i] + " (" + angkaKeKartu(b) + " " + op[j] + " (" + angkaKeKartu(c) + " " + op[k] + " " + angkaKeKartu(d) + "))";
                    break;
                }
                
                if (dblhasil == 24)
                {
                    *hasil += temphasil + "\n";
                    *counthasil += 1;
                    *is24 = true;
                }
            }
        }
    }
}

double operan(double a, double b, char op) {
    double hasil;

    switch (op)
    {
    case '+':
        hasil = a + b;
        break;
    case '-':
        hasil = a - b;
        break;
    case '*':
        hasil = a * b;
        break;
    case '/':
        if (b == 0)
        {
            hasil = 0;
        }
        else
        {
            hasil = a / b;
        }
        break;
    }
    return hasil;
}

string angkaKeKartu(double a) {
    string kartu;

    if (a == 1)
    {
        kartu = "A";
    }
    else if (a == 11)
    {
        kartu = "J";
    }
    else if (a == 12)
    {
        kartu = "Q";
    }
    else if (a == 13)
    {
        kartu = "K";
    }
    else
    {
        kartu = to_string((int)a);
    }
    return kartu;
}

void displaykartu(vector<string> h) {
    int i;

    for (i = 0; i < h.size(); i++) {
        cout << h[i] << " ";
    }
    cout << endl;
}

void simpanFile(string hasil, vector<string> kartuu) {
    ofstream file;
    string namafile;
    int i;

    namafile = "";
    for (i = 0; i < kartuu.size(); i++) {
        namafile += kartuu[i];
    }
    namafile += ".txt";
    file.open(namafile);
    file << hasil;
    file.close();
    cout << "Hasil telah disimpan di file " << namafile << endl;
}

int main() {
    vector<string> kartuu; 
    vector<double> kartuu1;
    string hasil;
    double executionTime;
    int counthasil;

    cout << "==================== 24 Solver : Card Game <3 ====================" << endl;
    inputanUser(&kartuu);
    kartuKeAngka(kartuu, &kartuu1);
    cout << "===============================================================" << endl;
    displaykartu(kartuu); 

    counthasil = 0;
    auto start = chrono::high_resolution_clock::now();
    bruteForceSolver24(kartuu1, &hasil, &counthasil);
    auto end = chrono::high_resolution_clock::now();
    executionTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << counthasil<< "jumlah solusi :" << endl;
    cout << hasil << endl;
    cout << "Execution time : " << executionTime << " microseconds" << endl;
    simpanFile(hasil, kartuu);

    return 0;
}