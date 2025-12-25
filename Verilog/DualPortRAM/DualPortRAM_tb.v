`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 24.12.2025 21:30:16
// Design Name: 
// Module Name: DualPortRAM_tb
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


module DualPortRAM_tb;
    reg clk;
    
    reg [7:0] input_data_a;
    reg [5:0] address_a;
    reg we_a;
    
    wire [7:0] output_data_a;
    
    reg [7:0] input_data_b;
    reg [5:0] address_b;
    reg we_b;
    
    wire [7:0] output_data_b;
    
    DualPortRAM dut1(
    
    .clk(clk),
    
    .input_data_a(input_data_a),
    .address_a(address_a),
    .we_a(we_a),
    .output_data_a(output_data_a),
    
    .input_data_b(input_data_b),
    .address_b(address_b),
    .we_b(we_b),
    .output_data_b(output_data_b)
    );
    
    always #5 clk = ~clk;
    
    initial
    begin
        input_data_a=0;
        input_data_a=0;
        address_a=0;
        address_a=0;
        we_a=0;
        we_b=0;

        clk =0;
        
        #10;
        
        $display("TEST");
                  
        $display("Write 0xAA to Address 7 at time [Time %0t]", $time);
        we_a=1;
        address_a=6'd7;
        input_data_a=8'hAA;
        
        #10;
        we_a=0;
        
        #10;
        
        $display("Read from Address 7 at time [Time %0t]", $time);
        address_b = 6'd7;
        
        #10;
        
        if (output_data_b == 8'hAA) 
            $display("Address 7 has correct data AA");
        else 
            $display("Address 7 has wrong data %h. Expected value= AA", output_data_b);
            
        #10;
        
        $display(" Write 11 to address 20 (port A) and 22 to address 30(port B)at [Time %0t]", $time);
        
        we_a = 1;
        
        address_a = 6'd20;
        input_data_a = 8'h11;
        
        we_b = 1;
        
        address_b = 6'd30;
        input_data_b = 8'h22;
        
        #10;
        
        we_a = 0;
        we_b = 0;
        
        #10;
        
        address_a = 6'd30;
        address_b = 6'd20;
        
        #10;
        
        if (output_data_a == 8'h22 && output_data_b == 8'h11)
            $display("Values are correct");
        else
            $display("Values are wrong");
            
        $stop;
    end
endmodule
