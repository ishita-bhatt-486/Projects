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
    integer k;
    
    initial begin
    // Initialize Registers
        Registers[0]  = 0;
        Registers[1]  = 4;
        Registers[2]  = 2;
        Registers[3]  = 24;
        Registers[4]  = 4;
        Registers[5]  = 1;
        Registers[6]  = 44;
        Registers[7]  = 4;
        Registers[8]  = 2;
        Registers[9]  = 1;
        Registers[10] = 23;
        Registers[11] = 4;
        Registers[12] = 90;
        Registers[13] = 10;
        Registers[14] = 20;
        Registers[15] = 30;
        Registers[16] = 40;
        Registers[17] = 50;
        Registers[18] = 60;
        Registers[19] = 70;
        Registers[20] = 80;
        Registers[21] = 80;
        Registers[22] = 90;
        Registers[23] = 70;
        Registers[24] = 60;
        Registers[25] = 65;
        Registers[26] = 4;
        Registers[27] = 32;
        Registers[28] = 12;
        Registers[29] = 34;
        Registers[30] = 5;
        Registers[31] = 10;
    end
    
    always @(posedge reset or posedge clk)
        begin
            if(reset)
                begin
                    for (k=0;k<32; k=k+1)
                        Registers[k]<= 32'b00;
                end
            else if(Reg_write)
                Registers[destination_reg]<=write_data;
        end
       
       assign read_data1_output= Registers[reg1];
       assign read_data2_output= Registers[reg2];
endmodule
