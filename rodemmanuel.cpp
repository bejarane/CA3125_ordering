///////// 2020. GNU GENERAL PUBLIC LICENSE /////////////////////////
//
//  Project     : Prueba de diferentes algoritmos de ordenamiento
//  File        : rodemmanuel.cpp
//  Description :
//      Archivo principal. Codigo para cada método de búsqueda y 
//              funcion de llamada inicial.
//
//  Authors     : E. Rodriguez
//
//  Git repository: https://github.com/bejarane/CA3125_sorting
////////////////////////////////////////////////////////////////////


#include <bits/stdc++.h>
using namespace std;
/**
 * Funcion para imprimir vector
 * @param data Se trata de un vector con los datos a ordenar
*/
void vPrint(vector <unsigned int> data){
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

vector <unsigned int> bubble (vector <unsigned int> data){
    vector <unsigned int> buffer  = data;
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
vector <unsigned int> insertion (vector <unsigned int> data){
    vector<unsigned int> buffer;
    int sizeA = data.size();
    int sizeB = 0;
    int posi;
    do{
        for (posi = 0; posi < sizeB && buffer[posi]<data[sizeB];posi++);
        vector <unsigned int>::iterator pointer = buffer.begin() + posi; //insert requiere un iterador, probablemente es mejor
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
vector <unsigned int> quick (vector <unsigned int> data, int bottom, int top){
    //vPrint(data);
    //cout << "ping1,"<<bottom<<" "<<top<<"\n";
    if ( (top-bottom) < 2){ //caso final, 1 o 0 casillas por ordenar
        if (data[top] < data[bottom] && top>bottom){
            data[bottom]^=data[top];
            data[top]^=data[bottom];
            data[bottom]^=data[top]; //intercambio bitwise
        }
        return data;
    }
    //cout << "ping1.5\n";
    unsigned int valP = data[top];
    //cout << "ping2\n";
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

vector <unsigned int> quick (vector <unsigned int> data){
    int top = data.size()-1;
    return quick(data, 0, top);
}

/**
 * Funcion para generar un  merge
 * @param data Se trata de un vector con los datos a ordenar
 * @return Un vector ordenado
*/
vector <unsigned int> merge (vector <unsigned int> data, int lower, int center, int upper){
    int t1 = center - lower + 1;
    int t2 = upper - center;

    vector <int> lowerV;
    lowerV.insert(lowerV.begin(),data.begin()+lower,data.begin()+center+1);

    vector <int> upperV;
    upperV.insert(upperV.begin(),data.begin()+center+1,data.begin()+upper+1);

    int i = 0, j = 0, k = lower;

    while (i < t1 && j < t2){
        if (lowerV[i]<=upperV[j]){
            data[k] = lowerV[i];
            i++;
        }else{
            data[k] = upperV[j];
            j++;
        }
        k++;
    }

    while (i<t1){
        data[k] = lowerV[i];
        i++;
        k++;
    }

    while (j<t2){
        data[k] = upperV[j];
        j++;
        k++;
    }

    return data;
}

/**
 * Funcion para ordenamiento por mergesort
 * @param data Se trata de un vector con los datos a ordenar
 * @return Un vector ordenado
*/
vector <unsigned int> mergeSort (vector <unsigned int> data, int lower, int upper){
    if (lower < upper){
        int center = lower + (upper-lower)/2; //evita el overflow en caso de que l sea muy muy grande

        data = mergeSort(data,lower,center);
        data = mergeSort(data, center+1, upper);

        data =  merge(data,lower,center,upper);
    }
    return data;
}


vector <unsigned int> mergeSort (vector <unsigned int> data){
    int upper  = data.size()-1;
    int lower = 0;
    return mergeSort(data,lower,upper);
}


vector <unsigned int> counter (vector<unsigned int> data, int total, int exp){
    vector <unsigned int> output = data;
    vector <int> counter (10,0);
    int i;
    for (i =0; i<total; i++)
        counter[(data[i]/exp)%10]++;

    for (i =1; i<10; i++)
        counter[i]+=counter[i-1];

    for (i = total-1; i>=0; i--){
        output[counter[(data[i]/exp)%10]-1]=data[i];
        counter[(data[i]/exp)%10]--;
    }

    return output;     
}


/**
 * Funcion para ordenamiento por radix sort
 * @param data Se trata de un vector con los datos a ordenar
 * @return Un vector ordenado
*/
vector <unsigned int> radix(vector <unsigned int> data){
    int total = data.size();
    unsigned int maxN = *max_element(data.begin(),data.end());

    for (int exp = 1; maxN / exp > 0; exp *=10)
       data = counter(data,total, exp);

    return data;
}

vector<unsigned int> randomGen(int b){
    vector <unsigned int> resultado;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned int> dist(0, (unsigned int)1<<31);
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
long int evaluator(vector <unsigned int> data, int cycles,vector<unsigned int>(*f)(vector<unsigned int>)){
    auto start_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    vector <unsigned int> result;

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

    //a = 1;
    //b = 2500;
    cin >> a >> b;

    //vector <unsigned int> test = {176311416, 597941521, 56451127, 716072915, 830816027};
    vector<unsigned int> test = randomGen(b);

    //vPrint(test);
    vector <unsigned int> result;

    times.push_back(evaluator(test,a,bubble));
    times.push_back(evaluator(test,a,insertion));
    times.push_back(evaluator(test,a,quick));
    times.push_back(evaluator(test,a,mergeSort));
    times.push_back(evaluator(test,a,radix));


    cout<< "\nResultados\n";
    for (unsigned int j = 0; j < times.size();j++){
        cout << tests[j] << " --> " << times[j] << " ms total\n";
    }

    return 0;
}