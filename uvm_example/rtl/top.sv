module top (
   input clk,
   input nrst,
   output pwm
);

parameter  STEPS     = 256;
parameter  MAIN_DIV  = 4;
parameter  DIV_RATIO = 1;

localparam DIV_PWM = MAIN_DIV;
localparam N_PWM   = STEPS;
localparam W_PWM   = $clog2(N_PWM);

wire en_pwm;
wire [W_PWM -1:0] q_pwm;

clk_div #(.N(DIV_PWM))  clk_div_pwm  (.*,.en(en_pwm));
updown_cpt #(.W(W_PWM)) pwm_cpt_inst (.*,.en(en_pwm), .q(q_pwm));

localparam DIV_CSG = 2*256*MAIN_DIV*DIV_RATIO;
localparam N_CSG   = STEPS;
localparam W_CSG   = $clog2(N_CSG);

wire en_csg;
wire [W_CSG -1:0] q_csg;

clk_div #(.N(DIV_CSG))  clk_div_csg  (.*,.en(en_csg));
updown_cpt #(.W(W_CSG)) csg_cpt_inst (.*,.en(en_csg), .q(q_csg));

always_ff @(posedge clk)
   pwm <= q_pwm < q_csg;

endmodule
