#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>

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
struct Reader
{
    string ID;
    string CardNumber;
    string Name;
    int Fiction;
    int NonFiction;
    int Points;
};

struct Borrowing
{
    string ReaderID;
    string eBookID;
    string BorrowingDate;
    string DueDate;
    bool Updated;
};

vector<Reader> readers;
vector<Borrowing> borrowings;

struct Transaction
{
    string readerID;
    string type;
    int points;
    string description;
    string date;
};

vector<Transaction> transactions;

bool loaded = false;
string systemDate;

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
void R1()
{
    // Clear previous data
    readers.clear();
    borrowings.clear();
    transactions.clear();

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
string generateReaderID()
{
    string ID;

    do
    {
        int number = rand() % 100000;

        stringstream result;

        result << "2026"
               << setfill('0')
               << setw(5)
               << number;

        ID = result.str();

    } while (findReader(ID) != -1);

    return ID;
}

int calculateCheckDigit(string card)
{
    int weights[3] = {7, 3, 1};

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
bool checkCardNumber(string card)
{
    for (int i = 0; i < readers.size(); i++)
    {
        if (readers[i].CardNumber == card)
        {
            return true;
        }
    }

    return false;
}
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
void R3()
{
    string ID;

    cout << "Please enter Reader ID: ";
    getline(cin, ID);

    int index = findReader(ID);

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
            for (int i = 0; i < borrowings.size(); )
            {
                if (borrowings[i].ReaderID == ID)
                {
                    borrowings.erase(borrowings.begin() + i);
                }
                else
                {
                    i++;
                }
            }

            for (int i = 0; i < transactions.size(); )
            {
                if (transactions[i].readerID == ID)
                {
                    transactions.erase(transactions.begin() + i);
                }
                else
                {
                    i++;
                }
            }

            readers.erase(readers.begin() + index);

            cout << "Reader account closed successfully.\n";
        }
        else
        {
            cout << "Operation cancelled.\n";
        }
    }

    else
    {
        cout << "\n*** Open Reader Account ***\n";

        if (readers.size() >= 100)
        {
            cout << "Maximum number of accounts reached.\n";
            return;
        }

        int count = 0;

        while (count < 3)
        {
            string name;
            string institution;
            string sequential;

            cout << "Reader Name (SURNAME Givenname): ";
            getline(cin, name);

            cout << "Institutional ID (80-87): ";
            getline(cin, institution);

            cout << "Sequential Number (10000-99999): ";
            getline(cin, sequential);

            bool nameValid = true;
            bool institutionValid = true;
            bool sequentialValid = true;

            size_t space = name.find(' ');

            if (name.empty() || name.length() > 30 ||
                space == string::npos || space == 0 ||
                name.back() == ' ')
            {
                nameValid = false;
            }

            if (nameValid)
            {
                for (int i = 0; i < space; i++)
                {
                    if (name[i] < 'A' || name[i] > 'Z')
                    {
                        nameValid = false;
                    }
                }
            }

            if (institution.length() != 2 ||
                institution[0] < '0' || institution[0] > '9' ||
                institution[1] < '0' || institution[1] > '9' ||
                institution < "80" ||
                institution > "87")
            {
                institutionValid = false;
            }

            if (sequential.length() != 5)
            {
                sequentialValid = false;
            }

            for (int i = 0; i < sequential.length(); i++)
            {
                if (sequential[i] < '0' ||
                    sequential[i] > '9')
                {
                    sequentialValid = false;
                }
            }

            if (sequential < "10000" ||
                sequential > "99999")
            {
                sequentialValid = false;
            }

            if (!nameValid || !institutionValid || !sequentialValid)
            {
                count++;

                cout << "Invalid input. Please check:\n";

                if (!nameValid)
                {
                    cout << "- Reader Name: use \"SURNAME Givenname\". "
                         << "Surname must be ALL CAPS, no leading/trailing spaces, "
                         << "and the full name must be at most 30 characters.\n";
                }

                if (!institutionValid)
                {
                    cout << "- Institutional ID: enter a 2-digit number from 80 to 87.\n";
                }

                if (!sequentialValid)
                {
                    cout << "- Sequential Number: enter a 5-digit number "
                         << "from 10000 to 99999.\n";
                }

                cout << "You have " << (3 - count)
                     << " attempt(s) left.\n";
                continue;
            }

            string card = institution + sequential
                          + "J" + name[0] + "1";

            card = card + to_string(calculateCheckDigit(card));

            if (checkCardNumber(card))
            {
                count++;
                cout << "Library Card already exists.\n";
                cout << "Please use a different Institution/Sequential combination.\n";
                cout << "You have " << (3 - count)
                     << " attempt(s) left.\n";
                continue;
            }

            Reader newReader;

            newReader.ID = generateReaderID();
            newReader.Name = name;
            newReader.CardNumber = card;
            newReader.Fiction = 0;
            newReader.NonFiction = 0;
            newReader.Points = 0;

            readers.push_back(newReader);

            cout << "Reader account opened successfully!\n";

            cout << "Reader ID: "
                 << newReader.ID << endl;

            cout << "Reader Name: "
                 << newReader.Name << endl;

            cout << "Library Card: "
                 << newReader.CardNumber << endl;

            cout << "Fiction Balance: 0\n";
            cout << "Non-Fiction Balance: 0\n";
            cout << "Reading Points: 0\n";

            return;
        }

        cout << "Account creation failed after 3 attempts.\n";
    }
}

