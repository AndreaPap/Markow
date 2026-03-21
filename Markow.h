typedef struct
{
    unsigned int Order;
    void* SystemPointer;        // double System[ Order ][ Order + 1 ] l'ultima colonna sono i termini noti
} LinearSystemStateType;

void LinearSystemStateFunction_Init( LinearSystemStateType* State, void* SystemPointer, unsigned int Order );
void LinearSystemStateFunction_Triangular( LinearSystemStateType* State );
void LinearSystemStateFunction_GaussStep( LinearSystemStateType* State, unsigned int Row );
void LinearSystemStateFunction_ScaleRow( LinearSystemStateType* State, unsigned int Row, double Scale );
void LinearSystemStateFunction_SumRow( LinearSystemStateType* State, unsigned int Row1, unsigned int Row2 );
void LinearSystemStateFunction_IsolateInColumn( LinearSystemStateType* State, unsigned int Row, unsigned int Column );
void LinearSystemStateFunction_RowExchange( LinearSystemStateType* State, unsigned int Row1, unsigned int Row2 );
void LinearSystemStateFunction_Solve( LinearSystemStateType* State );

void LinearSystemOutputFunction_PrintMatrix( LinearSystemStateType* State );
void LinearSystemOutputFunction_PrintCoeff( LinearSystemStateType* State );
void LinearSystemOutputFunction_PrintConst( LinearSystemStateType* State );

