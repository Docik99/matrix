#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class matrix_t{
    unsigned int stroki,stolbi;
    int **data;
    
    int ** Create_Matrix(int stroki,int stolbi){
        int **New_Matrix = new int *[stroki];
        for (int i=0;i<stroki;i++){
            New_Matrix[i]=new int [stolbi];
        }
        return New_Matrix;
    }
    
public:
    //constructor & destructor
    matrix_t(int in_stroki,int in_stolbi){
        stroki=in_stroki;
        stolbi=in_stolbi;
        data = Create_Matrix(stroki, stolbi);
    }
    ~matrix_t(){
        for (int i=0; i<stroki; i++){
            delete[] data[i];
        }
        delete[] data;
        cout<<"DESTRUCTOR"<<'\n';
        
    }
    //Copy constructor
   /*matrix_t(const matrix_t & object){
     stroki=object.stroki;
     stolbi=object.stolbi;
     data=Create_Matrix(stroki, stolbi);
        for ( int i = 0; i < stroki; ++i){
            for ( int j = 0; j < stolbi; ++j){
                data[i][j] = object.data[i][j];
            }
        }
    }
    */
    //methods
    ifstream & read( ifstream & stream )
    {   string size_mat;
        char symbol=',';
        getline(stream, size_mat);
        istringstream str(size_mat);
        if(str>>stroki && str>>symbol && str>>stolbi){
            data = Create_Matrix(stroki, stolbi);
            Zapolnenie_mat(stream, stroki, stolbi, data);
        }
        else{
            cout<<"An error has occured while reading input data"<<'\n';
        }
        return stream;
    }
    
    void Zapolnenie_mat(ifstream &file,int stroki_in,int stolbi_in,int **&data){
        for (int i = 0 ; i<stroki_in; i++) {
            string stroka;
            getline(file, stroka);
            istringstream str (stroka);
            for (int j = 0; j<stolbi_in; j++) {
                if (!(str>>data[i][j])) {
                    break;
                }
            }
        }
    }
    
    ostream & write(ostream & stream1) {
        ofstream file3("Result.txt");
        file3<<stroki<<","<<stolbi<<endl;
        for (int i = 0; i<stroki; i++) {
            for (int j = 0; j<stolbi; j++) {
                stream1<<data[i][j]<<" ";
                file3<<data[i][j]<<" ";
            }
            stream1<<'\n';
            file3<<'\n';
        }
        return stream1;
    }
    
    matrix_t add ( matrix_t & other)
    {
        matrix_t result(stroki,stolbi);
        for (int i = 0; i< stroki; i++) {
            for (int j = 0 ; j< stolbi; j++) {
                result.data[i][j]=data[i][j]+other.data [i][j];
            }
        }
        return result;
    }
    matrix_t sub ( matrix_t & other)
    {
        matrix_t result(stroki,stolbi);
        for (int i = 0; i< stroki; i++) {
            for (int j = 0 ; j< stolbi; j++) {
                result.data[i][j]=data[i][j]-other.data [i][j];
            }
        }
        return result;
    }
    matrix_t mul ( matrix_t & other)
    {
        matrix_t result(stroki,other.stolbi);
        for (int i = 0; i<stroki; i++) {
            for (int j = 0; j<other.stolbi; j++) {
                result.data[i][j] = 0;
                for (int h = 0; h<stolbi; h++) {
                    result.data[i][j] += data[i][h]*other.data[h][j];
                }
            }
        }
        return result;
    }
    
    matrix_t trans ()
    {
        matrix_t result(stolbi,stroki);
        for(int i = 0; i<stolbi; i++){
            for(int j = 0; j<stroki; j++){
                result.data[i][j] = data[j][i];
            }
        }
        return result;
    }
    unsigned int Get_Stroki(){
        return stroki;
    }
    unsigned int Get_Stolbi(){
        return stolbi;
    }
};
bool get_name_matr(ifstream &f1,ifstream &f2,string &name_file1,string &name_file2,char &op){
    string enter;
    getline(cin,enter);
    istringstream file(enter);
    char op2;
    while (file>>op2) {
        if(op2!='+' && op2!='-' && op2!='*' && op2!='T'){
            name_file1+=op2;
        }
        if (op2=='+' || op2=='-' || op2=='*'|| op2=='T') {
            op=op2;
            if (op2=='T') break;
            while (file>>op2) {
                if(op2!='+' && op2!='-' && op2!='*' && op2!='T'){
                    name_file2+=op2;
                }
                else return false;
            }
            break;
        }
    }
    if(name_file1!=""){
        f1.open(name_file1);
    }
    if(name_file2!=""){
       f2.open(name_file2);
    }
    if(f1.is_open()&&(op=='T'))  return true;
else if(f1.is_open()&&f2.is_open()) return true;
else return false;
}


int main() {
    matrix_t a(0,0),b(0,0);
    ifstream f1,f2;
    string name_file1="";
    string name_file2="";
    char op;
    if(!get_name_matr(f1, f2,name_file1,name_file2,op)){
        cout<<"An error has occured while reading input data"<<'\n';
        return 0;
    }
    switch (op) {
        case '+':{
            a.read(f1);
            b.read(f2);
            if (a.Get_Stolbi()==b.Get_Stolbi() && a.Get_Stroki()==b.Get_Stroki()) {
            matrix_t c=(a.add(b));
            c.write(cout);
            }
            else  cout<<"An error has occured while reading input data"<<'\n';
        }
            break;
        case '-':{
            a.read(f1);
            b.read(f2);
            if (a.Get_Stolbi()==b.Get_Stolbi() && a.Get_Stroki()==b.Get_Stroki()) {
            matrix_t c=(a.sub(b));
            c.write(cout);
            }
            else  cout<<"An error has occured while reading input data"<<'\n';
        }
            break;
        case '*':{
            a.read(f1);
            b.read(f2);
            if(a.Get_Stolbi()==b.Get_Stroki()){
            matrix_t c=(a.mul(b));
            c.write(cout);
            }
            else  cout<<"An error has occured while reading input data"<<'\n';
        }
            break;
        case 'T':{
            a.read(f1);
            matrix_t c=(a.trans());
            c.write(cout);
        }
            break;
        default:
    cout<<"An error has occured while reading input data"<<'\n';
            break;
         
    }
    return 0;
}
