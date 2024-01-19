input [7:0] minuend;
input [7:0] subtrahend;
output [7:0] difference;

  wire inv_subtrahend_7;
  wire inv_subtrahend_6;
  wire inv_subtrahend_5;
  wire inv_subtrahend_4;
  wire inv_subtrahend_3;
  wire inv_subtrahend_2;
  wire inv_subtrahend_1;
  wire inv_subtrahend_0;

  wire negator_carry_0;
  wire negator_carry_1;
  wire negator_carry_2;
  wire negator_carry_3;
  wire negator_carry_4;
  wire negator_carry_5;
  wire negator_carry_6;
  wire negator_carry_7;

  wire neg_subtrahend_7;
  wire neg_subtrahend_6;
  wire neg_subtrahend_5;
  wire neg_subtrahend_4;
  wire neg_subtrahend_3;
  wire neg_subtrahend_2;
  wire neg_subtrahend_1;
  wire neg_subtrahend_0;

  wire borrow_0;
  wire borrow_1;
  wire borrow_2;
  wire borrow_3;
  wire borrow_4;
  wire borrow_5;
  wire borrow_6;
  wire borrow_7;


assign inv_subtrahend_7 = ~subtrahend[7];
assign inv_subtrahend_6 = ~subtrahend[6];
assign inv_subtrahend_5 = ~subtrahend[5];
assign inv_subtrahend_4 = ~subtrahend[4];
assign inv_subtrahend_3 = ~subtrahend[3];
assign inv_subtrahend_2 = ~subtrahend[2];
assign inv_subtrahend_1 = ~subtrahend[1];
assign inv_subtrahend_0 = ~subtrahend[0];

  assign negator_carry_0 = inv_subtrahend_0;
  assign negator_carry_1 = negator_carry_0 & inv_subtrahend_1;
  assign negator_carry_2 = negator_carry_1 & inv_subtrahend_2;
  assign negator_carry_3 = negator_carry_2 & inv_subtrahend_3;
  assign negator_carry_4 = negator_carry_3 & inv_subtrahend_4;
  assign negator_carry_5 = negator_carry_4 & inv_subtrahend_5;
  assign negator_carry_6 = negator_carry_5 & inv_subtrahend_6;
  assign negator_carry_7 = negator_carry_6 & inv_subtrahend_7;

  assign neg_subtrahend_0 = ~inv_subtrahend_0;
  assign neg_subtrahend_1 = negator_carry_0 ^ inv_subtrahend_1;
  assign neg_subtrahend_2 = negator_carry_1 ^ inv_subtrahend_2;
  assign neg_subtrahend_3 = negator_carry_2 ^ inv_subtrahend_3;
  assign neg_subtrahend_4 = negator_carry_3 ^ inv_subtrahend_4;
assign neg_subtrahend_5 = negator_carry_4 ^ inv_subtrahend_5;
assign neg_subtrahend_6 = negator_carry_5 ^ inv_subtrahend_6;
assign neg_subtrahend_7 = negator_carry_6 ^ inv_subtrahend_7;

assign borrow_0 = minuend[0] & neg_subtrahend_0;
assign borrow_1 = borrow_0 | (minuend[1] & neg_subtrahend_1);
assign borrow_2 = borrow_1 | (minuend[2] & neg_subtrahend_2);
assign borrow_3 = borrow_2 | (minuend[3] & neg_subtrahend_3);
assign borrow_4 = borrow_3 | (minuend[4] & neg_subtrahend_4);
assign borrow_5 = borrow_4 | (minuend[5] & neg_subtrahend_5);
assign borrow_6 = borrow_5 | (minuend[6] & neg_subtrahend_6);
assign borrow_7 = borrow_6 | (minuend[7] & neg_subtrahend_7);

assign difference[0] = minuend[0] ^ subtrahend[0] ^ borrow_0;
assign difference[1] = minuend[1] ^ subtrahend[1] ^ borrow_1;
assign difference[2] = minuend[2] ^ subtrahend[2] ^ borrow_2;
assign difference[3] = minuend[3] ^ subtrahend[3] ^ borrow_3;
assign difference[4] = minuend[4] ^ subtrahend[4] ^ borrow_4;
assign difference[5] = minuend[5] ^ subtrahend[5] ^ borrow_5;
assign difference[6] = minuend[6] ^ subtrahend[6] ^ borrow_6;
assign difference[7] = minuend[7] ^ subtrahend[7] ^ borrow_7;

endmodule