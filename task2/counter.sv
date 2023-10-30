module counter #(
    parameter WIDTH = 8
)(
    // interface signals
    input   logic               clk,    // clock
    input   logic               rst,    // reset
    input   logic               en,     // counter enable
    input   logic               dir,    // direction to be set by flag
    output  logic   [WIDTH-1:0] count   // count output
);

always_ff @( posedge clk, posedge rst) 
    if (rst)    count <= {WIDTH{1'b0}};
    else    if (dir == 1)  count <= count + {{WIDTH-1{1'b0}}, en};
            else count <= count - {{WIDTH-1{1'b0}}, en};

endmodule
