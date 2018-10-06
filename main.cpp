#include <fstream>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <list>
#include <string.h>
//#include <stdlib.h>

using namespace std;

char ifileDir[50];
char ofileDir[50];

void Naive(const char* dir) {
    int height, width, total;
    int** matrix;
    int* head;
    //list<pair<int, int>> ans;
    list<int> ans_i;
    list<int> ans_j;


    ifstream ifile;
    ofstream ofile;

    string num = dir;


	strcat(ifileDir, dir);
	strcat(ifileDir, "/matrix.data");

	strcat(ofileDir, dir);
	strcat(ofileDir, "/final.peak");


    ifile.open(ifileDir, ios::in);
    ofile.open(ofileDir, ios::out);



    //fscanf(ifile, "%d %d\n", &height, &width);
    ifile >> height >> width;
    total = height * width;
    head = new int[height*width];
    matrix = new int*[height];

    for(int i=0; i<height; i++) {
        matrix[i] = head + width*i;
    }

    for(int i=0; i<total; i++) {
        //fscanf(ifile, "%d", head+i);
        //getchar();
        ifile >> head[i];
    }


    { // top row
        // top left
        if(matrix[0][0] > matrix[0][1] && matrix[0][0] > matrix[1][0]) {
            //ans.push_back({1, 1});
            ans_i.push_back(1);
            ans_j.push_back(1);
        }


        int i=0;
        for(int j=1; j<width-1; j++) {
            if(matrix[i][j] > matrix[i+1][j] &&
               matrix[i][j] > matrix[i][j-1] &&
               matrix[i][j] > matrix[i][j+1] ) {
                //ans.push_back({i+1, j+1});
                ans_i.push_back(i+1);
                ans_j.push_back(j+1);
            }
        }
        // top right
        if(matrix[0][width-1] > matrix[0][width-2] && matrix[0][width-1] > matrix[1][width-1]) {
            //ans.push_back({1, width});
            ans_i.push_back(1);
            ans_j.push_back(width);
        }
    }

    // between top and bottom
    for(int i=1; i<height-1; i++) {
        // leftmost
        if(matrix[i][0] > matrix[i-1][0] &&
           matrix[i][0] > matrix[i+1][0] &&
           matrix[i][0] > matrix[i][1] ) {
            //ans.push_back({i+1, 1});
            ans_i.push_back(i+1);
            ans_j.push_back(1);
        }
        // middle
        for(int j=1; j<width-1; j++) {
            if(matrix[i][j] > matrix[i-1][j] &&
               matrix[i][j] > matrix[i+1][j] &&
               matrix[i][j] > matrix[i][j-1] &&
               matrix[i][j] > matrix[i][j+1] ) {
                //ans.push_back({i+1, j+1});
                ans_i.push_back(i+1);
                ans_j.push_back(j+1);
            }
        }
        // right
        if(matrix[i][width-1] > matrix[i-1][width-1] &&
           matrix[i][width-1] > matrix[i+1][width-1] &&
           matrix[i][width-1] > matrix[i][width-2] ) {
            //ans.push_back({i+1, width});
            ans_i.push_back(i+1);
            ans_j.push_back(width);
        }
    }


    { // bottom row
        // bottom left
        if(matrix[height-1][0] > matrix[height-1][1] && matrix[height-1][0] > matrix[height-2][0]) {
            //ans.push_back({height, 1});
            ans_i.push_back(height);
            ans_j.push_back(1);
        }
        int i=height-1;
        for(int j=1; j<width-1; j++) {
            if(matrix[i][j] > matrix[i-1][j] &&
               matrix[i][j] > matrix[i][j-1] &&
               matrix[i][j] > matrix[i][j+1] ) {
                //ans.push_back({i+1, j+1});
                ans_i.push_back(i+1);
                ans_j.push_back(j+1);
            }
        }
        // bottom right
        if(matrix[height-1][width-1] > matrix[height-1][width-2] && matrix[height-1][width-1] > matrix[height-2][width-1]) {
            //ans.push_back({height, width});
            ans_i.push_back(height);
            ans_j.push_back(width);
        }
    }



    //fprintf(ofile, "%lu\n", ans_i.size());
    ofile << ans_i.size() << endl;
    for(std::list<int>::iterator iter_i = ans_i.begin(), iter_j = ans_j.begin();
        iter_i != ans_i.end(); iter_i++, iter_j++) {
        //fprintf(ofile, "%d %d\n", *iter_i, *iter_j);
        ofile << *iter_i << " " << *iter_j << endl;
    }

    /*
    printf("matrix: \n");
    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            printf("%8d ", matrix[i][j]);
        }
        printf("\n");
    }
    */

    delete[] head;
    delete[] matrix;
    ifile.close();
    ofile.close();
}


