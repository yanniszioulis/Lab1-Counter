module top #(
  parameter WIDTH = 8
)(
  // interface signals
  input  logic             clk,      // clock 
  input  logic             rst,      // reset 
  input  logic             en,       // enable
  input  logic             ld,       // load 
  input  logic [WIDTH-1:0] v,        // value to preload
  output logic [11:0]      bcd       // count output
);

  logic  [WIDTH-1:0]       count;    // interconnect wire

counter myCounter (
  .clk (clk),
  .rst (rst),
  .en (en),
  .count (count),
  .ld (ld),
  .v (v)
);

bin2bcd myDecoder (
  .x (count),
  .BCD (bcd)
);

endmodule
