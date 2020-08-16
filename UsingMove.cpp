#include <vector>
#include <string>
#include <utility>
#include <cstdio>


//EJEMPLO 1 --  STD::MOVE

//Muestra mensaje en la pantalla
void message(const std::string &s){
    puts(s.c_str());
    fflush(stdout);
}
//funcion para mostrar los vectores en pantalla
void disp_vector(const std::vector<std::string> &v){
    size_t size = v.size();
    printf("Tamaño del vector: %ld\n", size);
    if (size){
        for(std::string s:v){
            printf("[%s]",s.c_str());
        }
        puts("");
    }
    fflush(stdout);
}
template <typename T>
void cambio(T &a,T &b){
    message("cambiando()...");
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}

int main() {
    std::vector<std::string> v1 = {"uno","dos","tres","cuatro","cinco"};
    std::vector<std::string> v2 = {"seis","siete","ocho","nueve","diez"};
    message("Imprimiendo Vector v1: ");
    disp_vector(v1);
    message("\n");
    message("Imprimiendo Vector v2: ");
    disp_vector(v2);
    message("\n");
    message("***********************************************************");

    //Aqui aplicamos el estandar move para mover el valor derecho al v2
    //Solo funciona si el valor v1 se puede convertir en un rvalue.
    v2 = std::move(v1);
    message("Imprimiendo Vector v1: ");
    disp_vector(v1);
    message("\n");
    message("Imprimiendo Vector v2: ");
    disp_vector(v2);
    message("\n");
    message("***********************************************************");

    return 0;
}
