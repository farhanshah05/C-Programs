input [3:0] numeral_bit;

output c;

wire not_num_bit_3;
wire not_num_bit_2;
wire not_num_bit_1;
wire not_num_bit_0;

wire is_1_and_0;
wire is_1_and_2;

wire not_3_and_not_0;
wire not_3_and_not_2;

wire m_Term_is_03;
wire m_Term_is_06;
wire m_Term_is_07;

wire m_Term_is_3_or_7;
wire m_Term_is_3_7_6;

wire m_Term_02;

assign not_num_bit_3 = ~ numeral_bit[3];
assign not_num_bit_2 = ~ numeral_bit[2];
assign not_num_bit_1 = ~ numeral_bit[1];
assign not_num_bit_0 = ~ numeral_bit[0];

assign is_1_and_0 = numeral_bit[1] & numeral_bit[0];
assign is_1_and_2 = numeral_bit[1] & numeral_bit[2];

assign not_3_and_not_0 = not_num_bit_3 & not_num_bit_0;
assign not_3_and_not_2 = not_num_bit_2 & not_num_bit_3;

assign m_Term_is_03 = is_1_and_0 & not_3_and_not_2;
assign m_Term_is_06 = is_1_and_2 & not_3_and_not_0;
assign m_Term_is_07 = is_1_and_0 & numeral_bit[2];

assign m_Term_is_3_or_7 = m_Term_is_03 | m_Term_is_07;
assign m_Term_is_3_7_6 = m_Term_is_3_or_7 | m_Term_is_06;

assign m_Term_02 = not_num_bit_1 | m_Term_is_3_7_6 ;
assign c = m_Term_02;
