#include <fstream>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <vector>

#define printf //printf

using namespace std;

char ifileDir[50];
char ofileDir[50];

ifstream ifile;
ofstream ofile;

inline void Check_J(unsigned short& j_idx, short** ans_j, unsigned char& j_curr) {
    if(j_idx >= 15625) {
        j_idx = 0;
        j_curr++;
        ans_j[j_curr] = new short[15625];
    }
}

void BigRow_extraRow_deltaI_SepArr(unsigned short& height, unsigned short& width) {
    unsigned short height_1, width_1;
    int* head;
    short ans_i[1000];
    short* ans_j[32]; // maximum peak count = 1000*1000/2 = 500,000; divide into 32*15625;
    unsigned short j_idx = 0, i_count = 0;
    unsigned char j_curr = -1;
    unsigned short ith_count = 0;
    int total_count = 0;



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
        if(head[0] >= head[4] && head[0] >= head[1]) {
            ith_count++;
            //ans_j.push_back(1);
            ans_j[j_curr][j_idx++] = 1;
        }

        // middle cols
        for(int j=1; j<width_1; j++) {
            if(head[j<<2] >= head[    ((j-1)<<2)] &&
               head[j<<2] >= head[    ((j+1)<<2)] &&
               head[j<<2] >= head[1 + (j<<2)]) {
                ith_count++;
                //ans_j.push_back(j+1);
                ans_j[j_curr][j_idx++] = j+1;
            }
        }

        // top right
        if(head[    ((width-1)<<2)] >= head[    ((width-2)<<2)] && head[    ((width-1)<<2)] >= head[1 + ((width-1)<<2)]) {
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
            /// Part 1 - "0,1,2".  1 being the middle row
            if(++i >= height_1) break;
            for(int j=0; j<width; j++) {
                ifile >> head[2 + (j<<2)];
            }
                // leftmost col
            if(head[1] >= head[0] &&
               head[1] >= head[2] &&
               head[1] >= head[1 + 4]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + (j<<2)] >= head[    (j<<2)] &&
                   head[1 + (j<<2)] >= head[2 + (j<<2)] &&
                   head[1 + (j<<2)] >= head[1 + ((j-1)<<2)] &&
                   head[1 + (j<<2)] >= head[1 + ((j+1)<<2)]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
                // rightmost col
            if(head[1 + (width_1<<2)] >= head[    (width_1<<2)] &&
               head[1 + (width_1<<2)] >= head[2 + (width_1<<2)] &&
               head[1 + (width_1<<2)] >= head[1 + ((width_1-1)<<2)]) {
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
            for(int j=0; j<width; j++) {
                ifile >> head[    (j<<2)];
            }
                // leftmost col
            if(head[2    ] >= head[1    ] &&
               head[2    ] >= head[  0  ] &&
               head[2    ] >= head[2 + 4]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[2 + (j<<2)] >= head[1 + (j<<2)] &&
                   head[2 + (j<<2)] >= head[    (j<<2)] &&
                   head[2 + (j<<2)] >= head[2 + ((j-1)<<2)] &&
                   head[2 + (j<<2)] >= head[2 + ((j+1)<<2)]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
                // rightmost col
            if(head[2 + (width_1<<2)] >= head[1 + (width_1<<2)] &&
               head[2 + (width_1<<2)] >= head[    (width_1<<2)] &&
               head[2 + (width_1<<2)] >= head[2 + ((width_1-1)<<2)]) {
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
            for(int j=0; j<width; j++) {
                ifile >> head[1 + (j<<2)];
            }
                // leftmost col
            if(head[0    ] >= head[2    ] &&
               head[0    ] >= head[1    ] &&
               head[0    ] >= head[    4]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
                // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[    (j<<2)] >= head[2 + (j<<2)] &&
                   head[    (j<<2)] >= head[1 + (j<<2)] &&
                   head[    (j<<2)] >= head[    ((j-1)<<2)] &&
                   head[    (j<<2)] >= head[    ((j+1)<<2)]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
                // rightmost col
            if(head[    (width_1<<2)] >= head[2 + (width_1<<2)] &&
               head[    (width_1<<2)] >= head[1 + (width_1<<2)] &&
               head[    (width_1<<2)] >= head[    ((width_1-1)<<2)]) {
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
            if(head[1    ] >= head[  0  ] &&
               head[1    ] >= head[1 + 4]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[1 + (j<<2)] >= head[    (j<<2)] &&
                   head[1 + (j<<2)] >= head[1 + ((j-1)<<2)] &&
                   head[1 + (j<<2)] >= head[1 + ((j+1)<<2)]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
            // bottom right
            if(head[1 + (width_1<<2)] >= head[    (width_1<<2)] &&
               head[1 + (width_1<<2)] >= head[1 + ((width_1-1)<<2)]) {
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
            if(head[2    ] >= head[1    ] &&
               head[2    ] >= head[2 + 4]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[2 + (j<<2)] >= head[1 + (j<<2)] &&
                   head[2 + (j<<2)] >= head[2 + ((j-1)<<2)] &&
                   head[2 + (j<<2)] >= head[2 + ((j+1)<<2)]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
            // bottom right
            if(head[2 + (width_1<<2)] >= head[1 + (width_1<<2)] &&
               head[2 + (width_1<<2)] >= head[2 + ((width_1-1)<<2)]) {
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
            if(head[  0  ] >= head[2    ] &&
               head[  0  ] >= head[    4]) {
                ith_count++;
                //ans_j.push_back(1);
                Check_J(j_idx, ans_j, j_curr);
                ans_j[j_curr][j_idx++] = 1;
            }
            // middle cols
            for(int j=1; j<width_1; j++) {
                if(head[    (j<<2)] >= head[2 + (j<<2)] &&
                   head[    (j<<2)] >= head[    ((j-1)<<2)] &&
                   head[    (j<<2)] >= head[    ((j+1)<<2)]) {
                    ith_count++;
                    //ans_j.push_back(j+1);
                    Check_J(j_idx, ans_j, j_curr);
                    ans_j[j_curr][j_idx++] = j+1;
                }
            }
            // bottom right
            if(head[    (width_1<<2)] >= head[2 + (width_1<<2)] &&
               head[    (width_1<<2)] >= head[    ((width_1-1)<<2)]) {
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
    cout << "\n**********\nANS:\n";
    cout << total_count << "\n";
    */

    delete[] head;
    for(int x=0; x<=j_curr; x++) {
        delete[] ans_j[x];
    }
}


void SingleRow(unsigned short& width) {
    int* head = new int[width];
    vector<short> ans_j;

    for(int i=0; i<width; i++) {
        ifile >> head[i];
    }
    // left
    if(head[0] >= head[1])
        ans_j.push_back(1);
    // middle
    for(int i=1; i<width-1; i++) {
        if(head[i] >= head[i-1] && head[i] >= head[i+1])
            ans_j.push_back(i+1);
    }
    // right
    if(head[width-1] >= head[width-2]) {
        ans_j.push_back(width);
    }

    ofile << ans_j.size() << endl;
    for(int i=0; i<ans_j.size(); i++) {
        cout << "1 " << ans_j[i] << "\n";
    }

    delete[] head;
}


int main(int argc, char** argv)
{
    //clock_t s = clock();
    unsigned short height, width;

    if(argc <= 1) return 0xAAAA;
    // set directory
    strcat(ifileDir, argv[1]);
    strcat(ifileDir, "/matrix.data");
    strcat(ofileDir, argv[1]);
    strcat(ofileDir, "/ERfinal.peak");

    // open file
    ifile.open(ifileDir, ios::in);
    ofile.open(ofileDir, ios::out);

    // read dimension
    ifile >> height >> width;

    if(height <= 1) {
        SingleRow(width);
    }
    else {
        BigRow_extraRow_deltaI_SepArr(height, width);
    }


    // close file
    ifile.close();
    ofile.close();

    //printf("> %ld\n", clock() - s);

    return 0;
}
