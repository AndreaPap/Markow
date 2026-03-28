#include "Markow.h"

int main()
{
    Type_LinearSystemState a;
    /*double P[ 3 ][ 4 ] = 
    { 
        { 0.3 -1.0, 0.5,       0.1,       0.0 },
        { 0.4,      0.2 - 1.0, 0.1,       0.0 },
    //  { 0.3,      0.3,       0.8 -1.0,  0.0 },
        { 1.0,      1.0,       1.0,       -1.0 }
    };*/

    double Pa = 0.3;
    double Pb = 0.5;
    double Pc = 0.2;

    double P[ 6 ][ 7 ] =
    {
        { Pa,   Pb + Pc,    0,      0,          0,      0,          - Pa },
        { 0,    0,          Pb,     Pa - Pc,    0,      0,          - Pb },
        { 0,    0,          0,      0,          Pc,     Pa - Pb,    - Pc },
        { 1,    0,          0,      1,          0,      1,          - 1  },
        { 0,    1,          1,      0,          0,      1,          - 1  },
        { 0,    1,          0,      1,          1,      0,          - 1  }
    };

    LinearSystemStateFunction_Init( &a, P, 6 );
    
    LinearSystemStateFunction_Solve( &a );

    LinearSystemOutputFunction_PrintMatrix( &a );
    LinearSystemOutputFunction_PrintConst( &a );

    LinearSystemStateFunction_DeInit( &a );


    return 0;
}

