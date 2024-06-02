#include "mystring.h"
#include <iostream>

using std :: cout;
using std :: cin;
using std :: endl;
using namespace coen79_lab5;

int main()
{
  string mybad(" Hello World ");
  string mygood(mybad);
  string ohyeah('S');
  string nope, yeah, ohoh;
  char array_String[10] = "COEN79";
  char random = 'Z';

  cout << "original versions:" << endl;
  cout << "................................." << endl;
  cout << "mybad:" << mybad << endl;
  cout << "mygood:" <<mygood << endl;
  cout << "ohyeah:" << ohyeah << endl;
  cout << "nope:" << nope << endl;
  cout << endl;

  mybad += mybad;
  mygood += ohyeah;
  mybad += ohyeah;
  nope += random;
  nope += array_String;

  cout << "testing of string functions(+)(=)(+=):" << endl;
  cout << "................................." << endl;
  cout << "mybad:" << mybad << endl;
  cout << "mygood:" <<mygood << endl;
  cout << "ohyeah:" << ohyeah << endl;
  cout << "nope:" << nope << endl;
  cout << endl;

  yeah = mybad + mygood;
  ohoh = yeah + array_String;
  nope = nope + nope;


  cout << "More testing of string functions(+)(=)(+=):" << endl;
  cout << "................................." << endl;
  cout << "yeah" <<  yeah << endl;
  cout << "ohoh:" << ohoh << endl;
  cout << "nope:" << nope << endl;
  cout << endl;

  mybad.insert(nope,0);
  mygood.dlt(0,5);
  nope.replace(mygood, 5);
  ohyeah.insert(yeah,1);

  cout << "testing of string functions(insert)(dlt)(replace):" << endl;
  cout << "................................." << endl;
  cout << "mybad:" << mybad << endl << "length:" << mybad.length() << endl;
  cout << "mygood:" <<mygood << endl << "length:" << mygood.length()<< endl;
  cout << "ohyeah:" << ohyeah << endl << "length:" << ohyeah.length()<< endl;
  cout << "nope:" << nope << endl << "length:" << nope.length() << endl;
  cout << endl;

  string tofind1('S');
  string tofind2("Hello");
  char tofind3 = 'E';

  cout << "testing of string functions(search)(count):" << endl;
  cout << "................................." << endl;
  cout << "mybad:" << mybad << endl;
  cout << " having " << tofind1 << " at " << mybad.search(tofind1) << endl;
  cout << " having " << tofind2 << " at " << mybad.search(tofind2) << endl;
  cout << " having " << tofind3 << " at " << mybad.search(tofind3) << endl;
  cout << "mygood:" << mygood << endl;
  cout << " having " << tofind1 << " at " << mygood.search(tofind1) << endl;
  cout << " having " << tofind2 << " at " << mygood.search(tofind2) << endl;
  cout << " having " << tofind3 << " at " << mygood.search(tofind3) << endl;
  cout << "ohyeah:" << ohyeah << endl;
  cout << " having " << tofind1 << " at " << ohyeah.search(tofind1) << endl;
  cout << " having " << tofind2 << " at " << ohyeah.search(tofind2) << endl;
  cout << " having " << tofind3 << " at " << ohyeah.search(tofind3) << endl;
  cout << "nope:" << nope << endl;
  cout << " having " << tofind1 << " at " << nope.search(tofind1) << endl;
  cout << " having " << tofind2 << " at " << nope.search(tofind2) << endl;
  cout << " having " << tofind3 << " at " << nope.search(tofind3) << endl;
  cout << endl;

  return 0;
}