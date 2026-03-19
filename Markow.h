typedef struct
{
    unsigned int Order;
    void* SystemPointer;        // double System[ Order ][ Order + 1 ] l'ultima colonna sono i termini noti
} LinearSystemStateType;

void LinearSystemStateFunction_Init( LinearSystemStateType* State, void* SystemPointer, unsigned int Order );
void LinearSystemStateFunction_Triangular( LinearSystemStateType* State );
void LinearSystemStateFunction_GaussStep( LinearSystemStateType* State, unsigned int Row );

void LinearSystemOutputFunction_Print( LinearSystemStateType* State );
