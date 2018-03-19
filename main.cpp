#include <iostream>
  #include <fstream>
  #include <sstream>
  
  using namespace std;
  
  class matrix_t {
      unsigned int rows,collumns;
      int **data;
  
      int **create_matrix(int rows, int collumns){
          int **new_matrix = new int *[rows];
          for (int i = 0; i < rows; i++){
            new_matrix[i] = new int [collumns];
  
          }
      return new_matrix;
  }
  public:
  
      matrix_t(int stroki, int stolbi){
          rows = stroki;
          collumns = stolbi;
          data = create_matrix(rows,collumns);
  
      }
      ~matrix_t(){
          for (int i = 0; i < rows; i++) {
              delete[] data[i];
  
          }
          delete[] data;
      }
  
      void  zap_matr( ifstream & file, int strok,int stolb,int **&data) {
          for (int i = 0; i < strok; i++) {
              string str;
              getline(file, str);
              istringstream stream(str);
              for (int j = 0; j < strok; j++) {
                  if (!stream >> data[i][j]) {
                      break;
                  }
              }
  
          }
      }
  
      ifstream & read( ifstream & stream1){
          string matr_size;
          char symbol =',';
          getline(stream1, matr_size);
          istringstream stream(matr_size);
  
          if (stream >> rows && stream >> symbol && stream >> collumns){
              data = create_matrix(rows,collumns);
              zap_matr(stream1,rows,collumns,data);
          }
          else {
              cout << "input data error";
          }
          return stream1;
      }
  
      ostream & write( ostream & stream2) const {
          for (int i = 0; i < rows; i++) {
              for (int j = 0; j < collumns; j++) {
                  stream2 << data[i][j] << ' ';
              }
              stream2 << endl;
          }
          return stream2;
  
      }
  
      matrix_t add(matrix_t &other){
  
          matrix_t result(rows,collumns);
          for (int i = 0; i < rows; i++) {
              for (int j = 0; j < rows; j++) {
                  result.data[i][j] = data[i][j] + other.data[i][j];
              }
          }
          return result;
      }
  
      matrix_t subtr( matrix_t &other){
  
          matrix_t result(rows,collumns);
          for (int i = 0; i < rows; i++) {
              for (int j = 0; j < rows; j++) {
                  result.data[i][j] = data[i][j] - other.data[i][j];
              }
          }
          return result;
      }
  
      matrix_t mult( matrix_t &other){
          matrix_t result(rows,other.collumns);
          for (int i = 0; i < rows; i++) {
              for (int j = 0; j < other.collumns; j++) {
                 result.data[i][j] = 0;
                  for (int k = 0; k < collumns; k++){
                      result.data[i][j] += data[i][k]*other.data[k][j];
                  }
              }
          }
          return result;
  
      }
  
      matrix_t trans(){
          matrix_t result(rows,collumns);
          for (int i = 0; i < rows; i++) {
              for (int j = 0; j < rows; j++) {
                  result.data[i][j] = data[j][i];
              }
          }
          return result;
      }
      
      int get_rows(){
        return rows;
      }
      
      int get_collumns() {
        return collumns;
      }
  };
      bool matr_name( ifstream &file01, ifstream & file02, string & fname1,string & fname2, char & op){
          string vvod;
          getline(cin, vvod);
          istringstream stream(vvod);
          char opp;
  
          while (stream >> opp){
              if (opp != '+' || opp != '-' || opp != '*' || opp != 'T'){
                  fname1 += opp;
              }
              if (opp == '+' || opp == '-' || opp == '*' || opp == 'T'){
                  op = opp;
                  
                  while (stream >> opp){
                      if (opp != '+' && opp != '-' && opp != '*' && opp != 'T'){
                          fname2 += opp;
                      } 
                      else return false;
                      
                  }
                  break;
              }
          }
          if (fname1 != ""){
              file01.open(fname1);
          }
          if (fname2 != ""){
              file02.open(fname2);  
          }
           if(file01.is_open()&&file02.is_open()) return true;
           else return false;
      }
  int main(){
    matrix_t a(0,0),b(0,0);
    ifstream file01,file02;
    string f1_name;
    string f2_name;
    char op;
    
    if (!matr_name(file01,file02,f1_name,f2_name,op)) {
      cout << "error data input";
      return 0;
    }
    switch (op) {
      case '+': {
        a.read(file01);
        b.read(file02);
        if (a.get_rows() == b.get_rows() && a.get_collumns() == b.get_collumns()) {
          matrix_t c = (a.add(b));
          c.write(cout);
          
        }
        break;
      }
      case '-': {
        a.read(file01);
        b.read(file02);
        if (a.get_rows() == b.get_rows() && a.get_collumns() == b.get_collumns()) {
          matrix_t c = (a.subtr(b));
          c.write(cout);
          
        }
        break;
      }
      case '*': {
        a.read(file01);
        b.read(file02);
        if (a.get_rows() == b.get_rows() && a.get_collumns() == b.get_collumns()) {
          matrix_t c = (a.mult(b));
          c.write(cout);
          
        }
        break;
      }
      case 'T': {
        a.read(file01);
        matrix_t c = (a.trans());
        c.write(cout);
        }
        break;
      default: cout << "error data input";  
    }
    return 0;
  }