struct EBook
{
    string ID;
    string genre;
    string title;
};

const vector<EBook> EBOOKS = {
    {"F01", "Fiction", "Legend"},
    {"F02", "Fiction", "The hunger games"},
    {"F03", "Fiction", "Punching the air"},
    {"F04", "Fiction", "Looking for Alaska"},
    {"F05", "Fiction", "The big sleep"},
    {"N01", "Non-Fiction", "C++"},
    {"N02", "Non-Fiction", "Python"},
    {"N03", "Non-Fiction", "Java"},
    {"N04", "Non-Fiction", "HTML5"},
    {"N05", "Non-Fiction", "PHP"}
};

struct Gift
{
    int number;
    string description;
    int pointsRequired;
};

const vector<Gift> GIFTS = {
    {1, "Movie voucher", 200},
    {2, "$100 Bookstore voucher", 500},
    {3, "Library membership (1 year)", 1000}
};

bool isAllDigits(const string& text)
{
    if (text.empty())
    {
        return false;
    }

    for (int i = 0; i < (int)text.length(); i++)
    {
        if (text[i] < '0' || text[i] > '9')
        {
            return false;
        }
    }

    return true;
}

bool containsString(const vector<string>& list, const string& value)
{
    return find(list.begin(), list.end(), value) != list.end();
}

int readInt(const string& prompt)
{
    string line;

    while (true)
    {
        cout << prompt;

        if (!getline(cin, line))
        {
            return -1;
        }

        stringstream parser(line);
        int value = 0;

        if (parser >> value)
        {
            string leftover;
            if (!(parser >> leftover))
            {
                return value;
            }
        }

        cout << "Invalid input. Please enter an integer.\n";
    }
}

int readIntInRange(const string& prompt, int minValue, int maxValue)
{
    while (true)
    {
        int value = readInt(prompt);

        if (value == -1)
        {
            return -1; 
        }

        if (value >= minValue && value <= maxValue)
        {
            return value;
        }

        cout << "Invalid option. Please enter "
             << minValue << " to " << maxValue << ".\n";
    }
}

string readLine(const string& prompt)
{
    string line;

    cout << prompt;
    if (!getline(cin, line))
    {
        return "";
    }

    return line;
}

bool isValidInstitutionID(const string& institution)
{
    if (institution.length() != 2 || !isAllDigits(institution))
    {
        return false;
    }

    int value = stoi(institution);
    return value >= 80 && value <= 87;
}

bool isValidSequentialNumber(const string& sequential)
{
    if (sequential.length() != 5 || !isAllDigits(sequential))
    {
        return false;
    }

    int value = stoi(sequential);
    return value >= 10000 && value <= 99999;
}

bool isValidReaderName(const string& name)
{
    if (name.empty() || name.length() > 30)
    {
        return false;
    }

    size_t space = name.find(' ');

    if (space == string::npos || space == 0 || space == name.length() - 1)
    {
        return false;
    }

    for (size_t i = 0; i < space; i++)
    {
        if (name[i] < 'A' || name[i] > 'Z')
        {
            return false;
        }
    }

    return true;
}

