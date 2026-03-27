typedef struct
{
    unsigned int Order;
    double* SystemData;        // double System[ Order ][ Order + 1 ] l'ultima colonna sono i termini noti
} Type_LinearSystemState;

void LinearSystemStateFunction_Init             ( Type_LinearSystemState* State, void* SystemPointer, unsigned int Order );
void LinearSystemStateFunction_DeInit           ( Type_LinearSystemState* State );
void LinearSystemStateFunction_ScaleRow         ( Type_LinearSystemState* State, unsigned int Row, double Scale );
void LinearSystemStateFunction_SumRow           ( Type_LinearSystemState* State, unsigned int Row1, unsigned int Row2 );
void LinearSystemStateFunction_IsolateInColumn  ( Type_LinearSystemState* State, unsigned int Row, unsigned int Column );
void LinearSystemStateFunction_RowExchange      ( Type_LinearSystemState* State, unsigned int Row1, unsigned int Row2 );
void LinearSystemStateFunction_Solve            ( Type_LinearSystemState* State );

void LinearSystemOutputFunction_PrintMatrix     ( Type_LinearSystemState* State );
void LinearSystemOutputFunction_PrintCoeff      ( Type_LinearSystemState* State );
void LinearSystemOutputFunction_PrintConst      ( Type_LinearSystemState* State );

