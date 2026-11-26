#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

class Student
{
public:
    Student()///自构建
    {
        ID = 0;
        Name = "";
    }

    int setID()//这一行是我方便测试才写进去的，但是你别删，你要入id你再多建一个单独函数
    {
        ID = 9178;
        return ID;
    }

    bool checkACnum(int inputACnum)//校验id
    {
        if(ID == inputACnum)
        {
            return true;
        }else{
            return false;
        }
    }

private:
    int ID;
    string Name;
};



class Reader
{
  public :
  string ReaderID;
  string caedNo;
  string name;
  int fictionRollover;
  int nonFictionRollover;
  int points;
}；
class BorrowingRecord    //R4.3的
{
public:
    string readerID;
    string eBookID;
    string title;
    string genre;
    string borrowDate;
    string dueDate;
    bool updated;
};
vector <BorrowingRecord> borrow;
void currentborrow(string currentReaderID , string systemDate)
{
  BorrowingRecord newrecord;
  newrecord.readerID = currentReaderID;
  newrecord.borrowDate = systemDate;
  newrecore.updated = false;

  cout << "Enter eBook ID: ";
  cin >> newRecord.eBookID;

  if (newRecord.eBookID = "F01")
  {
    newRecord.title = "Legend";
    newRecord.genre = "Fiction"
  }
  if (newRecord.eBookID = "F02")
  {
    newRecord.title = "The hunter game";
    newRecord.genre = "Fiction"
  }
  if (newRecord.eBookID = "F03")
  {
    newRecord.title = "Punching the air";
    newRecord.genre = "Fiction"
  }
  if (newRecord.eBookID = "F04")
  {
    newRecord.title = "Looking for Alasta";
    newRecord.genre = "Fiction"
  }
  if (newRecord.eBookID = "F05")
  {
    newRecord.title = "The big sleep";
    newRecord.genre = "Fiction"
  }
  if (newRecord.eBookID = "N01")
  {
    newRecord.title = "C++";
    newRecord.genre = "Non-Fiction"
  }
  if (newRecord.eBookID = "N02")
  {
    newRecord.title = "Python";
    newRecord.genre = "Non-Fiction"
  }
  if (newRecord.eBookID = "N03")
  {
    newRecord.title = "Java";
    newRecord.genre = "Non-Fiction"
  }
  if (newRecord.eBookID = "N04")
  {
    newRecord.title = "HYML5";
    newRecord.genre = "Non-Fiction"
  }
  if (newRecord.eBookID = "N05")
  {
    newRecord.title = "PHP";
    newRecord.genre = "Non-Fiction"
  }
}





//默认加载过读者资料
void R4mainmenu(int ID)
{
    int R4option;
    do//菜单
    {
    cout << "Action for Reader ID: " << ID << endl;
    cout << "***** Reader Account Operations Menu ***********************\n";
    cout << "[1] Edit Reader Information\n";
    cout << "[2] Update Reading Points Balance based on Borrowing Records\n";
    cout << "[3] Create Borrowing Records\n";
    cout << "[4] Redeem Reading Points for a Gift & Transfer\n";
    cout << "[5] Replace Library Card\n";
    cout << "[6] Return to Main Menu\n";
    cout << "***********************************************************\n";
    cout << "Option (1-6): ";
    cin >> R4option;
    switch (R4option)
    {
        case 1:
        break;


        case 2:
        break;


        case 3:
        break;


        case 4:
        break;


        case 5:
        break;


        case 6:
        break;
      

        default:
        cout << "Invalid option.\n";
    }
    }while (R4option != 6);
    return;
}











int main()
{
    Student testStudent;
    testStudent.setID();//设置id为9178，方便测试
    
    int option;
    do//菜单
    {
    cout << "Welcome!\n";
    cout << "\n***** VLM Main Menu *****\n";
    cout << "[1] Load Starting Data\n";
    cout << "[2] Show All Reader Accounts\n";
    cout << "[3] Open or Close Reader Account\n";
    cout << "[4] Reader Account Operations\n";
    cout << "[5] Generate Statement\n";
    cout << "[6] Credits and Exit\n";
    cout << "***********************************************************\n";
    cout << "Option (1-6): ";
    cin >> option;

    switch (option)
    {
        case 1:
      //R1的
        break;


        case 2:
      //R2的
        break;


        case 3:
      //R3的
        break;


        case 4:
        int inputACnum;
        cout << "please enter the reader account number: ";
        cin >> inputACnum;

        if (testStudent.checkACnum(inputACnum)){
            R4mainmenu(inputACnum);//用该id启动R4菜单
        }else{
            cout << "Invalid reader account number.\n";
            break;
        }

        
        
        
        
        break;


        case 5:
      //R5的
        break;


        case 6:
      //R6的
        break;
      

        default:
        cout << "Invalid option.\n";
    }
    }while (option != 6);
    return 0;
}
