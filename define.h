#ifndef PULSE_OXIMETER_DEFINE_H
#define PULSE_OXIMETER_DEFINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*! ------------------------------------------------------------
  
  \struct absorp
 
  \brief measures
  
  ------------------------------------------------------------*/

typedef struct{
		float acr;  /*!< AC R */
		float dcr;  /*!< DC R */
		float acir;  /*!< AC IR */
		float dcir;  /*!< DC IR */
} absorp;

/*! ------------------------------------------------------------
  
  \struct oxy
 
  \brief   
  
  ------------------------------------------------------------*/

typedef struct{
		unsigned short spo2;  /*!< SPO2 */
		unsigned short pouls;  /*!< Pouls */
} oxy;

#endif // PULSE_OXIMETER_DEFINE_H