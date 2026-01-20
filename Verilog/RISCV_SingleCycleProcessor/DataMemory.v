`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2026 14:43:20
// Design Name: 
// Module Name: DataMemory
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


module DataMemory(

    input clk, reset, MemoryWrite, MemoryRead,
    input [31:0] read_address, Write_data,
    output [31:0] Memory_dataout 
    );
    
    reg [31:0] Data_Memory[63:0];
    integer k;
    
    always@(posedge clk or posedge reset)
    
    begin
        
        if(reset)
        begin
            for (k=0; k<64; k=k+1)
                Data_Memory[k]<= 32'b00;
        end
        
        else if(MemoryWrite)
            Data_Memory[read_address]<= Write_data;
            
    end
    
    assign Memory_dataout = (MemoryRead)? Data_Memory[read_address]: 32'b00; 
    
endmodule