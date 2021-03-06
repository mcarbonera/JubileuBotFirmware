#ifndef MAIN_H
#define MAIN_H

/**
 * Define se Uart0 ser? usada para debug
 * Se n?o definido, apenas bluetooth comunica.
 * */
//#define DEBUG_ACTIVE// Uart0 para debug.

/**
 * Se Definido, o motor ? ativado com uma sa?da
 * triangular:
 *
 *.\      /\      /\
 *._\____/__\____/__\__
 *.  \  /    \  /    \
 *.   \/      \/      \
 * Este modo de opera??o foi usado para obter as
 * curvas dos motores.
 */
// #define TESTE_MOTOR_X_ENCODER // Para verificar resposta do encoder

/*
 * Deve ser definido junto com TESTE_MOTOR_X_ENCODER.
 * Se definido, sa?da dos motores ser? constante.
 *
 * Usado para determinar se o c?lculo de rps est?
 * correto.
 */
// #define TESTE_MOTOR_RPS

/*
 * Utilizar filtro de m?dia m?vel para os sensores
 * para compensar quedas de tens?o.
 * Pode-se utilizar filtro RC passivo tamb?m!
 */
#define USAR_MEDIA_MOVEL_SENSORES
#define JANELA_MEDIA_MOVEL 5
#define USAR_MEDIA_MOVEL_APENAS_PARA_TRANSICAO

/*
 * Evitar todas as Comunica??es.
 * Antissocial igual o dono, bicho.
 */
//#define EVITAR_COMUNICACOES

#include "StateMachineComm.h"

#define CALCULOS_ODOMETRIA 10
#define FREQUENCIA_TIMER 10 // Hz
#define DT (1.0/FREQUENCIA_TIMER)
#define JUBILEU_R 0.034
#define JUBILEU_L 0.18

#define JUBILEU_MIN_RPM 60.0
#define JUBILEU_MAX_RPM 166.5
#define JUBILEU_MIN_VEL (JUBILEU_MIN_RPM*2.0*M_PI/60.0) // 6.2832 rad/s    ==  0.21363708953606095 m/s
#define JUBILEU_MAX_VEL (JUBILEU_MAX_RPM*2.0*M_PI/60.0) // 17.4358 rad/s   ==  0.593063493182867 m/s

#define JUBILEU_VEL (0.5f)

typedef struct JDInputOutput {
    double ObjX, ObjY;
    double CoordX, CoordY, CoordTheta;
    double v, w;
    double vel_r, vel_l;
    double motorEsquerdo, motorDireito;
    volatile double DistanciaSensor[5]; // retorno calculado (cm)
#ifdef USAR_MEDIA_MOVEL_SENSORES
    volatile double DistanciaSensorMediaMovel[5][JANELA_MEDIA_MOVEL];
    int iteracaoMediaMovel;
#ifdef USAR_MEDIA_MOVEL_APENAS_PARA_TRANSICAO
    volatile double DistanciaSensorTransicao[5];
#endif
#endif
    float sensorOffSet[2][5];
    t_sm_Comm *stateMachineComm; // para solicitar envio de dados durante execu??o de controlador (debug)
} JDInputOutput;

#endif
