#include "MarkowChain.h"

// inline sostituzione diretta e static visibile solo dentro questo .c
static inline double Get( Type_LinearSystemState* State, unsigned int Row, unsigned int Column ) 
{
    return State->SystemData[ Row * ( State->Order + 1 ) + Column ];
}

static inline double Set( Type_LinearSystemState* State, unsigned int Row, unsigned int Column, double Data ) 
{
    State->SystemData[ Row * ( State->Order + 1 ) + Column ] = Data;
}

void LinearSystemInit( Type_LinearSystemState* State, double* SystemData, unsigned int Order )
{
    State->Order = Order;
    State->SystemData = malloc( Order * ( Order + 1 ) * sizeof( double ) );

    for( unsigned int CurRow = 0; CurRow < Order; CurRow ++ )
    {
        for( unsigned int CurCol = 0; CurCol < Order + 1; CurCol ++ )
        {
            Set( State, CurRow, CurCol, SystemData[ ( CurRow * ( Order + 1 ) ) + CurCol ] );
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
            printf( PRINT_FORMAT "\t", Get( State, CurRow, CurCol ) );
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
            printf( PRINT_FORMAT "\t", Get( State, CurRow, CurCol ) );
        }
    printf( "\n" );
    }
    printf( "\n" );
}

void LinearSystemPrintConst( Type_LinearSystemState* State )
{
    
    for( unsigned int CurRow = 0; CurRow < State->Order; CurRow ++ )
    {
        printf( PRINT_FORMAT "\t", - Get( State, CurRow, State->Order ) );
        printf( "\n" );
    }
    printf( "\n" );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MarkowChainStateProbability( double* TransitionProbability, unsigned int Order, bool Verbose )
{
        double SystemData[ Order * ( Order + 1 ) ];

        for( unsigned int CurRow = 0; CurRow < Order; CurRow ++ )
        {
            for( unsigned int CurCol = 0; CurCol < Order + 1; CurCol ++ )
            {
                double Data;

                if( CurRow != Order - 1 )
                {
                    if( CurRow == CurCol ){ Data = TransitionProbability[ ( CurRow * Order ) + CurCol ] - 1.0; }
                    else if( CurCol == Order ){ Data = 0.0f; }
                    else{ Data = TransitionProbability[ ( CurRow * Order ) + CurCol ]; }
                }
                else
                {
                    Data = CurCol == Order ? - 1.0 : 1.0;
                }

                SystemData[ ( CurRow * ( Order + 1 ) ) + CurCol ] = Data; 
            }
        }

        Type_LinearSystemState System;

        LinearSystemInit( &System, SystemData, Order );
        if( Verbose ){ LinearSystemPrintMatrix( &System ); }
        LinearSystemSolve( &System );
        if( Verbose ){ LinearSystemPrintMatrix( &System ); }
        LinearSystemPrintConst( &System );
}