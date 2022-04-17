#include "stdio.h"
#include "util.hpp"
int MAX(int a,int b);
int MIN(int a,int b);
int collosion(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2){
	return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}
int MAX(int a,int b){
    return ((a>b)?a:b);
}
int MIN(int a,int b){
    return ((a<b)?a:b);
}
