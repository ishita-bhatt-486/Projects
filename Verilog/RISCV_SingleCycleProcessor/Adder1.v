`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09.01.2026 11:41:13
// Design Name: 
// Module Name: Adder1
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


module Adder1(
    input [32:0] from_PC,
    output [32:0] out_adder1
    );
    
    assign out_adder1 = 4+from_PC;
endmodule