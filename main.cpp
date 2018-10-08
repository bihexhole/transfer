#include <fstream>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <list>
#include <vector>
#include <string.h>
//#include <stdlib.h>

#define log //printf
#define log2 //printf

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
	strcat(ofileDir, "/Nfinal.peak");


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
    cout << "\n**********\nANS:\n";
    cout << ans_i.size() << endl;
    for(std::list<int>::iterator iter_i = ans_i.begin(), iter_j = ans_j.begin();
        iter_i != ans_i.end(); iter_i++, iter_j++) {
        //cout << *iter_i << " " << *iter_j << endl;
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


void printCur(int* head, int width, int mid) {
    log("\nCurrent:\n");

    if(mid == 1){
        log("   ");
        for(int j=0; j<width; j++) {
            log("%d ", head[0 + j*3]);
        }
        log("\n");
        log(" > ");
        for(int j=0; j<width; j++) {
            log("%d ", head[1 + j*3]);
        }
        log("\n");
        log("   ");
        for(int j=0; j<width; j++) {
            log("%d ", head[2 + j*3]);
        }
        log("\n");
    }
    if(mid == 2){
        log("   ");
        for(int j=0; j<width; j++) {
            log("%d ", head[1 + j*3]);
        }
        log("\n");
        log(" > ");
        for(int j=0; j<width; j++) {
            log("%d ", head[2 + j*3]);
        }
        log("\n");
        log("   ");
        for(int j=0; j<width; j++) {
            log("%d ", head[0 + j*3]);
        }
        log("\n");
    }
    if(mid == 0){
        log("   ");
        for(int j=0; j<width; j++) {
            log("%d ", head[2 + j*3]);
        }
        log("\n");
        log(" > ");
        for(int j=0; j<width; j++) {
            log("%d ", head[0 + j*3]);
        }
        log("\n");
        log("   ");
        for(int j=0; j<width; j++) {
            log("%d ", head[1 + j*3]);
        }
        log("\n");
    }

    log("\n");
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
	strcat(ofileDir, "/BRfinal.peak");


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
        int i=0; // i indicates middle row.  ex: row[i]>row[i-1] && row[i]>row[i+1]
/// Flattens out into three parts to avoid using i%3
        while(true) {
            //printf("%4d ", i);
            // Part 1 - "0,1,2".  1 being the middle row
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[2 + j*3];
                log("%d ", head[2+j*3]);
            }
            printCur(head, width, 1);
                // leftmost col
            if(head[1 + 0] > head[    0    ] &&
               head[1 + 0] > head[2 + 0] &&
               head[1 + 0] > head[1 + 3]) {
                ans_i.push_back(i+1);
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
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[0 + j*3];
                log("%d ", head[0+j*3]);
            }
            printCur(head, width, 2);
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
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[1 + j*3];
                log("%d ", head[1+j*3]);
            }
            printCur(head, width, 0);
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
            log("BotLeft012\n%10d%10d\n%10d%10d\n", head[0+0], 0, head[1+0], head[1+3]);
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
            log("BotLeft120\n%10d%10d\n%10d%10d\n", head[1+0], 0, head[2+0], head[2+3]);
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
        else { /// "2,0,1"
            // bottom left
            if(head[0 + 0] > head[2 + 0] &&
               head[0 + 0] > head[0 + 3]) {
                ans_i.push_back(height);
                ans_j.push_back(1);
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[0 + j*3] > head[2 + j*3] &&
                   head[0 + j*3] > head[0 + (j-1)*3] &&
                   head[0 + j*3] > head[0 + (j+1)*3]) {
                    ans_i.push_back(height);
                    ans_j.push_back(j+1);
                }
            }
            // bottom right
            if(head[0 + width_1*3] > head[2 + width_1*3] &&
               head[0 + width_1*3] > head[0 + (width_1-1)*3]) {
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

    cout << "\n**********\nANS:\n";
    cout << ans_i.size() << endl;
    for(std::list<int>::iterator iter_i = ans_i.begin(), iter_j = ans_j.begin();
        iter_i != ans_i.end(); iter_i++, iter_j++) {
        //cout << *iter_i << " " << *iter_j << endl;
    }

    delete[] head;
    ifile.close();
    ofile.close();
}

/* Nope.
void BigRow_DirectOutput(const char* dir) {
    unsigned int height, width, height_1, width_1;
    int* head;
    int nopeaks = 0;
    //list<pair<int, int>> ans;
    list<int> ans_i;
    list<int> ans_j;


    ifstream ifile;
    ofstream ofile;

    string num = dir;


	strcat(ifileDir, dir);
	strcat(ifileDir, "/matrix.data");

	strcat(ofileDir, dir);
	strcat(ofileDir, "/BRfinal.peak");


    ifile.open(ifileDir, ios::in);
    ofile.open(ofileDir, ios::out);



    //fscanf(ifile, "%d %d\n", &height, &width);
    ifile >> height >> width;
    height_1 = height-1;
    width_1 = width-1;

    head = new int[width*3];
    // Access element in this format:
    // head[ row + col*3 ]

    ofile << "         \n";

    { /// Topmost row
        // read first two row
        for(int i=0; i<2; i++) {
            for(int j=0; j<width; j++) {
                ifile >> head[ i+(j*3) ];
            }
        }

        // top left
        if(head[0 + 0] > head[0 + (1*3)] && head[0 + 0] > head[1 + 0]) {
            nopeaks++;
            ofile << 1 << " " << 1 << "\n";
            //ans_i.push_back(1);
            //ans_j.push_back(1);
        }

        // middle cols
        for(int j=1; j<width_1; j++) {
            if(head[0 + (j)*3] > head[0 + (j-1)*3] &&
               head[0 + (j)*3] > head[0 + (j+1)*3] &&
               head[0 + (j)*3] > head[1 + (j)*3]) {
                nopeaks++;
                ofile << 1 << " " << j+1 << "\n";
                //ans_i.push_back(1);
                //ans_j.push_back(j+1);
            }
        }

        // top right
        if(head[0 + (width-1)*3] > head[0 + (width-2)*3] && head[0 + (width-1)*3] > head[1 + (width-1)*3]) {
            nopeaks++;
            ofile << 1 << " " << width << "\n";
            //ans_i.push_back(1);
            //ans_j.push_back(width);
        }
    }

    { ///between top and bottom
        int i=0; // i indicates middle row.  ex: row[i]>row[i-1] && row[i]>row[i+1]
/// Flattens out into three parts to avoid using i%3
        while(true) {
            //printf("%4d ", i);
            // Part 1 - "0,1,2".  1 being the middle row
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[2 + j*3];
                log("%d ", head[2+j*3]);
            }
            printCur(head, width, 1);
                // leftmost col
            if(head[1 + 0] > head[    0    ] &&
               head[1 + 0] > head[2 + 0] &&
               head[1 + 0] > head[1 + 3]) {
                nopeaks++;
                ofile << i+1 << " " << 1 << "\n";
                //ans_i.push_back(i+1);
                //ans_j.push_back(1);
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + (j)*3] > head[    (j)*3] &&
                   head[1 + (j)*3] > head[2 + (j)*3] &&
                   head[1 + (j)*3] > head[1 + (j-1)*3] &&
                   head[1 + (j)*3] > head[1 + (j+1)*3]) {
                    nopeaks++;
                    ofile << i+1 << " " << j+1 << "\n";
                    //ans_i.push_back(i+1);
                    //ans_j.push_back(j+1);
                }
            }
                // rightmost col
            if(head[1 + width_1*3] > head[    width_1*3] &&
               head[1 + width_1*3] > head[2 + width_1*3] &&
               head[1 + width_1*3] > head[1 + (width_1-1)*3]) {
                nopeaks++;
                ofile << i+1 << " " << width << "\n";
                //ans_i.push_back(i+1);
                //ans_j.push_back(width);
            }

            /// Part 2 - "1,2,0"
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[0 + j*3];
                log("%d ", head[0+j*3]);
            }
            printCur(head, width, 2);
                // leftmost col
            if(head[2    ] > head[1    ] &&
               head[2    ] > head[  0  ] &&
               head[2    ] > head[2 + 3]) {
                nopeaks++;
                ofile << i+1 << " " << 1 << "\n";
                //ans_i.push_back(i+1);
                //ans_j.push_back(1);
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[2 + (j)*3] > head[1 + (j)*3] &&
                   head[2 + (j)*3] > head[    (j)*3] &&
                   head[2 + (j)*3] > head[2 + (j-1)*3] &&
                   head[2 + (j)*3] > head[2 + (j+1)*3]) {
                    nopeaks++;
                    ofile << i+1 << " " << j+1 << "\n";
                    //ans_i.push_back(i+1);
                    //ans_j.push_back(j+1);
                }
            }
                // rightmost col
            if(head[2 + width_1*3] > head[1 + width_1*3] &&
               head[2 + width_1*3] > head[    width_1*3] &&
               head[2 + width_1*3] > head[2 + (width_1-1)*3]) {
                nopeaks++;
                ofile << i+1 << " " << width << "\n";
                //ans_i.push_back(i+1);
                //ans_j.push_back(width);
            }

            /// Part 3 - "2,0,1"
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[1 + j*3];
                log("%d ", head[1+j*3]);
            }
            printCur(head, width, 0);
                // leftmost col
            if(head[0    ] > head[2    ] &&
               head[0    ] > head[1    ] &&
               head[0    ] > head[0 + 3]) {
                nopeaks++;
                ofile << i+1 << " " << 1 << "\n";
                //ans_i.push_back(i+1);
                //ans_j.push_back(1);
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[0 + (j)*3] > head[2 + (j)*3] &&
                   head[0 + (j)*3] > head[1 + (j)*3] &&
                   head[0 + (j)*3] > head[0 + (j-1)*3] &&
                   head[0 + (j)*3] > head[0 + (j+1)*3]) {
                    nopeaks++;
                    ofile << i+1 << " " << j+1 << "\n";
                    //ans_i.push_back(i+1);
                    //ans_j.push_back(j+1);
                }
            }
                // rightmost col
            if(head[0 + width_1*3] > head[2 + width_1*3] &&
               head[0 + width_1*3] > head[1 + width_1*3] &&
               head[0 + width_1*3] > head[0 + (width_1-1)*3]) {
                nopeaks++;
                ofile << i+1 << " " << width << "\n";
                //ans_i.push_back(i+1);
                //ans_j.push_back(width);
            }
        }
    }

    { /// bottom row
        if(height_1 % 3 == 1) { /// "0,1,2"
            // bottom left
            log("BotLeft012\n%10d%10d\n%10d%10d\n", head[0+0], 0, head[1+0], head[1+3]);
            if(head[1 + 0] > head[0 + 0] &&
               head[1 + 0] > head[1 + 3]) {
                nopeaks++;
                ofile << height << " " << 1 << "\n";
                //ans_i.push_back(height);
                //ans_j.push_back(1);
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + j*3] > head[0 + j*3] &&
                   head[1 + j*3] > head[1 + (j-1)*3] &&
                   head[1 + j*3] > head[1 + (j+1)*3]) {
                    nopeaks++;
                    ofile << height << " " << j+1 << "\n";
                    //ans_i.push_back(height);
                    //ans_j.push_back(j+1);
                }
            }
            // bottom right
            if(head[1 + width_1*3] > head[0 + width_1*3] &&
               head[1 + width_1*3] > head[1 + (width_1-1)*3]) {
                nopeaks++;
                ofile << height << " " << width << "\n";
                //ans_i.push_back(height);
                //ans_j.push_back(width);
            }
        }
        else if(height_1 % 3 == 2) { /// "1,2,0"
            // bottom left
            log("BotLeft120\n%10d%10d\n%10d%10d\n", head[1+0], 0, head[2+0], head[2+3]);
            if(head[2 + 0] > head[1 + 0] &&
               head[2 + 0] > head[2 + 3]) {
                nopeaks++;
                ofile << height << " " << 1 << "\n";
                //ans_i.push_back(height);
                //ans_j.push_back(1);
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[2 + j*3] > head[1 + j*3] &&
                   head[2 + j*3] > head[2 + (j-1)*3] &&
                   head[2 + j*3] > head[2 + (j+1)*3]) {
                    nopeaks++;
                    ofile << height << " " << j+1 << "\n";
                    //ans_i.push_back(height);
                    //ans_j.push_back(j+1);
                }
            }
            // bottom right
            if(head[2 + width_1*3] > head[1 + width_1*3] &&
               head[2 + width_1*3] > head[2 + (width_1-1)*3]) {
                nopeaks++;
                ofile << height << " " << width << "\n";
                //ans_i.push_back(height);
                //ans_j.push_back(width);
            }
        }
        else { /// "2,0,1"
            // bottom left
            if(head[0 + 0] > head[2 + 0] &&
               head[0 + 0] > head[0 + 3]) {
                nopeaks++;
                ofile << height << " " << 1 << "\n";
                //ans_i.push_back(height);
                //ans_j.push_back(1);
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[0 + j*3] > head[2 + j*3] &&
                   head[0 + j*3] > head[0 + (j-1)*3] &&
                   head[0 + j*3] > head[0 + (j+1)*3]) {
                    nopeaks++;
                    ofile << height << " " << j+1 << "\n";
                    //ans_i.push_back(height);
                    //ans_j.push_back(j+1);
                }
            }
            // bottom right
            if(head[0 + width_1*3] > head[2 + width_1*3] &&
               head[0 + width_1*3] > head[0 + (width_1-1)*3]) {
                nopeaks++;
                ofile << height << " " << width << "\n";
                //ans_i.push_back(height);
                //ans_j.push_back(width);
            }
        }
    }

    ofile.seekp(0, ios_base::beg);
    ofile << nopeaks;



    cout << "\n**********\nANS:\n";
    cout << nopeaks << "\n";


    delete[] head;
    ifile.close();
    ofile.close();
}
*/

// also short.
void BigRow_deltaI(const char* dir) {
    short height, width, height_1, width_1;
    int* head;
    //list<pair<int, int>> ans;
    vector<short> ans_i;
    vector<short> ans_j;
    short ith_count = 0;
    int total_count = 0;


    ifstream ifile;
    ofstream ofile;

    string num = dir;


	strcat(ifileDir, dir);
	strcat(ifileDir, "/matrix.data");

	strcat(ofileDir, dir);
	strcat(ofileDir, "/DIfinal.peak");


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
            //ans_i.push_back(1);
            ith_count++;
            ans_j.push_back(1);
        }

        // middle cols
        for(int j=1; j<width_1; j++) {
            if(head[0 + (j)*3] > head[0 + (j-1)*3] &&
               head[0 + (j)*3] > head[0 + (j+1)*3] &&
               head[0 + (j)*3] > head[1 + (j)*3]) {
                //ans_i.push_back(1);
                ith_count++;
                ans_j.push_back(j+1);
            }
        }

        // top right
        if(head[0 + (width-1)*3] > head[0 + (width-2)*3] && head[0 + (width-1)*3] > head[1 + (width-1)*3]) {
            //ans_i.push_back(1);
            ith_count++;
            ans_j.push_back(width);
        }

        ans_i.push_back(ith_count);
        total_count += ith_count;
        ith_count = 0;
    }

    { ///between top and bottom
        int i=0; // i indicates middle row.  ex: row[i]>row[i-1] && row[i]>row[i+1]
/// Flattens out into three parts to avoid using i%3
        while(true) {
            //printf("%4d ", i);
            /// Part 1 - "0,1,2".  1 being the middle row
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[2 + j*3];
                log("%d ", head[2+j*3]);
            }
            printCur(head, width, 1);
                // leftmost col
            if(head[1 + 0] > head[    0    ] &&
               head[1 + 0] > head[2 + 0] &&
               head[1 + 0] > head[1 + 3]) {
                //ans_i.push_back(i+1);
                ith_count++;
                ans_j.push_back(1);
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + (j)*3] > head[    (j)*3] &&
                   head[1 + (j)*3] > head[2 + (j)*3] &&
                   head[1 + (j)*3] > head[1 + (j-1)*3] &&
                   head[1 + (j)*3] > head[1 + (j+1)*3]) {
                    //ans_i.push_back(i+1);
                    ith_count++;
                    ans_j.push_back(j+1);
                }
            }
                // rightmost col
            if(head[1 + width_1*3] > head[    width_1*3] &&
               head[1 + width_1*3] > head[2 + width_1*3] &&
               head[1 + width_1*3] > head[1 + (width_1-1)*3]) {
                //ans_i.push_back(i+1);
                ith_count++;
                ans_j.push_back(width);
            }

            ans_i.push_back(ith_count);
            total_count += ith_count;
            ith_count = 0;


            /// Part 2 - "1,2,0"
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[0 + j*3];
                log("%d ", head[0+j*3]);
            }
            printCur(head, width, 2);
                // leftmost col
            if(head[2    ] > head[1    ] &&
               head[2    ] > head[  0  ] &&
               head[2    ] > head[2 + 3]) {
                //ans_i.push_back(i+1);
                ith_count++;
                ans_j.push_back(1);
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[2 + (j)*3] > head[1 + (j)*3] &&
                   head[2 + (j)*3] > head[    (j)*3] &&
                   head[2 + (j)*3] > head[2 + (j-1)*3] &&
                   head[2 + (j)*3] > head[2 + (j+1)*3]) {
                    //ans_i.push_back(i+1);
                    ith_count++;
                    ans_j.push_back(j+1);
                }
            }
                // rightmost col
            if(head[2 + width_1*3] > head[1 + width_1*3] &&
               head[2 + width_1*3] > head[    width_1*3] &&
               head[2 + width_1*3] > head[2 + (width_1-1)*3]) {
                //ans_i.push_back(i+1);
                ith_count++;
                ans_j.push_back(width);
            }

            ans_i.push_back(ith_count);
            total_count += ith_count;
            ith_count = 0;

            /// Part 3 - "2,0,1"
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[1 + j*3];
                log("%d ", head[1+j*3]);
            }
            printCur(head, width, 0);
                // leftmost col
            if(head[0    ] > head[2    ] &&
               head[0    ] > head[1    ] &&
               head[0    ] > head[0 + 3]) {
                //ans_i.push_back(i+1);
                ith_count++;
                ans_j.push_back(1);
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[0 + (j)*3] > head[2 + (j)*3] &&
                   head[0 + (j)*3] > head[1 + (j)*3] &&
                   head[0 + (j)*3] > head[0 + (j-1)*3] &&
                   head[0 + (j)*3] > head[0 + (j+1)*3]) {
                    //ans_i.push_back(i+1);
                    ith_count++;
                    ans_j.push_back(j+1);
                }
            }
                // rightmost col
            if(head[0 + width_1*3] > head[2 + width_1*3] &&
               head[0 + width_1*3] > head[1 + width_1*3] &&
               head[0 + width_1*3] > head[0 + (width_1-1)*3]) {
                //ans_i.push_back(i+1);
                ith_count++;
                ans_j.push_back(width);
            }

            ans_i.push_back(ith_count);
            total_count += ith_count;
            ith_count = 0;
        }
    }

    { /// bottom row
        if(height_1 % 3 == 1) { /// "0,1,2"
            // bottom left
            log("BotLeft012\n%10d%10d\n%10d%10d\n", head[0+0], 0, head[1+0], head[1+3]);
            if(head[1 + 0] > head[0 + 0] &&
               head[1 + 0] > head[1 + 3]) {
                //ans_i.push_back(height);
                ith_count++;
                ans_j.push_back(1);
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + j*3] > head[0 + j*3] &&
                   head[1 + j*3] > head[1 + (j-1)*3] &&
                   head[1 + j*3] > head[1 + (j+1)*3]) {
                    //ans_i.push_back(height);
                    ith_count++;
                    ans_j.push_back(j+1);
                }
            }
            // bottom right
            if(head[1 + width_1*3] > head[0 + width_1*3] &&
               head[1 + width_1*3] > head[1 + (width_1-1)*3]) {
                //ans_i.push_back(height);
                ith_count++;
                ans_j.push_back(width);
            }

            ans_i.push_back(ith_count);
            total_count += ith_count;
            ith_count = 0;
        }
        else if(height_1 % 3 == 2) { /// "1,2,0"
            // bottom left
            log("BotLeft120\n%10d%10d\n%10d%10d\n", head[1+0], 0, head[2+0], head[2+3]);
            if(head[2 + 0] > head[1 + 0] &&
               head[2 + 0] > head[2 + 3]) {
                //ans_i.push_back(height);
                ith_count++;
                ans_j.push_back(1);
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[2 + j*3] > head[1 + j*3] &&
                   head[2 + j*3] > head[2 + (j-1)*3] &&
                   head[2 + j*3] > head[2 + (j+1)*3]) {
                    //ans_i.push_back(height);
                    ith_count++;
                    ans_j.push_back(j+1);
                }
            }
            // bottom right
            if(head[2 + width_1*3] > head[1 + width_1*3] &&
               head[2 + width_1*3] > head[2 + (width_1-1)*3]) {
                //ans_i.push_back(height);
                ith_count++;
                ans_j.push_back(width);
            }

            ans_i.push_back(ith_count);
            total_count += ith_count;
            ith_count = 0;
        }
        else { /// "2,0,1"
            // bottom left
            if(head[0 + 0] > head[2 + 0] &&
               head[0 + 0] > head[0 + 3]) {
                //ans_i.push_back(height);
                ith_count++;
                ans_j.push_back(1);
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[0 + j*3] > head[2 + j*3] &&
                   head[0 + j*3] > head[0 + (j-1)*3] &&
                   head[0 + j*3] > head[0 + (j+1)*3]) {
                    //ans_i.push_back(height);
                    ith_count++;
                    ans_j.push_back(j+1);
                }
            }
            // bottom right
            if(head[0 + width_1*3] > head[2 + width_1*3] &&
               head[0 + width_1*3] > head[0 + (width_1-1)*3]) {
                //ans_i.push_back(height);
                ith_count++;
                ans_j.push_back(width);
            }

            ans_i.push_back(ith_count);
            total_count += ith_count;
            ith_count = 0;
        }
    }




    //fprintf(ofile, "%lu\n", ans_i.size());
    short row_idx = 1;
    ofile << total_count << "\n";
    for(std::vector<short>::iterator iter_i = ans_i.begin(), iter_j = ans_j.begin();
        iter_i != ans_i.end(); iter_i++) {
        short cnt = *iter_i;

        while(cnt--) { // cnt-- != 0
            ofile << row_idx << " " << *iter_j << "\n";
            iter_j++;
        }
        row_idx++;
    }



    cout << "\n**********\nANS:\n";
    cout << total_count << "\n";
    /*for(std::list<int>::iterator iter_i = ans_i.begin(), iter_j = ans_j.begin();
        iter_i != ans_i.end(); iter_i++, iter_j++) {
        //cout << *iter_i << " " << *iter_j << endl;
    }*/

    delete[] head;
    ifile.close();
    ofile.close();
}


