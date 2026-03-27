#include "Markow.h"

int main()
{
    Type_LinearSystemState a;
    double P[ 3 ][ 4 ] = 
    { 
        { 0.3 -1.0, 0.5,       0.1,       0.0 },
        { 0.4,      0.2 - 1.0, 0.1,       0.0 },
    //  { 0.3,      0.3,       0.8 -1.0,  0.0 },
        { 1.0,      1.0,       1.0,       -1.0 }
    };

    LinearSystemStateFunction_Init( &a, P, 3 );
    
    LinearSystemStateFunction_Solve( &a );

    LinearSystemOutputFunction_PrintMatrix( &a );
    LinearSystemOutputFunction_PrintConst( &a );

    LinearSystemStateFunction_DeInit( &a );


    return 0;
}