char extractReplacementDigit(const string& cardNumber)
{
    if (cardNumber.length() >= 10 &&
        cardNumber[9] >= '1' && cardNumber[9] <= '9')
    {
        return cardNumber[9];
    }

    return '1';
}

string buildCardNumber(const string& institution,
                       const string& sequential,
                       char reservedLetter,
                       char replacementDigit)
{
    string cardWithoutCheck =
        institution + sequential + "J" + reservedLetter + replacementDigit;

    return cardWithoutCheck + to_string(calculateCheckDigit(cardWithoutCheck));
}

bool cardUsedByOther(const string& cardNumber, const string& excludeReaderID)
{
    for (int i = 0; i < (int)readers.size(); i++)
    {
        if (readers[i].ID != excludeReaderID &&
            readers[i].CardNumber == cardNumber)
        {
            return true;
        }
    }

    return false;
}

const EBook* findEBook(const string& eBookID)
{
    for (int i = 0; i < (int)EBOOKS.size(); i++)
    {
        if (EBOOKS[i].ID == eBookID)
        {
            return &EBOOKS[i];
        }
    }

    return nullptr;
}

const Gift* findGift(int giftNumber)
{
    for (int i = 0; i < (int)GIFTS.size(); i++)
    {
        if (GIFTS[i].number == giftNumber)
        {
            return &GIFTS[i];
        }
    }

    return nullptr;
}

void displayReaderRecord(const Reader& reader)
{
    cout << left
         << setw(12) << "Reader ID"
         << setw(16) << "Library Card"
         << setw(26) << "Reader Name"
         << setw(8)  << "Fiction"
         << setw(11) << "Non-Fiction"
         << setw(8)  << "Points" << endl;

    cout << left
         << setw(12) << reader.ID
         << setw(16) << reader.CardNumber
         << setw(26) << reader.Name
         << setw(8)  << reader.Fiction
         << setw(11) << reader.NonFiction
         << setw(8)  << reader.Points << endl;
}

void displayEBookTable()
{
    cout << left
         << setw(10) << "eBook ID"
         << setw(13) << "Genre"
         << "Title" << endl;

    for (int i = 0; i < (int)EBOOKS.size(); i++)
    {
        cout << left
             << setw(10) << EBOOKS[i].ID
             << setw(13) << EBOOKS[i].genre
             << EBOOKS[i].title << endl;
    }
}

void displayGiftTable()
{
    cout << left
         << setw(12) << "Gift Number"
         << setw(28) << "Description"
         << "Points Required" << endl;

    for (int i = 0; i < (int)GIFTS.size(); i++)
    {
        cout << left
             << setw(12) << GIFTS[i].number
             << setw(28) << GIFTS[i].description
             << GIFTS[i].pointsRequired << endl;
    }
}

