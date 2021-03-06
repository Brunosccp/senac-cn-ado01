#include "lib.h"

void generateDat(){
    FILE *seno_file = fopen("seno.dat", "w");
    FILE *cosseno_file = fopen("cosseno.dat", "w");

    unsigned int i;
    for (i = 1; i <= 720; i++){
        double aprSen = seno(i);
        double aprCos = cosseno(i);
        double realSen = sin(i * PI / 180);
        double realCos = cos(i * PI / 180);

        double absolutError_sen = absolutError(realSen, aprSen);
        double absolutError_cos = absolutError(realCos, aprCos);

        double relativeError_sen = relativeError(absolutError_sen, realSen);
        double relativeError_cos = relativeError(absolutError_cos, realCos);
        //printf("valor de seno e cosseno de %d predicado e real: %f e %f; %f e %f\n",
        //i, aprSen, realSen, aprCos, realCos);
        //printf("erro absoluto de seno e cosseno de %d: %f e %f\n", i, relativeError_sen, relativeError_cos);

        fprintf(seno_file, "%d\t%f\t%f\t%f\n",i, aprSen, absolutError_sen, relativeError_sen);
        fprintf(cosseno_file, "%d\t%f\t%f\t%f\n",i, aprCos, absolutError_cos, relativeError_cos);
    }
    

    fclose(seno_file);
    fclose(cosseno_file);

}
void generatePlot(){
    FILE *seno_plot = popen("gnuplot -persistent", "w");
    FILE *cosseno_plot = popen("gnuplot -persistent", "w");

    //mudando output para png e nomeando arquivos
    fprintf(seno_plot, "set term png \n");
    fprintf(seno_plot, "set output \"seno.png\" \n");
    fprintf(cosseno_plot, "set term png \n");
    fprintf(cosseno_plot, "set output 'cosseno.png' \n");

    //dando titulo aos gráficos
    fprintf(seno_plot, "set title 'Function Sine' \n");
    fprintf(cosseno_plot, "set title 'Function Cosine' \n");

    //fazendo intervalo entre 0 e 720
    fprintf(seno_plot, "set xrange [0:720] \n");
    fprintf(cosseno_plot, "set xrange [0:720] \n");

    //pegando os dados do .dat e transformando em gráfico
    fprintf(seno_plot ,"plot \"seno.dat\" using 1:2 title 'Seno'\n");
    fprintf(cosseno_plot ,"plot \"cosseno.dat\" using 1:2 title 'Cosseno'\n");

    pclose(seno_plot);
    pclose(cosseno_plot);
}   
double cosseno(double x){
    unsigned int i;
    double result = 0;  

    double piRad = (x*PI) / 180;

    for (i=0; i < 25; i++){
        result += (pow(-1, i) / fat(2*i)) * pow(piRad, 2*i);
    }
    return result;
}
double seno(double x){
    unsigned int i;
    double result = 0;

    double piRad = x*PI / 180;
    for (i=0; i < 25; i++){
        result += (pow(-1, i) / fat(2*i + 1)) * pow(piRad, 2*i+1);
    }
    return result;
}
double fat(int x){
    unsigned int i;
    double result = 1;
    for(i = x; i > 0; i--){
        result *= i;
    }
    //printf("fatorial de %d: %f\n", x,result);
    return result;
}
double absolutError(double x, double y){
    double result = abs(x - y); 
    return result;
}
double relativeError(double absolutError, double x){
    double result = absolutError / x;
    return result;
}