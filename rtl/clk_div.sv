module clk_div (
   input clk,
   input nrst,
   output logic en
);

parameter  N = 32;
localparam W = $clog2(N);

logic[W-1:0] q;
always_ff@(posedge clk or negedge nrst)
   if(!nrst)
   begin
      q <= '0;
      en <= '0;
   end
   else
   begin
      en <= '0;
      q <= q + 'b1;
      if(q == 0)
         en <= 1'b1;
   end

endmodule
