/*
 * bit_operations.h
 *
 * Created: 21.11.2017 14:44:50
 *  Author: arefv
 */ 
#define set_bit(reg, bit) (reg |= (1 << bit))
#define clear_bit(reg, bit) (reg &= ~(1 << bit))
#define test_bit(reg, bit) (reg & (1 << bit))
#define loop_until_bit_is_set(reg, bit) while(!test_bit( reg, bit ))
#define loop_until_bit_is_clear(reg, bit) while(test_bit( reg, bit ))
