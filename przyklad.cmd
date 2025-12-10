#define ROTATE_SPEED 3
/*
* Przykladowy zestaw polecen
*/
Begin_Parallel_Actions
    Set Podstawa 2 0 0 3 0 0 // Polozenie obiektu A
    Set Podstawa.Ramie1 1 1 5 0 0 0 // Polozenie obiektu B
End_Parallel_Actions
Begin_Parallel_Actions
    Rotate Podstawa OX ROTATE_SPEED 4
End_Parallel_Actions
Begin_Parallel_Actions Pause 1000 /* Zawieszenie na 1 sek. */ End_Parallel_Actions
Begin_Parallel_Actions
    Move Podstawa 1 1
    Rotate Podstawa.Ramie1 OZ ROTATE_SPEED 60 /* Rotate i Move wykonywane razem */
    Move Podstawa.Ramie1 1 2 /* powoduja jazde po luku */
End_Parallel_Actions