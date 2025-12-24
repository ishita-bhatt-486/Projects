`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 24.12.2025 11:28:58
// Design Name: 
// Module Name: SinglePortRAM_tb
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


module SinglePortRAM_tb;
    reg [7:0] input_data;
    reg [5:0] address;
    reg we;
    reg clk;
    
    wire [7:0] output_data;
    
    SinglePortRAM_64x8 dut1(
        .input_data(input_data),
        .address(address),
        .we(we),
        .clk(clk),
        .output_data(output_data)
    );
    
    always #5 clk = ~clk;
    
    initial
        begin
            input_data=0;
            address=0;
            we=0;
            clk =0;
            
            #10
            
            $display("TEST");
                      
            $display("Write 0xAA to Address 7 at time [Time %0t]", $time);
            we=1;
            address=6'd7;
            input_data=8'hAA;
            
            #10
            
            $display("Write 0xFF to Address 10 at time [Time %0t]", $time);
            we=1;
            address=6'd10;
            input_data=8'hFF;
            
            #10
            
            $display("Read from Address 7 at time [Time %0t]", $time);
            we = 0;
            address = 6'd7;
            
            #10;
            
            if (output_data == 8'hAA) 
                $display("Address 7 has correct data AA");
            else 
                $display("Address 7 has wrong data %h. Expected value= AA", output_data);
            
            #10
            
            $display("Read from Address 10 at time [Time %0t]", $time);
            we = 0;
            address = 6'd10;
            
            #10;
                        
            if (output_data == 8'hFF) 
                $display("Address 10 has correct data FF");
            else 
                $display("Address 10 has wrong data %h. Expected value= FF", output_data);
            
            #10
           
           $stop;
        end
    
endmodule
