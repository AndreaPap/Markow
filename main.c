#include "MarkowChain.h"

int main()
{
    Type_LinearSystemState a;
    double P[ 3 * 4 ] = 
    { 
         ( 254.0 / 255.0 ) -1.0, 254.0 / 255.0, 0.01814994515059191, 0.0 ,
         1 / 255.0, -1.0, 0.0, 0.0 ,
        //{ 0.0, 1 / 255.0, 0.0, 0.0  },
         1.0, 1.0, 1.0, -1.0 
    };

    double P_[ 3 * 3 ] = 
    { 
         254.0 / 255.0 , 254.0 / 255.0, 0.01814994515059191,
         1 / 255.0, 0.0, 0.0,
         0.0, 1 / 255.0, 0.0
    };


    /*double Pa = 0.3;
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
    };*/

    LinearSystemInit( &a, P, 3 );
    LinearSystemPrintMatrix( &a );

    LinearSystemSolve( &a );

    LinearSystemPrintMatrix( &a );
    LinearSystemPrintConst( &a );

    LinearSystemDeInit( &a );

    MarkowChainStateProbability( P_, 3, false );
    return 0;
}

