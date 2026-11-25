//头文件区
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;
//R1-R3函数区


//R4函数区


//R5-R6函数区


//main主函数区
int main()
{
  int option;
  do
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
      //R4的
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
