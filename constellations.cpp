#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fstream>
#define CONSTEL 4
#define MAX_SNO 8
#define HOR 20
#define VER 10

using namespace std;

class posn{
    public:
        posn(){
            for(int i=0; i<CONSTEL; i++){
                for(int j=0; j<MAX_SNO; j++){
                    constel_sno[i][j] = 1;
                }
            }
        }
        
        void disp_tab(){
            for(int i=0; i<CONSTEL; i++){
                for(int j=0; j<MAX_SNO; j++){
                    cout<<constel_sno[i][j]<<"";
                }
                cout<<"||";
            }
        }
        
        void setall(int cnstl){
            for(int i=0; i<MAX_SNO; i++){
                constel_sno[cnstl][i] = 0;
            }
        }
    
        int constel_sno[CONSTEL][MAX_SNO];
        
};

int get_x(int starpos){
    int x = (starpos)%(HOR+1);
    return x;
}

int get_y(int starpos){
    int y = (starpos)/(HOR+1);
    return y;
}

class constels{
  public:
  
    constels(){
        
    }
  
    int move_next(int cur_pos, int cur_no){
        if(cur_no >= star_n){
            return -1;
        }
        int y = get_y(cur_pos);
        int x = get_x(cur_pos);
        // cout<<x<<",,"<<y<<" ";
        int next_x = x+spos[cur_no][0];
        int next_y = y+spos[cur_no][1];
        // cout<<next_x<<",,"<<next_y<<" ";
        int next_pos = next_y*21 + next_x;
        return next_pos;
    }
    
    int star_n;
    int spos[MAX_SNO][2]; // how much to move
    string name;
    char* symbol;
    
};

constels constel[CONSTEL];
int found_constel[CONSTEL] = {0};
posn s_check[HOR][VER];
int last_val;

int constel_check(fstream &f, int sno, int starpos, int constel_no = 1){
    static bool is_constel = false;
    if(starpos == -1){
        return true;
    }else if(starpos > last_val || starpos < 0){
        return false;
    }else{
        f.seekg(starpos, ios::beg);
        char cur_s = f.get();
        // cout<<cur_s<<","<<starpos<<" ";
        if(cur_s != '*'){
            return false;
        }
    }
    if(sno == 1){
        is_constel = false;
    }
    int cur_x = get_x(starpos), cur_y = get_y(starpos);
    if(s_check[cur_y][cur_x].constel_sno[constel_no][sno] == 0){
        return false;
    }else{
        int next = constel_check(f,sno+1, constel[constel_no-1].move_next(starpos, sno),constel_no);
        if (next == true){
            f.seekp(starpos);
            f.write(constel[constel_no-1].symbol,1);
            found_constel[constel_no-1] = 1;
            for(int i=0; i<CONSTEL; i++){
                if(i != constel_no-1 && is_constel != true){
                    s_check[cur_y][cur_x].setall(i);
                    is_constel = true;
                }else{
                    for(int j=0; j<MAX_SNO; j++){
                        if(j != sno-1){
                            s_check[cur_y][cur_x].constel_sno[constel_no][j] = 0;
                        }
                    }
                }
            }
            return true;
        }else{
            f.seekg(starpos);
        }
    }
    return false;
}

