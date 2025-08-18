/*
 * BIT_MATH.h
 *
 *  Created on: Aug 17, 2025
 *      Author: yusuf
 */

#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define SET_BIT(reg,bitN) 		(reg |= 1 << bitN)
#define CLR_BIT(reg,bitN)		(reg &= ~(1 << bitN))
#define TOG_BIT(reg,bitN) 		(reg ^= 1 << bitN)
#define GET_BIT(reg , bitN) 	((reg >> bitN) & 1)

#endif /* LIB_BIT_MATH_H_ */
