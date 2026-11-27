void R5()
{
    // 1. 输入 Reader ID，并查找读者
    string readerID;
    cout << "Please enter Reader ID: ";
    getline(cin, readerID);

    int index = findReader(readerID);
    if (index == -1)
    {
        cout << "Reader ID does not exist.\n";
        return;
    }

    // 2. 显示 Reader Name、Reader ID、图书证号码和报表日期
    string year = systemDate.substr(0, 4);
    string month = systemDate.substr(5, 2);
    string day = systemDate.substr(8, 2);
    string divider(68, '-');

    cout << "\nReader Name: " << readers[index].Name << endl;
    cout << "Reader ID: " << readers[index].ID << endl;
    cout << "Library Card Number: " << readers[index].CardNumber << endl;
    cout << "Statement Date: " << day << "-" << month << "-" << year << endl;

    // 3. 显示 Transactions 交易表格
    cout << endl << divider << endl;
    cout << "Transactions:\n";
    cout << left
        << setw(18) << "Type"
        << setw(18) << "Reading Points"
        << "Description" << endl;

    for (size_t i = 0; i < transactions.size(); i++)
    {
        if (transactions[i].readerID == readerID)
        {
            cout << setw(18) << transactions[i].type
                << setw(18) << transactions[i].points
                << transactions[i].description << endl;
        }
    }

    // 4. 显示 Borrowing History 借阅历史
    cout << endl << divider << endl;
    cout << "Borrowing History:\n";
    cout << setw(10) << "eBook ID"
        << setw(27) << "Title"
        << setw(18) << "Borrowing Date"
        << "Due Date" << endl;

    for (size_t i = 0; i < borrowings.size(); i++)
    {
        if (borrowings[i].ReaderID == readerID)
        {
            // 用 eBook ID 在 R4 的书目中查找书名
            string title = "Unknown";
            for (size_t j = 0; j < EBOOKS.size(); j++)
            {
                if (EBOOKS[j].ID == borrowings[i].eBookID)
                {
                    title = EBOOKS[j].title;
                    break;
                }
            }

            cout << setw(10) << borrowings[i].eBookID
                << setw(27) << title
                << setw(18) << borrowings[i].BorrowingDate
                << borrowings[i].DueDate << endl;
        }
    }

    // 5. 显示 Reader Account Summary 账户摘要
    cout << divider << endl;
    cout << "Reader Account Summary:\n";
    cout << "Total Reading Points Balance: " << readers[index].Points << endl;
    cout << "Fiction Rollover Balance: " << readers[index].Fiction << endl;
    cout << "Non-Fiction Rollover Balance: " << readers[index].NonFiction << endl;
}


void R6(int &option)
{
    string ans; //response from user
    do
    {
        cout << "Would you like to exit now? (Y/N): ";
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
            cout << "GoodBye!";
            option =6;
            break;
        }
        else if (ans == "N" || ans == "n")
        {
            option = 1; // option not equal to 6, back to main menu
            break;
        }
        else
        {
            cout << "Please type your option again!" << endl;
        }

    } while (ans != "Y" || ans != "y" || ans != "N" || ans != "n");
}
