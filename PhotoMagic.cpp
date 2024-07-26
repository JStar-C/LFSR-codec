// include libaries 
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "LFSR.hpp" // include header file

// function to convert alphanumeric password to seed and tap
void get_seed_and_tap(string& seed, int& tap);

int main(int argc, char* argv[])
{
  string seed = argv[3]; // initalise seed with alphanumeric password
  int tap = 0; // initalise tap
  
  get_seed_and_tap(seed, tap); // retrive customised seed and tap
  
  LFSR test(seed, tap); // initalise LFSR with customised seed and tap
  
  sf::Image image1; // initalise image object
  // NOTE: image1 represents source image
  if (!image1.loadFromFile(argv[1])) // if image fails to load
  {
    cout << "ERROR: Image failed to load. . ." << endl;
    return -1; // output error message  and return -1
  }
  sf::Image image2 = image1; // initalise image object
  // NOTE: image2 represents the modifided "encrypted" image
  
  cout << "Encrypting. . ." << endl; // output message to user
  
  sf::Vector2u size = image2.getSize(); // retrieve size of image
  sf::Color p; // initalise object to hold pixel colors 
  
  // loop across each pixel of the image
  for (unsigned int x = 0; x < size.x; x++) // loop x-values
  {
    for (unsigned int y = 0; y < size.y; y++) // loop y-values
    {
      p = image2.getPixel(x, y); // retireve pixel
      p.r ^= test.generate(8); // generate color for Red
      p.g ^= test.generate(8); // generate color for Green
      p.b ^= test.generate(8); // generate color for Blue
      image2.setPixel(x, y, p); // set pixel
    }
  }

  cout << "Encryption complete" << endl; // output message

  // initalise windows
  sf::RenderWindow window1(sf::VideoMode(size.x, size.y),
			   "Source file: (unencrypted)"); 
  sf::RenderWindow window2(sf::VideoMode(size.x, size.y),
			   "Output file: (encrypted)");
  
  sf::Vector2i pos(size.x + 25, 0); // initalise position vector
  window2.setPosition(pos); // set position of window2

  // initalise and load textures
  sf::Texture texture1;
  texture1.loadFromImage(image1);
  sf::Texture texture2;
  texture2.loadFromImage(image2);

  // initalise and load sprites
  sf::Sprite sprite1;
  sprite1.setTexture(texture1);
  sf::Sprite sprite2;
  sprite2.setTexture(texture2);
 
  while(window1.isOpen() || window2.isOpen()) // main event loop
  {
    sf::Event event; // initalise event object

    while (window1.pollEvent(event)) // window 1 event loop 
     {
      if ((event.type == sf::Event::Closed) ||
	  ((event.type == sf::Event::KeyPressed) &&
	   (event.key.code == sf::Keyboard::Escape)))
      { window1.close(); } // close if Esc is pressed or window closed
    }

    while (window2.pollEvent(event)) // window 2 event loop 
    {
      if ((event.type == sf::Event::Closed) ||
	  ((event.type == sf::Event::KeyPressed) &&
	   (event.key.code == sf::Keyboard::Escape)))
      { window2.close(); } // close if Esc is pressed or window closed
    }

    // window refresh sequences

    window1.clear();       // clear window 1
    window1.draw(sprite1); // re-draw
    window1.display();     // display
    
    window2.clear();       // clear window 2
    window2.draw(sprite2); // re-draw
    window2.display();     // display
  }

  // return if modified image successfully saved to output file
  return image2.saveToFile(argv[2]) ? 0 : -1;
}

// function to convert alphanumeric password to seed and tap
void get_seed_and_tap(string& seed, int& tap)
{
  int size = seed.size(); // retrieve size of seed
  unsigned int n = 1; // initalise variable to hold ASCII value
  int i = 0; // initalise counter variable

  // loop through seed and collect ASCII values by multiplication 
  for ( i = 0; i < size; i++ ) { n *= seed.at(i); }
  // increase value small size seeds
  if (size <= 1) { n *= 100; }
  
  seed.clear(); // clear the seed of all characters
  
  while( n != 0 ) // store n as a binary number in seed
  {
    seed = ( n % 2 == 0 ? "0" : "1") + seed; // insert result of modulo
    n /= 2; // divide n after each modulo insertion
    tap++; // count-up the tap for each bit added
  }
  
  tap = (tap / 2) + 1; // finalise tap position
}
