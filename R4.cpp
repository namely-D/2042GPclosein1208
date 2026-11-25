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

    bool checkACnum(int inputACnum)//校验id
    {
        return ID == inputACnum;
    }

private:
    int ID;
    string Name;
};


//默认加载过读者资料
void R4mainmenu()
{
    
}











int main()
{
    Student testStudent;
    
    int option;
    do//菜单
    {
    cout << "\n***** Main Menu *****\n";
    cout << "[1] Load Starting Data\n";
    cout << "[2] Show Reader Accounts\n";
    cout << "[3] Open/Close Reader Account\n";
    cout << "[4] Reader Account Operations\n";
    cout << "[5] Generate Statement\n";
    cout << "[6] Credits and Exit\n";
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
            R4mainmenu();//启动R4菜单
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