void BigRow(const char* dir) {
    unsigned int height, width, height_1, width_1;
    int* head;
    //list<pair<int, int>> ans;
    list<int> ans_i;
    list<int> ans_j;


    ifstream ifile;
    ofstream ofile;

    string num = dir;


	strcat(ifileDir, dir);
	strcat(ifileDir, "/matrix.data");

	strcat(ofileDir, dir);
	strcat(ofileDir, "/final.peak");


    ifile.open(ifileDir, ios::in);
    ofile.open(ofileDir, ios::out);



    //fscanf(ifile, "%d %d\n", &height, &width);
    ifile >> height >> width;
    height_1 = height-1;
    width_1 = width-1;

    head = new int[width*3];
    // Access element in this format:
    // head[ row + col*3 ]



    { /// Topmost row
        // read first two row
        for(int i=0; i<2; i++) {
            for(int j=0; j<width; j++) {
                ifile >> head[ i+(j*3) ];
            }
        }

        // top left
        if(head[0 + 0] > head[0 + (1*3)] && head[0 + 0] > head[1 + 0]) {
            ans_i.push_back(1);
            ans_j.push_back(1);
        }

        // middle cols
        for(int j=1; j<width_1; j++) {
            if(head[0 + (j)*3] > head[0 + (j-1)*3] &&
               head[0 + (j)*3] > head[0 + (j+1)*3] &&
               head[0 + (j)*3] > head[1 + (j)*3]) {
                ans_i.push_back(1);
                ans_j.push_back(j+1);
            }
        }

        // top right
        if(head[0 + (width-1)*3] > head[0 + (width-2)*3] && head[0 + (width-1)*3] > head[1 + (width-1)*3]) {
            ans_i.push_back(1);
            ans_j.push_back(width);
        }
    }

    { ///between top and bottom
        int i=0;
/// Flattens out into three parts to avoid using i%3
        while(true) {
            // Part 1 - "0,1,2".  1 being the middle row
            if(++i > height_1) break;
            for(int j=0; j<width; j++) {
                cin >> head[1 + j*3];
            }
                // leftmost col
            if(head[1 + 0] > head[    0    ] &&
               head[1 + 0] > head[2 + 0] &&
               head[1 + 0] > head[1 + 3]) {
                ans_i.push_back(2);
                ans_j.push_back(1);
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + (j)*3] > head[    (j)*3] &&
                   head[1 + (j)*3] > head[2 + (j)*3] &&
                   head[1 + (j)*3] > head[1 + (j-1)*3] &&
                   head[1 + (j)*3] > head[1 + (j+1)*3]) {
                    ans_i.push_back(i+1);
                    ans_j.push_back(j+1);
                }
            }
                // rightmost col
            if(head[1 + width_1*3] > head[    width_1*3] &&
               head[1 + width_1*3] > head[2 + width_1*3] &&
               head[1 + width_1*3] > head[1 + (width_1-1)*3]) {
                ans_i.push_back(i+1);
                ans_j.push_back(width);
            }

            /// Part 2 - "1,2,0"
            if(++i > height_1) break;
            for(int j=0; j<width; j++) {
                cin >> head[2 + j*3];
            }
                // leftmost col
            if(head[2    ] > head[1    ] &&
               head[2    ] > head[  0  ] &&
               head[2    ] > head[2 + 3]) {
                ans_i.push_back(i+1);
                ans_j.push_back(1);
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[2 + (j)*3] > head[1 + (j)*3] &&
                   head[2 + (j)*3] > head[    (j)*3] &&
                   head[2 + (j)*3] > head[2 + (j-1)*3] &&
                   head[2 + (j)*3] > head[2 + (j+1)*3]) {
                    ans_i.push_back(i+1);
                    ans_j.push_back(j+1);
                }
            }
                // rightmost col
            if(head[2 + width_1*3] > head[1 + width_1*3] &&
               head[2 + width_1*3] > head[    width_1*3] &&
               head[2 + width_1*3] > head[2 + (width_1-1)*3]) {
                ans_i.push_back(i+1);
                ans_j.push_back(width);
            }

            /// Part 3 - "2,0,1"
            if(++i > height_1) break;
            for(int j=0; j<width; j++) {
                cin >> head[   j*3];
            }
                // leftmost col
            if(head[0    ] > head[2    ] &&
               head[0    ] > head[1    ] &&
               head[0    ] > head[0 + 3]) {
                ans_i.push_back(i+1);
                ans_j.push_back(1);
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[0 + (j)*3] > head[2 + (j)*3] &&
                   head[0 + (j)*3] > head[1 + (j)*3] &&
                   head[0 + (j)*3] > head[0 + (j-1)*3] &&
                   head[0 + (j)*3] > head[0 + (j+1)*3]) {
                    ans_i.push_back(i+1);
                    ans_j.push_back(j+1);
                }
            }
                // rightmost col
            if(head[0 + width_1*3] > head[2 + width_1*3] &&
               head[0 + width_1*3] > head[1 + width_1*3] &&
               head[0 + width_1*3] > head[0 + (width_1-1)*3]) {
                ans_i.push_back(i+1);
                ans_j.push_back(width);
            }
        }
    }

    { /// bottom row
        if(height_1 % 3 == 1) { /// "0,1,2"
            // bottom left
            if(head[1 + 0] > head[0 + 0] &&
               head[1 + 0] > head[1 + 3]) {
                ans_i.push_back(height);
                ans_j.push_back(1);
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + j*3] > head[0 + j*3] &&
                   head[1 + j*3] > head[1 + (j-1)*3] &&
                   head[1 + j*3] > head[1 + (j+1)*3]) {
                    ans_i.push_back(height);
                    ans_j.push_back(j+1);
                }
            }
            // bottom right
            if(head[1 + width_1*3] > head[0 + width_1*3] &&
               head[1 + width_1*3] > head[1 + (width_1-1)*3]) {
                ans_i.push_back(height);
                ans_j.push_back(width);
            }
        }
        else if(height_1 % 3 == 2) { /// "1,2,0"
            // bottom left
            if(head[2 + 0] > head[1 + 0] &&
               head[2 + 0] > head[2 + 3]) {
                ans_i.push_back(height);
                ans_j.push_back(1);
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[2 + j*3] > head[1 + j*3] &&
                   head[2 + j*3] > head[2 + (j-1)*3] &&
                   head[2 + j*3] > head[2 + (j+1)*3]) {
                    ans_i.push_back(height);
                    ans_j.push_back(j+1);
                }
            }
            // bottom right
            if(head[2 + width_1*3] > head[1 + width_1*3] &&
               head[2 + width_1*3] > head[2 + (width_1-1)*3]) {
                ans_i.push_back(height);
                ans_j.push_back(width);
            }
        }
        else { /// "2,1,0"
            // bottom left
            if(head[1 + 0] > head[2 + 0] &&
               head[1 + 0] > head[1 + 3]) {
                ans_i.push_back(height);
                ans_j.push_back(1);
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + j*3] > head[2 + j*3] &&
                   head[1 + j*3] > head[1 + (j-1)*3] &&
                   head[1 + j*3] > head[1 + (j+1)*3]) {
                    ans_i.push_back(height);
                    ans_j.push_back(j+1);
                }
            }
            // bottom right
            if(head[1 + width_1*3] > head[2 + width_1*3] &&
               head[1 + width_1*3] > head[1 + (width_1-1)*3]) {
                ans_i.push_back(height);
                ans_j.push_back(width);
            }
        }
    }




    //fprintf(ofile, "%lu\n", ans_i.size());
    ofile << ans_i.size() << endl;
    for(std::list<int>::iterator iter_i = ans_i.begin(), iter_j = ans_j.begin();
        iter_i != ans_i.end(); iter_i++, iter_j++) {
        //fprintf(ofile, "%d %d\n", *iter_i, *iter_j);
        ofile << *iter_i << " " << *iter_j << endl;
    }

    /*
    printf("matrix: \n");
    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            printf("%8d ", matrix[i][j]);
        }
        printf("\n");
    }
    */

    delete[] head;
    ifile.close();
    ofile.close();
}





int main(int argc, char** argv)
{
    //clock_t s = clock();

    /// assuming width>=2 && height>=3

    if(argc >= 2){
        BigRow(argv[1]);

    }
    else exit(0xAAAAAAAA);


    //printf("> %ld\n", clock() - s);

    return 0;
}

