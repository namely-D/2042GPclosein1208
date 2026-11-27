#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>//R2 排序
#include <ctime>//R1 日期计算、R3 随机编号
#include <sstream>//生成日期和读者编号字符串
using namespace std;
class Student
{
public:
    Student()
    {
        ID = 0;
        Name = "";
    }

    int setID()
    {
        ID = 9178;
        return ID;
    }

    bool checkACnum(int inputACnum)
    {
        if (ID == inputACnum)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

private:
    int ID;
    string Name;
};
// Reader Account Records
struct Reader
{
    string ID;
    string CardNumber;
    string Name;
    int Fiction;
    int NonFiction;
    int Points;
};

// Borrowing Records
struct Borrowing
{
    string ReaderID;
    string eBookID;
    string BorrowingDate;
    string DueDate;
    bool Updated;
};

// Shared data
vector<Reader> readers;
vector<Borrowing> borrowings;

bool loaded = false;
string systemDate;

//1. 日期检查函数（老师要求日期必须是2026年内的有效日期。）
bool checkDate(string date)
{
    if (date.length() != 10)
    {
        return false;
    }

    if (date[4] != '-' || date[7] != '-')
    {
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i != 4 && i != 7)
        {
            if (date[i] < '0' || date[i] > '9')
            {
                return false;
            }
        }
    }

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (year != 2026)
    {
        return false;
    }

    if (month < 1 || month > 12)
    {
        return false;
    }

