/*
MACCHINA DI MEALY:

INTRODUCTION TO EMBEDDED SYSTEMS pagina 56 eq 3.1
Let x : N → Inputs and y : N → Outputs denote that input and output valuations at each
reaction. Hence, x(0) ∈ Inputs is the first input valuation and y(0) ∈ Outputs is the first
output valuation. The dynamics of the state machine are given by the following equation:
(s(n + 1), y(n)) = update(s(n), x(n)) 

le funzioni devono produrre output basandosi sullo stato attuale, segue che l'aggiornamento dello stato avviene dopo
la produzione dell'output che può avvenire tramite ritorno di valori, side effects ( tipo printf ), puntatori a buffer, ecc...
lo stato non viene ritornato ma modificato alla fine al fine di risparmiare copie e ram. Bisogna prestare attenzione 
all'aggiornamento dello stato in quanto le modifiche devono essere computate su porzioni di stato non modificate.
*/

typedef struct
{
    unsigned int Order;
    double* SystemData;        // double System[ Order ][ Order + 1 ] l'ultima colonna sono i termini noti
} Type_LinearSystemState;

void LinearSystemInit             ( Type_LinearSystemState* State, double* SystemData, unsigned int Order );
void LinearSystemDeInit           ( Type_LinearSystemState* State );
void LinearSystemScaleRow         ( Type_LinearSystemState* State, unsigned int Row, double Scale );
void LinearSystemSumRow           ( Type_LinearSystemState* State, unsigned int Row1, unsigned int Row2 );
void LinearSystemIsolateInColumn  ( Type_LinearSystemState* State, unsigned int Row, unsigned int Column );
void LinearSystemRowExchange      ( Type_LinearSystemState* State, unsigned int Row1, unsigned int Row2 );
void LinearSystemSolve            ( Type_LinearSystemState* State );

void LinearSystemPrintMatrix     ( Type_LinearSystemState* State );
void LinearSystemPrintCoeff      ( Type_LinearSystemState* State );
void LinearSystemPrintConst      ( Type_LinearSystemState* State );

void MarkowChainStateProbability ( double* TransitionProbability, unsigned int Order );

