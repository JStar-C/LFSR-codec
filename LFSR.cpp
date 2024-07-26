// Author: Joseph Calles

#include "LFSR.hpp" // include C++ header file

//  Pre-condition: given_seed is a valid string object consisting
//                 only of '1's and '0's
// Post-condition: most significant bit placed in the "front" of vector
LFSR::LFSR(string given_seed, int t) // constructor definition for LFSR
{
   int i = 0; // index counter variable
   int length = given_seed.length(); // retrieve length of string object
   bool bit = false; // initalise boolean variable 

   for( i = 0; i < length; i++ ) // loop through given_seed
   {
     // convert characters in string to boolean
     given_seed.at(i) == '0' ? bit = false : bit = true;

     // insert boolean values into _register in "reading order"
     _register.push_back(bit); 
   }

   _tap_index = (_register.size() - t - 1); // set tap index
   // vector is arranged in "reading order", so we must subtract t
   // .size() begins counting at 1, so we must -1
}

//  Pre-condition: _register is a vector of boolean values
// Post-condition: front of register is removed and XOR'd with tap value
//                 to determine return value, the return value is
//                 push_back'd into the vector as a boolean
int LFSR::step() // step definition for LFSR
{
  // remove the front of the _register and XOR it with the _tap
  
  // if the step and the front do not match
  if(*(_register.erase(_register.begin())) != _register.at(_tap_index) )
   {
     _register.push_back(true); // push_back a value of true (1)
     return 1; // 1 (indicating a true value)
   }
   else // if the step and the front do match
   {
     _register.push_back(false); // push_back a value of false (0)
     return 0; // return 0 (indicating a false false)
   }
}

//  Pre-condition: int k is within bounds of vector and is >= 0
// Post-condition: step() is called k times, thereby shifting
//                 all the bits k position. Returns the decimal
//                 value of all bits returned by step()
int LFSR::generate(const int k) // generate definition for LFSR
{
  int i = 0; // counter variable
  int sum = 0; // sum variable

  for ( i = 0; i < k; i++ ) // loop k times
  {
    sum = (sum * 2) + this->step(); // simulate steps
  }

  return sum; // return calculated sum
}

//  Pre-condition: object reference lfsr must be valid
// Post-condition: all bits in lfsr _register are wriiten on the ostrem.
//                 No bits are altered
// insertion operator overloader
ostream& operator<< (ostream& out, const LFSR& lfsr) 
{
  int i = 0; // counter variable
  int length = lfsr._register.size(); // retrieve length of _register
  
  for( i = 0; i < length; i++ ) // loop through _register 
  {
    out << lfsr._register.at(i); // output each bit in _register
  }
  
  return out; // return ostream
}
