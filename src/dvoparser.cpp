#include "dvoparser.hpp"
#define MAXVERTS (int)1e6
#define MAXEDGES (int)1e6
using std::ios;

unsigned int bytesToUShort(char *ptr) {
	#define ABSOLUTE_VALUE(i) (unsigned i) (unsigned char)
	
	return ABSOLUTE_VALUE(short) (ptr[0]) << 8 | ABSOLUTE_VALUE(short) (ptr[1]);
}

unsigned int bytesToUInt(char *ptr) {
	return ABSOLUTE_VALUE(int) (ptr[0]) << 24 |
	       ABSOLUTE_VALUE(int) (ptr[1]) << 16 |
	       ABSOLUTE_VALUE(int) (ptr[2]) << 8  |
	       ABSOLUTE_VALUE(int) (ptr[3]);
}

unsigned long bytesToULong(char *ptr) {
	return ABSOLUTE_VALUE(long) (ptr[0]) << 56 |
	       ABSOLUTE_VALUE(long) (ptr[1]) << 48 |
	       ABSOLUTE_VALUE(long) (ptr[2]) << 40 |
	       ABSOLUTE_VALUE(long) (ptr[3]) << 32 |
	       ABSOLUTE_VALUE(long) (ptr[4]) << 24 |
	       ABSOLUTE_VALUE(long) (ptr[5]) << 16 |
	       ABSOLUTE_VALUE(long) (ptr[6]) << 8  |
	       ABSOLUTE_VALUE(long) (ptr[7]);
}

double bytesToDouble(char *ptr) {
	unsigned long ulong = bytesToULong(ptr);
	return *(double *)&ulong;
}

std::string readDVBFile(std::string filename) {
	std::ifstream file ( filename, ios::in | ios::binary );
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string filecontent = buffer.str();
	
	return filecontent;
}

Object parseDVOContent(std::string filename) {
	std::string content = readDVBFile(filename);
	Object empty = Object({}, {});
	
	if(content.empty()) {
		printf("Error while loading object ");
		std::cout << filename;
		printf(": file either does not exist or is empty\n");
		return empty;
	}
	if(content.rfind("DIMVIS", 0) != 0) {
		printf("Error while loading object");
		std::cout << filename;
		printf(": file does not begin with DIMVIS\n");
		return empty;
	}
	unsigned int rank = bytesToUShort(&content[6]);
	unsigned int numverts = bytesToUInt(&content[8]);
	unsigned int numedges = bytesToUInt(&content[12]);
	if(numverts > MAXVERTS || numedges > MAXEDGES) {
		printf("Error while loading object ");
		std::cout << filename;
		printf(": too many edges or vertices (%u vertices > %u or %u edges > %u).\nRank %u.\n", numverts, MAXVERTS, numedges, MAXEDGES, (int)rank);
		return empty;
	}
	
	/*int strlen = content.length();
	for(int i = 0; i < strlen; i++) {
		printf("%02x", (unsigned char)(content[i]));
	}
	putchar(10);*/
	
	char *vertsstart = &content[16];
	char *edgesstart = vertsstart + 8 * numverts * rank;
	
	Object object (rank, numverts, numedges);
	
	for(int i = 0; i < numverts; i++) {
		for(int j = 0; j < rank; j++) {
			char *ptrv = vertsstart + 8 * (i * rank + j);
			object.points[i].vector[j] = bytesToDouble(ptrv);
		}
	}
	
	for(int i = 0; i < numedges; i++) {
		char *ptre = edgesstart + 4 * i;
		object.lines[i] = bytesToUInt(ptre);
	}
	
	printf("Loaded object ");
	std::cout << filename << "\n";
	return object;
}

Object loadDVO(std::string filename) {
	return parseDVOContent(DVB_LOCATION + filename + ".dvo");
}