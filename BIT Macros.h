/*
 * BIT Macros.h
 *
 * Created: 2/11/2022 11:42:53 PM
 
 *   Author : Habeba Hamada
 */ 

#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

#define REGISTER_SIZE           8
#define SET_BIT(REG,BIT)      (REG|=(1<<BIT))                              //TO SET BIT
#define CLEAR_BIT(REG,BIT)    (REG&= (~(1<<BIT)))                          //TO CLEAR BIT
#define TOGGLE_BIT(REG,BIT)   (REG^=(1<<BIT))                              //TO TOGGLE BIT
#define READ_BIT(REG,BIT)     ((REG&(1<<BIT)) >>BIT)                       //TO READ A SINGLE BIT FROM A REGISTER
#define BIT_IS_SET(REG,BIT)   ((REG&(1<<BIT)) >>BIT)                       //TO DETERMINE IF THE BIT IS SET OR NOT
#define BIT_IS_CLEAR(REG,BIT) (!((REG&(1<<BIT)) >>BIT))                    //TO DETERMINE IF THE BIT IS CLEAR OR NOT
#define ROR(REG,NUM)          (REG=(REG>>NUM)|(REG<<(REGISTER_SIZE-NUM)))  //TO SHIFT REGISTER RIGHT
#define ROL(REG,NUM)          (REG=(REG<<NUM)|(REG>>(REGISTER_SIZE-NUM)))  //TO SHIFT REGISTER LEFT


#endif