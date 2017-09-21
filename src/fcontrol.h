#ifndef FCONTROL_H
#define FCONTROL_H


/*! \mainpage fcontrol
 *
 * This project is a control library.
 * Currently two types of blocks can be used:
 * - \subpage SystemBlock "z transfer function block"
 *
 * - \subpage PIDBlock "pid controller block"
 *
 */ 

/*! \page SystemBlock z transfer function block
 *
 * z transfer function block
 *
 */

/*! \page PIDBlock pid controller block
 *
 * This page is about how program pid.
 * Following sections describe parameters:
 * - \ref P "Proportional parameter"
 * - \ref I "Integral param"
 */


#include "SystemBlock.h"
#include "FSystemBlock.h"
#include "ControllerBlock.h"
#include "TransferFunction.h"
#include "PIDBlock.h"
#include "StateVariable.h"


#endif // FCONTROL_H

