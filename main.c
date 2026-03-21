#include "Markow.h"

int main()
{
    LinearSystemStateType a;
    double P[ 4 ][ 5 ] = 
    { 
        {1,3,1,-1,-1},
        {3,9,4,1,-1},
        {2,1,5,2,0},
        {0,1,-1,-1,-2}
    };

    LinearSystemStateFunction_Init( &a, P, 4 );

    LinearSystemStateFunction_RowExchange( &a, 0, 3 );

    LinearSystemStateFunction_Solve( &a );

    LinearSystemOutputFunction_PrintMatrix( &a );
    LinearSystemOutputFunction_PrintConst( &a );

    // Metti scambio righe invece di ricorsione!!

    return 0;
}

