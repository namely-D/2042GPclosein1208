void R6(int &option)
{
    string ans;
    do
    {
        cout << "Would you like to exit now? (Yes/No): ";
        cin >> ans;

        if (ans == "Y" || ans == "y")
        {
            cout << "Group Member: \n";
            cout << "WONG Yam Chung 25015029A   A02A\n";
            cout << "KWAN Sze Man   25036800A   A02A\n";
            cout << "CHEN Jinxiang  25040155A   A02B\n";
            cout << "FU Kei Leung   25099927A   A02B\n";
            cout << "CHOW Nok Hei   25201465A   A02A\n";
            cout << "NG Lap Yin     25204013A   A02C\n";
            option =6;
            break;
        }
        else if (ans == "N" || ans == "n")
        {
            option = 1;
            break;
        }
        else
        {
            cout << "Please type your option again!" << endl;
        }

    } while (ans != "Y" || ans != "y" || ans != "N" || ans != "n");
}
