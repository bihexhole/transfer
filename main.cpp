#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <list>
#include <stdlib.h>
#include <string.h>

//#include "Generate_matrix.h"
//#include "Version_naive.h"

using namespace std;


void TheF(char* dir) {
    int height, width, total;
    int** matrix;
    int* head;
    //list<pair<int, int>> ans;
    list<int> ans_i;
    list<int> ans_j;


    FILE* ifile = NULL;
    FILE* ofile = NULL;

    char ifileDir[30] = {0};
    char ofileDir[30] = {0};
    strcpy(ifileDir, strcat(dir, "/matrix.data"));
    strcat(ofileDir, strcat(dir, "/final.peak"));

    if((ifile = fopen(ifileDir, "r") ) == NULL) {
        exit(999);
    }
    ofile = fopen(ofileDir, "w");



    fscanf(ifile, "%d %d\n", &height, &width);
    total = height * width;
    head = new int[height*width];
    matrix = new int*[height];

    for(int i=0; i<height; i++) {
        matrix[i] = head + width*i;
    }

    for(int i=0; i<total; i++) {
        fscanf(ifile, "%d", head+i);
        //getchar();
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



    fprintf(ofile, "%d\n", ans_i.size());
    for(std::list<int>::iterator iter_i = ans_i.begin(), iter_j = ans_j.begin();
        iter_i != ans_i.end(); iter_i++, iter_j++) {
        fprintf(ofile, "%d %d\n", *iter_i, *iter_j);
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
    fclose(ifile);
    fclose(ofile);
}


int main(int argc, char** argv)
{
    //clock_t s = clock();
    //Generate_matrix();
    //Pattern_matrix();

    if(argc >= 2)
        TheF(argv[1]);
    else return 0xAAAAA;

    //printf("> %ld\n", clock() - s);

    return 0;
}

