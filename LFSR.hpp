#ifndef LFSR_HPP
#define LFSR_HPP

// include directives
#include <iostream>
#include <string>
#include <vector>

using namespace std; // namespace directive 

// Linear Feedback Shift Register (LFSR)

class LFSR
{
public:
  // constructor declaration
  LFSR(string seed, int t); 

  // member function declarations
  int step();
  int generate(const int k); 

  // insertion operator overloader
  friend ostream& operator<< (ostream& out, const LFSR& x);

private:
  vector<bool> _register; // class representation of register
  int _tap_index;         // class representation of tap index
};

#endif
