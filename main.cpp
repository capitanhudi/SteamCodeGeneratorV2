#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <time.h>
#include <ctime>
#include <windows.h>

using namespace std;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main()
{
    string desktop = getenv("USERPROFILE");
    desktop += "\\Desktop\\";

    srand(time(NULL));
    char alphabet[26];
    for (int ch = 'A'; ch <= 'Z'; ch++)
    {
        alphabet[ch - 'A'] = ch;
    }
    char numbers[11] = {"0123456789"};

    int num = 0;
    ifstream file;
    while (true)
    {
        if (num == 0)
        {
            file.open(desktop + "steamkeys.txt");
            if (file)
            {
                num++;
                file.close();
            }
            else
            {
                break;
                file.close();
            }
        }
        else
        {
            string fname = desktop + "steamkeys(" + to_string(num) + ").txt ";
            file.open(fname);
            if (file)
            {
                num++;
                file.close();
            }
            else
            {
                break;
                file.close();
            }
        }
    }

    ofstream fout;
    string filename = "steamkeys" + (num == 0 ? "" : ("(" + to_string(num) + ")")) + ".txt";
    fout.open(desktop + filename);

    int count{};
    cout << "Kac tane key istiyon:";
    cin >> count;
    cout << "\n";
    ShowConsoleCursor(false);

    int letterProb = 55;
    int numProb = 45;
    int keyLenght = 5;
    int pBarWidth = 80;
    float progress{};

    cout << "Dosyalar hazirlaniyor..." << endl;

    string line{};
    for (int i = 0; i < count; i++)
    {
        clock_t begin_time = clock();
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < keyLenght; k++)
            {
                if (rand() % (letterProb + numProb) < numProb)
                {
                    line += numbers[rand() % 10];
                }
                else
                {
                    line += alphabet[rand() % 26];
                }
            }
            if (j != 2)
            {
                line += "-";
            }
        }
        fout << line << endl;
        line = "";

        cout << "[";
        int pos = pBarWidth * progress;
        for (int l = 0; l < pBarWidth; ++l)
        {
            if (l < pos)
                std::cout << "#";
            else if (l == pos)
                std::cout << "#";
            else
                std::cout << " ";
        }

        float t = round(float(clock() - begin_time) / CLOCKS_PER_SEC * (count - i));
        cout << "] " << progress * 100 << "%"
             << " - tahmini sure " << t << " saniye\r";
        cout.flush();
        progress = float(i) / float(count);
    }
    fout.close();

    cout << "Dosyalar hazir. Masaustune bak ;)" << endl;

    system("pause");

    return 0;
}
