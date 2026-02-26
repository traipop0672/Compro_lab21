    #include <iostream>
    #include <cstdlib>
    using namespace std;

    int main(int argc , char *argv[]){
        double sum = 0;
        if(argc != 1){
            for( int i = 0 ; i < argc ; i++){
                sum += atoi(argv[i]);
            }
            double avg = sum/(argc-1);
            cout << "\n---------------------------------\n";
            cout << "Average of " << argc - 1 <<" numbers = " << avg ;
            cout << "\n---------------------------------";
        } else {
            cout << "Please input numbers to find average.";
        }
        return 0;


    }