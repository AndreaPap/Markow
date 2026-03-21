#include "Markow.h"
#include <stdlib.h>
#include <stdio.h>

#define STATE ( ( double ( * )[ State->Order + 1 ] )( State->SystemPointer ) )

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
    double Pivot = STATE[ Row ][ Row ];
    
    for( unsigned int CurRow = Row + 1; CurRow < State->Order; CurRow ++ )
    {
        for( unsigned int CurCol = 0; CurCol < State->Order + 1; CurCol ++ ) // le colonne sono una in più dell'ordine per il termine noto
        {
            STATE[ CurRow ][ CurCol ] +=
            STATE[ Row ][ CurCol ] * ( -STATE[ CurRow ][ Row ] / Pivot );
        }
    }
}

void LinearSystemStateFunction_ScaleRow( LinearSystemStateType* State, unsigned int Row, double Scale )
{
    for( unsigned int CurCol = 0; CurCol < State->Order + 1; CurCol ++ )
    {
       STATE[ Row ][ CurCol ] *= Scale;
    }
}

void LinearSystemStateFunction_SumRow( LinearSystemStateType* State, unsigned int Row1, unsigned int Row2 )
{
    for( unsigned int Cur = 0; Cur < State->Order + 1; Cur ++ )
    {
        STATE[ Row1 ][ Cur ] += STATE[ Row2 ][ Cur ];
    }
}

void LinearSystemStateFunction_IsolateInColumn( LinearSystemStateType* State, unsigned int Row, unsigned int Column )
{
    for( unsigned int Cur = 0; Cur < State->Order; Cur ++ )
    {
        if( Cur != Row && STATE[ Cur ][ Column ] != 0.0 )
        {
            if( STATE[ Row ][ Column ] != 0.0 )
            {

            }
            LinearSystemStateFunction_ScaleRow( State, Cur, - STATE[ Row ][ Column ] / STATE[ Cur ][ Column ] );
            LinearSystemStateFunction_SumRow( State, Cur, Row );
        }
    }
}

void LinearSystemStateFunction_RowExchange( LinearSystemStateType* State, unsigned int Row1, unsigned int Row2 )
{
    double Row1Data[ State->Order + 1 ];
    double Row2Data[ State->Order + 1 ];

    for( unsigned int Cur = 0; Cur < State->Order + 1; Cur ++ )
    {
        Row1Data[ Cur ] = STATE[ Row1 ][ Cur ];
        Row2Data[ Cur ] = STATE[ Row2 ][ Cur ];
    }
    for( unsigned int Cur = 0; Cur < State->Order + 1; Cur ++ )
    {
        STATE[ Row1 ][ Cur ] = Row2Data[ Cur ];
        STATE[ Row2 ][ Cur ] = Row1Data[ Cur ];
    }
}

void LinearSystemStateFunction_Solve( LinearSystemStateType* State )
{
    for( unsigned int Cur = 0; Cur < State->Order; Cur ++ )
    {
        if( STATE[ Cur ][ Cur ] == 0.0f )
        {
            for( unsigned int CurSearch = 0; CurSearch < State->Order; CurSearch ++ )
            {
                if( STATE[ CurSearch ][ Cur ] != 0.0f )
                {
                    LinearSystemStateFunction_RowExchange( State, Cur, CurSearch );
                    break;  // rompe il blocco iterativo più vicino
                }
            }
        }
        LinearSystemStateFunction_IsolateInColumn( State, Cur, Cur );
    }
    for( unsigned int Cur = 0; Cur < State->Order; Cur ++ )
    {
        LinearSystemStateFunction_ScaleRow( State, Cur, 1.0 / STATE[ Cur ][ Cur ] );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinearSystemOutputFunction_PrintMatrix( LinearSystemStateType* State )
{
    for( unsigned int CurRow = 0; CurRow < State->Order; CurRow ++ )
    {
        for( unsigned int CurCol = 0; CurCol < State->Order + 1; CurCol ++ )
        {
            printf( "%+.3f\t",STATE[ CurRow ][ CurCol ] );
        }
    printf( "\n" );
    }
    printf( "\n" );
}

void LinearSystemOutputFunction_PrintCoeff( LinearSystemStateType* State )
{
    for( unsigned int CurRow = 0; CurRow < State->Order; CurRow ++ )
    {
        for( unsigned int CurCol = 0; CurCol < State->Order; CurCol ++ )
        {
            printf( "%+.3f\t",STATE[ CurRow ][ CurCol ] );
        }
    printf( "\n" );
    }
    printf( "\n" );
}

void LinearSystemOutputFunction_PrintConst( LinearSystemStateType* State )
{
    
    for( unsigned int CurRow = 0; CurRow < State->Order; CurRow ++ )
    {
        printf( "%+.3f\t",-STATE[ CurRow ][ State->Order ] );
        printf( "\n" );
    }
    printf( "\n" );
}