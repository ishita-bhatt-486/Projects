`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 13.01.2026 16:14:52
// Design Name: 
// Module Name: RegisterFile
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


module RegisterFile(
    input clk, reset, Reg_write,
    input [4:0] reg1, reg2, destination_reg,
    input [31:0] write_data,
    output [31:0] read_data1_output, read_data2_output
    );
    
    reg [31:0] Registers [31:0];
    
    always @(posedge reset or posedge clk)
        begin
            if(reset)
                begin
                    for (int k=0;k<32; k=k+1)
                        Registers[k]<= 32'b00;
                end
            else if(Reg_write)
                Registers[destination_reg]<=write_data;
        end
       
       assign read_data1_output= Registers[reg1];
       assign read_data2_output= Registers[reg2];
endmodule
