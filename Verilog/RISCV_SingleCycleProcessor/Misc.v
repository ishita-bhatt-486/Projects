`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2026 15:23:08
// Design Name: 
// Module Name: Misc
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2026 14:57:23
// Design Name: 
// Module Name: Multiplexers
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


//Adders
module adder1(

input [31:0] pc_Adder_in,
output [31:0] pc_Adder_out
);

assign pc_Adder_out = pc_Adder_in+ 4;
endmodule

module adder2(

input [31:0] in1, in2,
output [31:0] sum_out
);

assign sum_out = in1+in2;
endmodule

//Multiplexer
module Mux1(
    input s1,
    input [31:0] A1, B1,
    output [31:0] Mux1_out
    );
    
    assign Mux1_out =(s1==1'b0)? A1:B1;
endmodule

module Mux2(
    input s2,
    input [31:0] A2, B2,
    output [31:0] Mux2_out
    );
    
    assign Mux2_out =(s2==1'b0)? A2:B2;
endmodule

module Mux3(
    input s3,
    input [31:0] A3, B3,
    output [31:0] Mux3_out
    );
    
    assign Mux3_out =(s3==1'b0)? A3:B3;
endmodule

//AND_gate
module AND_gate(
    input branch, zero,
    output and_out
);

    assign and_out = branch & zero; 
endmodule