int constellation()
{
    constel[0].star_n = 5;
    constel[0].name = "Cassiopeia,The Queen";
    constel[0].symbol = "A";
    constel[0].spos[0][0] = 0, constel[0].spos[0][1] = 0;
    constel[0].spos[1][0] = 0, constel[0].spos[1][1] = 2;
    constel[0].spos[2][0] = 2, constel[0].spos[2][1] = 0;
    constel[0].spos[3][0] = -1, constel[0].spos[3][1] = 2;
    constel[0].spos[4][0] = 2, constel[0].spos[4][1] = 0;
    // constel[0].spos = {{0,0},{0,2},{2,0},{-1,2},{2,0}};
    
    constel[1].star_n = 5;
    constel[1].name = "Cepheus,The King";
    constel[1].symbol = "B";
    constel[1].spos[0][0] = 0, constel[1].spos[0][1] = 0;
    constel[1].spos[1][0] = -2, constel[1].spos[1][1] = -3;
    constel[1].spos[2][0] = 0, constel[1].spos[2][1] = -4;
    constel[1].spos[3][0] = 3, constel[1].spos[3][1] = 2;
    constel[1].spos[4][0] = 1, constel[1].spos[4][1] = 3;
    // constel[1].spos = {{0,0},{-2,-3},{0,-4},{3,2},{1,3}};
    
    constel[2].star_n = 7;
    constel[2].name = "Ursa Minor,The King";
    constel[2].symbol = "C";
    constel[2].spos[0][0] = 0, constel[2].spos[0][1] = 0;
    constel[2].spos[1][0] = 1, constel[2].spos[1][1] = 1;
    constel[2].spos[2][0] = 2, constel[2].spos[2][1] = 0;
    constel[2].spos[3][0] = 2, constel[2].spos[3][1] = -1;
    constel[2].spos[4][0] = 1, constel[2].spos[4][1] = 0;
    constel[2].spos[5][0] = 1, constel[2].spos[5][1] = -1;
    constel[2].spos[6][0] = -1, constel[2].spos[6][1] = -1;
    // constel[2].spos = {{0,0},{1,1},{2,0},{2,-1},{1,0},{1,-1},{-1,-1}};
    
    constel[3].star_n = 4;
    constel[3].name = "Libra";
    constel[3].symbol = "D";
    constel[3].spos[0][0] = 0, constel[3].spos[0][1] = 0;
    constel[3].spos[1][0] = 1, constel[3].spos[1][1] = 4;
    constel[3].spos[2][0] = 1, constel[3].spos[2][1] = -3;
    constel[3].spos[3][0] = -1, constel[3].spos[3][1] = -2;
    // constel[3].spos = {{0,0},{1,4},{1,-3},{-1,-2}};
    
    
    string Fname;
    cout<<"Enter the name of file containing the data: ";
    cin>>Fname;
    const char* fname = Fname.c_str();
    
    fstream ff;
    ff.open(fname, ios::in | ios::ate);
    last_val = ff.tellg();
    ff.close();
    
    fstream f1, f2;
    f1.open(fname, ios::in);
    f2.open("test2.txt", ios::out);
    string line;
    string lines = "";
    while(getline(f1,line)){
        lines = lines+line+'\n';
    }
    lines = lines.substr(0, lines.size()-1);
    f2<<lines;
    f1.close();
    f2.close();
    
    // cout<<last_val<<"|||";
    
    fstream f;
    int constel_found = 0;
    f.open(fname, ios::out | ios::in);
    f.seekg(0,ios::beg);
    string test;
	int compiler_test[2];
	int comp_n = 0;
    while(true){
        // cout<<f.tellg()<<"||";
		if(comp_n < 2){
			compiler_test[comp_n++] = f.tellg();
		}else if(comp_n == 2){
			if(compiler_test[1] != 1){
				cout<<"Compiler Error, Please try a different compiler for seekg";
				return 0;
			}
		}
        char star = f.get();
        // cout<<star<<"~";
        if(f.eof()){
            break;
        }
        if(star == '*'){
            int starpos = f.tellg()-1;
            // cout<<star<<"/"<<starpos<<"|";
            for(int constel_check_no = 1; constel_check_no <= CONSTEL; constel_check_no++){
                int res = constel_check(f, 1, starpos,constel_check_no);
                if(res == 1){
                    constel_found++;
                    break;
                }
            }
            if(constel_found == CONSTEL){
                break;
            }
            f.seekg(starpos+1,ios::beg);
        }
    }
    f.close();

    // for(int i=0; i<HOR; i++){
    //     for(int j=0; j<VER; j++){
    //         s_check[i][j].disp_tab();
    //     }
    //     cout<<endl;
    // }
    
    rename(fname,"constellation_output.txt");
    rename("test2.txt",fname);
    
    cout<<"Constellations in your input (if any) have been successfully identified!!\n";
    cout<<"SYMBOL\tCONSTELLATION\n";
    for(int i=0; i<CONSTEL; i++){
        if(found_constel[i] == 1){
            cout<<"  "<<constel[i].symbol<<"\t"<<constel[i].name<<endl;
        }
    }
    
    return 0;
}