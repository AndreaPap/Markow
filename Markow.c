#include "Markow.h"
#include <stdlib.h>
#include <stdio.h>

void LinearSystemStateFunction_Init( LinearSystemStateType* State, void* SystemPointer, unsigned int Order )
{
    State->Order = Order;
    State->SystemPointer = SystemPointer;
}

void LinearSystemStateFunction_Triangular( LinearSystemStateType* State )
{
    for( unsigned int Cur = 0; Cur < State->Order; Cur ++ )
    {
        LinearSystemStateFunction_GaussStep( State, Cur );
    }
}

void LinearSystemStateFunction_GaussStep( LinearSystemStateType* State, unsigned int Row )
{
    double ( *CastSystemPointer )[ State->Order + 1 ] = 
        ( double ( * )[ State->Order + 1 ] )( State->SystemPointer );

    double Pivot = CastSystemPointer[ Row ][ Row ];
    
    for( unsigned int CurRow = Row + 1; CurRow < State->Order; CurRow ++ )
    {
        for( unsigned int CurCol = 0; CurCol < State->Order + 1; CurCol ++ ) // le colonne sono una in più dell'ordine per il termine noto
        {
            CastSystemPointer[ CurRow ][ CurCol ] +=
            CastSystemPointer[ Row ][ CurCol ] * ( -CastSystemPointer[ CurRow ][ Row ] / Pivot );
        }
    }
}

void LinearSystemOutputFunction_Print( LinearSystemStateType* State )
{
    for( unsigned int CurRow = 0; CurRow < State->Order; CurRow ++ )
    {
        for( unsigned int CurCol = 0; CurCol <= State->Order; CurCol ++ )
        {
            printf( "%.1f\t",( ( double ( * )[ State->Order + 1 ] )( State->SystemPointer ) )[ CurRow ][ CurCol ] );
        }
    printf( "\n" );
    }
    printf( "\n" );
}