inline void Check_J(unsigned short& j_idx, short** ans_j, unsigned char& j_curr) {
    if(j_idx >= 15625) {
        j_idx = 0;
        j_curr++;
        ans_j[j_curr] = new short[15625];
    }
}

void BigRow_deltaI_SepArr(const char* dir) {
    unsigned short height, width, height_1, width_1;
    int* head;
    //list<pair<int, int>> ans;
    short ans_i[1000];
    short* ans_j[32]; // maximum peak count = 1000*1000/2 = 500,000; divide into 32*15625;
    unsigned short j_idx = 0, i_count = 0;
    unsigned char j_curr = -1;
    unsigned short ith_count = 0;
    int total_count = 0;


    ifstream ifile;
    ofstream ofile;

    string num = dir;


	strcat(ifileDir, dir);
	strcat(ifileDir, "/matrix.data");

	strcat(ofileDir, dir);
	strcat(ofileDir, "/DISAfinal.peak");


    ifile.open(ifileDir, ios::in);
    ofile.open(ofileDir, ios::out);



    //fscanf(ifile, "%d %d\n", &height, &width);
    ifile >> height >> width;
    height_1 = height-1;
    width_1 = width-1;

    head = new int[width*3];
    // Access element in this format:
    // head[ row + col*3 ]

    ans_j[++j_curr] = new short[15625];
    j_idx = 0;

    { /// Topmost row
      // Doesn't need check_j
        // read first two row
        for(int i=0; i<2; i++) {
            for(int j=0; j<width; j++) {
                ifile >> head[ i+(j*3) ];
            }
        }

        // top left
        if(head[0 + 0] > head[0 + (1*3)] && head[0 + 0] > head[1 + 0]) {
            ith_count++;
            //ans_j.push_back(1);
            ans_j[j_curr][j_idx++] = 1;
        }

        // middle cols
        for(int j=1; j<width_1; j++) {
            if(head[0 + (j)*3] > head[0 + (j-1)*3] &&
               head[0 + (j)*3] > head[0 + (j+1)*3] &&
               head[0 + (j)*3] > head[1 + (j)*3]) {
                ith_count++;
                //ans_j.push_back(j+1);
                ans_j[j_curr][j_idx++] = j+1;
            }
        }

        // top right
        if(head[0 + (width-1)*3] > head[0 + (width-2)*3] && head[0 + (width-1)*3] > head[1 + (width-1)*3]) {
            ith_count++;
            //ans_j.push_back(width);
            ans_j[j_curr][j_idx++] = width;
        }

        //ans_i.push_back(ith_count);
        ans_i[i_count++] = ith_count;
        total_count += ith_count;
        ith_count = 0;
    }

    { ///between top and bottom
        int i=0; // i indicates middle row.  ex: row[i]>row[i-1] && row[i]>row[i+1]
/// Flattens out into three parts to avoid using i%3
        while(true) {
            //printf("%4d ", i);
            /// Part 1 - "0,1,2".  1 being the middle row
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[2 + j*3];
                log("%d ", head[2+j*3]);
            }
                // leftmost col
            if(head[1 + 0] > head[    0    ] &&
               head[1 + 0] > head[2 + 0] &&
               head[1 + 0] > head[1 + 3]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + (j)*3] > head[    (j)*3] &&
                   head[1 + (j)*3] > head[2 + (j)*3] &&
                   head[1 + (j)*3] > head[1 + (j-1)*3] &&
                   head[1 + (j)*3] > head[1 + (j+1)*3]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
                // rightmost col
            if(head[1 + width_1*3] > head[    width_1*3] &&
               head[1 + width_1*3] > head[2 + width_1*3] &&
               head[1 + width_1*3] > head[1 + (width_1-1)*3]) {
                ith_count++;
                //ans_j.push_back(width);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = width;
            }

            //ans_i.push_back(ith_count);
            ans_i[i_count++] = ith_count;
            total_count += ith_count;
            ith_count = 0;


            /// Part 2 - "1,2,0"
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[0 + j*3];
                log("%d ", head[0+j*3]);
            }
                // leftmost col
            if(head[2    ] > head[1    ] &&
               head[2    ] > head[  0  ] &&
               head[2    ] > head[2 + 3]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[2 + (j)*3] > head[1 + (j)*3] &&
                   head[2 + (j)*3] > head[    (j)*3] &&
                   head[2 + (j)*3] > head[2 + (j-1)*3] &&
                   head[2 + (j)*3] > head[2 + (j+1)*3]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
                // rightmost col
            if(head[2 + width_1*3] > head[1 + width_1*3] &&
               head[2 + width_1*3] > head[    width_1*3] &&
               head[2 + width_1*3] > head[2 + (width_1-1)*3]) {
                ith_count++;
                //ans_j.push_back(width);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = width;
            }

            //ans_i.push_back(ith_count);
            ans_i[i_count++] = ith_count;
            total_count += ith_count;
            ith_count = 0;

            /// Part 3 - "2,0,1"
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[1 + j*3];
                log("%d ", head[1+j*3]);
            }
                // leftmost col
            if(head[0    ] > head[2    ] &&
               head[0    ] > head[1    ] &&
               head[0    ] > head[0 + 3]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[0 + (j)*3] > head[2 + (j)*3] &&
                   head[0 + (j)*3] > head[1 + (j)*3] &&
                   head[0 + (j)*3] > head[0 + (j-1)*3] &&
                   head[0 + (j)*3] > head[0 + (j+1)*3]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
                // rightmost col
            if(head[0 + width_1*3] > head[2 + width_1*3] &&
               head[0 + width_1*3] > head[1 + width_1*3] &&
               head[0 + width_1*3] > head[0 + (width_1-1)*3]) {
                ith_count++;
                //ans_j.push_back(width);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = width;
            }

            //ans_i.push_back(ith_count);
            ans_i[i_count++] = ith_count;
            total_count += ith_count;
            ith_count = 0;
        }
    }

    { /// bottom row
        if(height_1 % 3 == 1) { /// "0,1,2"
            // bottom left
            log("BotLeft012\n%10d%10d\n%10d%10d\n", head[0+0], 0, head[1+0], head[1+3]);
            if(head[1 + 0] > head[0 + 0] &&
               head[1 + 0] > head[1 + 3]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + j*3] > head[0 + j*3] &&
                   head[1 + j*3] > head[1 + (j-1)*3] &&
                   head[1 + j*3] > head[1 + (j+1)*3]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
            // bottom right
            if(head[1 + width_1*3] > head[0 + width_1*3] &&
               head[1 + width_1*3] > head[1 + (width_1-1)*3]) {
                ith_count++;
                //ans_j.push_back(width);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = width;
            }

            //ans_i.push_back(ith_count);
            ans_i[i_count++] = ith_count;
            total_count += ith_count;
            ith_count = 0;
        }
        else if(height_1 % 3 == 2) { /// "1,2,0"
            // bottom left
            log("BotLeft120\n%10d%10d\n%10d%10d\n", head[1+0], 0, head[2+0], head[2+3]);
            if(head[2 + 0] > head[1 + 0] &&
               head[2 + 0] > head[2 + 3]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[2 + j*3] > head[1 + j*3] &&
                   head[2 + j*3] > head[2 + (j-1)*3] &&
                   head[2 + j*3] > head[2 + (j+1)*3]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
            // bottom right
            if(head[2 + width_1*3] > head[1 + width_1*3] &&
               head[2 + width_1*3] > head[2 + (width_1-1)*3]) {
                ith_count++;
                //ans_j.push_back(width);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = width;
            }

            //ans_i.push_back(ith_count);
            ans_i[i_count++] = ith_count;
            total_count += ith_count;
            ith_count = 0;
        }
        else { /// "2,0,1"
            // bottom left
            if(head[0 + 0] > head[2 + 0] &&
               head[0 + 0] > head[0 + 3]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[0 + j*3] > head[2 + j*3] &&
                   head[0 + j*3] > head[0 + (j-1)*3] &&
                   head[0 + j*3] > head[0 + (j+1)*3]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
            // bottom right
            if(head[0 + width_1*3] > head[2 + width_1*3] &&
               head[0 + width_1*3] > head[0 + (width_1-1)*3]) {
                ith_count++;
                //ans_j.push_back(width);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = width;
            }

            //ans_i.push_back(ith_count);
            ans_i[i_count++] = ith_count;
            total_count += ith_count;
            ith_count = 0;
        }
    }




    short row_idx = 1;
    short jarr_idx = 0;
    ofile << total_count << "\n";
    for(unsigned short i = 0, j=0; i<i_count; i++) {
        short cnt = ans_i[i];

        while(cnt--) { // cnt-- != 0
            if(j >= 15625) {
                j=0;
                jarr_idx++;
            }
            ofile << row_idx << " " << ans_j[jarr_idx][j++] << "\n";
        }
        row_idx++;
    }



    /*
    short row_idx = 1;
    ofile << total_count << "\n";
    for(std::vector<short>::iterator iter_i = ans_i.begin(), iter_j = ans_j.begin();
        iter_i != ans_i.end(); iter_i++) {
        short cnt = *iter_i;

        while(cnt--) { // cnt-- != 0
            ofile << row_idx << " " << *iter_j << "\n";
            iter_j++;
        }
        row_idx++;
    }
    */



    cout << "\n**********\nANS:\n";
    cout << total_count << "\n";
    /*for(std::list<int>::iterator iter_i = ans_i.begin(), iter_j = ans_j.begin();
        iter_i != ans_i.end(); iter_i++, iter_j++) {
        //cout << *iter_i << " " << *iter_j << endl;
    }*/

    ifile.close();
    ofile.close();
    delete[] head;
    for(int x=0; x<=j_curr; x++) {
        delete ans_j[x];
    }
}



void BigRow_extraRow_deltaI_SepArr(const char* dir) {
    unsigned short height, width, height_1, width_1;
    int* head;
    //list<pair<int, int>> ans;
    short ans_i[1000];
    short* ans_j[32]; // maximum peak count = 1000*1000/2 = 500,000; divide into 32*15625;
    unsigned short j_idx = 0, i_count = 0;
    unsigned char j_curr = -1;
    unsigned short ith_count = 0;
    int total_count = 0;


    ifstream ifile;
    ofstream ofile;

    string num = dir;


    strcat(ifileDir, dir);
    strcat(ifileDir, "/matrix.data");

    strcat(ofileDir, dir);
    strcat(ofileDir, "/DISAfinal.peak");


    ifile.open(ifileDir, ios::in);
    ofile.open(ofileDir, ios::out);



    //fscanf(ifile, "%d %d\n", &height, &width);
    ifile >> height >> width;
    height_1 = height-1;
    width_1 = width-1;

    head = new int[width<<2];
    // Access element in this format:
    // head[ row + col*3 ]

    ans_j[++j_curr] = new short[15625];
    j_idx = 0;

    { /// Topmost row
      // Doesn't need check_j
        // read first two row
        for(int i=0; i<2; i++) {
            for(int j=0; j<width; j++) {
                ifile >> head[ i+(j<<2) ];
            }
        }

        // top left
        if(head[0] > head[4] && head[0] > head[1]) {
            ith_count++;
            //ans_j.push_back(1);
            ans_j[j_curr][j_idx++] = 1;
        }

        // middle cols
        for(int j=1; j<width_1; j++) {
            if(head[j<<2] > head[    ((j-1)<<2)] &&
               head[j<<2] > head[    ((j+1)<<2)] &&
               head[j<<2] > head[1 + (j<<2)]) {
                ith_count++;
                //ans_j.push_back(j+1);
                ans_j[j_curr][j_idx++] = j+1;
            }
        }

        // top right
        if(head[    ((width-1)<<2)] > head[    ((width-2)<<2)] && head[    ((width-1)<<2)] > head[1 + ((width-1)<<2)]) {
            ith_count++;
            //ans_j.push_back(width);
            ans_j[j_curr][j_idx++] = width;
        }

        //ans_i.push_back(ith_count);
        ans_i[i_count++] = ith_count;
        total_count += ith_count;
        ith_count = 0;
    }

    { ///between top and bottom
        int i=0; // i indicates middle row.  ex: row[i]>row[i-1] && row[i]>row[i+1]
/// Flattens out into three parts to avoid using i%3
        while(true) {
            //printf("%4d ", i);
            /// Part 1 - "0,1,2".  1 being the middle row
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[2 + (j<<2)];
                log("%d ", head[2+(j<<2)]);
            }
                // leftmost col
            if(head[1] > head[0] &&
               head[1] > head[2] &&
               head[1] > head[1 + 4]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + (j<<2)] > head[    (j<<2)] &&
                   head[1 + (j<<2)] > head[2 + (j<<2)] &&
                   head[1 + (j<<2)] > head[1 + ((j-1)<<2)] &&
                   head[1 + (j<<2)] > head[1 + ((j+1)<<2)]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
                // rightmost col
            if(head[1 + (width_1<<2)] > head[    (width_1<<2)] &&
               head[1 + (width_1<<2)] > head[2 + (width_1<<2)] &&
               head[1 + (width_1<<2)] > head[1 + ((width_1-1)<<2)]) {
                ith_count++;
                //ans_j.push_back(width);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = width;
            }

            //ans_i.push_back(ith_count);
            ans_i[i_count++] = ith_count;
            total_count += ith_count;
            ith_count = 0;


            /// Part 2 - "1,2,0"
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[    (j<<2)];
                log("%d ", head[0+(j<<2)]);
            }
                // leftmost col
            if(head[2    ] > head[1    ] &&
               head[2    ] > head[  0  ] &&
               head[2    ] > head[2 + 4]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[2 + (j<<2)] > head[1 + (j<<2)] &&
                   head[2 + (j<<2)] > head[    (j<<2)] &&
                   head[2 + (j<<2)] > head[2 + ((j-1)<<2)] &&
                   head[2 + (j<<2)] > head[2 + ((j+1)<<2)]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
                // rightmost col
            if(head[2 + (width_1<<2)] > head[1 + (width_1<<2)] &&
               head[2 + (width_1<<2)] > head[    (width_1<<2)] &&
               head[2 + (width_1<<2)] > head[2 + ((width_1-1)<<2)]) {
                ith_count++;
                //ans_j.push_back(width);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = width;
            }

            //ans_i.push_back(ith_count);
            ans_i[i_count++] = ith_count;
            total_count += ith_count;
            ith_count = 0;

            /// Part 3 - "2,0,1"
            if(++i >= height_1) break;
            log("Scanning row %d...\n   ", i+1);
            for(int j=0; j<width; j++) {
                ifile >> head[1 + (j<<2)];
                log("%d ", head[1+(j<<2)]);
            }
                // leftmost col
            if(head[0    ] > head[2    ] &&
               head[0    ] > head[1    ] &&
               head[0    ] > head[    4]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[    (j<<2)] > head[2 + (j<<2)] &&
                   head[    (j<<2)] > head[1 + (j<<2)] &&
                   head[    (j<<2)] > head[    ((j-1)<<2)] &&
                   head[    (j<<2)] > head[    ((j+1)<<2)]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
                // rightmost col
            if(head[    (width_1<<2)] > head[2 + (width_1<<2)] &&
               head[    (width_1<<2)] > head[1 + (width_1<<2)] &&
               head[    (width_1<<2)] > head[    ((width_1-1)<<2)]) {
                ith_count++;
                //ans_j.push_back(width);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = width;
            }

            //ans_i.push_back(ith_count);
            ans_i[i_count++] = ith_count;
            total_count += ith_count;
            ith_count = 0;
        }
    }

    { /// bottom row
        if(height_1 % 3 == 1) { /// "0,1,2"
            // bottom left
            if(head[1    ] > head[  0  ] &&
               head[1    ] > head[1 + 4]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + (j<<2)] > head[    (j<<2)] &&
                   head[1 + (j<<2)] > head[1 + ((j-1)<<2)] &&
                   head[1 + (j<<2)] > head[1 + ((j+1)<<2)]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
            // bottom right
            if(head[1 + (width_1<<2)] > head[    (width_1<<2)] &&
               head[1 + (width_1<<2)] > head[1 + ((width_1-1)<<2)]) {
                ith_count++;
                //ans_j.push_back(width);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = width;
            }

            //ans_i.push_back(ith_count);
            ans_i[i_count++] = ith_count;
            total_count += ith_count;
            ith_count = 0;
        }
        else if(height_1 % 3 == 2) { /// "1,2,0"
            // bottom left
            if(head[2    ] > head[1    ] &&
               head[2    ] > head[2 + 4]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[2 + (j<<2)] > head[1 + (j<<2)] &&
                   head[2 + (j<<2)] > head[2 + ((j-1)<<2)] &&
                   head[2 + (j<<2)] > head[2 + ((j+1)<<2)]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
            // bottom right
            if(head[2 + (width_1<<2)] > head[1 + (width_1<<2)] &&
               head[2 + (width_1<<2)] > head[2 + ((width_1-1)<<2)]) {
                ith_count++;
                //ans_j.push_back(width);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = width;
            }

            //ans_i.push_back(ith_count);
            ans_i[i_count++] = ith_count;
            total_count += ith_count;
            ith_count = 0;
        }
        else { /// "2,0,1"
            // bottom left
            if(head[  0  ] > head[2    ] &&
               head[  0  ] > head[    4]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[    (j<<2)] > head[2 + (j<<2)] &&
                   head[    (j<<2)] > head[    ((j-1)<<2)] &&
                   head[    (j<<2)] > head[    ((j+1)<<2)]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
            // bottom right
            if(head[    (width_1<<2)] > head[2 + (width_1<<2)] &&
               head[    (width_1<<2)] > head[    ((width_1-1)<<2)]) {
                ith_count++;
                //ans_j.push_back(width);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = width;
            }

            //ans_i.push_back(ith_count);
            ans_i[i_count++] = ith_count;
            total_count += ith_count;
            ith_count = 0;
        }
    }




    short row_idx = 1;
    short jarr_idx = 0;
    ofile << total_count << "\n";
    for(unsigned short i = 0, j=0; i<i_count; i++) {
        short cnt = ans_i[i];

        while(cnt--) { // cnt-- != 0
            if(j >= 15625) {
                j=0;
                jarr_idx++;
            }
            ofile << row_idx << " " << ans_j[jarr_idx][j++] << "\n";
        }
        row_idx++;
    }



    /*
    short row_idx = 1;
    ofile << total_count << "\n";
    for(std::vector<short>::iterator iter_i = ans_i.begin(), iter_j = ans_j.begin();
        iter_i != ans_i.end(); iter_i++) {
        short cnt = *iter_i;

        while(cnt--) { // cnt-- != 0
            ofile << row_idx << " " << *iter_j << "\n";
            iter_j++;
        }
        row_idx++;
    }
    */



    cout << "\n**********\nANS:\n";
    cout << total_count << "\n";
    /*for(std::list<int>::iterator iter_i = ans_i.begin(), iter_j = ans_j.begin();
        iter_i != ans_i.end(); iter_i++, iter_j++) {
        //cout << *iter_i << " " << *iter_j << endl;
    }*/

    ifile.close();
    ofile.close();
    delete[] head;
    for(int x=0; x<=j_curr; x++) {
        delete ans_j[x];
    }
}


int main(int argc, char** argv)
{
    clock_t s = clock();

    /// assuming width>=2 && height>=3

    //BigRow("106062223");
    //BigRow_deltaI("106062223");
    BigRow_deltaI_SepArr("106062223");
    //BigRow_extraRow_deltaI_SepArr("106062223");
    //Naive("106062223");
    /*
    if(argc >= 2){
        BigRow(argv[1]);
    }
    else exit(0xAAAAAAAA);
    */

    printf("> %ld\n", clock() - s);

    return 0;
}

