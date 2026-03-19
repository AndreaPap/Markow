#include "Markow.h"

int main()
{
    LinearSystemStateType a;
    double Data[ 3 ][ 4 ] = 
    { 
        { 1, 2, 3, 5 },
        { 2, 2, 5, 1 },
        { 7, 4, 3, 9 },
};
    LinearSystemStateFunction_Init( &a, Data, 3 );
    LinearSystemOutputFunction_Print( &a );
    LinearSystemStateFunction_Triangular( &a );
    LinearSystemOutputFunction_Print( &a );
    return 0;
}

