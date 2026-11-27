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

// 交易记录由 R4 生成、R5 读取。放在这里，R1/R3 才能在清理数据时引用。
struct Transaction
{
    string readerID;
    string type;          // "Redemption" 或 "Transfer"
    int points;
    string description;
    string date;
};

vector<Transaction> transactions;

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
    transactions.clear();

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

//3. 计算 Check Digit
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
//4. 检查图书证号码是否重复
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
void R3()
{
    string ID;

    cout << "Please enter Reader ID: ";
    getline(cin, ID);

    int index = findReader(ID);

    // Close Reader Account
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
            // Delete borrowing records
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

            // Delete transaction records that belong to the closed account.
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

            // Delete reader account
            readers.erase(readers.begin() + index);

            cout << "Reader account closed successfully.\n";
        }
        else
        {
            cout << "Operation cancelled.\n";
        }
    }

    // Open Reader Account
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

            // 三项分别校验，但校验规则保持不变，尤其是姓名大小写规则不放松。
            bool nameValid = true;
            bool institutionValid = true;
            bool sequentialValid = true;

            // Check reader name
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

            // Check Institutional ID
            if (institution.length() != 2 ||
                institution[0] < '0' || institution[0] > '9' ||
                institution[1] < '0' || institution[1] > '9' ||
                institution < "80" ||
                institution > "87")
            {
                institutionValid = false;
            }

            // Check Sequential Number
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

            // Generate Library Card Number
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

            // Create new reader
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

//R4.4 的兑换和转账会生成 Transaction，R5 的 statement 需要用到这些记录。
//这里由 R4 定义一次，R5 成员直接复用即可，不要再重复定义同名结构。


// 电子书目录，对应题目里的 Table 3。这个表在 R4.3 中用于查询和展示。
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

// 礼物兑换目录，对应题目里的 Table 4。
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

// 判断字符串是否全部由数字组成。
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

// 判断 vector 里是否已经存在某个字符串。R4.2 用这个来做借阅去重。
bool containsString(const vector<string>& list, const string& value)
{
    return find(list.begin(), list.end(), value) != list.end();
}

// 按行读取一个整数。整行读取的好处是：
// 1. 不会把数字后面的换行符留给下一个 getline，避免姓名被吞掉；
// 2. 输入不是数字时，可以很干净地提示重试，而不会让 cin 进入错误状态。
int readInt(const string& prompt)
{
    string line;

    while (true)
    {
        cout << prompt;

        if (!getline(cin, line))
        {
            // 输入流结束（例如重定向文件被读完）。返回 -1 作为哨兵值。
            return -1;
        }

        stringstream parser(line);
        int value = 0;

        if (parser >> value)
        {
            // 确认数字后面没有多余的非法内容，例如 "1abc" 应该算非法。
            string leftover;
            if (!(parser >> leftover))
            {
                return value;
            }
        }

        cout << "Invalid input. Please enter an integer.\n";
    }
}

// 读取一个限定范围的整数。所有菜单选项都用它，避免重复写范围判断。
int readIntInRange(const string& prompt, int minValue, int maxValue)
{
    while (true)
    {
        int value = readInt(prompt);

        if (value == -1)
        {
            return -1; // 输入流结束，交给调用方处理
        }

        if (value >= minValue && value <= maxValue)
        {
            return value;
        }

        cout << "Invalid option. Please enter "
             << minValue << " to " << maxValue << ".\n";
    }
}

// 按行读取一个字符串。返回空串通常表示输入流结束，调用方需要自行判断。
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

// 校验 Institutional ID：必须是 80 到 87 之间的两位数字。
bool isValidInstitutionID(const string& institution)
{
    if (institution.length() != 2 || !isAllDigits(institution))
    {
        return false;
    }

    int value = stoi(institution);
    return value >= 80 && value <= 87;
}

// 校验 Sequential Number：必须是 10000 到 99999 之间的五位数字。
bool isValidSequentialNumber(const string& sequential)
{
    if (sequential.length() != 5 || !isAllDigits(sequential))
    {
        return false;
    }

    int value = stoi(sequential);
    return value >= 10000 && value <= 99999;
}

