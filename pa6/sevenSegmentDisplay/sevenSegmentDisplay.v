input [3:0] numeral_bit;

output a;
output b;
output c;
output d;
output e;
output f;
output g;

wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

wire var1;
wire var2;
wire var3;
wire var4;
wire var5;

wire supervar1;
wire supervar2;
wire supervar3;
wire supervar4;
wire supervar5;
wire supervar6;
wire supervar7;

wire doublesup1;


assign not_numeral_bit_3 = ~numeral_bit[3];
assign not_numeral_bit_2 = ~numeral_bit[2];
assign not_numeral_bit_1 = ~numeral_bit[1];
assign not_numeral_bit_0 = ~numeral_bit[0];

assign var1 = not_numeral_bit_1 & not_numeral_bit_2;
assign var2 = not_numeral_bit_0 & not_numeral_bit_1;
assign var3 = not_numeral_bit_0 & not_numeral_bit_3;
assign var4 = not_numeral_bit_0 & not_numeral_bit_2;
assign var5 = not_numeral_bit_2 & not_numeral_bit_3;


assign supervar1 = var1 & not_numeral_bit_3;
assign supervar2 = var2 & var3;
assign supervar3 = var2 & not_numeral_bit_3;
assign supervar4 = var2 & not_numeral_bit_2;
assign supervar5 = var4 & not_numeral_bit_3;

assign doublesup1 = supervar2 & var4;


assign a = supervar1 & doublesup1;
assign b = supervar3 & supervar4;
assign c = supervar5 & supervar1;
assign d = supervar4 & supervar1;
assign e = supervar5 & supervar4;
assign f = supervar4 & supervar3;
assign g = var2 & var5;
