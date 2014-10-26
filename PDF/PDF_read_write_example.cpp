/*

Simple read in of PDF EXAMPLE


Reads in pdf, saves as a char*, prints as new pdf


Note: pdf is just stored as a c_string


Alex Cremona Oct 2014

*/

#include <fstream>
#include <string>


int main()
{
	char inName[256] = "Simple.pdf";
	char outName[256] = "testOut.pdf";
	//std::string content;
	std::ifstream fin;
	std::ofstream fout;


	//open pdf in binary
	fin.open(inName, std::ios::in | std::ios::binary);
	
	//find length
	fin.seekg (0, fin.end);
	int length = fin.tellg();
	fin.seekg (0, fin.beg);

	// define buffer
	char * buffer = new char [length];

	//READ IN ALL INTO BUFFER
	fin.read(buffer, length);

	fin.close();
	
	
	//set string for saving
	std::string = buffer;




	//open output in Binary and output content elsewhere
	fout.open(outName, std::ios::out | std::ios::binary);
	fout.write(buffer, length);
	fout.close();

	return 0;



}
