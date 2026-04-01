#include "Markow.h"
#include <stdlib.h>
#include <stdio.h>

// inline sostituzione diretta e static visibile solo dentro questo .c
static inline double Get( Type_LinearSystemState* State, unsigned int Row, unsigned int Column ) 
{
    return State->SystemData[ Row * ( State->Order + 1 ) + Column ];
}

static inline double Set( Type_LinearSystemState* State, unsigned int Row, unsigned int Column, double Data ) 
{
    State->SystemData[ Row * ( State->Order + 1 ) + Column ] = Data;
}

void LinearSystemInit( Type_LinearSystemState* State, void* SystemPointer, unsigned int Order )
{
    State->Order = Order;
    State->SystemData = malloc( Order * ( Order + 1 ) * sizeof( double ) );

    for( unsigned int CurRow = 0; CurRow < Order; CurRow ++ )
    {
        for( unsigned int CurCol = 0; CurCol < Order + 1; CurCol ++ )
        {
            Set( State, CurRow, CurCol,
                ( ( double ( * )[ State->Order + 1 ] )( SystemPointer ) )[ CurRow ][ CurCol ] );
        }
    }
}

void LinearSystemDeInit( Type_LinearSystemState* State )
{
    State->Order = 0;
    free( State->SystemData );
}

void LinearSystemScaleRow( Type_LinearSystemState* State, unsigned int Row, double Scale )
{
    for( unsigned int CurCol = 0; CurCol < State->Order + 1; CurCol ++ )
    {
       Set( State, Row, CurCol, Get( State, Row, CurCol ) * Scale );
    }
}

void LinearSystemSumRow( Type_LinearSystemState* State, unsigned int Row1, unsigned int Row2 )
{
    for( unsigned int Cur = 0; Cur < State->Order + 1; Cur ++ )
    {
        Set( State, Row1, Cur,
            Get( State, Row1, Cur ) + Get( State, Row2, Cur ) );
    }
}

void LinearSystemIsolateInColumn( Type_LinearSystemState* State, unsigned int Row, unsigned int Column )
{
    double Reference = Get( State, Row, Column );

    for( unsigned int Cur = 0; Cur < State->Order; Cur ++ )
    {
        double ToNull = Get( State, Cur, Column );

        if( Cur != Row && ToNull != 0.0 )
        {
            LinearSystemScaleRow( State, Cur, - Reference / ToNull );
            LinearSystemSumRow( State, Cur, Row );
        }
    }
}

void LinearSystemRowExchange( Type_LinearSystemState* State, unsigned int Row1, unsigned int Row2 )
{
    double Tmp1;
    double Tmp2;

    for( unsigned int Cur = 0; Cur < State->Order + 1; Cur ++ )
    {
        Tmp1 = Get( State, Row1, Cur );
        Tmp2 = Get( State, Row2, Cur );

        Set( State, Row1, Cur, Tmp2 );
        Set( State, Row2, Cur, Tmp1 );
    }
}

void LinearSystemSolve( Type_LinearSystemState* State )
{
    for( unsigned int Cur = 0; Cur < State->Order; Cur ++ )
    {
        if( Get( State, Cur, Cur ) == 0.0f )
        {
            for( unsigned int CurSearch = Cur + 1; CurSearch < State->Order; CurSearch ++ )
            {
                if( Get( State, CurSearch, Cur ) != 0.0f )
                {
                    LinearSystemRowExchange( State, Cur, CurSearch );
                    break;  // rompe il blocco iterativo più vicino
                }
            }
        }
        LinearSystemIsolateInColumn( State, Cur, Cur );
    }
    for( unsigned int Cur = 0; Cur < State->Order; Cur ++ )
    {
        LinearSystemScaleRow( State, Cur, 1.0 / Get( State, Cur, Cur ) );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinearSystemPrintMatrix( Type_LinearSystemState* State )
{
    for( unsigned int CurRow = 0; CurRow < State->Order; CurRow ++ )
    {
        for( unsigned int CurCol = 0; CurCol < State->Order + 1; CurCol ++ )
        {
            printf( "%+.3f\t", Get( State, CurRow, CurCol ) );
        }
    printf( "\n" );
    }
    printf( "\n" );
}

void LinearSystemPrintCoeff( Type_LinearSystemState* State )
{
    for( unsigned int CurRow = 0; CurRow < State->Order; CurRow ++ )
    {
        for( unsigned int CurCol = 0; CurCol < State->Order; CurCol ++ )
        {
            printf( "%+.3f\t", Get( State, CurRow, CurCol ) );
        }
    printf( "\n" );
    }
    printf( "\n" );
}

void LinearSystemPrintConst( Type_LinearSystemState* State )
{
    
    for( unsigned int CurRow = 0; CurRow < State->Order; CurRow ++ )
    {
        printf( "%+.3f\t", - Get( State, CurRow, State->Order ) );
        printf( "\n" );
    }
    printf( "\n" );
}
    