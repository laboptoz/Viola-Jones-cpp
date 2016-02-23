/*
*  PORT LINUX TO WINDOWS CHANGE LOG:
*  image.c, readPgm(), line131 //changed fopen(,'r') to fopen(,'rb') //fix sub and cntrl-z errors since windows reads 'r' as text and 'rb' as binary //This did not occur in Linux version
*  image.c, writePgm(), line207 //changed fopen(,'w') to fopen(,'wb') //fix sub and cntrl-z errors since windows writes 'w' as text and 'wb' as binary //This did not occur in Linux version
*  haar.cpp, readTextClassifier(), line670, line713 //changed fopen(,'r') to fopen(,'rb')//not completely necessary since this fopen() only reads integer numbers... good for completeness
*  haar.cpp, ScaleImage_Invoker(), line545 //changed x <= x2 ...to... x <= x2-1 //potential memory fault noted in evalWeakClassifier() function within haar.cpp ... this is a result of indexing an array not allocated in memory??? //This did not occur in Linux version
*  haar.cpp, ScaleImage_Invoker(), line546 //changed y <= y2 ...to... y <= y2-1 //potential memory fault noted in evalWeakClassifier() function within haar.cpp ... this is a result of indexing an array not allocated in memory??? //This did not occur in Linux version
*/

/*
 *  TU Eindhoven
 *  Eindhoven, The Netherlands
 *
 *  Name            :   faceDetection.cpp
 *
 *  Author          :   Francesco Comaschi (f.comaschi@tue.nl)
 *
 *  Date            :   November 12, 2012
 *
 *  Function        :   Main function for face detection
 *
 *  History         :
 *      12-11-12    :   Initial version.
 *
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;  If not, see <http://www.gnu.org/licenses/>
 *
 * In other words, you are welcome to use, share and improve this program.
 * You are forbidden to forbid anyone else to use, share and improve
 * what you give them.   Happy coding!
 */

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "stdio-wrapper.h"
#include "haar.h"

#define INPUT_FILENAME "Face.pgm"
#define OUTPUT_FILENAME "Output.pgm"

using namespace std;


int main (int argc, char *argv[])
{

	int flag;

	int mode = 1;
	int i;

	/* detection parameters */
	float scaleFactor = 1.2;
	int minNeighbours = 1;


	printf("-- entering main function --\r\n");

	printf("-- loading image --\r\n");

	MyImage imageObj;
	MyImage *image = &imageObj;               //get address of image in memory

	flag = readPgm((char *)"Face.pgm", image);//read the .pgm image
	if (flag == -1)
	{
		printf( "Unable to open input image\n");
		return 1;
	}

    //flag = writePgm((char *)OUTPUT_FILENAME, image);//debug the windows readPgm() and writePgm functions in image.c

	printf("-- loading cascade classifier --\r\n");

	/*myCascade cascadeObj;
	myCascade *cascade = &cascadeObj;*/

    int Num_of_CascadesObjs = 8;
	myCascade* cascade[Num_of_CascadesObjs];
	myCascade temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7;//,temp8, temp9, temp10, temp11, temp12, temp13, temp14, temp15, temp16, temp17;
    myCascade tempArr[Num_of_CascadesObjs] = {temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7};//,temp8, temp9, temp10, temp11, temp12, temp13, temp14, temp15, temp16, temp17};

	MySize minSize = {20, 20};
	MySize maxSize = {0, 0};

    /* classifier properties */
	for (int i=0;i<Num_of_CascadesObjs; i++)
	{
        tempArr[i].n_stages=25;                     //number of strong classifier stages
        tempArr[i].total_nodes=2913;                //number of total weak classifier notes in the cascade
        tempArr[i].orig_window_size.height = 24;    //original window height
        tempArr[i].orig_window_size.width = 24;     //original window width
        cascade[i] = &tempArr[i];
	}

	readTextClassifier();

	std::vector<MyRect> result;

	printf("-- detecting faces --\r\n");

	result = detectObjects(image, minSize, maxSize, cascade, scaleFactor, minNeighbours);

	for(i = 0; i < result.size(); i++ )
	{
		MyRect r = result[i];
		drawRectangle(image, r);
	}

	printf("-- saving output --\r\n");
	flag = writePgm((char *)OUTPUT_FILENAME, image);

	printf("-- image saved --\r\n");

	/* delete image and free classifier */
	releaseTextClassifier();
	freeImage(image);

	return 0;
}