// 校验 Reader Name：
// - 格式为 "SURNAME Givenname"；
// - 姓在前、名在后，中间必须有一个空格；
// - 姓必须全是大写字母；
// - 全名不超过 30 个字符（包含空格）。
bool isValidReaderName(const string& name)
{
    if (name.empty() || name.length() > 30)
    {
        return false;
    }

    size_t space = name.find(' ');

    // 必须有一个空格，且空格不能在最前面或最后面。
    if (space == string::npos || space == 0 || space == name.length() - 1)
    {
        return false;
    }

    // 姓氏部分必须全部是大写字母。
    for (size_t i = 0; i < space; i++)
    {
        if (name[i] < 'A' || name[i] > 'Z')
        {
            return false;
        }
    }

    return true;
}

// 提取卡号中的 Replacement Digit（卡号第 10 个字符，索引 9）。
// 如果卡号格式异常，回退到 '1'，保证程序不会崩溃。
char extractReplacementDigit(const string& cardNumber)
{
    if (cardNumber.length() >= 10 &&
        cardNumber[9] >= '1' && cardNumber[9] <= '9')
    {
        return cardNumber[9];
    }

    return '1';
}

// 根据 Institution、Sequential、姓氏首字母、Replacement Digit 生成完整卡号。
// Check Digit 由 R1-R3 的 calculateCheckDigit() 计算，不要在这里重写。
string buildCardNumber(const string& institution,
                       const string& sequential,
                       char reservedLetter,
                       char replacementDigit)
{
    string cardWithoutCheck =
        institution + sequential + "J" + reservedLetter + replacementDigit;

    return cardWithoutCheck + to_string(calculateCheckDigit(cardWithoutCheck));
}

// 检查一个新卡号是否被“其他”读者占用。编辑当前读者时，不能把当前读者的
// 旧卡号误判为重复，所以用 excludeReaderID 排除自己。
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

// 在 EBOOKS 中按 ID 查找电子书。找不到返回 nullptr。
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

// 在 GIFTS 中按礼物编号查找。找不到返回 nullptr。
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

// 显示单个读者账户的全部字段。R4.1、R4.2、R4.6 都会用到。
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

// 显示 Table 3 电子书目录。R4.3 中用。
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

// 显示 Table 4 礼物目录。R4.4 中用。
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

// 显示某个读者所有“尚未更新积分”的借阅记录。R4.2 和 R4.6 都用。
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

// 新增一条交易记录。交易日期统一用系统日期。
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

// 测试模式退出时，按 Reader ID 清理借阅记录。正常读者不会调用这个函数。
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

// 测试模式退出时，按 Reader ID 清理读者账户。
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

// 测试模式退出时，按 Reader ID 清理交易记录。
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

// R4.1 修改读者资料。
// 注意：Reader ID 是账户唯一标识，修改资料时保持不变，只重新生成卡号。
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

            // 用新的 Institution、Sequential、姓氏首字母重新生成卡号。
            // Replacement Digit 保持当前值不变，只有 R4.5 才把它加一。
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

