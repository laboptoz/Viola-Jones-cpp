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

	myCascade* cascade[8];
	myCascade temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7;

	MySize minSize = {20, 20};
	MySize maxSize = {0, 0};

	/* classifier properties */
    temp0.n_stages=25;                   //number of strong classifier stages
	temp0.total_nodes=2913;              //number of total weak classifier notes in the cascade
	temp0.orig_window_size.height = 24;  //original window height
	temp0.orig_window_size.width = 24;   //original window width

	cascade[0] = &temp0;

	temp1.n_stages=25;                   //number of strong classifier stages
	temp1.total_nodes=2913;              //number of total weak classifier notes in the cascade
	temp1.orig_window_size.height = 24;  //original window height
	temp1.orig_window_size.width = 24;   //original window width

	cascade[1] = &temp1;

	temp2.n_stages=25;                   //number of strong classifier stages
	temp2.total_nodes=2913;              //number of total weak classifier notes in the cascade
	temp2.orig_window_size.height = 24;  //original window height
	temp2.orig_window_size.width = 24;   //original window width

	cascade[2] = &temp2;

	temp3.n_stages=25;                   //number of strong classifier stages
	temp3.total_nodes=2913;              //number of total weak classifier notes in the cascade
	temp3.orig_window_size.height = 24;  //original window height
	temp3.orig_window_size.width = 24;   //original window width

	cascade[3] = &temp3;

	temp4.n_stages=25;                   //number of strong classifier stages
	temp4.total_nodes=2913;              //number of total weak classifier notes in the cascade
	temp4.orig_window_size.height = 24;  //original window height
	temp4.orig_window_size.width = 24;   //original window width

	cascade[4] = &temp4;

	temp5.n_stages=25;                   //number of strong classifier stages
	temp5.total_nodes=2913;              //number of total weak classifier notes in the cascade
	temp5.orig_window_size.height = 24;  //original window height
	temp5.orig_window_size.width = 24;   //original window width

	cascade[5] = &temp5;

	temp6.n_stages=25;                   //number of strong classifier stages
	temp6.total_nodes=2913;              //number of total weak classifier notes in the cascade
	temp6.orig_window_size.height = 24;  //original window height
	temp6.orig_window_size.width = 24;   //original window width

	cascade[6] = &temp6;

	temp7.n_stages=25;                   //number of strong classifier stages
	temp7.total_nodes=2913;              //number of total weak classifier notes in the cascade
	temp7.orig_window_size.height = 24;  //original window height
	temp7.orig_window_size.width = 24;   //original window width

	cascade[7] = &temp7;

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
