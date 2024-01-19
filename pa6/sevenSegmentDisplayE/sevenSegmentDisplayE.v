input [3:0] numeral_bit;

output e;

wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

wire m_Term_00;
wire m_Term_02;
wire m_Term_06;
wire m_Term_08;

wire m_Term_00_or_m_Term_08;
wire m_Term_02_or_m_Term_06;

wire not_var1_var2;
wire not_3_and_not_2;
wire not_1_and_not_0;

assign not_numeral_bit_3 = ~numeral_bit[3];
assign not_numeral_bit_2 = ~numeral_bit[2];
assign not_numeral_bit_1 = ~numeral_bit[1];
assign not_numeral_bit_0 = ~numeral_bit[0];

assign not_3_and_not_2 = not_numeral_bit_3 & not_numeral_bit_2;
assign not_1_and_not_0 = not_numeral_bit_1 & not_numeral_bit_0;

assign not_var1_var2 = not_numeral_bit_3 & numeral_bit[1];

assign m_Term_00_or_m_Term_08 = not_numeral_bit_2 & not_1_and_not_0;
assign m_Term_02_or_m_Term_06 = not_var1_var2 & not_numeral_bit_0;

assign e = m_Term_00_or_m_Term_08 | m_Term_02_or_m_Term_06;
