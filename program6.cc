/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <iostream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <cstring>
#include <string>
#include<bits/stdc++.h> 
#include "cdk.h"
#include "stdint.h"


#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 18
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader
{
public:
 uint32_t magicNumber; /* Should be 0xFEEDFACE */
 uint32_t versionNumber;
 uint64_t numRecords;
};

/*
* Records in the file have a fixed length buffer
* that will hold a C-Style string. This is the
* size of the fixed length buffer.
*/
const int maxRecordStringLength = 25;
class BinaryFileRecord
{
public:
 uint8_t strLength;
 char stringBuffer[maxRecordStringLength];
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"0", "a", "b", "c"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"0", "a", "b", "c", "d", "e"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }
 	/* Display the Matrix */
 	drawCDKMatrix(myMatrix, true);

	/* Open and read binary file */
	BinaryFileHeader *myHeader = new BinaryFileHeader();
	BinaryFileRecord *myRecord = new BinaryFileRecord();

	ifstream binInfile ("/scratch/perkins/cs3377.bin", ios::in | ios::binary);

	binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
	binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));

	/* Format and store the magic number for display */
 	stringstream ss;
	ss << hex << myHeader->magicNumber;
	string mNumber;
	ss >> mNumber;
	transform(mNumber.begin(), mNumber.end(), mNumber.begin(), ::toupper);
	mNumber = "Magic: 0x" + mNumber;
	
	// Clear string stream
	ss.str( std::string() );
	ss.clear();

 	/* Format and store version number */
	string version;
	ss << myHeader->versionNumber;
	ss >> version;
	version = "Version: " + version;

	// Clear string stream
	ss.str( std::string() );
	ss.clear();

	/* Format and store number of records */
	string records;
	ss << myHeader->numRecords;
	ss >> records;
	records = "NumRecords: " + records;

	// Clear string stream
	ss.str( std::string() );
	ss.clear();
	/*
	* Dipslay the magic number
	*/
  	setCDKMatrixCell(myMatrix, 1, 1, mNumber.c_str());

	/*
   	* Dipslay the version number
   	*/
	setCDKMatrixCell(myMatrix, 1, 2, version.c_str());

	/*
   	* Dipslay the number of records
   	*/
	setCDKMatrixCell(myMatrix, 1, 3, records.c_str());

  	drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (10);


	binInfile.close();

  // Cleanup screen
  endCDK();
	
}
