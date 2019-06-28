module updown_cpt #(
   parameter W = 8
)
(
   input clk,
   input nrst,
   input en,
   output logic [W-1:0] q
);

always_ff@(posedge clk or negedge nrst)
begin:updown_main
logic inc;

   if(!nrst)
   begin
      q   <= '0;
      inc  = 1'b1;
   end
   else if(en)
   begin
      if(q == {W{1'b1}}) inc = '0;
      if(q == '0)        inc  = 1'b1;

      if(inc)
            q <= q + 1'b1;
      else
            q <= q - 1'b1;
   end
end

endmodule