// R4.2 根据借阅记录更新积分。
// 这是 R4 里逻辑最重的部分，按以下顺序处理：
//   1. 找出该读者所有 Updated == false 的记录；
//   2. Borrowing Bonus：每本“历史从未计过”的唯一书 50 分；
//   3. Genre Explorer Bonus：Fiction 与 Non-Fiction 配对，每对 100 分；
//   4. 剩余未配对的书记入 Rollover Balance，且每种最多保留 3；
//   5. 更新读者积分、Rollover Balance，并把本批记录标记为 Updated。
void updateReadingPoints(const string& readerID)
{
    int index = findReader(readerID);

    if (index == -1)
    {
        cout << "Reader account does not exist.\n";
        return;
    }

    // 第一步：收集所有尚未结算的借阅记录。
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

    // 第二步：整理“历史已经计过分”的书目。
    // 如果一本书之前结算过，本次再出现也不应该再拿 Borrowing Bonus，
    // 这是为了满足“同一本书借多次只算一次”的规则。
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

        // 历史计过，或者本批已经计过，都跳过，不能重复计分。
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

    // 第三步：计算 Borrowing Bonus。
    int borrowingBonus = (int)newlyCountedBooks.size() * 50;

    // 第四步：计算 Genre Explorer Bonus。
    // 当前已有的 Rollover Balance 也要一起参与配对。
    int totalFiction = readers[index].Fiction + newFictionCount;
    int totalNonFiction = readers[index].NonFiction + newNonFictionCount;

    int genreSets = min(totalFiction, totalNonFiction);
    int genreBonus = genreSets * 100;

    // 配对后剩余的部分存回 Rollover Balance，每种最多保留 3。
    int newFictionRollover = min(3, totalFiction - genreSets);
    int newNonFictionRollover = min(3, totalNonFiction - genreSets);

    int totalEarned = borrowingBonus + genreBonus;

    // 第五步：更新读者账户。
    readers[index].Points += totalEarned;
    readers[index].Fiction = newFictionRollover;
    readers[index].NonFiction = newNonFictionRollover;

    // 第六步：把本批所有未结算记录都标记为已结算。
    for (int i = 0; i < (int)pendingIndices.size(); i++)
    {
        borrowings[pendingIndices[i]].Updated = true;
    }

    // 第七步：输出题目要求的积分计算明细。
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

// R4.3 新建借阅记录。
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

// R4.4 的兑换子功能。
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

// R4.4 的转账子功能。
void transferPoints(const string& readerID)
{
    int sourceIndex = findReader(readerID);

    if (sourceIndex == -1)
    {
        cout << "Reader account does not exist.\n";
        return;
    }

    // 9178 只是测试账号，退出 R4 后会被清理。如果允许它向正式读者转分，
    // 正式读者的余额和交易记录都会被污染，所以测试模式下禁止转账。
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

// R4.4 的主菜单。题目只要求两个子选项，这里额外加一个“返回”，更符合
// 菜单类程序的操作习惯。
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

// R4.5 补办图书证。Replacement Digit 加一，并重新计算 Check Digit。
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

    // 规格说明 Replacement Digit 最大为 9，到了 9 就不能再补办。
    if (replacementDigit == '9')
    {
        cout << "This library card has reached the replacement limit.\n";
        return;
    }

    char newReplacementDigit = replacementDigit + 1;

    // 卡号前 9 位保持不变，第 10 位（Replacement Digit）加一，
    // 然后重新计算第 11 位（Check Digit）。
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


// 进入某个读者账户后，反复显示 R4 菜单，直到用户选择 6。
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
    // 主菜单其实已经挡掉了“未加载数据”的情况，这里再挡一次作为双保险。
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

    // 正式路径：先去 R1-R3 的 readers 数据库里查找。
    if (findReader(readerID) != -1)
    {
        R4MainMenu(readerID);
        return;
    }

    // 测试路径：保留 9178，但只临时建一个测试读者，退出后立即清理，
    // 这样 9178 不会出现在正式读者列表里。
    if (readerID == "9178")
    {
        Reader testReader;
        testReader.ID = "9178";
        testReader.CardNumber = "8012345JA13"; // 用题目示例卡号，方便测试 R4.5
        testReader.Name = "TEST User";
        testReader.Fiction = 0;
        testReader.NonFiction = 0;
        testReader.Points = 1000;

        readers.push_back(testReader);

        cout << "Test mode: temporary reader 9178 created.\n";
        R4MainMenu(readerID);

        // 退出测试模式，清理测试期间产生的所有数据。
        eraseBorrowingsForReader(readerID);
        eraseTransactionsForReader(readerID);
        eraseReaderForTest(readerID);

        return;
    }

    cout << "Reader ID does not exist.\n";
}


// ---------------------------------------------------------------------------
// 最终主程序：R1-R4 已整合，R5/R6 暂留占位。
// case 4 直接调用 R4()。R4() 内部会先用字符串 Reader ID 查 readers；
// 输入 9178 时仍会走临时测试读者，退出后自动清理，正式数据不受影响。
// ---------------------------------------------------------------------------
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

        // R1.3：选项 2-5 必须先加载起始数据。
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
                cout << "R5 is not implemented yet.\n";
                break;

            case 6:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid option.\n";
        }
    } while (option != 6);

    return 0;
}
