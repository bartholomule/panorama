#include <ctime>
#include <iostream>
#include <map>
using std::map;

#include "llapi/procedural.h"
#include "llapi/user_functions.h"
#include "generic/template_functions.h"

ostream& operator<<(ostream& o, const TAttribute& tab)
{
  o << "A{" << tab.AttributeName() << "(" << EAttribType_to_str(tab.eType) << ")}";
  return o;
}

multimap<string, string>   tConfigData;

class foo
{
 public:
  int bar()
  {
    static int num_calls = 0;
    cout << __PRETTY_FUNCTION__ << endl;
    cout << "Num calls=" << num_calls << endl;
    return ++num_calls;
  }
  double bar2()
  {
    static int num_calls = 0;
    cout << __PRETTY_FUNCTION__ << endl;
    cout << "Num calls=" << num_calls << endl;
    return ++num_calls;
  }
  bool works(bool b = true)
  {
    cout << "Works=" << b << endl;
    return !!b;
  }

  void ick(const TVector& vec)
  {
    cout << "ick="
	 << vec.x() << ","
	 << vec.y() << ","
	 << vec.z()      
	 << endl;
  }  

  int trash(int i)
  {
    static int ick = 0;
    cout << __PRETTY_FUNCTION__ << endl;
    ick += i;

    return ick;
  }  
  
  typedef map<string,magic_pointer<user_function> > fn_map_type;

  fn_map_type get_user_functions()
  {
    fn_map_type fns;

    fns["bar"] = create_user_function(this,&foo::bar);
    fns["bar2"] = create_user_function(this,&foo::bar2);
    fns["trash"] = create_user_function(this,&foo::trash);
    fns["works"] = create_user_function(this,&foo::works);
    fns["ick"] = create_user_function(this,&foo::ick);

    return fns;
  }
};


double barfola()
{
  cout << __PRETTY_FUNCTION__ << endl;
  static double ick = 1;
  ick *= double(2.5);
  return ick / double(2.5);
}

double barfola2(int i)
{
  cout << __PRETTY_FUNCTION__ << endl;
  static double ick = 0;
  ick += i;
  cout << "Ick is: " << ick << endl;
  return ick;
}


void do_it()
{
  user_arg_vector vec;
  typedef map<string,magic_pointer<user_function> > fn_map_type;
  fn_map_type fns;
  foo f;
  fns = f.get_user_functions();

  //  vec.push_back(new TAttribInt(1000));
  vec.push_back(new TAttribVector(TVector(1,2,3)));  
  
  for(fn_map_type::iterator i = fns.begin();
      i != fns.end();
      ++i)
  {
    cout << "Found function named " << i->first << endl;
    cout << i->second->call(vec) << endl;
  }
}

int main (int argc, char *argv[])
{
  //  TProcedural proc;
  
  //  for(int i = 1; i <= 10; ++i)
  {
    //    cout << "iteration " << i << endl;
    do_it();
  }
  
  return 0;

}  /* main() */
