//头文件区
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

//类
class Student
{
public:
    Student()///自构建
    {
        ID = 0;
        Name = "";
    }

void setID()//这一行是我方便测试才写进去的，但是你别删，你要入id你再多建一个单独函数
    {
        ID = 9178;
    }

bool cheackACnum(int inputACnum)//校验id
    {
        return ID == inputACnum;
    }

private:
    int ID;
    string Name;
};





//R1-R3函数区


//R4函数区


//R5-R6函数区


//main主函数区
int main()
{
    Student sampleStudent;
    
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
        R4mainmenu();//启动R4菜单
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