    int days[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (day < 1 || day > days[month - 1])
    {
        return false;
    }

    return true;
}

//2. 计算21天后的日期
string calculateDueDate(string date)
{
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    int days[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    day = day + 21;

    while (day > days[month - 1])
    {
        day = day - days[month - 1];
        month++;

        if (month > 12)
        {
            month = 1;
            year++;
        }
    }

    stringstream result;

    result << year << "-"
        << setfill('0') << setw(2) << month << "-"
        << setfill('0') << setw(2) << day;

    return result.str();
}
//3. R1 主函数
void R1()
{
    // Clear previous data
    readers.clear();
    borrowings.clear();

    // R1.1 Load Reader Account Records
    readers.push_back({
        "202456734", "8066778JW14",
        "WONG Claire", 0, 0, 100
        });

    readers.push_back({
        "202333890", "8378678JM15",
        "MA Kathy", 0, 0, 200
        });

    readers.push_back({
        "202067856", "8138876JC24",
        "CHAN Peter", 0, 0, 500
        });

    readers.push_back({
        "202211843", "8689000JC11",
        "CHEUNG Alice", 0, 0, 1000
        });

    // Load Borrowing Records
    borrowings.push_back({
        "202211843", "F01", "", "", false
        });

    borrowings.push_back({
        "202211843", "F02", "", "", false
        });

    borrowings.push_back({
        "202333890", "F01", "", "", false
        });

    borrowings.push_back({
        "202067856", "N05", "", "", false
        });

    borrowings.push_back({
        "202067856", "N02", "", "", false
        });

    borrowings.push_back({
        "202211843", "N01", "", "", false
        });

    cout << "Starting data loaded successfully!" << endl;

    // R1.2 Set System Date
    cout << "\n*** Set System Date ***\n";

    int count = 0;
    string date;

    while (count < 3)
    {
        cout << "Please enter system date (YYYY-MM-DD): ";
        getline(cin, date);

        if (checkDate(date))
        {
            break;
        }
        else
        {
            count++;
            cout << "Invalid date. Please try again.\n";
        }
    }

    if (count == 3)
    {
        date = "2026-06-30";

        cout << "Warning: Default date is used.\n";
    }

    systemDate = date;

    // Update all borrowing records
    for (int i = 0; i < borrowings.size(); i++)
    {
        borrowings[i].BorrowingDate = systemDate;
        borrowings[i].DueDate = calculateDueDate(systemDate);
    }

    loaded = true;

    cout << "System date: " << systemDate << endl;
    cout << "Due date: "
        << calculateDueDate(systemDate) << endl;
}
//R1–R3 函数区：R2（排序和输出数据。）
void R2()
{
    // Copy the original data
    vector<Reader> sortedReaders = readers;
    vector<Borrowing> sortedBorrowings = borrowings;

    // Sort reader accounts by name
    for (int i = 0; i < sortedReaders.size(); i++)
    {
        for (int j = i + 1; j < sortedReaders.size(); j++)
        {
            if (sortedReaders[i].Name > sortedReaders[j].Name)
            {
                swap(sortedReaders[i], sortedReaders[j]);
            }
        }
    }

    // Display Reader Account Records
    cout << "\n*** Reader Account Records ***\n";

    cout << left
        << setw(12) << "Reader ID"
        << setw(16) << "Library Card"
        << setw(32) << "Reader Name"
        << setw(10) << "Fiction"
        << setw(15) << "Non-Fiction"
        << setw(10) << "Points"
        << endl;

    for (int i = 0; i < sortedReaders.size(); i++)
    {
        cout << left
            << setw(12) << sortedReaders[i].ID
            << setw(16) << sortedReaders[i].CardNumber
            << setw(32) << sortedReaders[i].Name
            << setw(10) << sortedReaders[i].Fiction
            << setw(15) << sortedReaders[i].NonFiction
            << setw(10) << sortedReaders[i].Points
            << endl;
    }

    // Sort borrowing records by date (Descending)
    for (int i = 0; i < sortedBorrowings.size(); i++)
    {
        for (int j = i + 1; j < sortedBorrowings.size(); j++)
        {
            if (sortedBorrowings[i].BorrowingDate <
                sortedBorrowings[j].BorrowingDate)
            {
                swap(sortedBorrowings[i], sortedBorrowings[j]);
            }
        }
    }

    // Display Borrowing Records
    cout << "\n*** Borrowing Records ***\n";

    cout << left
        << setw(12) << "Reader ID"
        << setw(10) << "eBook ID"
        << setw(18) << "Borrowing Date"
        << setw(18) << "Due Date"
        << "Updated"
        << endl;

    for (int i = 0; i < sortedBorrowings.size(); i++)
    {
        if (sortedBorrowings[i].Updated == false)
        {
            cout << left
                << setw(12) << sortedBorrowings[i].ReaderID
                << setw(10) << sortedBorrowings[i].eBookID
                << setw(18) << sortedBorrowings[i].BorrowingDate
                << setw(18) << sortedBorrowings[i].DueDate
                << sortedBorrowings[i].Updated
                << endl;
        }
    }
}

//R1–R3 函数区：R3
//1. 查找 Reader ID
int findReader(string ID)
{
    for (int i = 0; i < readers.size(); i++)
    {
        if (readers[i].ID == ID)
        {
            return i;
        }
    }

    return -1;
}
//2. 自动生成 Reader ID
string generateReaderID()
{
    string ID;

    do
    {
        ID = systemDate.substr(0, 4);

        for (int i = 0; i < 5; i++)
        {
            ID = ID + to_string(rand() % 10);
        }

    } while (findReader(ID) != -1);

    return ID;
}

//3. 计算 Check Digit
int calculateCheckDigit(string card)
{
    int weights[3] = { 7, 3, 1 };

    int sum = 0;
    int value;

    for (int i = 0; i < card.length(); i++)
    {
        if (card[i] >= '0' && card[i] <= '9')
        {
            value = card[i] - '0';
        }
        else
        {
            value = card[i] - 'A' + 10;
        }

        sum = sum + value * weights[i % 3];
    }

    return sum % 10;
}
//4. 检查图书证号码是否重复
bool checkCardNumber(string card)
{
    for (int i = 0; i < readers.size(); i++)
    {
        if (readers[i].CardNumber == card ||
            readers[i].CardNumber.substr(2, 5)
            == card.substr(2, 5))
        {
            return true;
        }
    }

    return false;
}
//5. Y/N 确认函数
bool confirmation()
{
    string answer;

    while (true)
    {
        cout << "Please confirm (Y/N): ";
        getline(cin, answer);

        if (answer == "Y" || answer == "y")
        {
            return true;
        }
        else if (answer == "N" || answer == "n")
        {
            return false;
        }
        else
        {
            cout << "Invalid input.\n";
        }
    }
}
//6. R3 主函数
// Check whether a string contains digits only
bool checkDigits(string text)
{
    if (text.empty())
    {
        return false;
    }

    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] < '0' || text[i] > '9')
        {
            return false;
        }
    }

    return true;
}

