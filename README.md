# expr_eval()
This is a function that takes a mathematical expression in string form as parameter, and returns its value by using Shunting-Yard algorithm.

Expression may contain only the following:

    Unnecessary pair of parantheses or spaces,
    '+', '-' , '*', '/', '%' operators,
    natural numbers as operands.
 
sample I/O:

    expr_eval("2 - 5") return -3
    
    expr_eval("2   *  3 - ((5))") returns 1.

    expr_eval("   ( ( 5)*3)    -  (  (7*(1)) / 1 * 2)") returns 1
    
    expr_eval(" 5 % ( ( 4) *   1 /  1 ) - ((1))") returns 0
