#include "list.h"
#include "polynomial.h"

using namespace std;

void cleaner()
{
  while (getchar() != '\n');
  cin.clear();
}

int check(int a, int b)
{
  int choice = INT_MIN;
  while ((choice < a) || (choice > b))
  {
    cin >> choice;
    if ((choice < a) || (choice > b))
    {
      cout << "Invalid number entered. Try typing again." << endl;
      cleaner();
    }
  }
  return choice;
}

int main()
{
  int exit = 1;
  VecOfPolymomial vec;
  while (exit != 2)
  {
    system("cls");
    int choice = -1;
    Polynomial tmpPol;
    Polynomial tmpRes;
    std::string tmp;
    int tmpx = 0, tmpy = 0, tmpz = 0;
    try
    {
      cout << "Choose what you need:\n 1) Load polynomials from a file (the old information will be deleted)\n 2) Save polynomials to a file (the old information in the file will be deleted)\n 3) Create a polynomial\n 4) Add one polynomial to another\n 5) Subtract one polynomial from another\n 6) Multiply one polynomial by another\n 7) Calculate the value of a polynomial at a point\n";
      choice = check(1, 7);
      cleaner();
      switch (choice)
      {
      case 1:
        cout << " Reading from a file is in progress...\n";
        vec.ReadFromFile();
        cout << " Done!\n";
        break;
      case 2:
        cout << " Saving to a file is in progress...\n";
        vec.SaveInFile();
        cout << " Done!\n";
        break;
      case 3:
        cout << "Enter a new polynomial:\n";
        getline(cin, tmp);
        vec.push_back(tmp);
        cout << "The new polynomial is saved!\n";
        break;
      case 4:
        system("cls");
        cout << "4) Add one polynomial to another\n Select the first polynomial from the existing list:\n" << vec;
        choice = check(1, vec.pols.size());
        tmpPol = vec.pols[choice - 1];
        system("cls");
        cout << "4) Add one polynomial to another\n The first polynomial: " << tmpPol;
        cout << "\n Select the second polynomial from the existing list:\n" << vec;
        choice = check(1, vec.pols.size());
        tmpRes = tmpPol + vec.pols[choice - 1];
        system("cls");
        cout << "4) Add one polynomial to another\n First polynomial: " << tmpPol << "\n Second polynomial: " << vec.pols[choice - 1] << "\n The result of addition: " << tmpRes << "\n Save the result to a list of existing polynomials?\n 1) Yes\n 2) No\n";
        choice = check(1, 2);
        if (choice == 1)
        {
          vec.push_back(tmpRes);
          cout << " Done!\n";
        }
        break;
      case 5:
        system("cls");
        cout << "5) Subtract one polynomial from another\n Select the first polynomial from the existing list:\n" << vec;
        choice = check(1, vec.pols.size());
        tmpPol = vec.pols[choice - 1];
        system("cls");
        cout << "5) Subtract one polynomial from another\n First polynomial: " << tmpPol;
        cout << "\n Select the second polynomial from the existing list:\n" << vec;
        choice = check(1, vec.pols.size());
        tmpRes = tmpPol - vec.pols[choice - 1];
        system("cls");
        cout << "5) Subtract one polynomial from another\n First polynomial: " << tmpPol << "\n Second polynomial: " << vec.pols[choice - 1] << "\n The result of subtraction: " << tmpRes << "\n Save the result to a list of existing polynomials?\n 1) Yes\n 2) No\n";
        choice = check(1, 2);
        if (choice == 1)
        {
          vec.push_back(tmpRes);
          cout << " Done!\n";
        }
        break;
      case 6:
        system("cls");
        cout << "6) Multiply one polynomial by another\n Select the first polynomial from the existing list:\n" << vec;
        choice = check(1, vec.pols.size());
        tmpPol = vec.pols[choice - 1];
        system("cls");
        cout << "6) Multiply one polynomial by another\n First polynomial: " << tmpPol;
        cout << "\n Select the second polynomial from the existing list:\n" << vec;
        choice = check(1, vec.pols.size());
        try
        {
          tmpRes = tmpPol * vec.pols[choice - 1];
        }
        catch (string exc)
        {
          cout << "An error occurred during multiplication: the permissible maximum value of the degree was exceeded\n";
          break;
        }
        system("cls");
        cout << "6) Multiply one polynomial by another\n First polynomial: " << tmpPol << "\n Second polynomial: " << vec.pols[choice - 1] << "\n The result of multiplication: " << tmpRes << "\n Save the result to a list of existing polynomials?\n 1) Yes\n 2) No\n";
        choice = check(1, 2);
        if (choice == 1)
        {
          vec.push_back(tmpRes);
          cout << " Done!\n";
        }
        break;
      case 7:
        system("cls");
        cout << "7) Calculate the value of a polynomial at a point\n Select the polynomial from the existing list:\n" << vec;
        choice = check(1, vec.pols.size());
        tmpPol = vec.pols[choice - 1];
        system("cls");
        cout << "7) Calculate the value of a polynomial at a point\n Selected polynomial: " << tmpPol;
        cout << "\n Enter the coordinates of the point (x,y,z separated by a space):";
        cin >> tmpx;
        cin >> tmpy;
        cin >> tmpz;
        cout << " Result: " << tmpPol.value_in_dot(tmpx, tmpy, tmpz) << '\n';
        break;
      default:
        break;
      }
    }
    catch (string exc)
    {
      cout << exc;
    }
    cout << "\nContinue using the program?\n\t1 - Yes\n\t2 - No\n\t";
    cin >> exit;
    cleaner();
    cout << '\n';
  }
  system("pause");
  return 0;
}
