#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Filter.h"

// allows for AVX2 register use
#include "immintrin.h"

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

class Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
        int value;
        input >> value;
        filter -> set(i,j,value);
      }
    }
    return filter;
  } else {
    cerr << "Bad input in readFilter:" << filename << endl;
    exit(-1);
  }
}


double applyFilter(class Filter *filter, cs1300bmp *input, cs1300bmp *output)
{
  //timer
  long long cycStart, cycStop;
  cycStart = rdtscll();

  
  output -> width = input -> width;
  output -> height = input -> height;
    
  //perform in-loop funtion calls outside of for loops
  int in_height = (input -> height) - 1;
  int in_width = (input -> width) - 1;
  int f_00 = filter -> get(0, 0);
  int f_01 = filter -> get(0, 1);
  int f_02 = filter -> get(0, 2);
  int f_10 = filter -> get(1, 0);
  int f_11 = filter -> get(1, 1);
  int f_12 = filter -> get(1, 2);
  int f_20 = filter -> get(2, 0);
  int f_21 = filter -> get(2, 1);
  int f_22 = filter -> get(2, 2);
  // determine the divisor without having to access the file throuhg getDivisor()
  int f_divisor = f_00+f_01+f_02+f_10+f_11+f_12+f_20+f_21+f_22;
  if (f_divisor == 0) { f_divisor = 1; }
  else if (f_divisor == 16) { f_divisor = 20; }
    
  // First I rearranged the for loops to index with the row first, then the collumn for each plane, as this
  // takes advantage of memory usage by row-major order, as items at each index can be retrived continuosly
  // Additionally, I unrolled the inner j i for loop so that it calculated 2 pixel at a time, instead of
  // just one, effectivley cuttin in half the run time
  // 
  for(int row = 1; row < in_height; row++) {
    for(int col = 1; col < in_width; col++) {
      // initialize pixels to but used in loop unrolling
      int pixel = input -> color[0][row - 1][col - 1] * f_00;
      pixel += input -> color[0][row - 1][col] * f_01;
      pixel += input -> color[0][row - 1][col + 1] * f_02;
      pixel += input -> color[0][row][col - 1] * f_10;
      pixel += input -> color[0][row][col] * f_11;
      pixel += input -> color[0][row][col + 1] * f_12;
      pixel += input -> color[0][row + 1][col - 1] * f_20;
      pixel += input -> color[0][row + 1][col] * f_21;
      pixel += input -> color[0][row + 1][col + 1] * f_22;
      // compute the pixel
      if (f_divisor != 1) {
           pixel = pixel / f_divisor; 
      }
      if (pixel < 0) {
	    pixel = 0;
	  }
	  if (pixel > 255)  { 
	    pixel = 255;
	  }
      // store pixel the pixel in output
      output -> color[0][row][col] = pixel;
      
      // initialize pixels to but used in loop unrolling
      pixel = input -> color[1][row - 1][col - 1] * f_00;
      pixel += input -> color[1][row - 1][col] * f_01;
      pixel += input -> color[1][row - 1][col + 1] * f_02;
      pixel += input -> color[1][row][col - 1] * f_10;
      pixel += input -> color[1][row][col] * f_11;
      pixel += input -> color[1][row][col + 1] * f_12;
      pixel += input -> color[1][row + 1][col - 1] * f_20;
      pixel += input -> color[1][row + 1][col] * f_21;
      pixel += input -> color[1][row + 1][col + 1] * f_22;
      // compute the pixel
	  if (f_divisor != 1) {
           pixel = pixel / f_divisor; 
      }
      if (pixel < 0) {
	    pixel = 0;
	  }
	  if (pixel > 255)  { 
	    pixel = 255;
	  }
      // store pixel the pixel in output
      output -> color[1][row][col] = pixel;
        
      // initialize pixels to but used in loop unrolling
      pixel = input -> color[2][row - 1][col - 1] * f_00;
      pixel += input -> color[2][row - 1][col] * f_01;
      pixel += input -> color[2][row - 1][col + 1] * f_02;
      pixel += input -> color[2][row][col - 1] * f_10;
      pixel += input -> color[2][row][col] * f_11;
      pixel += input -> color[2][row][col + 1] * f_12;
      pixel += input -> color[2][row + 1][col - 1] * f_20;
      pixel += input -> color[2][row + 1][col] * f_21;
      pixel += input -> color[2][row + 1][col + 1] * f_22;
      // compute the pixel
	  if (f_divisor != 1) {
           pixel = pixel / f_divisor; 
      }
      if (pixel < 0) {
	    pixel = 0;
	  }
	  if (pixel > 255)  { 
	    pixel = 255;
	  }
      // store pixel the pixel in output
      output -> color[2][row][col] = pixel;
     
    }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