void displayOutstandingBorrowings(const string& readerID)
{
    cout << left
         << setw(12) << "Reader ID"
         << setw(10) << "eBook ID"
         << setw(16) << "Borrowing Date"
         << setw(16) << "Due Date"
         << "Updated" << endl;

    bool found = false;

    for (int i = 0; i < (int)borrowings.size(); i++)
    {
        if (borrowings[i].ReaderID == readerID &&
            borrowings[i].Updated == false)
        {
            cout << left
                 << setw(12) << borrowings[i].ReaderID
                 << setw(10) << borrowings[i].eBookID
                 << setw(16) << borrowings[i].BorrowingDate
                 << setw(16) << borrowings[i].DueDate
                 << borrowings[i].Updated << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No outstanding borrowing records.\n";
    }
}


void addTransaction(const string& readerID,
                    const string& type,
                    int points,
                    const string& description)
{
    Transaction record;
    record.readerID = readerID;
    record.type = type;
    record.points = points;
    record.description = description;
    record.date = systemDate;

    transactions.push_back(record);
}

void eraseBorrowingsForReader(const string& readerID)
{
    for (int i = 0; i < (int)borrowings.size(); )
    {
        if (borrowings[i].ReaderID == readerID)
        {
            borrowings.erase(borrowings.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

void eraseReaderForTest(const string& readerID)
{
    for (int i = 0; i < (int)readers.size(); )
    {
        if (readers[i].ID == readerID)
        {
            readers.erase(readers.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

void eraseTransactionsForReader(const string& readerID)
{
    for (int i = 0; i < (int)transactions.size(); )
    {
        if (transactions[i].readerID == readerID)
        {
            transactions.erase(transactions.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

void editReaderInformation(const string& readerID)
{
    int index = findReader(readerID);

    if (index == -1)
    {
        cout << "Reader account does not exist.\n";
        return;
    }

    cout << "\n*** Edit Reader Information ***\n";
    displayReaderRecord(readers[index]);

    int attempts = 0;

    while (attempts < 3)
    {
        string name = readLine("Reader Name (SURNAME Givenname): ");
        string institution = readLine("Institutional ID (80-87): ");
        string sequential = readLine("Sequential Number (10000-99999): ");

        string errorMessage;

        if (!isValidReaderName(name))
        {
            errorMessage = "Invalid Reader Name.";
        }
        else if (!isValidInstitutionID(institution))
        {
            errorMessage = "Invalid Institutional ID.";
        }
        else if (!isValidSequentialNumber(sequential))
        {
            errorMessage = "Invalid Sequential Number.";
        }
        else
        {
            char replacementDigit =
                extractReplacementDigit(readers[index].CardNumber);

            string newCardNumber =
                buildCardNumber(institution, sequential,
                                name[0], replacementDigit);

            if (cardUsedByOther(newCardNumber, readerID))
            {
                errorMessage = "Library Card Number already exists.";
            }
            else
            {
                cout << "\nNew Reader Information:\n";
                cout << "Reader Name: " << name << endl;
                cout << "Institutional ID: " << institution << endl;
                cout << "Sequential Number: " << sequential << endl;
                cout << "New Library Card Number: " << newCardNumber << endl;

                if (confirmation())
                {
                    readers[index].Name = name;
                    readers[index].CardNumber = newCardNumber;

                    cout << "\nReader information updated successfully.\n";
                    displayReaderRecord(readers[index]);
                    return;
                }
                else
                {
                    cout << "Operation cancelled.\n";
                    return;
                }
            }
        }

        attempts++;
        cout << errorMessage << " You have "
             << (3 - attempts) << " attempt(s) left.\n";
    }

    cout << "Edit failed after 3 invalid attempts.\n";
}

void updateReadingPoints(const string& readerID)
{
    int index = findReader(readerID);

    if (index == -1)
    {
        cout << "Reader account does not exist.\n";
        return;
    }

    vector<int> pendingIndices;

    for (int i = 0; i < (int)borrowings.size(); i++)
    {
        if (borrowings[i].ReaderID == readerID &&
            borrowings[i].Updated == false)
        {
            pendingIndices.push_back(i);
        }
    }

    if (pendingIndices.empty())
    {
        cout << "No outstanding borrowing records to update.\n";
        return;
    }

    cout << "\n*** Outstanding Borrowing Records ***\n";
    displayOutstandingBorrowings(readerID);

    vector<string> alreadyCountedBooks;

    for (int i = 0; i < (int)borrowings.size(); i++)
    {
        if (borrowings[i].ReaderID == readerID &&
            borrowings[i].Updated == true)
        {
            alreadyCountedBooks.push_back(borrowings[i].eBookID);
        }
    }

    vector<string> newlyCountedBooks;
    int newFictionCount = 0;
    int newNonFictionCount = 0;

    for (int i = 0; i < (int)pendingIndices.size(); i++)
    {
        int recordIndex = pendingIndices[i];
        string eBookID = borrowings[recordIndex].eBookID;

        if (containsString(alreadyCountedBooks, eBookID) ||
            containsString(newlyCountedBooks, eBookID))
        {
            continue;
        }

        if (eBookID[0] == 'F')
        {
            newlyCountedBooks.push_back(eBookID);
            newFictionCount++;
        }
        else if (eBookID[0] == 'N')
        {
            newlyCountedBooks.push_back(eBookID);
            newNonFictionCount++;
        }
    }

    int borrowingBonus = (int)newlyCountedBooks.size() * 50;

    int totalFiction = readers[index].Fiction + newFictionCount;
    int totalNonFiction = readers[index].NonFiction + newNonFictionCount;

    int genreSets = min(totalFiction, totalNonFiction);
    int genreBonus = genreSets * 100;

    int newFictionRollover = min(3, totalFiction - genreSets);
    int newNonFictionRollover = min(3, totalNonFiction - genreSets);

    int totalEarned = borrowingBonus + genreBonus;

    readers[index].Points += totalEarned;
    readers[index].Fiction = newFictionRollover;
    readers[index].NonFiction = newNonFictionRollover;

    for (int i = 0; i < (int)pendingIndices.size(); i++)
    {
        borrowings[pendingIndices[i]].Updated = true;
    }

    cout << "\n*** Reading Points Calculation ***\n";
    cout << "Borrowing Bonus: "
         << (int)newlyCountedBooks.size()
         << " unique book(s) x 50 = " << borrowingBonus << " points\n";
    cout << "Genre Explorer Bonus: "
         << genreSets << " Genre Set(s) x 100 = "
         << genreBonus << " points\n";
    cout << "Total reading points earned: " << totalEarned << " points\n";

    cout << "\n*** Updated Reader Account Record ***\n";
    displayReaderRecord(readers[index]);
}

void createBorrowingRecord(const string& readerID)
{
    int index = findReader(readerID);

    if (index == -1)
    {
        cout << "Reader account does not exist.\n";
        return;
    }

    cout << "\n*** Create Borrowing Record ***\n";
    displayEBookTable();

    string eBookID = readLine("\nPlease enter eBook ID: ");
    const EBook* book = findEBook(eBookID);

    if (book == nullptr)
    {
        cout << "Invalid eBook ID. Operation aborted.\n";
        return;
    }

    cout << "Genre: " << book->genre << endl;
    cout << "Title: " << book->title << endl;

    if (!confirmation())
    {
        cout << "Operation cancelled.\n";
        return;
    }

    Borrowing newRecord;
    newRecord.ReaderID = readerID;
    newRecord.eBookID = eBookID;
    newRecord.BorrowingDate = systemDate;
    newRecord.DueDate = calculateDueDate(systemDate);
    newRecord.Updated = false;

    borrowings.push_back(newRecord);

    cout << "\nBorrowing record created successfully.\n";
    cout << "eBook ID: " << newRecord.eBookID << endl;
    cout << "Borrowing Date: " << newRecord.BorrowingDate << endl;
    cout << "Due Date: " << newRecord.DueDate << endl;
}

void redeemGift(const string& readerID)
{
    int index = findReader(readerID);

    if (index == -1)
    {
        cout << "Reader account does not exist.\n";
        return;
    }

    cout << "\n*** Redeem Reading Points for a Gift ***\n";
    displayGiftTable();

    int giftNumber = readIntInRange(
        "\nPlease select gift number (1-3): ", 1, 3);

    if (giftNumber == -1)
    {
        return;
    }

    const Gift* gift = findGift(giftNumber);

    if (gift == nullptr)
    {
        cout << "Invalid gift number. Operation aborted.\n";
        return;
    }

    if (gift->pointsRequired > readers[index].Points)
    {
        cout << "Insufficient reading points. Operation aborted.\n";
        return;
    }

    cout << "Gift: #" << gift->number << " " << gift->description << endl;
    cout << "Points required: " << gift->pointsRequired << endl;

    if (!confirmation())
    {
        cout << "Operation cancelled.\n";
        return;
    }

    readers[index].Points -= gift->pointsRequired;

    string description = "Gift #" + to_string(gift->number)
                         + ": " + gift->description;
    addTransaction(readerID, "Redemption", -gift->pointsRequired, description);

    cout << "\nRedemption successful.\n";
    displayReaderRecord(readers[index]);
}

void transferPoints(const string& readerID)
{
    int sourceIndex = findReader(readerID);

    if (sourceIndex == -1)
    {
        cout << "Reader account does not exist.\n";
        return;
    }

    if (readerID == "9178")
    {
        cout << "Test mode does not support transfers to real reader accounts.\n";
        return;
    }

    cout << "\n*** Transfer Reading Points ***\n";

    string targetID = readLine("Please enter target Reader ID: ");
    int targetIndex = findReader(targetID);

    if (targetIndex == -1)
    {
        cout << "Target reader account does not exist. Operation aborted.\n";
        return;
    }

    if (targetID == readerID)
    {
        cout << "Cannot transfer points to the same reader account.\n";
        return;
    }

    int amount = readInt("Reading points to transfer: ");

    if (amount == -1)
    {
        return;
    }

    if (amount <= 0)
    {
        cout << "The amount must be positive. Operation aborted.\n";
        return;
    }

    if (amount > readers[sourceIndex].Points)
    {
        cout << "Insufficient reading points. Operation aborted.\n";
        return;
    }

    cout << "Target reader name: " << readers[targetIndex].Name << endl;
    cout << "Amount to transfer: " << amount << endl;

    if (!confirmation())
    {
        cout << "Operation cancelled.\n";
        return;
    }

    readers[sourceIndex].Points -= amount;
    readers[targetIndex].Points += amount;

    addTransaction(readerID, "Transfer", -amount,
                   "Transfer to " + readers[targetIndex].Name
                   + " (ID: " + targetID + ")");
    addTransaction(targetID, "Transfer", amount,
                   "Transfer from " + readers[sourceIndex].Name
                   + " (ID: " + readerID + ")");

    cout << "\nTransfer completed.\n";
    cout << "\nSource account:\n";
    displayReaderRecord(readers[sourceIndex]);
    cout << "\nTarget account:\n";
    displayReaderRecord(readers[targetIndex]);
}

void redeemOrTransfer(const string& readerID)
{
    int choice = 0;

    do
    {
        cout << "\n***** Redeem / Transfer Menu *****\n";
        cout << "[1] Redeem Reading Points for a Gift\n";
        cout << "[2] Transfer Reading Points\n";
        cout << "[3] Return\n";
        cout << "***********************************\n";

        choice = readIntInRange("Option (1 - 3): ", 1, 3);

        if (choice == -1)
        {
            return;
        }

        if (choice == 1)
        {
            redeemGift(readerID);
        }
        else if (choice == 2)
        {
            transferPoints(readerID);
        }
    } while (choice != 3);
}

void replaceLibraryCard(const string& readerID)
{
    int index = findReader(readerID);

    if (index == -1)
    {
        cout << "Reader account does not exist.\n";
        return;
    }

    cout << "\n*** Replace Library Card ***\n";
    cout << "Current Library Card Number: "
         << readers[index].CardNumber << endl;

    if (!confirmation())
    {
        cout << "Operation cancelled.\n";
        return;
    }

    string cardNumber = readers[index].CardNumber;
    char replacementDigit = extractReplacementDigit(cardNumber);

    if (replacementDigit == '9')
    {
        cout << "This library card has reached the replacement limit.\n";
        return;
    }

    char newReplacementDigit = replacementDigit + 1;

    string cardWithoutCheck = cardNumber.substr(0, 9) + newReplacementDigit;
    string newCardNumber =
        cardWithoutCheck + to_string(calculateCheckDigit(cardWithoutCheck));

    readers[index].CardNumber = newCardNumber;

    cout << "\nLibrary card replaced successfully.\n";
    cout << "New Library Card Number: " << newCardNumber << endl;
}

// R4.6 返回主菜单前，显示最新读者资料和未结算借阅记录。
void displayReturnSummary(const string& readerID)
{
    int index = findReader(readerID);

    if (index == -1)
    {
        cout << "Reader account does not exist.\n";
        return;
    }

    cout << "\n*** Latest Reader Account Record ***\n";
    displayReaderRecord(readers[index]);

    cout << "\n*** Outstanding Borrowing Records ***\n";
    displayOutstandingBorrowings(readerID);
}

void R4MainMenu(const string& readerID)
{
    int choice = 0;

    do
    {
        cout << "\nAction for Reader ID: " << readerID << endl;
        cout << "***** Reader Account Operations Menu ***********************\n";
        cout << "[1] Edit Reader Information\n";
        cout << "[2] Update Reading Points Balance based on Borrowing Records\n";
        cout << "[3] Create Borrowing Records\n";
        cout << "[4] Redeem Reading Points for a Gift & Transfer\n";
        cout << "[5] Replace Library Card\n";
        cout << "[6] Return to Main Menu\n";
        cout << "***********************************************************\n";

        choice = readIntInRange("Option (1 - 6): ", 1, 6);

        if (choice == -1)
        {
            return;
        }

        switch (choice)
        {
            case 1:
                editReaderInformation(readerID);
                break;

            case 2:
                updateReadingPoints(readerID);
                break;

            case 3:
                createBorrowingRecord(readerID);
                break;

            case 4:
                redeemOrTransfer(readerID);
                break;

            case 5:
                replaceLibraryCard(readerID);
                break;

            case 6:
                displayReturnSummary(readerID);
                break;
        }
    } while (choice != 6);
}

void R4()
{
    if (!loaded)
    {
        cout << "Please load starting data first.\n";
        return;
    }

    string readerID = readLine("Please enter Reader ID: ");

    if (readerID.empty())
    {
        cout << "Invalid Reader ID.\n";
        return;
    }

    if (findReader(readerID) != -1)
    {
        R4MainMenu(readerID);
        return;
    }

    if (readerID == "9178")
    {
        Reader testReader;
        testReader.ID = "9178";
        testReader.CardNumber = "8012345JA13"; 
        testReader.Name = "TEST User";
        testReader.Fiction = 0;
        testReader.NonFiction = 0;
        testReader.Points = 1000;

        readers.push_back(testReader);

        cout << "Test mode: temporary reader 9178 created.\n";
        R4MainMenu(readerID);

        eraseBorrowingsForReader(readerID);
        eraseTransactionsForReader(readerID);
        eraseReaderForTest(readerID);

        return;
    }

    cout << "Reader ID does not exist.\n";
}

 void R5 ()
 {
	string readerID;
	cout << "ENTER YOUR READER ID : ";
	getline (cin,readerID);

	int index = findReader(readerID);

	string statementDate =
        systemDate.substr(8, 2) + "-" +
        systemDate.substr(5, 2) + "-" +
        systemDate.substr(0, 4);

	if(index == -1)
	{
		cout << "Reader does not exits . " << endl;
		return;
	}
	else
	{
		cout << "\n***Reader Statement***\n";
		cout << "Reader Name :" << readers[index].Name << endl;
		cout << "Reader ID : " << readers[index].ID  << endl;
		cout << "Library Card Number : " << readers[index].CardNumber << endl;
		cout << "Statement Date : " << systemDate << endl;
		
		cout << "------------------------------------------------------------\n" << endl;

		cout << "Transactions:" << endl;
		cout << left << setw(15) << "Type" << setw(15) << "Reading Point" << setw(15) << "Description" << endl;
		bool transactionFound = false;

    for (int i = 0; i < transactions.size(); i++)
    {
        if (transactions[i].readerID == readerID)
        {
            cout << left
                 << setw(15) << transactions[i].type
                 << setw(15) << transactions[i].points
                 << transactions[i].description
                 << endl;

            transactionFound = true;
        }
    }

    if (transactionFound == false)
    {
        cout << "No transaction records." << endl;
    }

    cout << "------------------------------------------------------------\n";

    cout << "Borrowing History:\n";

    cout << left
         << setw(18) << "eBook ID"
         << setw(18) << "Title"
         << setw(18) << "Borrowing"
         << "Due"
         << endl;

    cout << left
         << setw(18) << ""
         << setw(18) << ""
         << setw(18) << "Date"
         << "Date"
         << endl;

    bool borrowingFound = false;

    for (int i = 0; i < borrowings.size(); i++)
    {
        if (borrowings[i].ReaderID == readerID)
        {
            const EBook* book =
                findEBook(borrowings[i].eBookID);

            string title = "";

            if (book != nullptr)
            {
                title = book->title;
            }

            cout << left
                 << setw(18) << borrowings[i].eBookID
                 << setw(18) << title
                 << setw(18) << borrowings[i].BorrowingDate
                 << borrowings[i].DueDate
                 << endl;

            borrowingFound = true;
        }
    }

    if (borrowingFound == false)
    {
        cout << "No borrowing records." << endl;
    }

    cout << "------------------------------------------------------------\n";

    cout << "Reader Account Summary:\n";

    cout << left
         << setw(42) << "Total Reading Points Balance"
         << ": " << readers[index].Points << endl;

    cout << left
         << setw(42) << "Fiction Rollover Balance"
         << ": " << readers[index].Fiction << endl;

    cout << left
         << setw(42) << "Non-Fiction Rollover Balance"
         << ": " << readers[index].NonFiction << endl;

	}
 }

void R6(int &option)
{
    string ans;
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
            option = 6;
            cout << "Goodbye!";
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
        cout << "***********************************************************\n";
        cout << "Option (1-6): ";

        if (!(cin >> option))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid option.\n";
            continue;
        }

        cin.ignore(10000, '\n');

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

            case 4:
                R4();
                break;

            case 5:
                R5();
                break;

            case 6:
				R6(option);
                break;

            default:
                cout << "Invalid option.\n";
        }
    } while (option != 6);

    return 0;
}
