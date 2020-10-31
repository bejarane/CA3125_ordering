#include <bits/stdc++.h>
using namespace std;
/**
 * Funcion para imprimir vector
 * @param data Se trata de un vector con los datos a ordenar
*/
void vPrint(vector <unsigned long int> data){
    for (unsigned int j = 0; j < data.size(); j++){
        cout << data[j] << " ";
    }
    cout << endl;
}


/**
 * Funcion para ordenamiento por bubblesort
 * @param data Se trata de un vector con los datos a ordenar
 * @return Un vector ordenado
*/

vector <unsigned long int> bubble (vector <unsigned long int> data){
    vector <unsigned long int> buffer  = data;
    int position = buffer.size()-1;
    int last = 0;
    int change;
    int count = 0;
    do{    
        change = 0;
        for (int j = 0; j < position; j++){
            if (buffer[j]>buffer[j+1]){ //intercambio
                buffer[j]^=buffer[j+1];
                buffer[j+1]^=buffer[j];
                buffer[j]^=buffer[j+1];
                change ++;
                last = j; //el ultimo cambio siempre estará ordenado
            }
            count ++;
        }
        position = last;
    }
    while(change > 0);
    return buffer;
}

/**
 * Funcion para ordenamiento por insertionsort
 * @param data Se trata de un vector con los datos a ordenar
 * @return Un vector ordenado
*/
vector <unsigned long int> insertion (vector <unsigned long int> data){
    vector<unsigned long int> buffer;
    int sizeA = data.size();
    int sizeB = 0;
    int posi;
    do{
        for (posi = 0; posi < sizeB && buffer[posi]<data[sizeB];posi++);
        vector <unsigned long int>::iterator pointer = buffer.begin() + posi; //insert requiere un iterador, probablemente es mejor
        //hacer el for de interadores y no hacer esta operación, si el comentario sigue aqui es porque no lo cambié
        buffer.insert(pointer,data[sizeB]);
        sizeB ++;
        ///cout << "bebop" << endl;
    }
    while(sizeB<sizeA);

    return buffer;
}

/**
 * Funcion para ordenamiento por quicksort
 * @param data Se trata de un vector con los datos a ordenar
 * @return Un vector ordenado
*/


vector <unsigned long int> quick (vector <unsigned long int> data, int bottom, int top){
    if ( (top-bottom) < 2){ //caso final, 1 o 0 casillas por ordenar
        if (data[top] < data[bottom]){
            data[bottom]^=data[top];
            data[top]^=data[bottom];
            data[bottom]^=data[top]; //intercambio bitwise
        }
        return data;
    }
    unsigned long int valP = data[top];
    int lower = bottom, upper = top-1;
    while(lower!=upper+1){
        if (data[lower]>valP){
            if (data[upper]< valP){
                data[lower]^=data[upper];
                data[upper]^=data[lower];
                data[lower]^=data[upper]; //intercambio bitwise
                lower ++;
                upper --;
            }else{
                upper --;
            }
        }else{
            lower ++;
        }
    }
    if (lower!=top){
        data[lower]^=data[top];
        data[top]^=data[lower];
        data[lower]^=data[top]; //intercambio bitwise para el pivote
    }
    //cout<<"A" << endl;
    data = quick (data,bottom,lower-1);
    //cout<<"B" << endl;
    data = quick (data, lower , top);

    return data;

}

vector <unsigned long int> quick (vector <unsigned long int> data){
    int top = data.size()-1;
    return quick(data, 0, top);
}

/**
 * Funcion para ordenamiento por mergesort
 * @param data Se trata de un vector con los datos a ordenar
 * @return Un vector ordenado
*/

/**
 * Funcion para ordenamiento por bubblesort
 * @param data Se trata de un vector con los datos a ordenar
 * @return Un vector ordenado
*/

vector<unsigned long int> randomGen(int b){
    vector <unsigned long int> resultado;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned long int> dist(0, 1<<31);
    while (b>0){
        resultado.push_back(dist(gen));
        b--;
    }

    /*
    srand(time(0));
    while (b>0){
        resultado.push_back(rand());
        b--;
    }*/
    return resultado;
}


/**
 * Funcion para realizar test y calcular tiempo
 * @param f Se trata de una funcion
 * @return Tiempo de desarrollo
*/
long int evaluator(vector <unsigned long int> data, int cycles,vector<unsigned long int>(*f)(vector<unsigned long int>)){
    auto start_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    vector <unsigned long int> result;

    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < cycles; i++){
        result = (*f)(data);
    }
    end_time = std::chrono::high_resolution_clock::now();

    //vPrint(result);

    return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
}


int main(){
    int a,b;

    vector <long int> times;
    const vector <string> tests = {"Bubble Sort","Insertion Sort","Quick Sort","Merge Sort","Radix Sort"};

    cin >> a >> b;

    //vector <int> test = {0,8,5,6,7,1,2,8,6,5,12,585,12,11,13,15};
    vector<unsigned long int> test = randomGen(b);

    //vPrint(test);
    vector <unsigned long int> result;

    times.push_back(evaluator(test,a,bubble));
    times.push_back(evaluator(test,a,insertion));
    times.push_back(evaluator(test,a,quick));


    cout<< "\nResultados\n";
    for (unsigned int j = 0; j < times.size();j++){
        cout << tests[j] << " --> " << times[j] << " ms total\n";
    }

    return 0;
}