// Check Reader ID
bool checkReaderID(string ID)
{
    return ID.length() == 9 && checkDigits(ID);
}

// Check Reader Name
bool checkReaderName(string name)
{
    if (name.empty() || name.length() > 30)
    {
        return false;
    }

    size_t space = name.find(' ');

    if (space == string::npos ||
        space == 0 || name.back() == ' ')
    {
        return false;
    }

    // Check uppercase surname
    for (int i = 0; i < space; i++)
    {
        if (name[i] < 'A' || name[i] > 'Z')
        {
            return false;
        }
    }

    // Check all characters
    for (int i = 0; i < name.length(); i++)
    {
        char c = name[i];

        if (!((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == ' ' || c == '-'))
        {
            return false;
        }
    }

    return true;
}

void R3()
{
    string ID;

    // Input Reader ID
    int attempts = 0;

    while (attempts < 3)
    {
        cout << "Please enter Reader ID: ";
        getline(cin, ID);

        if (checkReaderID(ID))
        {
            break;
        }

        attempts++;
        cout << "Invalid Reader ID.\n";
    }

    if (attempts == 3)
    {
        cout << "Too many invalid inputs.\n";
        return;
    }

    int index = findReader(ID);

    // =====================================
    // Close Reader Account
    // =====================================

    if (index != -1)
    {
        cout << "\n*** Close Reader Account ***\n";

        cout << "Reader ID: "
            << readers[index].ID << endl;

        cout << "Reader Name: "
            << readers[index].Name << endl;

        cout << "Library Card: "
            << readers[index].CardNumber << endl;

        cout << "Fiction Balance: "
            << readers[index].Fiction << endl;

        cout << "Non-Fiction Balance: "
            << readers[index].NonFiction << endl;

        cout << "Reading Points: "
            << readers[index].Points << endl;

        if (confirmation())
        {
            int removed = 0;

            // Delete corresponding borrowing records
            for (int i = 0; i < borrowings.size(); )
            {
                if (borrowings[i].ReaderID == ID)
                {
                    borrowings.erase(
                        borrowings.begin() + i
                    );

                    removed++;
                }
                else
                {
                    i++;
                }
            }

            // Delete reader account
            readers.erase(readers.begin() + index);

            cout << "Reader account closed successfully.\n";

            cout << removed
                << " borrowing records removed.\n";
        }
        else
        {
            cout << "Operation cancelled.\n";
        }

        return;
    }

    // =====================================
    // Open Reader Account (Registration)
    // =====================================

    cout << "\nReader ID does not exist.\n";
    cout << "*** Open Reader Account ***\n";

    if (readers.size() >= 100)
    {
        cout << "Maximum number of accounts reached.\n";
        return;
    }

    string name;
    string institution;
    string sequential;

    bool valid = false;

    // Input Reader Name
    for (int i = 0; i < 3; i++)
    {
        cout << "Reader Name (SURNAME Givenname): ";
        getline(cin, name);

        if (checkReaderName(name))
        {
            valid = true;
            break;
        }

        cout << "Invalid reader name.\n";
    }

    if (!valid)
    {
        cout << "Registration failed.\n";
        return;
    }

    // Input Institutional ID
    valid = false;

    for (int i = 0; i < 3; i++)
    {
        cout << "Institutional ID (80-87): ";
        getline(cin, institution);

        if (institution.length() == 2 &&
            checkDigits(institution) &&
            institution >= "80" &&
            institution <= "87")
        {
            valid = true;
            break;
        }

        cout << "Invalid Institutional ID.\n";
    }

    if (!valid)
    {
        cout << "Registration failed.\n";
        return;
    }

    // Input Sequential Number
    valid = false;
    string card;

    for (int i = 0; i < 3; i++)
    {
        cout << "Sequential Number (10000-99999): ";
        getline(cin, sequential);

        if (sequential.length() != 5 ||
            !checkDigits(sequential) ||
            sequential < "10000" ||
            sequential > "99999")
        {
            cout << "Invalid Sequential Number.\n";
            continue;
        }

        // Generate Library Card Number
        card = institution + sequential
            + "J" + name[0] + "1";

        card = card +
            to_string(calculateCheckDigit(card));

        // Check duplicate number
        if (checkCardNumber(card))
        {
            cout << "Sequential Number already exists.\n";
            continue;
        }

        valid = true;
        break;
    }

    if (!valid)
    {
        cout << "Registration failed.\n";
        return;
    }

    // Create new reader account
    Reader newReader;

    newReader.ID = generateReaderID();
    newReader.Name = name;
    newReader.CardNumber = card;

    newReader.Fiction = 0;
    newReader.NonFiction = 0;
    newReader.Points = 0;

    // Save new account into the shared vector
    readers.push_back(newReader);

    // Display registration result
    cout << "\nRegistration successful!\n";

    cout << "Reader ID: "
        << newReader.ID << endl;

    cout << "Reader Name: "
        << newReader.Name << endl;

    cout << "Library Card Number: "
        << newReader.CardNumber << endl;

    cout << "Fiction Balance: "
        << newReader.Fiction << endl;

    cout << "Non-Fiction Balance: "
        << newReader.NonFiction << endl;

    cout << "Reading Points: "
        << newReader.Points << endl;

    cout << "Total Reader Accounts: "
        << readers.size() << endl;
}

//这个部分最重要的是把 R1、R2、R3 连接到组员已经写好的 Main Menu。
int main()
{
    Student testStudent;
    testStudent.setID();

    srand(time(0));

    int option = 0;

    cout << "Welcome!\n";

    do
    {
        cout << "\n***** VLM Main Menu *****\n";
        cout << "[1] Load Starting Data\n";
        cout << "[2] Show All Reader Accounts\n";
        cout << "[3] Open or Close Reader Account\n";
        cout << "[4] Reader Account Operations\n";
        cout << "[5] Generate Statement\n";
        cout << "[6] Credits and Exit\n";
        cout << "***********************************\n";
        cout << "Option (1-6): ";

        if (!(cin >> option))
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Invalid option.\n";
            continue;
        }

        cin.ignore(10000, '\n');

        // R1.3
        if (option >= 2 && option <= 5 && loaded == false)
        {
            cout << "Please load starting data first.\n";
            continue;
        }

        switch (option)
        {
        case 1:
            R1();
            break;

        case 2:
            R2();
            break;

        case 3:
            R3();
            break;
            // R4 - Other group member
        case 4:
        {
            string inputACnum;

            cout << "Please enter Reader ID: ";
            getline(cin, inputACnum);

            int index = findReader(inputACnum);

            if (index != -1)
            {
                cout << "Reader account found!\n";

                cout << "Reader ID: "
                    << readers[index].ID << endl;

                cout << "Reader Name: "
                    << readers[index].Name << endl;

                // R4mainmenu(inputACnum);
            }
            else
            {
                cout << "Invalid reader account number.\n";
            }

            break;
        }
            break;

        case 5:
            // R5 - Other group member
            cout << "R5 is not implemented yet.\n";
            break;

        case 6:
            // Temporary exit for testing
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid option.\n";
        }

    } while (option != 6);

    return 0;
}
